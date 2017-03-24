HOMEWORK 8: BIDIRECTIONAL MAPS


NAME:  < Dong Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 623/ stack overflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 35 hours >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer (please be concise!)  You may assume that the tree is
reasonably well balanced for all operations.  (You do not need to
implement re-balancing.)

n = the number of elements

k = maximum number of links stored in a single node 
    (for extra credit non one-to-one associations)


size: O(1)

insert: O(log n)

erase: O(log n)

find: O(log n)

operator[]: O(log n)

key_begin: O(log n)

key_end: O(1)

value_begin: O(log n)

value_end: O(1)

key iterator++/--: O(log n)

value iterator++/--: O(log n)

follow_link: O(1)

default constructor: O(1)

copy constructor: O(n)

destructor:O(n)

assignment operator:O(n)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


