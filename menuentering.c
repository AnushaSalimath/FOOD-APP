#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int count=0;
typedef struct S_menu {

	char name[25];
	 
	  float price;
	  char des[5];
	   int present;
	    char type[3];
		struct S_menu*next;
	struct S_menu *previous;
	
} menu;

void PrintList(menu *start) {
	menu *cur = start;
	int count = 0;
	
	menu *ahead = NULL;
	menu *behind = NULL;
	
	while(cur != NULL) {
		count++;
		
		ahead = cur->next;
		behind = cur->previous;
		
		printf("ENTRY:%d Name:%s price:%f Desc:%s available:%d Type:%s Ahead:%s Behind:%s\n",count,
			cur->name,
			cur->price,cur->des,cur->present,cur->type,
			(ahead == NULL) ? "None" : ahead->name,
			(behind == NULL) ? "None" : behind->name
			);
		cur = cur->next;
		ahead = NULL;
		behind = NULL;
	}	
	printf("Total entry:%d\n",count);
}

menu *newdata() {
	printf("Enter DISH,PRICE,DESC,AVAILABLE,Type: ");
	char input[60];
	fgets( input, 59, stdin);
	menu *new1=malloc(sizeof(menu));
	sscanf(input,"%s %f %s %d %s",new1->name,&new1->price,new1->des,&new1->present,new1->type);
	new1->next = NULL;
	new1->previous = NULL;
	return new1;
}

menu *AddToStart(menu *startPtr) {
	menu *new1 = newdata();
	if(startPtr != NULL) {
		startPtr->previous = new1;
		new1->next = startPtr;
	}
	
	return new1;
}

menu *AddToEnd(menu *startPtr) {
	menu *returnPtr = startPtr;
	menu *new1 = NULL;
	
	if(startPtr == NULL) {
		new1 = AddToStart(startPtr);
		returnPtr = new1;
	} else {
		menu *index = startPtr;
		while (index->next != NULL) {
			index = index->next;
		}
		new1 = newdata();
		index->next = new1;
		new1->next = NULL;
		new1->previous = index;
	}
	return returnPtr;
}

menu *Delete(menu *startPtr) {

	printf("Enter Name To Delete:");
	char input[16];
	fgets(input, 15, stdin);
	
	menu *Ref = startPtr;
	menu *Delete = NULL;
	
	while(Ref != NULL) {
	
		if(strncmp(input, Ref->name, strlen(Ref->name)) == 0) {
			Delete = Ref;
			break;
		}
		
		Ref = Ref->next;
	}
	
	if(startPtr != NULL && Delete == startPtr) {
		if(Delete->next != NULL) {
		 Delete->next->previous = NULL;
			startPtr = Delete->next;
		} else {
			startPtr = NULL;
		}
	} else {
		if(Delete != NULL) {
			if(Delete->previous != NULL) {
				Delete->previous->next = Delete->next;
			}
			
			if(Delete->next != NULL) {
				Delete->next->previous = Delete->previous;
			}
		}
	}
	
	if(Delete != NULL) {
		Delete = NULL;
		free(Delete);
	}
	
	return startPtr;
	
}
void CleanUp(menu *start) {
	
	menu *freeMe = start;
	menu *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->next;
		printf("Free Name:%s\n",
			freeMe->name);
			
		freeMe = holdMe;
	}	
}

void WriteListToFile(menu *start) { // passing the 1st data of LL as an arg
	FILE *pFile; // file pointer pointing to the 1st data in "menu.txt"
	pFile = fopen("menu.txt", "wb");
	// we will open the file "menu.txt" in write mode
	if(pFile != NULL) {  //checking whther file is empty or not
		menu *cur = start; //lets assume cur acts as a temporary var
		
		menu *holdNext = NULL; //temp next 
		menu *holdPrevious = NULL;//temp prev
		
		while(cur != NULL) { // whether LL is empty or not
			holdNext = cur->next; // ice store
			holdPrevious = cur->previous; // piz
			// we are going temporarily disconnect the node from LL
			cur->next = NULL; // past->next=null
			cur->previous = NULL; //past->prev=null
			// seeking into the file 
			fseek(pFile, 0, SEEK_END);
			// 1st arg=stream,2nd arg = the required offset, 3rd arg = seeking till the end of the file 
			fwrite(cur, sizeof(menu), 1, pFile);//func() that will help you write into a file
			// cur: current node to be written ,2nd : the size of the  var/data, 3rd: one block of data, 4th destination
			printf("Writing:%s to file\n",cur->name);
			// prinitng the confirmation
			cur->next = holdNext; //ice
			cur->previous = holdPrevious;//piz
			// connecting the node back to the LL
			holdNext = NULL;
			holdPrevious = NULL;
			
			cur = cur->next; 
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("FILE OPEN ERROR\n");
	}
	
}

menu *ReadNextFromFile(menu *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(menu));
		returnValue = fread(start, sizeof(menu), 1, pFile);
		start->next = NULL;
		start->previous = NULL;
	} else {
		menu *index = start;
		menu *new1 = malloc(sizeof(menu));
		while(index->next != NULL) {
			index = index->next;
		}
		returnValue = fread(new1, sizeof(menu), 1, pFile);
		index->next = new1;
		new1->next = NULL;
		new1->previous = index;
	}
	return start;
}

menu *ReadListIn(menu *start) { // reading a file and writing it into a LL
	
	FILE *pFile; // creating the file pointer
	pFile = fopen("menu.txt", "r");
	// we will open the file "menu.txt" read mode
	if(pFile != NULL) { //check whether file is present or not
	
		CleanUp(start); // refreshing the data
		start = NULL;
		//start(head of struct menu)
		fseek(pFile, 0, SEEK_END); // file ko end tak padhenge
		long fileSize = ftell(pFile);
		//ftell is func which will return the size of the file 
		rewind(pFile);
		//this will go back to the starting of the file
		
		int numEntries = (int)(fileSize / (sizeof(menu)));
		printf("numEntries:%d\n",numEntries);
		
		int loop = 0;
		//traversing through the file and then storing it into the LL
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(menu) * loop), SEEK_SET);
			//10*0, stating/beginning of the file6
			start = ReadNextFromFile(start, pFile);
		}
	}  else {
		printf("FILE OPEN ERROR FOR READ\n");
	}
	
	return start;

}

int main() {	
	
	char command[16];
	char input[16];	
	
	menu *start = NULL;
	
	while( fgets( input, 15, stdin) ) {
		
		sscanf(input,"%s",command);	
		
		if ( strncmp(command, "quit", 4) == 0) {
			printf("\n\nBreaking...\n");
			break;		
		} else if ( strncmp(command, "print", 5) == 0) {
			PrintList(start);
		} else if ( strncmp(command, "write", 5) == 0) {
			WriteListToFile(start);
		} else if ( strncmp(command, "read", 4) == 0) {
			start = ReadListIn(start);
		} else if ( strncmp(command, "addstart", 8) == 0) {
			start = AddToStart(start);
			PrintList(start);
		} else if ( strncmp(command, "add", 3) == 0) {
			start = AddToEnd(start);
			PrintList(start);
		} else if ( strncmp(command, "insert", 6) == 0) {
			if(start == NULL) {
				start = AddToStart(start);
			} 
		}//else if(strncmp(command,"new",3)==0)
				//newreport(start);
				else if(strncmp(command,"delete",6)==0)
				 Delete(start);
		
			//PrintList(start);
		
	}
	
	CleanUp(start);
	
	return 0;

}
