#include "../headers/minishell.h"

void    add_files_tonode(t_files *fil)
{
    t_var *var = get_struc_var(NULL);
    // printf("\nfilename=%s|typeRedir=%c|addressNodefile=%p|addressWholeCmd=%p\n", fil->file_name, fil->type ,fil, var->prsTail);
    t_files *curr;
    
    curr = var->prsTail->file_head;
    if (!curr)
        var->prsTail->file_head = fil;
    else
    {
        while (curr->next)
            curr = curr->next;
        curr->next = fil;
    }  
}

void add_prs_tonode(t_parser *node){
     t_var *var = get_struc_var(NULL);

     if (!var->prs){
        var->prs = node;
        var->prsTail = node; 
     }  
    else {
         var->prsTail->next_prs = node;
         var->prsTail =  node;
    }
}