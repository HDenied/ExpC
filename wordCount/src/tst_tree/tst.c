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
    uint longest_word;
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

uint get_size_longest_word(const TST_TREE*tree)
{
    return tree->longest_word;
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

    branch->n_occ++;
    tree->total_diff_words++;
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

    node = (*tree_ptr)->root;

    if ((*tree_ptr)->longest_word < w_len)
        (*tree_ptr)->longest_word=w_len;

    

    /*Word actually exists*/
    if(w_len)
    {
        while(node && *(word+num_match_ch))
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
        {
            /* Test if the word is new */
            if(p_node->n_occ==0)
                (*tree_ptr)->total_diff_words++;

            p_node->n_occ++;
        }
        /*Word is new than it needs to be added*/
        else if(p_node && node==NULL)
        {
            /*Full word in the tree is a prefix of actual word */
            if(p_node->c==NULL && 
               p_node->val == *(word+num_match_ch-1))
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

                node->p=p_node;
            }
        }
        /* First word in the tree */
        else if(p_node==NULL && node==NULL)
        {
            node =_TST_gen_branch(*tree_ptr, word);
            (*tree_ptr)->root=node;
        }
        else
        {
            log_err("Unexpected path.");
            assert(false);
        }
    }
}

void TST_pick_w(TST_TREE **tree_ptr, WORD_S *word_s)
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


