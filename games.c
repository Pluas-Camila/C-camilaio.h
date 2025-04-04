#include <stdio.h>
#include <string.h> //will use fgets, strcmp, strcspn

#define S_Length 101 //100 characters + \0 character
// Defining structure where game data is stored
struct game { //Then we define the elements that we will need inside the structure
    int score;
    double price;
    char title[S_Length];
    char genre[S_Length];
    char console[S_Length];
    char rating[S_Length];
};
int search(struct game list[], int n, struct game result[], char *search_console); //define search
//array of games, the number of games, the array to store the results, and the console that we are trying to search for.

int main() {
    FILE *input_file, *output_file;
    char fname[S_Length], ConsoleName[S_Length]; //arrays to store console name and string

    struct game games[1000], search_results[1000]; //from the structure we create arrays that will store the list of games
    //being read from the file, and search results

    int count = 0;
    int result;

    
    printf("Enter file name: ");
    fgets(fname, sizeof(fname), stdin);//reads file
    fname[strcspn(fname, "\n")] = '\0';  // Remove newline


    input_file = fopen(fname, "r"); //opens to read the file
    if (input_file == NULL) { //if the file is empty it will print an error
        printf("Error opening file %s\n", fname);
        return 1;
    }

    // Prompt user for the console to search
    printf("Enter the console for searching: "); //asks for the nme of the console
    fgets(ConsoleName, sizeof(ConsoleName), stdin);
    ConsoleName[strcspn(ConsoleName, "\n")] = '\0';  // Remove newline

    //The file has commas, numbers and so on on a specific order, I used those specifics to know where is the name the genre and so on..

    while (fscanf(input_file, "%[^,], %[^,], %d, %lf, %[^,], %[^\n]\n",
                   games[count].title,//until the first comma there will be the name
                   games[count].genre,//after first comma there is the genre
                   &games[count].score,// the first whole number is the review score
                   &games[count].price,// second double number is the price
                   games[count].console,// after that the console name
                   games[count].rating) == 6) { // there has to be a total of 6 elements
        count++;
        if (count >= 1000) { // more than 1000 games will break the loop
            break;
        }
    }

    // Close the file
    fclose(input_file);

    // Calls function to search
    result = search(games, count, search_results, ConsoleName);


    output_file = fopen("result.csv", "w"); //Opens a file and writes the result information
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    // Write the search results to the output file
    for (int i = 0; i < result; i++) { // loops around the result array and writes that into the output file
        fprintf(output_file, "%s, %s, %d, %.2lf, %s, %s\n",
                search_results[i].title,
                search_results[i].genre,
                search_results[i].score,
                search_results[i].price,
                search_results[i].console,
                search_results[i].rating);
    }

    // Closes output file
    fclose(output_file);

    printf("Search complete. Results written to result.csv\n");

    return 0;
}





int search(struct game list[], int n, struct game result[], char *search_console) {
    int count = 0;

    // The for loop will loop through all the games
    for (int i = 0; i < n; i++) {
        if (strcmp(list[i].console, search_console) == 0) {
            // compares the console name with the string were the name is, and will return 0 if they match
            result[count] = list[i]; // stores the game
            count++;
        }
    }
    return count;  // Number of matches
}

