HOMEWORK 9: IMAGE COMPARISON HASHING


NAME:  < Dong Hu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< STACKOVERFLOW >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30 hours >




i = # of images
w = width x h = height (average size image)
s x s = seed size
r x r = typical subregion match. 
t = hash table size 
c = fraction of hash table to compare


ANALYSIS OF SIMPLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

O(i^2*(w*h)*(w*h)*(s*s)+(r-s)*(r-s))
i^2 for times of comparison, since each two need to be compared;
w*h*w*h for the outer loop to find the starter point of seed if match
s*s for the inner loop to find the seed if the whole seed match
plus (r-s)*(r-s) is the for loop to extend the board


ANALYSIS OF HASH TABLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

O(i^2*((w-s)*(h-s)+c*(s*s))
i^2 for times of comparison
(w-s)*(h-s) for the time to store the seeds in hash tables
c*(s*s) is to go through fraction of hash tables and need s*s to make sure the seed match


SUMMARY OF RESULTS: 
Test your implementation on a variety of images and command line
arguments and summarize and discuss the results (both running time and
quality of results).

The results are good and the output graph looks similar to the sample output.


EXTRA CREDIT -- MULTIPLE ROTATION AND/OR 90/180/270 ROTATION AND
HORIZONTAL/VERTICAL FLIP:
Discuss your implementation and results of testing.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!






