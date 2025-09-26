#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct words {
    char *word;
    float score;
    float SD;
    int SIS_array[10];
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("input incorrect\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error opening first file\n");
        return 1;
    }

    FILE *analysis = fopen(argv[2], "r");
    if (analysis == NULL) {
        printf("Error opening second file\n");
        return 1;
    }

    int top = 10;
    int num = 0;
    struct words *eachword = malloc(top * sizeof(struct words));
    if (eachword == NULL) {
        printf("Memory allocation failed\n");
        fclose(f);
        return 1;
    }

    char tempword[100]; // Declare tempword here

    while (1) {
    int result = fscanf(f, "%99s %f %f [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]",
                               tempword, &eachword[num].score, &eachword[num].SD,
                               &eachword[num].SIS_array[0], &eachword[num].SIS_array[1],
                               &eachword[num].SIS_array[2], &eachword[num].SIS_array[3],
                               &eachword[num].SIS_array[4], &eachword[num].SIS_array[5],
                               &eachword[num].SIS_array[6], &eachword[num].SIS_array[7],
                               &eachword[num].SIS_array[8], &eachword[num].SIS_array[9]);
    if (result == EOF) {
        break; // End of file reached
    }
    if (result != 13) {
        // Clear input buffer until a newline is encountered
        int c;
        while ((c = fgetc(f)) != '\n' && c != EOF);
        continue; // Continue to the next line
    }
        eachword[num].word = strdup(tempword);
        if (eachword[num].word == NULL) {
            printf("Memory allocation failed\n");
            fclose(f);
            for (int i = 0; i < num; i++) {
                free(eachword[i].word);
            }
            free(eachword);
            return 1;
        }
        num++;
    
    if (num >= top) {
        int new_top = top * 2; // Double the size
        struct words *new_eachword = realloc(eachword, new_top * sizeof(struct words));
        if (new_eachword == NULL) {
            printf("Memory reallocation failed\n");
            fclose(f);
            for (int i = 0; i < num; i++) {
                free(eachword[i].word);
            }
            free(eachword);
            return 1;
        }
        eachword = new_eachword;
        top = new_top;
    }
}
//above this line is reading the first file

    printf("string sample                                                                        score\n");
    printf("--------------------------------------------------------------------------------------------------\n");


    char singleline[200];
    char *singleword;
    

    while(!feof(analysis)){
        fgets(singleline,200,analysis);
        

        char singleline_copy[200];
        strcpy(singleline_copy, singleline); 

        singleword = strtok(singleline_copy, " \t\n,.;!");

        float tol = 0.0;
        int count = 0;
        float result;
        while(singleword != NULL){

            
            for (int i = 0; singleword[i] != '\0'; i++) {
                if (isupper(singleword[i])) {
                    singleword[i] = tolower(singleword[i]);
                }
            }
        
    
            
            for (int i = 0; i < num; i++) {
                
                if(strcmp(eachword[i].word, singleword) == 0){
                    
                    tol += eachword[i].score;
                    break; 
                }
            }
            count++;
            

            singleword = strtok(NULL, " \t\n,.;!");
        }

        
        
        if(count != 0){
            result = (double)tol/count;
        }
        else{
            result = 0.0;
        }

        if(feof(analysis)){
            break;
        }
        
        printf("%s                                                                                    %f\n",singleline,result);



        
    }




    fclose(f);
    fclose(analysis);

    for (int i = 0; i < num; i++) {
        free(eachword[i].word);
    }
    free(eachword);


}
 