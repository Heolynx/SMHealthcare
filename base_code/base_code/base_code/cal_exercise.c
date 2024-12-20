//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//  and mastered by Chaeeun Heo
// 241215 : exercise.c file -> error presents;; I am searching the solution... 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size=0;
static int exercise_count=0; //// I wrote the variation. here is no error....

/*
    description : read the information in "excercises.txt"
    241215 : I wrote 'loadExercises' function. 
*/


void loadExercises(const char *path){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    // 241215 : I wrote function so that it can read exercises.txt and saved in structure
    exercise_count=0;
    while (fscanf(file,"%s %d",exercise_list[exercise_count].exercise_name, &exercise_list[exercise_count].calories_burned_per_minute)!=EOF) {
		exercise_count++;
		if (exercise_count >= MAX_EXERCISES){  //it is process checking maximum size
        	break;
		}
    }
    

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    // 241215 : I wrote 'print the list of exercises'
    printf("The list of exercises: \n");
    for (i=0; i<exercise_count; i++){
    	printf("%d. %s (%d kcal/min)\n", i + 1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
    }
    printf("%d. Exit\n", exercise_count + 1);
	
    // ToCode: to enter the exercise to be chosen with exit option
    // 241215 : I wrote 'select exercise'
    printf("Choose an exercise (1-%d):", exercise_count + 1);
    scanf("%d", &choice); 
    
    if (choice == exercise_count + 1) {
        printf("Exit selected. No exercise recorded.\n");
        return; // 241215 : option exit 
    } else if (choice < 1 || choice > exercise_count) {
        printf("[Warning] Invalid option selected.\n");
        return; // 241215 : invalid input
    }
 
    // To enter the duration of the exercise
    // 241215 : I wrote the duration of the exercise. 
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);
    
    if (duration <= 0) {
        printf("[Warning] Duration must be a positive number.\n");
        return; // 241215: invalid input
    }

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    // 241215 :  array starts 0. so choice -1 wrote
    int calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration;
    health_data->total_calories_burned += calories_burned;
    
    Exercise exercise = exercise_list[choice - 1]; // 241220 : I had many error this part..... I searched the solution and found 'strcpy'.
    strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise.exercise_name); // 241220 copy exercise name to health_data
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = calories_burned; //241220 copy exercise calories to health_data
    health_data->exercise_count++; 
    
    printf("You have burned %d kcal by doing %s for %d minutes.\n", 
           calories_burned, exercise_list[choice - 1].exercise_name, duration);
           


}
