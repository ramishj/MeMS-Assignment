Certainly! Here's the documentation for the provided data structures:

### 1. `Sub_chain_node` Structure

The `Sub_chain_node` structure represents a node within a sub-chain, which is part of a hierarchical memory management system.

#### Structure Members:

- **`void *end_virtual_address`**: Represents the ending virtual address of the memory block associated with this node.
  
- **`void *start_virtual_address`**: Denotes the starting virtual address of the memory block represented by this node.

- **`struct Main_node *my_main_node`**: Points to the main node to which this sub-chain node belongs.

- **`struct Sub_chain_node *left`** and **`struct Sub_chain_node *right`**: Pointers to the left and right child nodes, respectively, within the hierarchical structure.

- **`int isHole`**: An indicator flag. Set to `1` if the node represents a hole (unused memory block), otherwise `0`.

#### Purpose:
 Each node represents a segment of memory and can be linked to a main node. It is used in managing memory allocation and identifying available or used memory blocks within the system.

### 2. `Main_node` Structure

The `Main_node` structure represents a primary node within a memory management system that oversees a collection of sub-chains.

#### Structure Members:

- **`int number_of_pages`**: Signifies the number of pages allocated.

- **`void *start_virtual_address`**: Indicates the starting virtual address for the memory block associated with this main node.

- **`void *start_physical_address`**: Represents the starting physical address corresponding to the memory block managed by this main node.

- **`struct Main_node *child`** and **`struct Main_node *parent`**: Pointers to the child and parent nodes, respectively.

- **`struct Sub_chain_node *sub_list`**: Points to the list of sub-chain nodes associated with this main node.


It seems like you're initializing several variables without explicit context or a specific purpose. However, I can provide a brief explanation of each variable and potential use cases within a memory management system:

### Global Variables:

1. **`struct Main_node *head = NULL;`**  
   - **Purpose:** `head refers to the starting point or the main node linked list.

2. **`struct Main_node *tail = NULL;`**  
   - **Purpose:** `tail` indicates the end or the last node in a main node linked list. 

3. **`void *curr_line_in_main_page = NULL;`**  
   - **Purpose:** `curr_line_in_main_page` could be a pointer that tracks the current line or position within a specific main memory page. This is last pointer to keep track of where to allocate the next data structure.

4. **`void *main_page = NULL;`**  
   - **Purpose:** `main_page` refers to the page where the data stuctures are being stored.

5. **`void *start_mems_virtual_address;`**  
   - **Purpose:**  indicates the starting virtual address of the allocated memory. 

6. **`void *last_next_virtual_address;`**  
   - **Purpose:** `last_next_virtual_address` represent the next address to last allocated virtual address.

   This initialization function **mems_init()** is to set up the initial state for managing memory, setting various pointers and attributes for a memory management system.


**void mems_finish_node(struct Main_node *node)**:
        This deallocates all the allocated page to main node passed then recursively calls itself on the child.

**void mems_finish()**:
        This calls the mems_finish_node on the head's child to deallocate all pages in all the main node.


**size_t size_of_sub_segment(struct Sub_chain_node *n)**:
        This calculates the size the allocated memory whose record the sub node n is recording.

**size_of_main_segment(struct Main_node *n)**:
        This calculates the size the allocated memory whose record the main node n is recording.

*size_t size_left_in_main_page()**: used to calculate the size left in main page. this will be used to allocate new data structes. i:e new nodes.

**void *mem_malloc_subchain(size_t size, struct Main_node *n)**:
        This traveses the subchain of the main node n using the traveser walker. if it find a hole node it check for suitable size and then accordingly allocates the memroy being asked and returns the vierutal address stored by the sub chain.
        if the sub node size is more than the required then it spilts the node and allcates a new sub node declaring that hole. 
        if it doesn't find any space it returns null.

**void *mem_malloc_node(size_t size, struct Main_node *n)**:
        This calls the mem_malloc_subchain on the main node n and then if it return an non-null virtual address then it returns that else it calls itself recursively on n's child. 
        if doesn't find any space it returns null

**void *mems_malloc(size_t size)**:
        This calls mems_malloc_node on head's child if it returns a non null virtual address then it returns that. 
        else it goes on the allocates new main node.
        first it decides how many page main node it requires based on the size asked.
        then it allocates new memory using mmap.
        it set its members. updates all the necessary global variables.
        it then also allocates the new sub node of the new main node decalaring it all hole . 
        Then it simply calls mem_malloc_subchain(size, child) on the newly created main. which will not fail to return a non null address as it was just created.

**void print_main_node_stats(struct Main_node *n)**:
        This prints the stats of the main node in the format required by the assignment.

**void print_sub_chain_node_stats(struct Sub_chain_node *n)**:
        This prints the stats of the sub node in the format required by the assignment.

**void print_sub_chain_length_array(struct Main_node* n)**:
        This is used to calculate the sub chain length of main node n 
        and then prints it then recursively calls it self on its child.


**void mems_print_stats()**:
        This prints the stats using the above three funcitons also at the same time calculating the number of used pages, unused memory and main node list length by iterating through the main node list


**void* mems_get(void *v_ptr)**:
        In this it iterates through the main node and check wether the virtual address falls withing the range of virtual address it holds record of. If yes then calclates it the offset adds it on the start physical addresss and then returns that. 
        Before returning it iterates through the sublist to check wether the corresponding subnode is hole or not. if it is hoel it return segmentation fault.

**void mems_free(void* v_ptr)**:
        It iterates through the main node list check which main node the virtual address falls in then declares the particular node as hole at check if it's adjacent node are hole or not, if yes it merges it by deleting the required nodes of the linked list.
        if it doesn't find the virtual address not allocated, that is that it doesn't match any then it prints :  "pointer being freed was not allocated"
