/*Nawfal Cherkaoui Elmalki, 10/7/21

This program scans input from Resume.txt and Keywords.txt, searches the resume for the example keywords, and prints to console the number of keywords found.

Note: I developed this program before my understanding of dynamic memory allocation.*/

// pre-processor directives
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void keyword_Reader(char resume[], int* counter) {
	FILE* keywords_text;
	char keywords[10000];

	keywords_text = fopen("Keywords.txt", "r");
	if (keywords_text == NULL) {
		printf("Failed to open the file.\n");
		exit(-1);
	}

	while(fscanf(keywords_text, " %[^,] ,", keywords)!=EOF) {
		*counter += count_Occurrences(resume, keywords);
	}

	fclose(keywords_text);
} //Sets the keywords array equal to a keyword and then calls count_Occurences to count the occurences of that keyword, before moving on to the next.

int count_Occurrences(char* str, char* toSearch)
{
	int i, j, found, count;
	int stringLen, searchLen;

	stringLen = strlen(str); //length of the resume
	searchLen = strlen(toSearch); //length of the specific keyword

	count = 0;

	for (i = 0; i <= stringLen - searchLen; i++)
	{
		found = 1;
		for (j = 0; j < searchLen; j++)
		{
			if (toupper(str[i + j]) != toupper(toSearch[j]))
			{
				found = 0;
				break;
			}
		}

		if (found == 1)
		{
			count++;
		}
	}

	return count;
} //Checks resume[] index by index and checks if the next few indexes match keyword[].

int main() {
	char resume[10000];
	int counter=0, i = 0;
	FILE* resume_text;

	resume_text = fopen("Resume.txt", "r");
	if (resume_text == NULL) {
		printf("Failed to open the file.\n");
		exit(-1);
	}

	while (feof(resume_text) != 1) {
		resume[i] = fgetc(resume_text);
		i++;
	} //Reads resume.txt into resume[] character by character.
	resume[i] = '\0';

	fclose(resume_text);

	keyword_Reader(resume, &counter);

	printf("%i Keywords Found.\n", counter);

	return 0;
} //Driver Function