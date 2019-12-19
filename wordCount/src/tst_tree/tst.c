#include<tst.h>
#include<utils.h>

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
    struct TST_node_s * p;  // Previous node
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

bool is_root(const TST_TREE *tree, TST_NODE *node)
{
    if(!tree)
        return false;
    return tree->root == node;
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

TST_NODE *get_root(TST_TREE *tree)
{
    return tree->root;
}

/******************************OLD_FUN*****************************************************************/
void _rm_link_parent(TST_NODE *node)
{
    TST_NODE *parent= node->p; 

    assert(node);

    if(parent)
    {
        if(parent->c == node)
           parent->c=NULL;
        else if(parent->l == node)
           parent->l=NULL;
        else if(parent->r == node)
           parent->r=NULL;

        node->p=NULL;
    }

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
        tree->root->p=NULL;
        last_node = tree->root;
        last_node->val=*word;
        tree->alloc_n++;
        attached_nodes++;
        word++;
    }
    else if (!last_node)
    {
        log_err("A node to attach the branch must be provided");
        assert(false);
    }

    while(*word)
    {
        switch (branch)
        {
            case C_BRANCH:
            {

                last_node->c = calloc(1,sizeof(TST_NODE));
                last_node->c->val=*word;
                last_node->c->p = last_node;
                last_node=last_node->c;
                tree->alloc_n++;
                word++;
                break;
            }
            case R_BRANCH:
            {
                last_node->r = calloc(1,sizeof(TST_NODE));
                last_node->r->val=*word;
                last_node->r->p = last_node;
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
                last_node->l->p = last_node;
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

bool TST_path_add(TST_TREE **tree_ptr, TST_NODE **last_matching, const char *word)
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
/****************************************************************************************************/

TST_NODE* _rm_lk_parent(TST_NODE *node)
{
    TST_NODE *parent= node->p; 

    assert(node);

    if(parent)
    {
        if(parent->c == node)
           parent->c=NULL;
        else if(parent->l == node)
           parent->l=NULL;
        else if(parent->r == node)
           parent->r=NULL;

        node->p=NULL;
        return parent;
    }

    return NULL;

}

void _prune(TST_TREE **tree, TST_NODE *node)
{
    TST_NODE *p_node=NULL;
    while(node && node->n_occ==0)
    {
        if(is_end_word(node))
        {
            break;
        }
        
        if(is_leaf(node))
        {
            p_node = _rm_lk_parent(node);
            free(node);
            (*tree)->alloc_n--;
        }
         /* root rotation as the central word has been removed */
        else if (is_root(*tree,node) &&
                 node->c==NULL)
        {
            if(node->l)
            {
                TST_NODE *l_root=node->l;
                TST_NODE *r_node=node->r;
                log_err("Node on the left side of the root should have been already pruned");
                assert(false);
                l_root->r=r_node;
                l_root->p=NULL;
                free((*tree)->root);
                (*tree)->root=l_root;
                (*tree)->alloc_n--;
            }
            else
            {
                TST_NODE *r_root=node->r;
                r_root->p=NULL;
                free((*tree)->root);
                (*tree)->root=r_root;
                (*tree)->alloc_n--;
            }
            break;
            
        }
        else
        {
            p_node=node->p;
        }
        
        node=p_node;

    }

    (*tree)->total_diff_words--;

    if((*tree)->total_diff_words==0 && (*tree)->alloc_n==0)
    {
        free(*tree);
        *tree=NULL;
    }
    else if((*tree)->total_diff_words==0 && (*tree)->alloc_n!=0)
    {
        log_err("Removing a non empty tree");
        assert(false);
    }
    

}

TST_NODE *_TST_gen_branch(TST_TREE *tree, char *word)
{
    TST_NODE *branch=NULL;
    TST_NODE *head_node=NULL;

    while(*word)
    {
        if(branch)
        {
            branch->c=calloc(1,sizeof(TST_NODE));
            branch->c->val=*word;
            branch->c->p=branch;
            branch=branch->c;
        }
        else
        {
            branch=calloc(1,sizeof(TST_NODE));
            branch->val=*word;
            branch->p=NULL;
            head_node=branch;
        }

        word++;
        tree->alloc_n++;
        
    }

    return head_node;
}

void TST_insert_w(TST_TREE **tree_ptr, char *word)
{
    uint num_match_ch = 0;
    TST_NODE *node = NULL;
    TST_NODE *p_node = NULL;
    char num_matching_ch= 0;
    uint w_len = UTILS_get_word_len(word);

    if(*tree_ptr==NULL)
    {
        *tree_ptr=calloc(1,sizeof(TST_TREE));
        memset(*tree_ptr,0,sizeof(TST_TREE));
    }

    /*Word actually exists*/
    if(w_len)
    {
        while(node)
        {
            p_node=node;
            if (node->val == *(word+num_match_ch))
            {
                node = node->c;
                num_match_ch++;
            }
            else if(node->val > *(word+num_match_ch))
                node= node->l;
            else if (node->val < *(word+num_match_ch))
                node=node->r;
        }

        /*word exists and it is contained in the dictionary already*/
        if(w_len==num_match_ch)
            node->n_occ++;
        /*Word is new than it needs to be added*/
        else if(p_node && node==NULL)
        {
            /*Full word in the tree is a prefix of actual word */
            if(is_leaf(p_node))
            {
                node =_TST_gen_branch(*tree_ptr, word+num_match_ch);
                p_node->c=node;
                node->p=p_node;
            }
            /*Partial word in the tree is a prefix of actual word */
            else
            {
                if(p_node->val > *(word+num_match_ch))
                {
                    node =_TST_gen_branch(*tree_ptr, word+num_match_ch);
                    p_node->l=node;

                }
                else if(p_node->val < *(word+num_match_ch))
                {
                    node =_TST_gen_branch(*tree_ptr, word+num_match_ch);
                    p_node->r=node;

                }
                else if(p_node->val == *(word+num_match_ch))
                {
                    log_err("Trying to overwrite the tree dictionary with word %s",word);
                    assert(false);
                }

                node->p=p_node;
            }
        }
        /* First word in the tree */
        else if(p_node==NULL && node==NULL)
        {
            node =_TST_gen_branch(*tree_ptr, word);
            (*tree_ptr)->root=node;
            (*tree_ptr)->total_diff_words++;

        }
        else
        {
            log_err("Unexpected path.");
            assert(false);
        }
    }
}

void TST_path_rm(TST_TREE **tree_ptr, TST_NODE *node, WORD_S *word, uint pos)
{
    if (node)
    {
        if(!word->is_finished)
        {
            //Condition necessary to terminate recursion
            TST_path_rm(tree_ptr, node->l, word, pos);
        }

        if(!word->is_finished)
        {
            if(pos>=W_LEN)
            {
                log_err("Word size grater than the maximul allowed (%d chars)", W_LEN);
                assert(false);
            }

            word->word[pos]= node->val;

            if(is_end_word(node) && is_leaf(node))
            {
                word->number=node->n_occ;
                word->word[pos+1] = '\0'; 
                word->is_finished=true;
                node->n_occ=0;
                (*tree_ptr)->total_diff_words--;
            }

        }

        if(!word->is_finished)
        {
            TST_path_rm(tree_ptr, node->c, word, pos+1);
        }

        if(!word->is_finished)
        {
            TST_path_rm(tree_ptr, node->r, word, pos);
        }

        
        if(is_leaf(node) && !is_end_word(node))
        {
            _rm_link_parent(node);
            free(node);
            (*tree_ptr)->alloc_n--;

            if ((*tree_ptr)->alloc_n==0)
            {
                free(*tree_ptr);
                *tree_ptr=NULL;
            }

        }

        //Because the left msot and central nodes are the ones pruned
        //when we are level 0 and they are all pruned a rotation at root level must be performed
        if(word->is_finished &&
           is_root(*tree_ptr,node) &&
           !is_end_word(node) &&
           node->r &&
           node->c==NULL &&
           node->l==NULL)
        {
            TST_NODE *new_root=node->r;
            new_root->p=NULL;
            (*tree_ptr)->root=new_root;
            free(node);
            (*tree_ptr)->alloc_n--;
        }

    } 

}

void TST_path_rmv(TST_TREE **tree_ptr, WORD_S *word_s)
{
    TST_NODE *node = (*tree_ptr)->root;
    uint num_w=0;
    while(true)
    {
        if(!is_leaf(node))
        {
            if (node->l)
                node=node->l;
            else if (node->c)            
            {
                word_s->word[num_w]=node->val; 
                node=node->c;
                num_w++;
            }
            else if (node->r)
                node=node->r;
            
        }
        else
        {
            word_s->word[num_w]=node->val; 
            num_w++;
            word_s->word[num_w]='\0';
            word_s->number = node->n_occ;
            node->n_occ=0;
            _prune(tree_ptr, node);
            break;
        }


    }
}


