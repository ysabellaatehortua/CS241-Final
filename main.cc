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

	map<const string, int> profile = createDict("is");;

//	map<const string, int>* profile = (map<const string, int>*)malloc(sizeof(map<const string, int>));
//	if (profile == NULL) {
//		printf("Error with memory allocation -  exiting program.");
//		exit(1);
//	}
	
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
			
//				map<const string, int> tmpMap = createDict("is");
	
				char x[1024];
	
				while(fscanf(fp, "%1023s", x) == 1) {
					addWord(profile, x);
					}
						
				//add to the profile
//				profile[size] = tmpMap;
		
				size++;

//				profile = (map<const string, int>*)realloc(profile, (size+1)* sizeof(map<const string, int>));
				
				
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
	map<const string, int> checkMap = createDict("is");
	
	while(!done) {
	
		printf("Enter text to compare to the profile\n");
		scanf("%s", inputbuffer);

		FILE* fp2 = fopen(inputbuffer, "r");

		if (fp2) {


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
        double profTotal = 0;
        double checkTotal = 0;
	map<string, int>::iterator it;
        map<string, int>::iterator it2;


        for(it = profile.begin(); it != profile.end(); it++)
        {
                profTotal += (double) it->second;//because some works are going to be longer than others we should make a total number then we can make a ratio
                                        //for when each word appears
	}
	
	for(it = checkMap.begin(); it != checkMap.end(); it++)
	{
                checkTotal += (double) it->second;//same thing for the one we are checking
        }

	it2 = checkMap.begin();//need this to increment through the checkMap in the following for loop
	
        for(it = profile.begin(); it != profile.end(); it++)
        {
                double profilePercent = 100 * ((double) it->second / profTotal);//this will average the amount of times a word shows up throughout the profile
                                                                        //making it easier to check with the one work we are checking
                double checkPercent = 100 * ((double) it2->second / checkTotal);
		
		it2++;//because the it2 isn't in the for loop it can increment right here
		
                if(checkPercent != 0 && profilePercent != 0)//if it is 0 then I don't really think we can say something is inconsistent (unless the corresponding word in the profile is really high?)
                {
                        if((checkPercent + 25) <= profilePercent || (checkPercent - 25) >= profilePercent)//this 25 is pretty subjective but if this is 
                                                                //true then it's inconsistent with the works getting read in because a word would show up >25% away from the profile occurences
                        {
                                plagCount++;//flagging for one word not matching with the profile we built
                        }
                }

                if(checkPercent == 0 && profilePercent > 0)//if this is the case then a word doesn't show up in the checked work but is used in the profile
                {                                       //pretty fishy right?
                        plagCount++;
                }

                if(checkPercent > 0 && profilePercent == 0)//if this is the case then a word is not in the profile but is in the checked work
                {
                        plagCount++;
                }
        }

        double percentageFlagged = 100* ((double) plagCount / 277);
        //there are 277 function words so if more than 25% of them are popping flags then we should be suspicous I think, but this is subjective as well
	//also added a message for more than 75% of flags
	
	int messageprinted = 0;
	
	if(percentageFlagged >= 75 && messageprinted == 0)
	{
		printf("%s\n", "There are flags on at least 75% of these function words, meaning that it really doesn't match with the profile you have built.");
		messageprinted = 1;
	}
	
	if(percentageFlagged >= 50 && messageprinted == 0)
	{
		printf("%s\n", "There are flags on 50%-75% of the function words, so it's likely that the checked source is not from the profiled author.");
	}
	
        if(percentageFlagged >= 25 && messageprinted == 0)//if it's in this range it might be plagiarized but we can't be sure
        {
                printf("%s\n", "There are flags on 25%-50% of the function words, so it doesn't match up very well with the profile but we can't say for sure whether or not it is plagiarized.");
		messageprinted = 1;
        }
	
	if(percentageFlagged < 25 && messageprinted == 0)
	{
		printf("%s\n", "Less than 25% of the function words are being flagged, so the likelyhood of this being plagiarized is low.");
		messageprinted = 1;
	}

//free(profile);
return 0;

}
