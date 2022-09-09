This file should contain:

  - your name: Jason Jin
  - your UNI: hj2602
  - lab assignment number: 4
  - description for each part
  
The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.

Part 1 (a): Working

lookup: 
 168: {jason} said {hello}
 174: {jason} said {this is my part1(a)}


Part 1 (b): Working but valgrind output line number starts first

Valgrind Output:

==21502== Memcheck, a memory error detector
==21502== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==21502== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==21502== Command: ./mdb-lookup /home/jae/cs3157-pub/bin/mdb-cs3157
==21502== 
lookup:  168: {jason} said {hello}
 174: {jason} said {this is my part1(a)}

lookup: ==21502== 
==21502== HEAP SUMMARY:
==21502==     in use at exit: 0 bytes in 0 blocks
==21502==   total heap usage: 1,184 allocs, 1,184 frees, 39,736 bytes allocated
==21502== 
==21502== All heap blocks were freed -- no leaks are possible
==21502== 
==21502== For counts of detected and suppressed errors, rerun with: -v
==21502== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
