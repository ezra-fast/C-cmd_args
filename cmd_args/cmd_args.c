/*Date: Wednesday November 9
 *Author: Ezra Fast
 *Description: This program takes in command line arguments from the user and uses them to find a given number of words of a specific length
 * a given number of times, and then writes each of those words to an output file specified by the user, and prints them as output. This program is for 
 * Secure Programming Essentials Lab Assignment 6 Problem 2.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// This should be run with a variation of the following command line argument: ./cmdline2 --letters b,n,p,l --len 7 -c 2 -f textfile.txt --out words7long.txt

char * extract_letters(char cmd3[], char letters[]);
int functionality_v1(FILE * input, FILE * output, char file_contents[][15], char uppered[], char letters[], int count, int length);

int main(int argc, char * argv[])
{
    printf("\n");

    if (argc != 11) // Checking for proper argumentation. 
    {
        printf("Improper Number of Arugments Given\n");
        return 1;
    }

    // majority of the variable declarations:
    char letters[10] = {'A'};
    int length = atoi(argv[4]);
    int count = atoi(argv[6]);
    char file_contents[1000][15] = {'A'};
    FILE * output = fopen(argv[10], "w+");
    FILE * input = fopen(argv[8], "r");
    
    // Checking if either FILE is NULL:
    if (input == NULL)
    {
        printf("Input file is NULL\n");
        return 2;
    }
    if (output == NULL)
    {
        printf("Output file is NULL\n");
        return 3;
    }

    // Using my own function to turn the cmd line arg of letters into a more useable format:
    extract_letters(argv[2], letters);
    
    // Making an uppercase array of the same letters in order to be case-insensitive:
    char uppered[10] = {'A'};
    for (int r = 0; r < strlen(letters); r++)
    {
        uppered[r] = toupper(letters[r]);
    }

    // calling a behemoth function to abstract away logic and output writing from the main function:
    functionality_v1(input, output, file_contents, uppered, letters, count, length);

    return 0;
}



// Function that takes in FILE *s, 1 and 2 dimensional arrays, as well as length and count to print the output as well as read it to the designated output file:
int functionality_v1(FILE * input, FILE * output, char file_contents[][15], char uppered[], char letters[], int count, int length)
{
    int words = 0;
    for (int i = 0; ; i++)
    {
        int holder = fscanf(input, "%s", file_contents[i]); // storing return value and calling function to fill file_contents
        for(int k = 0; k < strlen(letters); k++)
        {
            if (file_contents[i][0] == letters[k] && strlen(file_contents[i]) == length || file_contents[i][0] == uppered[k] && strlen(file_contents[i]) == length)
            {
                printf("%s\n", file_contents[i]);
                fprintf(output, "%s \n", file_contents[i]);
                words++;
            }
            if (words >= count || *file_contents[i] < 32 || *file_contents[i] > 122)
            {
                fclose(input); // closing both files prior to finishing execution
                fclose(output);
                printf("\n"); // printing newline for nicer output
                return 0;
            }
        }
    }
}


// Function to extract just the letters from the command line input:
char * extract_letters(char cmd3[], char letters[])
{
    static int counter = 0;
    for (int i = 0; i < strlen(cmd3); i++)
    {
        if(cmd3[i] != ',' && cmd3[i] >= 97 && cmd3[i] <= 122)
        {
            letters[counter] = cmd3[i];
            counter++;
        }
    }
    return letters;
}
