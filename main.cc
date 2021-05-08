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
	//compare profiles

 //pretty sure that the maps are profile and checkMap...right?

        int plagCount = 0;//this will count up when we find inconsistencies
        int ps = profile.size();
        double profTotal = 0;
        double checkTotal = 0;

        for(int i = 0; i < ps; i++)
        {
                profTotal += profile[i];//because some works are going to be longer than others we should make a total number then we can make a ratio
                                        //for when each word appears
                checkTotal += checkMap[i];//same thing for the one we are checking
        }

        for(int i = 0; i < ps; i++)
        {
                double profileRatio = ((double) profile[i] / profTotal);//this will average the amount of times a word shows up throughout the profile
                                                                        //making it easier to check with the one work we are checking
                double checkRatio = ((double) checkMap[i] / checkTotal);
                if(checkRatio != 0)//if it is 0 then I don't really think we can say something is inconsistent (unless the corresponding word in the profile is really high?)
                {
                        if((checkRatio + 0.03) <= profileRatio || (checkRatio - 0.03) >= profileRatio)//this 0.03 is pretty subjective but if this is 
                                                                //true then it's inconsistent with the works getting read in because a word would show up >3% away from the profile occurences
                        {
                                plagCount++;//flagging for one word not matching with the profile we built
                        }
                }

                if(checkRatio == 0 && profileRatio > 0)//if this is the case then a word doesn't show up in the checked work but is used in the profile
                {                                       //pretty fishy right?
                        plagCount++;
                }

                if(checkRatio > 0 && profileRatio == 0)//if this is the case then a word is not in the profile but is in the checked work
                {
                        plagCount++;
                }
        }

        double percentageFlagged = 100* ((double) plagCount / 277);
        //there are 277 function words so if more than 25% of them are popping flags then we should be suspicous I think, but this is subjective as well
	//also added a message for more than 75% of flags
	
	int messageprinted = 0;
	
	if(precentageFlagged >= 75 && messageprinted == 0)
	{
		printf("%s\n", "This is most likely plagiarized. Like it's not looking good");
		messageprinted = 1;
	}
	
        if(percentageFlagged >= 25 && messageprinted == 0)//if it's in this range it might be plagiarized but we can't be sure
        {
                printf("%s\n", "Alright well you might want to pull this person in to office hours, there might be something a little suspicious going on");
		messageprinted = 1;
        }
	
	if(percentageFlagged < 25 && messageprinted == 0)
	{
		printf("%s\n", "There aren't a lot of flags so this is probably not plagiarized");
		messageprinted = 1;
	}

free(profile);
return 0;

}
