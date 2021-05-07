#include <iostream>
#include <fstream>
#include <string>
#include <map>
int main(int argc, char* argv[]){
	const char* file=argv[1];
   const char* file2 = argv[2];
	int x;
	FILE* fp = fopen(file,"r");
   FILE* fp2 = fopen(file2, "r");
	while((x=fgetc(fp))!=EOF){
      // send each line to comparision function that returns dictionary of keywords
	}

	fclose(fp);
   fclose(file2);
