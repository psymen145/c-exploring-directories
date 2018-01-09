## assignment

Searching in the file heirarchy

The intent of this assignment is to write a code that will search for a file whose name the user is not sure about. The code will use the functions that we have discussed to search in a directory.

The utility will be called "aka" and the user will supply a partial filename to search for. aka will return a possible match to that filename or print an error message if no match was found: 

websol01$ aka /uses1/whtilock/srcv/aks.c 
/users1/whitlock/src/aka.c

As shown above, the program aka.c will try to correct, in each part of the filename, mismatches in which:

a single letter has been dropped or added
the wrong letter is present
a pair of letters has been exchanged
All the above errors occurred in the sample command above.
If the user has too many errors in a partial filename, aka will print an error message: 

websol01$ aka /use/whit/src/???.c 
No match found
