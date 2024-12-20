//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//  masterde by HCE 2413274

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	
	// To initialize the health data object
    HealthData healthdata = {0};  
    
    // Tocode: to read the list of the exercises and diets
    // 241215 : load function bringing in
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);
    
    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    // 241220 : HCE wrote systems with switchm and fill out the if and while, switch
    do {
    	if (healthdata.total_calories_intake >= 2000){
            printf("You have consumed all your calories for today! \n");
            break;
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&healthdata);
                break;
                
            case 2:
            	inputDiet(&healthdata);
                break;
                
            case 3:
            	printHealthData(&healthdata);
                break;
                
            case 4:
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (healthdata.total_calories_intake < 2000 && choice != 4);           //241220 if intake is not 2000 or choice is wrong -> keep going

    return 0;
}

