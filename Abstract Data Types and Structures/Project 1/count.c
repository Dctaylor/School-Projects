#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *text_file;
    # define MAX_WORD_LENGTH 30
    int word_count = 0;
    char buffer[MAX_WORD_LENGTH +1];
    
    //Open the file
    text_file = fopen(argv[1], "r");
    
    //If the file can't be opened, return error
    if(text_file == NULL) {
        printf("File cannot be opened");
        return 1;
    }
    
    //Getting the word count
    while(fscanf(text_file, "%s", buffer) == 1) {
        word_count++;
    }
    
    //Printing out word count
    printf("%i total words \n", word_count);
    
    //Close the file
    fclose(text_file);
    
    return 0;
    
}