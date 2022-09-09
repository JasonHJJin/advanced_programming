This file should contain:

  - your name: Jason Jin
  - your UNI: hj2602
  - lab assignment number: 3
  - description for each part

The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.

Part1) Working!

Valgrind Error:
==31794== Memcheck, a memory error detector
==31794== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31794== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31794== Command: ./mylist-test
==31794== 
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==31794== 
==31794== HEAP SUMMARY:
==31794==     in use at exit: 0 bytes in 0 blocks
==31794==   total heap usage: 19 allocs, 19 frees, 1,312 bytes allocated
==31794== 
==31794== All heap blocks were freed -- no leaks are possible
==31794== 
==31794== For counts of detected and suppressed errors, rerun with: -v
==31794== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)  





Part2) Working!

Valgrind Error:
==30841== Memcheck, a memory error detector
==30841== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==30841== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==30841== Command: ./revecho this is homework part number two dude
==30841== 
dude
two
number
part
homework
is
this

dude found
==30841== 
==30841== HEAP SUMMARY:
==30841==     in use at exit: 0 bytes in 0 blocks
==30841==   total heap usage: 8 allocs, 8 frees, 2,672 bytes allocated
==30841== 
==30841== All heap blocks were freed -- no leaks are possible
==30841== 
==30841== For counts of detected and suppressed errors, rerun with: -v
==30841== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
