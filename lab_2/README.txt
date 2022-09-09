This file should contain:

  - your name: Jason Jin
  - your UNI: hj2602
  - lab assignment number: 2
  - description for each part: 
                              Part 1) Working (no extra functionalities
                              added, used selection sort
                              instead of qsort. 
                              Part 2) Working (no extra functionalities
                              added).


Valgrind message attached (Part 1):

==8076== Memcheck, a memory error detector
==8076== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8076== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==8076== Command: ./isort
==8076== 
original: 83 86 77 15 93 35 86 92 49 
ascending: 15 35 49 77 83 86 86 92 93 
descending: 93 92 86 86 83 77 49 35 15 
==8076== 
==8076== HEAP SUMMARY:
==8076==     in use at exit: 0 bytes in 0 blocks
==8076==   total heap usage: 5 allocs, 5 frees, 2,668 bytes allocated
==8076== 
==8076== All heap blocks were freed -- no leaks are possible
==8076== 
==8076== For counts of detected and suppressed errors, rerun with: -v
==8076== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Valgrind message attached (Part 2):

==15953== Memcheck, a memory error detector
==15953== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==15953== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==15953== Command: ./twecho this is my lab number two
==15953== 
this THIS
is IS
my MY
lab LAB
number NUMBER
two TWO
==15953== 
==15953== HEAP SUMMARY:
==15953==     in use at exit: 0 bytes in 0 blocks
==15953==   total heap usage: 9 allocs, 9 frees, 2,147 bytes allocated
==15953== 
==15953== All heap blocks were freed -- no leaks are possible
==15953== 
==15953== For counts of detected and suppressed errors, rerun with: -v
==15953== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
