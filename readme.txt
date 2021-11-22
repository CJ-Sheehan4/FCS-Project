CJ Sheehan

SIDE NOTES

Task #23:
I'm sorry for not including my new NFA.h and NFA.cpp files 
with the commit for task 23. I got too used to only adding main.cpp,
along with the DFA files before a commit that I forgot to add the NFA files. 

Task #29:
I decided to change the definition of my TT object. It was getting difficult to code with long lines of code. 
I also created one addition NFA called N13. I got to my N5 NFA when creating the tree and realised it was infinite. 
I also wrote another NFA called N14. 

Task #30:
definition starts at line 3598, includes a helper function named treeLoop which is at line 3621

This is not an ideal implementation but It works. I made some changes in the tree again as well. 
The functions takes the NFA and creates the root with the state and string. 
Then It creates the first list of children for the root. From there it calls a recursive function
that loops through the lists of trees, creating more lists of trees for the given nodes. 
If you look at line 2993 in main.cpp, there are examples of trees that will print and they should match
up to trees I did by hand that I have also included in this commit. 

Task #31:
starts at line 2971 - 3150
by uncommenting a line you will see a tree that will resemble the ones I wrote by hand that I have included
in the previous commit. 

Task #32:
I created a seperate file for the Config class opposed to having it defined at the top of main. I felt it was
approriate to utilize this class to write the (Backtracking) algorithm/function. 