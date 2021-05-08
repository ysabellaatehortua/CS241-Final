#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "header.h"
#include <map>
#include <string>
#include <array>
#include <iostream>

int main(){
	//intro
	printf("Welcome to the plagiarism detector (press ENTER to continue)");
	getchar();
	//buffer size for text files
	char inputbuffer[100];

	map<const string, int>* profile = (map<const string, int>*)malloc(sizeof(map<const string, int>));
	if (profile == NULL) {
		printf("Error with memory allocation -  exiting program.");
		exit(1);
	}
	
	int size = 0;

	//while loop for creating profiles of multiple text files
	bool done;
	done = false;
	while(!done){
		printf("Enter a text file to build the profile (press ENTER with no text when done)\n");
		//scanf("%s", inputbuffer);

		fgets(inputbuffer, sizeof inputbuffer, stdin);

		if(inputbuffer[0] != '\n'){
			inputbuffer[strcspn(inputbuffer, "\n")] = 0;
			printf("adding %s\n", inputbuffer);
			//open up the file
			
			FILE* fp = fopen(inputbuffer, "r");

			if (fp) {
			
				map<const string, int> tmpMap = createDict("is");
	
				char x[1024];
	
				while(fscanf(fp, "%1023s", x) == 1) {
					addWord(tmpMap, x);
					}
						
				//add to the profile
				profile[size] = tmpMap;
		
				size++;

				profile = (map<const string, int>*)realloc(profile, (size+1)* sizeof(map<const string, int>));

				fclose(fp);
			
			}

			else {
				printf("File not found.\n\n");
			}
		}
		else{
			done = true;
			break;

		}
	}

	done = false;
	
	while(!done) {
	
		printf("Enter text to compare to the profile\n");
		scanf("%s", inputbuffer);

		FILE* fp2 = fopen(inputbuffer, "r");

		if (fp2) {

			map<const string, int> checkMap = createDict("is");
			char y[1024];

			while(fscanf(fp2, "%1023s", y) == 1) {
			addWord(checkMap, y);
			}

			fclose(fp2);
			done = true;
		}
	
		else {
			printf("File not found.");
		}
	}

	for (int i = 0; i < size; i++) {
		//compare profiles
	}

free(profile);
return 0;

}
