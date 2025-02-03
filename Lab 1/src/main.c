// Includes
#include <stdio.h>

int user_interaction();

int main() {

    /** RANGE INPUT **/

    // Variable Declarations
    int min = 1, max = 0;

    // Prompt User for the Range
    while (max < min) {
        printf("Range, minimum: ");
        scanf("%d", &min);

        printf("Range, maximum: ");
        scanf("%d", &max);
    }

    /** PROGRAM GUESS NUMBER **/

    // Variable Declarations
    int counter = 0, state = 1;
    int program_guessed_number = (max + min) / 2;

    printf("Guessed number: %d\n", program_guessed_number);

    while (state != 3) {
        state = user_interaction();

        if (state == 1) {
            max = program_guessed_number - 1;
        } else if (state == 2) {
            min = program_guessed_number + 1;
        }

        program_guessed_number = (max + min) / 2;

        printf("Guessed number: %d\n", program_guessed_number);
        counter++;
    }

    printf("FOUND IT\n");
    printf("No. of tries: %d\n", counter);

    return 0;
}

/** User Interaction Written by Me **/
// int user_interaction() {
//
//     int userInput;
//
//     printf("1.  TOO LARGE\n");
//     printf("2.  TOO SMALL\n");
//     printf("3.  FOUND\n");
//     
//     printf("Input: ");
//     scanf("%d", &userInput);
//     printf("\n");
//
//     return userInput;
// }

// User Interaction Written by AI
int user_interaction() {
    printf("1. TOO LARGE\n");
    printf("2. TOO SMALL\n");
    printf("3. FOUND\n");
    printf("Input: ");
    
    int user_input;
    scanf("%d", &user_input);
    
    return user_input;
}
