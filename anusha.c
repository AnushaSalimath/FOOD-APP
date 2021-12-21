/*------------------------------------------------------------------------------------------------------------------
                                 NAME OF THE PROJECT:MY FOODAPP
                                    NAME : ANUSHA SALIMATH
                                    USN : 1NH19CS020
                                    ACADEMIC YEAR : 2020 - 2021
--------------------------------------------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<menuentering.h>  //ALL THE WORKING OPERATIONS ARE LOCATED HERE
int main(){
	int op;
	start1=NULL; //head of the cart linked list.
	start=ReadListIn(start);//reading the menu data from the file to the menu linked list .
		start2 = ReadListIn1(start2);//reading the employee list from the file
	 while(op!=3){
	 	start1=NULL;
	 	system("cls");
	 	 printf("\t\t\t\t\t\t:MYFOODAPP:\n"); 
	 	  printf("\n\t\t\t\t\t\t1.Admin\n");
	 	   printf("\n\t\t\t\t\t\t2.Customer\n");
	 	    printf("\n\t\t\t\t\t\tEnter choice:");
	 	     scanf("%d",&op);
	 	     switch(op){
	 	     	case 1:cp();break;
	 	     	 case 2:customer();break;
			  }
	 }
	  return 0;
}
