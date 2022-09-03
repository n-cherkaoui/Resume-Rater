/*Nawfal Cherkaoui Elmalki, 10/7/21

This program scans input from Resume.txt and Keywords.txt, searches the resume for the example keywords, and prints to console the number of keywords found.

Note: I developed this program prior to my understanding of dynamic memory allocation.*/

// pre-processor directives
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void keyword_Reader(char resume[], int* counter); //Reads in keywords from keywords.txt and calls count_Occurences
int count_Occurrences(char* resume, char* keywords); //Loops through resume[] and updates keyword_Count if a keyword is found.


int main() {
	char resume[10000];
	int counter=0, i = 0;
	FILE* resume_text;

	resume_text = fopen("Resume.txt", "r"); //Opens resume.txt for reading
	if (resume_text == NULL) {
		printf("Failed to open the file.\n");
		exit(-1);
	}

	while (feof(resume_text) != 1) { //Reads resume.txt into the resume array
		resume[i] = fgetc(resume_text);
		i++;
	} 
	resume[i] = '\0';

	fclose(resume_text);

	keyword_Reader(resume, &counter);

	printf("%i Keywords Found.\n", counter); //Prints keywords found in resume

	return 0;
} //Driver Function


void keyword_Reader(char resume[], int* counter) {
	FILE* keywords_text;
	char keywords[10000];

	keywords_text = fopen("Keywords.txt", "r");
	if (keywords_text == NULL) {
		printf("Failed to open the file.\n");
		exit(-1);
	}

	while (fscanf(keywords_text, " %[^,] ,", keywords) != EOF) {
		*counter += count_Occurrences(resume, keywords);
	}

	fclose(keywords_text);
} 

int count_Occurrences(char* resume, char* keywords)
{
	int i, j, found, keyword_Count = 0;
	int stringLen, searchLen;

	stringLen = strlen(resume); //length of the resume
	searchLen = strlen(keywords); //length of the specific keyword

	for (i = 0; i <= stringLen - searchLen; i++)
	{
		found = 1;
		for (j = 0; j < searchLen; j++)
		{
			if (toupper(resume[i + j]) != toupper(keywords[j]))
			{
				found = 0;
				break;
			}
		}

		if (found == 1)
		{
			keyword_Count++;
		}
	}

	return keyword_Count;
} 
