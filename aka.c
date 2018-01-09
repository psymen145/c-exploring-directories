/* how_good():  tries to decide the closeness of two strings */
/*
 *  return values
 *  0   the two strings are identical
 *  1   two characters are transposed: "char" and "cahr"
 *  2   one character is wrong:  "char" "cher"
 *  3   one character is added:  "chaar" "char"
 *  4   one character is deleted: "chr" "char"
 *  -1  no match found
*/

#include        <fcntl.h>
#include	<string.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <sys/types.h>
#include        <unistd.h>
#include	<dirent.h>
#define 	EQ(s,t)  (strcmp(s,t) == 0)

/* function prototypes */

int how_good(const char *s, const char *t);
char* find_name(char* dirname, char* guessname);
char* concat(char* s1, char* s2);

int main(int argc, char *argv[])
{
	char* s = "/";
	char* backdir = "../";
	char* cd = "./";
	char* token;
	char* correct_dir = "";
	char* result;
	char* temp;

	if(argc != 2){
		perror("Please supply a filename");
		exit(0);
	}
	
	if(strncmp(argv[1], backdir, 3) == 0){
		correct_dir = malloc(strlen(backdir) + 1);
		strcpy(correct_dir, backdir);	
		argv[1] += 3;
	}
	else if(strncmp(argv[1], cd, 2) == 0){
		correct_dir = malloc(strlen(cd) + 1);
		strcpy(correct_dir, cd);	
		argv[1] += 2;
	}
	else if(strncmp(argv[1], s, 1) == 0){
		correct_dir = malloc(strlen(s) + 1);
		strcpy(correct_dir, s);
		argv[1] += 1;
	}
	else{
		correct_dir = malloc(strlen(cd) + 1);
		strcpy(correct_dir, cd);	
	}
	
	token = strtok(argv[1], s);
	if(token == NULL){
		printf("Supply a longer directory to look for\n");
		exit(0);
	}
	
	while(token != NULL){
		if(find_name(correct_dir, token) != NULL){
			/* copy contents of current "correct_dir" */
			temp = malloc(strlen(correct_dir) + 1);
			strcpy(temp, correct_dir);
			correct_dir = malloc(strlen(correct_dir) + strlen(find_name(correct_dir, token) + strlen("/")) + 1);		
			strcpy(correct_dir, temp);
			strcat(correct_dir, find_name(correct_dir, token));
			strcat(correct_dir, "/");
		}
		else{
			break;
		}		
		token = strtok(NULL, s);
	}
	
	printf("Correct path: %s\n", correct_dir);
	return 0;
}

char* find_name(char* dirname, char* guessname)
{
	DIR *dp;
	struct dirent *entry;
		
	if((dp = opendir(dirname)) == NULL){
		return NULL;
	}
	
	while((entry = readdir(dp)) != NULL){
		if(how_good(entry->d_name, guessname) == 0){	/* if perfect match */
			return (entry->d_name);			
		}
		else if(how_good(entry->d_name, guessname) > 0){	/* if possible match */
			return (entry->d_name);
		}
	}

	return NULL; /* No possible matches */
}

int how_good(const char *s, const char *t)
{

	if(EQ(s,t))
	  return 0;		/* exact match*/

	while(*s++ == *t++)   	/* move to discrepancy*/
		;

	if (*--s) {
	   if (*--t) {
		if (s[1] && t[1] && *s == t[1] && *t == s[1] && EQ(s+2,t+2))
		   return 1;	/*two characters transposed*/

		if (EQ(s+1, t+1))
		   return 2;	/* one character mismatch */
	   
		if (EQ(s+1, t))
		   return 3;	/*extra character in the middle of one string*/
		
		if (EQ(s, t+1))
		   return 4;	/*character missing in the string*/
	   }

	   if (EQ(s+1,t))
		   return 3;	/*extra character at end of string*/
	}

	if (*--t && EQ(s, t+1))
	   return 4;		/*missing character at end of string*/

	return -1;		/* no match found */
}
