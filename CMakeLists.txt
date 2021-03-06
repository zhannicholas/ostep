cmake_minimum_required(VERSION 3.16)
project(ostep C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -pthread)

find_package(Threads REQUIRED)

add_executable(p1 ch05/examples/p1.c)
add_executable(p2 ch05/examples/p2.c)
add_executable(p3 ch05/examples/p3.c)
add_executable(hw1 ch05/homework/hw1.c)
add_executable(hw2 ch05/homework/hw2.c)
add_executable(hw3 ch05/homework/hw3.c)
add_executable(hw4 ch05/homework/hw4.c)
add_executable(hw5 ch05/homework/hw5.c)
add_executable(hw6 ch05/homework/hw6.c)
add_executable(hw7 ch05/homework/hw7.c)
add_executable(hw8 ch05/homework/hw8.c)

add_executable(va ch13/examples/va.c)
add_executable(memory_user ch13/homework/memory_user.c)

add_executable(ch14-hw1 ch14/homework/hw1.c)
add_executable(ch14-hw4 ch14/homework/hw4.c)
add_executable(ch14-hw5 ch14/homework/hw5.c)
add_executable(ch14-hw6 ch14/homework/hw6.c)
add_executable(ch14-hw7 ch14/homework/hw7.c)
add_executable(ch14-hw8 ch14/homework/hw8.c)

add_executable(ch21-mem ch21/homework/mem.c)

include_directories(include/)
add_executable(ch26-t0 ch26/examples/t0.c)
add_executable(ch26-t1 ch26/examples/t1.c)

add_executable(thread_create ch27/examples/thread_create.c)
add_executable(thread_create_with_return_args ch27/examples/thread_create_with_return_args.c)
add_executable(thread_create_simple_args ch27/examples/thread_create_simple_args.c)
add_executable(thread_create_with_return_args_return_pointer ch27/examples/thread_create_with_return_args_return_pointer.c)

add_executable(main-deadlock ch27/homework/main-deadlock.c)
add_executable(main-deadlock-global ch27/homework/main-deadlock-global.c)
add_executable(main-race ch27/homework/main-race.c)
add_executable(main-signal ch27/homework/main-signal.c)
add_executable(main-signal-cv ch27/homework/main-signal-cv.c)