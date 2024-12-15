//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static int diet_count = 0;            
static Diet diets[MAX_DIETS];         


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    diet_count = 0;
    while (fscanf(file, "%s %d", diets[diet_count].food_name, &diets[diet_count].calories_intake) != EOF) {
    	 diet_count++;
        if (diet_count >= MAX_DIETS){
        	printf("[Warning!!]Exceeded maximum size.");
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    // 241215 : print the list of diets.
    printf("The list of diets:\n");
    for (i=0; i < diet_count; i++) {
        printf("%d. %s (%d kcal)\n", i + 1, diets[i].food_name, diets[i].calories_intake);
    }
    printf("%d. Exit\n", diet_count + 1);
    
    
	// ToCode: to enter the diet to be chosen with exit option
	// 241215 : select diets
	 printf("Choose a diet (1-%d): ", diet_count + 1);
    scanf("%d", &choice);

    if (choice == diet_count + 1) {
        printf("Exit selected. No diet recorded.\n");
        return; // option of end
    } else if (choice < 1 || choice > diet_count) {
        printf("[Error] Invalid option selected.\n");
        return; // 유invalid input
    }
    

    // ToCode: to enter the selected diet in the health data
    // 241215 : 
    int calories_intake = diets[choice - 1].calories_intake;
    health_data->total_calories_intake += calories_intake;

    printf("You have consumed %d kcal by eating %s.\n", 
           calories_intake, diets[choice - 1].food_name);
    

    // ToCode: to enter the total calories intake in the health data
    health_data->total_calories_intake += calories_intake; 

     // 사용자에게 결과 출력
    printf("You have consumed %d kcal by eating %s.\n", 
       calories_intake, diets[choice - 1].food_name);

}

