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
	char inputbuffer[100] = {'\0'};
	
	map<const string, int> profile[100];
	int size = 0;

	//while loop for creating profiles of multiple text files
	bool done;
	done = false;
	while(!done){
		printf("Enter a text file to build the profile (press ENTER with no text when done)\n");
		scanf("%s", inputbuffer);
		if(inputbuffer[0] != '\0'){
			printf("adding %s\n", inputbuffer);
			//open up the file
			
			FILE* fp = fopen(inputbuffer, "r");

			// Add error message for fnf
			
			map<const string, int> tmpMap = createDict("is");

			char x[1024];

			while(fscanf(fp, "%1023s", x) == 1) {
				addWord(tmpMap, x);
			}
				
			//add to the profile
			profile[size] = tmpMap;
		
			size++;

			fclose(fp);
		}
		else{
			break;
		}
	}

return 0;

}
