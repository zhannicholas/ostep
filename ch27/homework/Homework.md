# Interlude: Thread API

## Homework (Code) 

In this section, we’ll write some simple multi-threaded programs and use a specific tool, called helgrind, to find problems in these programs. Read the README in the homework download for details on how to build the programs and run helgrind. 

## Questions 

1. First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you? 

    `helgrind` 指了竞争出现的代码行，并且告知我们读写操作有存在竞争。
    ```
    ==1368== ---Thread-Announcement------------------------------------------
    ==1368==
    ==1368== Thread #1 is the program's root thread
    ==1368==
    ==1368== ---Thread-Announcement------------------------------------------
    ==1368==
    ==1368== Thread #2 was created
    ==1368==    at 0x499E282: clone (clone.S:71)
    ==1368==    by 0x48612EB: create_thread (createthread.c:101)
    ==1368==    by 0x4862E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
    ==1368==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==1368==    by 0x109209: main (main-race.c:14)
    ==1368==
    ==1368== ----------------------------------------------------------------
    ==1368==
    ==1368== Possible data race during read of size 4 at 0x10C014 by thread #1
    ==1368== Locks held: none
    ==1368==    at 0x10922D: main (main-race.c:15)
    ==1368==
    ==1368== This conflicts with a previous write of size 4 by thread #2
    ==1368== Locks held: none
    ==1368==    at 0x1091BE: worker (main-race.c:8)
    ==1368==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==1368==    by 0x4862608: start_thread (pthread_create.c:477)
    ==1368==    by 0x499E292: clone (clone.S:95)
    ==1368==  Address 0x10c014 is 0 bytes inside data symbol "balance"
    ==1368==
    ==1368== ----------------------------------------------------------------
    ==1368==
    ==1368== Possible data race during write of size 4 at 0x10C014 by thread #1
    ==1368== Locks held: none
    ==1368==    at 0x109236: main (main-race.c:15)
    ==1368==
    ==1368== This conflicts with a previous write of size 4 by thread #2
    ==1368== Locks held: none
    ==1368==    at 0x1091BE: worker (main-race.c:8)
    ==1368==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
    ==1368==    by 0x4862608: start_thread (pthread_create.c:477)
    ==1368==    by 0x499E292: clone (clone.S:95)
    ==1368==  Address 0x10c014 is 0 bytes inside data symbol "balance"
    ```

2. What happens when you remove one of the offending lines of code? Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases? 

* `helgrind` 没有报告任何错误
* `helgrind` 告诉我们可能存在竞争
* `helgrind` 没有报告任何错误

3. Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have? 

    会发生死锁。

4. Now run helgrind on this code. What does helgrind report? 

   ```
   ==3703== ---Thread-Announcement------------------------------------------
   ==3703==
   ==3703== Thread #3 was created
   ==3703==    at 0x499E282: clone (clone.S:71)
   ==3703==    by 0x48612EB: create_thread (createthread.c:101)
   ==3703==    by 0x4862E0F: pthread_create@@GLIBC_2.2.5 (pthread_create.c:817)
   ==3703==    by 0x4842917: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x10939F: main (main-deadlock.c:24)
   ==3703==
   ==3703== ----------------------------------------------------------------
   ==3703==
   ==3703== Thread #3: lock order "0x10C040 before 0x10C080" violated
   ==3703==
   ==3703== Observed (incorrect) order is: acquisition of lock at 0x10C080
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x109269: worker (main-deadlock.c:13)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==
   ==3703==  followed by a later acquisition of lock at 0x10C040
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x109298: worker (main-deadlock.c:14)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==
   ==3703== Required order was established by acquisition of lock at 0x10C040
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x10920B: worker (main-deadlock.c:10)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==
   ==3703==  followed by a later acquisition of lock at 0x10C080
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x10923A: worker (main-deadlock.c:11)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==
   ==3703==  Lock at 0x10C040 was first observed
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x10920B: worker (main-deadlock.c:10)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==  Address 0x10c040 is 0 bytes inside data symbol "m1"
   ==3703==
   ==3703==  Lock at 0x10C080 was first observed
   ==3703==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x10923A: worker (main-deadlock.c:11)
   ==3703==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
   ==3703==    by 0x4862608: start_thread (pthread_create.c:477)
   ==3703==    by 0x499E292: clone (clone.S:95)
   ==3703==  Address 0x10c080 is 0 bytes inside data symbol "m2"
   ==3703==
   ```

5. Now run helgrind on main-deadlock-global.c. Examine the code; does it have the same problem that main-deadlock.c has? Should helgrind be reporting the same error? What does this tell you about tools like helgrind? 

* `main-deadlock-global.c` 使用了粒度较大的锁 `g`，解决了前面的问题
* `helgrind` 仍然报告了死锁的问题，但实际上该程序内不存在死锁
* `helgrind` 之类的工具的报告结果并不完全正确，仅供参考

6. Let’s next look at main-signal.c. This code uses a variable (done) to signal that the child is done and that the parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?) 

   主线程一直在自旋等待，会消耗 CPU 资源。

7. Now run helgrind on this program. What does it report? Is the code correct? 

   `helgrind` 告诉我们可能存在竞争。但实际上，代码中不存在竞争。

8. Now look at a slightly modified version of the code, which is found in main-signal-cv.c. This version uses a condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version? Is it correctness, or performance, or both? 

   Both.

9. Once again run helgrind on main-signal-cv. Does it report any errors?

   No.