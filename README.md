# MeMS-Assignment

<h1><br>MeMS - Memory Management System</br></h1>
<h3>MeMS (Memory Management System) is a custom memory management system implemented in C. </h3>
<h3>It provides functions for allocating, freeing, and managing memory flexibly and efficiently.</h3>
<h2>Features</h2>
<li>Dynamic memory allocation: MeMS allows users to allocate memory of any size by reusing segments from the free list or by using the mmap system call to allocate more memory on the heap.</li>
<li>Efficient memory management: MeMS optimizes memory usage by reusing unused space from mapping and by merging adjacent free segments.</li>
<li>Virtual and physical address mapping: MeMS provides functions to map virtual addresses to physical addresses and vice versa.</li>
<li>Statistics tracking: MeMS keeps track of memory usage statistics, including the number of used pages, unused memory, and the length of the main and sub-chain.</li>

<h2>Usage<h2>
<h3>To use MeMS in your C program, follow these steps:</h3>
<li>Include the mems.h header file in your source code.</li>
<li>Initialize the MeMS system by calling the mems_init() function.</li>
<li>Allocate memory using the mems_malloc() function.</li>
<li>Free memory using the mems_free() function.</li>
<li>Print memory usage statistics using the mems_print_stats() function.</li>
<li>Clean up the MeMS system by calling the mems_finish() function.</li>
