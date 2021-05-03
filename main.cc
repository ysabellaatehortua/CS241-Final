#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


int main(){
	//intro
	printf("Welcome to the plagiarism detector (press ENTER to continue)");
	getchar();
	//buffer size for text files
	char inputbuffer[100] = {'\0'};
	//while loop for creating profiles of multiple text files
	bool done;
	done = false;
	while(!done){
		printf("Enter a text file to build the profile (press ENTER with no text when done)\n");
		scanf("%s", inputbuffer);
		if(inputbuffer[0] != '\0'){
			printf("adding %s\n", inputbuffer);
			//open up the file
			//add to the profile
		}
		else{
			break;
		}
	}

return 0;

}
