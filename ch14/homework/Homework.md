# Interlude: Memory API

## Homework (Code) 

In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use some tools to help you find the bugs you inserted. Then, you will realize how awesome these tools are and use them in the future, thus making yourself more happy and productive. The tools are the debugger (e.g., gdb) and a memory-bug detector called valgrind [SN05]. 

## Questions 

1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program? 
   
    > Segmentation fault.

2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you? 

    ```
    Starting program: /home/ubuntu/ostep/ch14/null
    
    Program received signal SIGSEGV, Segmentation fault.
    0x0000555555555161 in main () at null.c:5
    5           printf("%d\n", *p);
    ```

3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool? 

    ```
    ==26220== Memcheck, a memory error detector
    ==26220== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==26220== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==26220== Command: ./null
    ==26220==
    ==26220== Invalid read of size 4
    ==26220==    at 0x109161: main (null.c:5)
    ==26220==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ==26220==
    ==26220==
    ==26220== Process terminating with default action of signal 11 (SIGSEGV)
    ==26220==  Access not within mapped region at address 0x0
    ==26220==    at 0x109161: main (null.c:5)
    ==26220==  If you believe this happened as a result of a stack
    ==26220==  overflow in your program's main thread (unlikely but
    ==26220==  possible), you can try to increase the size of the
    ==26220==  main thread stack using the --main-stacksize= flag.
    ==26220==  The main thread stack size used in this run was 8388608.
    ==26220==
    ==26220== HEAP SUMMARY:
    ==26220==     in use at exit: 0 bytes in 0 blocks
    ==26220==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==26220==
    ==26220== All heap blocks were freed -- no leaks are possible
    ==26220==
    ==26220== For lists of detected and suppressed errors, rerun with: -s
    ==26220== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    Segmentation fault
    ```

4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)? 

   gdb 没有发现任何问题
   ```
   Starting program: /mnt/c/Code/Blizzards-Code/homework_in_books/ostep/cmake-build-debug/ch14-hw4
   [Inferior 1 (process 27289) exited normally]
   ```
   
   valgrind 检测到了堆上的内存泄露：
   
   ```
   ==27293== Memcheck, a memory error detector
   ==27293== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
   ==27293== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
   ==27293== Command: /mnt/c/Code/Blizzards-Code/homework_in_books/ostep/cmake-build-debug/ch14-hw4
   ==27293==
   ==27293==
   ==27293== HEAP SUMMARY:
   ==27293==     in use at exit: 1,048,576 bytes in 1 blocks
   ==27293==   total heap usage: 1 allocs, 0 frees, 1,048,576 bytes allocated
   ==27293==
   ==27293== 1,048,576 bytes in 1 blocks are definitely lost in loss record 1 of 1
   ==27293==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==27293==    by 0x10915E: main (hw4.c:9)
   ==27293==
   ==27293== LEAK SUMMARY:
   ==27293==    definitely lost: 1,048,576 bytes in 1 blocks
   ==27293==    indirectly lost: 0 bytes in 0 blocks
   ==27293==      possibly lost: 0 bytes in 0 blocks
   ==27293==    still reachable: 0 bytes in 0 blocks
   ==27293==         suppressed: 0 bytes in 0 blocks
   ==27293==
   ==27293== For lists of detected and suppressed errors, rerun with: -s
   ==27293== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
   ```

5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct? 

   运行的时候看起来一切正常。但是 valgrind 报告了详细的错误信息：
   
   ```
   ==28245== Memcheck, a memory error detector
   ==28245== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
   ==28245== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
   ==28245== Command: /mnt/c/Code/Blizzards-Code/homework_in_books/ostep/cmake-build-debug/ch14-hw5
   ==28245==
   ==28245== Invalid write of size 4
   ==28245==    at 0x10916D: main (hw5.c:9)
   ==28245==  Address 0x4a481d0 is 0 bytes after a block of size 400 alloc'd
   ==28245==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==28245==    by 0x10915E: main (hw5.c:8)
   ==28245==
   ==28245==
   ==28245== HEAP SUMMARY:
   ==28245==     in use at exit: 400 bytes in 1 blocks
   ==28245==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
   ==28245==
   ==28245== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
   ==28245==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==28245==    by 0x10915E: main (hw5.c:8)
   ==28245==
   ==28245== LEAK SUMMARY:
   ==28245==    definitely lost: 400 bytes in 1 blocks
   ==28245==    indirectly lost: 0 bytes in 0 blocks
   ==28245==      possibly lost: 0 bytes in 0 blocks
   ==28245==    still reachable: 0 bytes in 0 blocks
   ==28245==         suppressed: 0 bytes in 0 blocks
   ==28245==
   ==28245== For lists of detected and suppressed errors, rerun with: -s
   ==28245== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
   ```

6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it? 

   运行看起来一切正常。但是 valgrind 捕获到了错误：
   
   ```
   ==31290== Memcheck, a memory error detector
   ==31290== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
   ==31290== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
   ==31290== Command: /mnt/c/Code/Blizzards-Code/homework_in_books/ostep/cmake-build-debug/ch14-hw6
   ==31290==
   before free, element at index 99: 99
   ==31290== Invalid read of size 4
   ==31290==    at 0x109204: main (hw6.c:15)
   ==31290==  Address 0x4a481cc is 396 bytes inside a block of size 400 free'd
   ==31290==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==31290==    by 0x1091F9: main (hw6.c:14)
   ==31290==  Block was alloc'd at
   ==31290==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
   ==31290==    by 0x10919E: main (hw6.c:9)
   ==31290==
   after free, element at index 99: 99
   ==31290==
   ==31290== HEAP SUMMARY:
   ==31290==     in use at exit: 0 bytes in 0 blocks
   ==31290==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
   ==31290==
   ==31290== All heap blocks were freed -- no leaks are possible
   ==31290==
   ==31290== For lists of detected and suppressed errors, rerun with: -s
   ==31290== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
   ```

7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

   不需要工具即可发现错误：
   ```
   free(): invalid pointer
   ```

8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs. 

9. Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.
