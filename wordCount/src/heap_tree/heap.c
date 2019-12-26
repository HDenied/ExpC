#include<utils.h>
#include<heap.h>


struct HEAP_level_s
{
    uint start_idx;
    uint free_index;
    uint level_num;
    DATA *block;
    struct HEAP_level_s *n_blk;
    struct HEAP_level_s *p_blk;
};

typedef struct HEAP_level_s HEAP_LVL;

struct HEAP_tree_s
{
    uint num_words;
    HEAP_LVL *root;
    HEAP_LVL *end_level;
};

typedef struct HEAP_tree_s HEAP_TREE;

uint HEAP_get_num_w(HEAP_TREE *tree)
{
    if(tree)
        return tree->num_words;

    log_err("tree not initialized");
    assert(false);
}

uint HEAP_get_num_lvl(HEAP_TREE *tree)
{
    if(tree)
        return tree->end_level->level_num;
        
    log_err("tree not initialized");
    assert(false);

}

void HEAP_print_tree(HEAP_TREE *tree, uint num_elements)
{
    if(tree)
    {
        uint idx=0;
        uint inner_idx=0;
        uint max_lvl_words=1;
        uint max_words=tree->num_words;
        HEAP_LVL *curr_lvl=tree->root;

        while(idx<max_words)
        {
            for(inner_idx=0; inner_idx<max_lvl_words; inner_idx++)
            {   
                if(idx<num_elements && UTILS_is_valid(&curr_lvl->block[inner_idx]))
                {
                    printf("%+10u %s\n",  curr_lvl->block[inner_idx].n_occ, curr_lvl->block[inner_idx].word);
                    idx++;
                }
                else
                    return; 
            }

            curr_lvl=curr_lvl->n_blk;
            max_lvl_words=1<<curr_lvl->level_num;
        }

    }
    else
    {
        log_err("Tree not initialized");
        assert(false);
    }
    
}


void _HEAP_create_next_lvl(HEAP_TREE **tree)
{
    DATA *lvl_blk = NULL;
    HEAP_LVL *lvl = NULL;
    uint num_el = 0;
    uint lvl_num = 0;

    if(*tree)
    {
        lvl_num = (*tree)->end_level->level_num + 1;
    }
    else
    {
        *tree=calloc(1,sizeof(HEAP_TREE));
        if(!(*tree))
        {
            log_err("Not enough memory to create a tree");
            assert(false);
        }
        lvl_num=0;
    }

    num_el=1<<lvl_num;
    lvl_blk = calloc(num_el, sizeof(DATA));

    if(!lvl_blk)
    {
        log_err("Not enough memory to hold data for level %u", lvl_num);
        assert(false);
    }

    lvl = calloc(1,sizeof(HEAP_LVL));

    if(!lvl)
    {
        log_err("Not enough memory to create a level");
        assert(false);
    }
    
    // Init level
    lvl->block=lvl_blk;
    lvl->level_num=lvl_num;
    lvl->start_idx= (1<<lvl_num)-1;
    
    
    // Update tree
    if((*tree)->root!=NULL)
    {
        (*tree)->end_level->n_blk=lvl;
        lvl->p_blk=(*tree)->end_level;
    }
    else
    {
        (*tree)->root=lvl;
        lvl->p_blk=NULL;
    }

    (*tree)->end_level=lvl;

}

DATA* _HEAP_get_free_slot(HEAP_TREE **tree, HEAP_LVL **lvl)
{
    HEAP_LVL *actual_lvl=NULL;
    if(!(*tree))
    {
        _HEAP_create_next_lvl(tree);
       
    }

    actual_lvl=(*tree)->end_level;

    while(true)
    {

        if(actual_lvl->free_index < (1<<actual_lvl->level_num))
        {
            *lvl=actual_lvl;
            return &(actual_lvl->block[actual_lvl->free_index]);
        }
        
        _HEAP_create_next_lvl(tree);
        actual_lvl=(*tree)->end_level;

    }


}

void _HEAP_erase_lvl(HEAP_LVL **lvl, HEAP_LVL **p_lvl)
{
    *p_lvl = NULL;

    if(*lvl)
    {
        uint idx=0, end=0;
        end=(*lvl)->free_index;
        (*p_lvl) = (*lvl)->p_blk;

        while(idx<end)
        {
            UTILS_deallocate_w(&((*lvl)->block[idx]));
            idx++;
        }

        free((*lvl)->block);
        free(*lvl);
        *lvl=NULL;
    }
   
}

void HEAP_insert_w(HEAP_TREE **tree, DATA *data)
{
    HEAP_LVL *heap_lvl=NULL;
    DATA *slot=_HEAP_get_free_slot(tree,&heap_lvl);

    UTILS_move_w(data,slot);
    heap_lvl->free_index++;
    (*tree)->num_words++;
}

bool HEAP_get_w_pos(HEAP_TREE **tree, uint idx_tree, HEAP_LVL **heap_lvl, uint *idx_lvl)
{
    if(*tree)
    {
        uint lvl_num = 0;
        uint max_elements_lvl=0;
        HEAP_LVL *lvl=(*tree)->root;
        *heap_lvl = NULL;
        *idx_lvl=EMPTY_NODE;


        while(true)
        {   
            max_elements_lvl+=1<<lvl_num;
            if (idx_tree>=lvl->start_idx && idx_tree<max_elements_lvl)
                break;

            lvl= lvl->n_blk;
            if (!lvl)
                return false;
            lvl_num++;
        }

        if (lvl->block[idx_tree-lvl->start_idx].word == NULL)
            return false;

        *heap_lvl=lvl;
        *idx_lvl=idx_tree-lvl->start_idx;
        return true;
        
    }

    return false;
}

bool HEAP_get_node(HEAP_LVL *heap_lvl, uint idx, DATA **data)
{
    *data=NULL;

    if (heap_lvl)
    {
        uint end = 1<<(heap_lvl->level_num);
        if (idx>=0 && idx<end)
        {
            *data=&(heap_lvl->block[idx]);
            return true;
        }


    }

    return false;
}

bool HEAP_get_parent_pos(HEAP_LVL *child_lvl, uint lvl_child_idx, HEAP_LVL **parent_lvl, uint *lvl_parent_idx)
{
    *lvl_parent_idx=EMPTY_NODE;
    if (child_lvl)
    {
        if (lvl_child_idx>=0 && (1<<(child_lvl->level_num)))
        {
            *parent_lvl=child_lvl->p_blk;
            if(*parent_lvl)
            {
                *lvl_parent_idx= lvl_child_idx>>1;
                return true;
            }

        }
    }
    return false;
}

bool HEAP_get_child_pos(HEAP_LVL *parent_lvl, uint lvl_parent_idx, HEAP_LVL **child_lvl, uint *lvl_l_idx, uint *lvl_r_idx)
{
    *lvl_l_idx=EMPTY_NODE;
    *lvl_r_idx=EMPTY_NODE;

    if(parent_lvl && 
       lvl_parent_idx!=EMPTY_NODE)
    {
        *child_lvl=parent_lvl->n_blk;
        if(*child_lvl)
        {
            *lvl_l_idx=lvl_parent_idx<<1;
            *lvl_r_idx=(lvl_parent_idx<<1)+1;
            return true;
        }

    }
    return false;
}

void HEAP_erase(HEAP_TREE **tree)
{
    HEAP_LVL *curr_lvl=NULL, *p_level=NULL;

    if(*tree)
    {
        curr_lvl=(*tree)->end_level;
        while(true)
        {
           _HEAP_erase_lvl(&curr_lvl, &p_level); 
           if(p_level)
           {
                curr_lvl=p_level;
                p_level=NULL;
           }
           else
                break;
        }

    }

    free(*tree);
}

int HEAP_occ_is_grater(DATA *d1, DATA *d2)
{
    if( d1 && d2)
    {
        if(d1->n_occ > d2->n_occ)
        {
            return 1;
        }
        else if (d1->n_occ < d2->n_occ)
        {
            return 0;
        }
        else
        {
            log_err("Element can't be equal");
            assert(false);
        }
        
    }
    else
    {
        log_err("Data missing");
        assert(false);
    }
    
}

uint _HEAP_from_rel_to_abs_idx(uint lvl, uint rel_idx)
{
    return (1<<lvl) + rel_idx - 1;
}

void _HEAP_sift(HEAP_TREE *tree, uint p_abs_idx, int (*cmp)(DATA *d1, DATA *d2))
{
    uint p_rel_idx=0, l_rel_idx=0, r_rel_idx=0;
    uint next_abs_idx=0;
    HEAP_LVL *p_lvl=NULL, *c_lvl=NULL;
    DATA *p_data=NULL, *l_data=NULL, *r_data=NULL;
    DATA *tmp_data = NULL;
    uint tmp_lvl=0;
    uint tmp_idx=0;   

    //Get parent relative idx and level
    if(!HEAP_get_w_pos(&tree, p_abs_idx, &p_lvl, &p_rel_idx))
    {
        log_err("Parent node not existent");
        assert(false);
    }
    else if(!HEAP_get_node(p_lvl, p_rel_idx, &p_data))
    {
        log_err("Parent node out of bound");
        assert(false);
    }

    tmp_lvl= p_lvl->level_num;
    tmp_idx= p_rel_idx;
    tmp_data = p_data;
    next_abs_idx=p_abs_idx;


    //Get children relative indexes and levels
    if(HEAP_get_child_pos(p_lvl, p_rel_idx, &c_lvl, &l_rel_idx, &r_rel_idx))
    {
        
        if(!HEAP_get_node(c_lvl, l_rel_idx, &l_data))
        {
            log_err("Left child node out of bound");
            assert(false);
        }
        else if(!HEAP_get_node(c_lvl, r_rel_idx, &r_data))
        {
            log_err("Right child node out of bound");
            assert(false);
        }
        else
        {
            
            if(UTILS_is_valid(l_data) && cmp(l_data, tmp_data))
            {
               tmp_data=l_data;
               tmp_lvl=c_lvl->level_num;
               tmp_idx=l_rel_idx;
            }

            if(UTILS_is_valid(r_data) && cmp(r_data, tmp_data))
            {
               tmp_data=r_data;
               tmp_lvl=c_lvl->level_num;
               tmp_idx=r_rel_idx;
            }

            next_abs_idx = _HEAP_from_rel_to_abs_idx(tmp_lvl, tmp_idx);
            
        }

        if (next_abs_idx != p_abs_idx)
        {
            UTILS_swap_w(p_data,tmp_data);
            _HEAP_sift(tree, next_abs_idx, cmp);

        }

    }


}

void HEAP_build(HEAP_TREE *tree, int (*cmp)(DATA *d1, DATA *d2))
{
    uint total_elements=0;

    if (tree)
    {
        total_elements = tree->num_words;
        if(total_elements>1)
        {
            uint start_idx = (total_elements>>1)-1;
            int idx = start_idx;

            while(idx>=0)
            {
                _HEAP_sift(tree, idx, cmp);
                idx--;
            }

        }
    }
    else
    {
        log_err("Tree not existent");
        assert(false);
    }
    

}

void HEAP_sort(HEAP_TREE *tree, uint num_elements)
{}