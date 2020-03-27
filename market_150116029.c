// ARDA BAYRAM - 150116029

//This program simulate a market stock system
#include <stdio.h>
#include <stdlib.h>

//Create structure
struct Firm{
	int firmID;
	char firmName[100];
	struct Firm *nextFirm;
};

//Change name of structure
typedef struct Firm firm;

//Create structure
struct Food{
	char prod_name[400];
	int exp_day;
	int exp_month;
	int exp_year;
};

//Change name of structure
typedef struct Food food;

//Create structure
struct FoodStock{
	struct Food ffood;
	struct FoodStock *nextfood;
};

//Change name of structure
typedef struct FoodStock foodstock;

//Create function prototypes
firm *readFirms(char filename[]);
void printFirms(firm *firmptr);
foodstock *readFoods(char filename[]);
void printFoods(foodstock *foodptr, char filename[]);
foodstock *stockOut(foodstock *foodptr, int day, int month, int year);

int main(void){ //In main call funstions and print interface
	
	firm *firms;
	firms = readFirms("firms.txt");
	printFirms(firms);
	
	foodstock *stocks;
	stocks = readFoods("products.txt");
	printFoods(stocks, "initial_stock.txt");
	
	int day, month, year;
	printf("Please enter the day, month and year to be checked\n");
	scanf("%d %d %d", &day, &month, &year);	
	
	stocks = stockOut(stocks, day, month, year);
	printFoods(stocks, "final_stock.txt");
	
	
}

firm *readFirms(char filename[]){ //Read firms from a file
	
	FILE *fPointer;
	fPointer = fopen(filename, "r"); //Open the file for reading
	char singleLine[100];
	int id;
	
	firm * start = NULL;
	firm * prevPtr;
	firm * curPtr;	
	
	while(!feof(fPointer)){ //Check file
		
	   	firm * newPtr = (firm *)malloc(sizeof(firm)); //Create space in memory
		
		fgets(singleLine, 100, fPointer); //Read the file line by line 
		
		if(feof(fPointer) ) { //Check end of file
    		break ;
      	}
      
		char *tokenPtr = strtok(singleLine, " "); //Seperate content to tokens
	
  		while (tokenPtr != NULL) { //Check all content taken as token or not
  		
		   	if(newPtr != NULL){ //Assign values to structures
		   		newPtr -> firmID = atoi(tokenPtr);
				id = atoi(tokenPtr);
				   			   		
		   		if (tokenPtr != NULL) { 
      			tokenPtr = strtok(NULL, " ");
      			      			
      			strcpy(newPtr -> firmName, tokenPtr);
				newPtr -> nextFirm = NULL;
      			
		   		prevPtr = NULL;
		   		curPtr = start;
			   }
			   
			   while(curPtr != NULL && id < curPtr -> firmID){
			   		prevPtr = curPtr;
			   		curPtr = curPtr -> nextFirm;
			   	}
			   	
			   	if(prevPtr == NULL){
			   		newPtr->nextFirm = start;
					start = newPtr;	
				}
				else{
					prevPtr->nextFirm = newPtr;
					newPtr->nextFirm = curPtr;
				}
			}
			else{
				printf("No memory available!");
			}
      	 	     
      		tokenPtr = strtok(NULL, " "); 
 		} 
 				
	}
	
	fclose(fPointer); //Close the file
	
	return start;
}

//Print the firms
void printFirms(firm *firmptr){
	 
	 puts("Firms:");
	 
      // while not the end of the firms
      while (firmptr != NULL) { 
         printf("firm no %d\tfirm name %s", firmptr->firmID, firmptr->firmName);
         firmptr = firmptr->nextFirm;   
      } 
}

foodstock *readFoods(char filename[]){ //Read products from the file
	
	FILE *fPointer;
	fPointer = fopen(filename, "r"); //Open the file 
	char singleLine[400];
	char name[100];
	char type[100];
	char namef[100];
	char fullname[300];
	int amount;
	int n = 0;
				
	foodstock * start = NULL;
	foodstock * curPtr;	

	while(!feof(fPointer)){ //Check end of the file
				
		fgets(singleLine, 400, fPointer); //Read the file line by line 
		
		if(feof(fPointer) ) { //Check end of the file
    		break ;
      	}
      
		char *tokenPtr = strtok(singleLine, " "); //Seperate content to tokens
	
  		if (tokenPtr != NULL) { //Check all content taken as token or not
  			
		   	strcpy(name, tokenPtr);
			if (tokenPtr != NULL) {
      			tokenPtr = strtok(NULL, " ");
      			strcpy(type, tokenPtr);
			}
			if (tokenPtr != NULL) {
     			tokenPtr = strtok(NULL, " ");
				strcpy(namef, tokenPtr);
			}
			if (tokenPtr != NULL) {
				tokenPtr = strtok(NULL, " ");			   
				amount = atoi(tokenPtr);
			}
			
			strcpy(fullname, strcat(name ,strcat(type, namef)));	
			foodstock * newPtr = (foodstock *)malloc(sizeof(foodstock)); //Open space to structure
			strcpy(newPtr->ffood.prod_name, fullname); //Assign values to structure
			newPtr->ffood.exp_day = 1 + (rand()%14);
			newPtr->ffood.exp_month = 1 + (rand()%4);
			newPtr->ffood.exp_year = 2018 + (rand()%2);
			if(n==0) //Check first turn
				start = newPtr;
			
			int i;
			if(n==0){ //Check first turn
				
			for(i = 1; i < amount; i++) {
				curPtr = newPtr;
		 		newPtr = (foodstock *)malloc(sizeof(foodstock)); //Open space to structure
				strcpy(newPtr->ffood.prod_name, fullname); //Assign values to structure
				newPtr->ffood.exp_day = 1 + (rand()%14);
				newPtr->ffood.exp_month = 1 + (rand()%4);
				newPtr->ffood.exp_year = 2018 + (rand()%2);
				curPtr->nextfood = newPtr;
			}
			curPtr = newPtr;
			}
			else{ //After first turn use that
				for(i = 1; i < amount; i++) {
			  		curPtr->nextfood = newPtr;
					curPtr = newPtr;
					newPtr = (foodstock *)malloc(sizeof(foodstock));
					strcpy(newPtr->ffood.prod_name, fullname);
					newPtr->ffood.exp_day = 1 + (rand()%14);
					newPtr->ffood.exp_month = 1 + (rand()%4);
					newPtr->ffood.exp_year = 2018 + (rand()%2);
				}
				curPtr->nextfood = newPtr;
				curPtr = newPtr;
			}
		}
		n++;
       	tokenPtr = strtok(NULL, " "); 
    }
	curPtr->nextfood = NULL; 
 	fclose(fPointer); //Close the file
	return start;
}

void printFoods(foodstock *foodptr, char filename[]){ //Print products to a file 
	
	FILE *file;
	foodstock *temp = NULL;
	
	if ((file = fopen(filename, "w")) == NULL) { //Open the file and check it
      puts("File could not be opened");
   	}
	else{
		for(temp = foodptr; temp != NULL; temp = temp->nextfood){
			//Print datas to file
			fprintf(file, "%s EXP : %d/%d/%d\n", temp->ffood.prod_name, temp->ffood.exp_day, temp->ffood.exp_month, temp->ffood.exp_year);
			
		}
	}
	
	fclose(file); //Close the file	    

}

foodstock *stockOut(foodstock *foodptr, int day, int month, int year){ //Delete products that have passing expration date
	
	foodstock *start = NULL;
	foodstock *curr;
	foodstock *prev;
	foodstock *temp;
	start = foodptr;
	prev = foodptr;

	if(foodptr == NULL){ //Check pointer
		printf("Program did not find your linked list!\n");
	}
	else{
		int n = 0; //To use check if start in the firts structure in the list
		for(curr=foodptr; curr != NULL;){
			if(curr->ffood.exp_year > year){ //Check year
				curr = curr->nextfood; //Take next structure
				if(n != 0) //Check if start in the firts structure in the list
					prev = prev->nextfood;
				n++;	
				continue;
			}
			else if(curr->ffood.exp_year == year){ //Check year
				if(curr->ffood.exp_month > month){ //Check month
					curr = curr->nextfood;
					if(n != 0)
						prev = prev->nextfood;
					n++;	
					continue;					
				}
				else if(curr->ffood.exp_month == month){ //Check month
					if(curr->ffood.exp_day >= day){ //Check day
						curr = curr->nextfood;
						if(n != 0)
							prev = prev->nextfood;
						n++;	
						continue;						
					}
					else{
						temp = curr;
						prev->nextfood = curr->nextfood;
						curr = curr->nextfood;
						if(n==0){
							if(start == prev){
								start = start->nextfood;
								prev = start;
							}
						}
						free(temp);	//Free the structure						
					}
				}
				else{
					temp = curr;
					prev->nextfood = curr->nextfood;
					curr = curr->nextfood;
					if(n==0){
						if(start == prev){
							start = start->nextfood;
							prev = start;	
						}
					}
					free(temp);					
				}
			}
			else{
				temp = curr;
				prev->nextfood = curr->nextfood;
				curr = curr->nextfood;
				if(n==0){
					if(start == prev){
						start = start->nextfood;
						prev = start;	
					}	
				}
				free(temp);				
			}
		}
	}
	return start;
}
