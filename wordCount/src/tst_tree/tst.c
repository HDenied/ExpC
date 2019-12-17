#include<stdio.h>
#include<tst.h>
#include<assert.h>

enum _BRANCH_E{
    C_BRANCH=0,
    R_BRANCH,
    L_BRANCH
};

typedef enum _BRANCH_E BRANCH_E;

struct TST_tree{

    TST_NODE *root;
    uint total_diff_words;    
    uint alloc_n;


};

struct TST_node_s{
    char val;
    struct TST_node_s * l;
    struct TST_node_s * c;
    struct TST_node_s * r;
    uint n_occ;

};

uint get_total_words(const TST_TREE*tree)
{
    return tree->total_diff_words;
}

uint get_alloc_num(const TST_TREE*tree)
{
    return tree->alloc_n;
}


bool is_leaf(const TST_NODE* node)
{
    if( node->c == NULL &&
        node->r == NULL &&
        node->l == NULL 
        )
        return true;

    return false;
}

bool is_end_word(const TST_NODE* node)
{
    if(node->n_occ)
        return true;
    else false;
}

uint get_num_occ(const TST_NODE* node)
{
    return node->n_occ;
}

uint _attach_branch(TST_TREE **tree_ptr, TST_NODE **last_matching, const char *word, BRANCH_E branch)
{
    TST_TREE *tree= *tree_ptr;
    TST_NODE *last_node = *last_matching;
    uint attached_nodes=0;

    if(!tree)
    {
        tree = calloc(1,sizeof(TST_TREE));
        *tree_ptr = tree;
        tree->root = calloc(1,sizeof(TST_NODE));
        last_node = tree->root;
        last_node->val=*word;
        tree->alloc_n++;
        attached_nodes++;
        word++;
    }
    else if (!last_node)
    {
        log_err("A node to attach the branch must be provided");
        assert(0);
    }

    while(*word)
    {
        switch (branch)
        {
            case C_BRANCH:
            {

                last_node->c = calloc(1,sizeof(TST_NODE));
                last_node->c->val=*word;
                last_node=last_node->c;
                tree->alloc_n++;
                word++;
                break;
            }
            case R_BRANCH:
            {
                last_node->r = calloc(1,sizeof(TST_NODE));
                last_node->r->val=*word;
                last_node=last_node->r;
                (*tree_ptr)->alloc_n++;
                word++;
                branch = C_BRANCH;
                break;
            }
            case L_BRANCH:
            {
                last_node->l = calloc(1,sizeof(TST_NODE));
                last_node->l->val=*word;
                last_node=last_node->l;
                (*tree_ptr)->alloc_n++;
                word++;
                branch = C_BRANCH;
                break;
            }
            default:
            {
                log_err("Unexpected path");
                assert(0);
            }
        }
        attached_nodes++;
       
    }
    *last_matching = last_node;
    return attached_nodes;
}

uint _TST_path_finder(TST_TREE **tree_ptr, TST_NODE **last_matching, const char *word)
{
    uint num_match_ch = 0;
    TST_TREE *tree= *tree_ptr;
    TST_NODE *last_node = tree->root;
    TST_NODE *prev_node = NULL;

    while(*word)
    {
        prev_node = last_node;
        if (last_node->val == *word)
            last_node = last_node->c;
        else if(last_node->val > *word)
            last_node= last_node->l;
        else if (last_node->val < *word)
            last_node=last_node->r;

        // Truncation occurs here because the function will return
        // the last matching word if the already existent word is shorter
        if(!last_node && prev_node->n_occ>0)
        {
            if (prev_node->val == *word)
                num_match_ch++;

            word++;
            break;
        }
        // There is a match in the word keep going
        else if(last_node)
        {
            
            if (prev_node->val == *word)
            {
                word++;
                num_match_ch++;
            }
        }
        // There is no match at all in the word
        else
        {
            break;
        }
        
    }

    *last_matching = prev_node;
    return num_match_ch;

}

bool TST_path_builder(TST_TREE **tree_ptr, TST_NODE **last_matching, const char *word)
{
    uint num_match_ch = 0;
    TST_TREE *tree= *tree_ptr;
    TST_NODE *last_node = NULL;
    char last_matching_ch= *word;

    if(*word == '\0')
        return num_match_ch;

    else if (!tree)
    {
        num_match_ch += _attach_branch(tree_ptr, last_matching, word, C_BRANCH);
        word+=num_match_ch;

    }
    else
    {
        num_match_ch +=_TST_path_finder(&tree, last_matching, word);
        word+=num_match_ch;
        last_node = *last_matching;

    }

    // Attach remaining part to the tree
    if (*word)
    {
        last_matching_ch = (num_match_ch>0)? *(word-1): *word;
        num_match_ch=0;

        if (is_leaf(last_node) && last_node->val==last_matching_ch)
            num_match_ch+=_attach_branch(tree_ptr, &last_node, word, C_BRANCH);
        else
        {
            if (last_node->val>*word)
                num_match_ch+=_attach_branch(tree_ptr, &last_node, word, L_BRANCH);
            else
                num_match_ch+=_attach_branch(tree_ptr, &last_node, word, R_BRANCH);
            
        }
        word+=num_match_ch;
        *last_matching=last_node;
        
    }
    
    // Update the stats
    if(!(*word))
    {
        if ((*last_matching)->n_occ == 0) 
            (*tree_ptr)->total_diff_words++;

        (*last_matching)->n_occ++;
        return true;
    }
    else
    {
        return false;
    }

}

void TST_pop_word(TST_TREE **tree_ptr, TST_NODE *node, WORD_S *word, uint pos)
{
    if (node)
    {

        TST_pop_word(tree_ptr, node->l, word, pos);

        word->word[pos]= node->val;

        if(is_end_word(node))
        {
            word->number=node->n_occ;
            word->word[pos+1] = '\0'; 
            node->n_occ=0;
        }

        if(is_leaf(node))
            free(node);


        TST_pop_word(tree_ptr, node->c, word, pos+1);

        TST_pop_word(tree_ptr, node->r, word, pos);

    } 

}


TST_NODE * get_root(TST_TREE *tree)
{
    return tree->root;
}
