/*
All the main functions with respect to the MeMS are inplemented here
read the function discription for more details

NOTE: DO NOT CHANGE THE NAME OR SIGNATURE OF FUNCTIONS ALREADY PROVIDED
you are only allowed to implement the functions 
you can also make additional helper functions a you wish

REFER DOCUMENTATION FOR MORE DETAILS ON FUNSTIONS AND THEIR FUNCTIONALITY
*/
// add other headers as required
#include<stdio.h>
#include<stdlib.h>


/*
Use this macro where ever you need PAGE_SIZE.
As PAGESIZE can differ system to system we should have flexibility to modify this 
macro to make the output of all system same and conduct a fair evaluation. 
*/
#define PAGE_SIZE 4096


/*
Initializes all the required parameters for the MeMS system. The main parameters to be initialized are:
1. the head of the free list i.e. the pointer that points to the head of the free list
2. the starting MeMS virtual address from which the heap in our MeMS virtual address space will start.
3. any other global variable that you want for the MeMS implementation can be initialized here.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_init(){

}


/*
This function will be called at the end of the MeMS system and its main job is to unmap the 
allocated memory using the munmap system call.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_finish(){
    
}


/*
Allocates memory of the specified size by reusing a segment from the free list if 
a sufficiently large segment is available. 

Else, uses the mmap system call to allocate more memory on the heap and updates 
the free list accordingly.

Note that while mapping using mmap do not forget to reuse the unused space from mapping
by adding it to the free list.
Parameter: The size of the memory the user program wants
Returns: MeMS Virtual address (that is created by MeMS)
*/ 
void* mems_malloc(size_t size){

}



/*
this function print the stats of the MeMS system like
1. How many pages are utilised by using the mems_malloc
2. how much memory is unused i.e. the memory that is in freelist and is not used.
3. It also prints details about each node in the main chain and each segment (PROCESS or HOLE) in the sub-chain.
Parameter: Nothing
Returns: Nothing but should print the necessary information on STDOUT
*/
void print_main_node_stats(struct Main_node *n)
{
    void *endv = (void *)((char *)n->start_virtual_address + n->number_of_pages * PAGE_SIZE - 1);
    printf("Main[%lu:%lu]->", (unsigned long)n->start_virtual_address, (unsigned long)endv);

}
void print_sub_chain_node_stats(struct Sub_chain_node *n)
{
    if (n->isHole)
    {
        printf("H[%lu:%lu]<->", (unsigned long)n->start_virtual_adrress, (unsigned long)n->end_virtual_address);
    }
    else
    {
        printf("P[%lu:%lu]<->", (unsigned long)n->start_virtual_adrress, (unsigned long)n->end_virtual_address);
    }

}
void print_sub_chain_length_array(struct Main_node* n){
    if(n==NULL){
        return;
    }
    else{
        int cnt = 0;
        struct Sub_chain_node* walker = n->sub_list;
        while(walker!=NULL){
            cnt++;
            walker = walker->right;
        }
        printf("%d, ", cnt);
        print_sub_chain_length_array(n->child);
    }
}
void mems_print_stats()
{
    printf("----------------MeMS SYSTEM STATS------------------------\n");
    int usedPages = 0;
    size_t unusedMemory = 0;
    int cnt_mainnode = 1;
    if (head == NULL)
    {
        printf("no memory allocated at all\n");
        return;
    }
    struct Main_node *currentMain = head->child;
    while (currentMain != NULL)
    {
        print_main_node_stats(currentMain);
        usedPages+=currentMain->number_of_pages;
        struct Sub_chain_node* currentSub = currentMain->sub_list;
        int cnt_sub_node = 1;
        while(currentSub!=NULL){
            if(currentSub->isHole){
                unusedMemory+=size_of_sub_segment(currentSub);
            }
            print_sub_chain_node_stats(currentSub);
            cnt_sub_node++;
            currentSub = currentSub->right;
            
        }
        printf("NULL\n");
        cnt_mainnode++;
        currentMain = currentMain->child;
    }
    printf("Pages used: %d\n", usedPages);
    printf("Space unused %zu\n", unusedMemory);
    printf("Main chain length: %d\n", cnt_mainnode-1);
    printf("Sub-chain length array: ");
    printf("[");
    print_sub_chain_length_array(head->child);
    printf("]\n");
    printf("----------------------------------\n");
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/
void* mems_get(void *v_ptr)
{
    struct Main_node* walker = head->child;
    while(walker!=NULL){
        void* endv = (void*)((char*)walker->start_virtual_address + walker->number_of_pages*PAGE_SIZE);
        struct Sub_chain_node *subWalker= walker->sub_list;
        if(v_ptr<endv){
            while(subWalker!=NULL){
                if(v_ptr>=subWalker->start_virtual_adrress && v_ptr<=subWalker->end_virtual_address && subWalker->isHole==0){
                    size_t offset =(size_t)((char*)v_ptr - (char*)walker->start_virtual_address);
                    void* pa = (void*)(walker->start_physical_address + offset);
                    return pa;
                }
                else if (v_ptr>=subWalker->start_virtual_adrress && v_ptr<=subWalker->end_virtual_address && subWalker->isHole==1)
                {
                    printf("Segmentation Fault\n");
                    exit(1);
                }
                else{
                    subWalker=subWalker->right;
                }
           }    
            
        }
        else{
            walker = walker->child;
        }
    }
    printf("pa not found");
    return NULL;
}

/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: nothing
*/
void mems_free(void* v_ptr) {
    struct Main_node* next = head->child;
    while (next != NULL) {
        struct Sub_chain_node* current = next->sub_list;
        while (current != NULL) {
            if (v_ptr == current->start_virtual_adrress) {
                
                current->isHole = 1;

             
                if (current->left != NULL && current->left->isHole == 1) {
                  
                    current->left->end_virtual_address = current->end_virtual_address;

                   
                    current->left->right = current->right;

                    if (current->right != NULL) {
                        current->right->left = current->left;
                    }

                  
                    // munmap(current, sizeof(struct Sub_chain_node));

                    current = current->left; 
                }

                
                if (current->right != NULL && current->right->isHole == 1) {
                    // printf("woriking\n");
                    current->end_virtual_address = current->right->end_virtual_address;
                    // printf("worirrrrking\n");
                    
                    current->right = current->right->right;

                    
                    if (current->right != NULL) {
                        // printf("woooooooooooooooooriking\n");
                        current->right->left = current;
                        
                    }

                   
                    // munmap(current->right, sizeof(struct Sub_chain_node));
                }

                return; 
            } else {
                current = current->right;
            }
        }
        next = next->child;
    }
    printf("pointer being freed was not allocated");
    exit(0);
}
