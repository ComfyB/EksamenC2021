#include "source.h" //header with declaration of a letteroccurencecounter and the needed libraries

int main(void)
{
    int ch, ch2;  //two ints that work as a buffer for the
    long decimal; //long to hold the two integer values after covertion to base 10 from b16

    FILE *fptrIn = fopen("hexdec", "r");    //open file for reading
    FILE *fptrOut = fopen("toascii", "rw"); //openfile for reading and writing

    if (fptrIn == NULL || fptrOut == NULL) //check if file is found and opened correctly
    {
        printf("File Not found");
        exit(1);
    }
    while ((ch = fgetc(fptrIn)) != EOF) // read one and one char into "buffer"
    {
        ch2 = fgetc(fptrIn);                     //Reads char 2
        strncat((char *)&ch, (char *)&ch2, 1);   //Puts the two values after eachother before convertion Casted to char * from int.
        decimal = strtol((char *)&ch, NULL, 16); //Converts the two characters to base 10 from base 16.

        fputc(decimal, fptrOut);    // writes the cast character to output file
        printf("%c", (int)decimal); //prints the character in terminal.  casted to int as char are ints in c.
    }
    letterOccurenceCounter(fptrOut); //run the program for counting. Could have been written so it counted every char while running the while loop earlier
                                     //but the task was ambigious. I chose to intepret that it was supposed to do it after the main function .

    fclose(fptrIn);  //
    fclose(fptrOut); // close both files

    return 0;
}
void letterOccurenceCounter(FILE *in) //passing the pointer to the fopen in line 9
{
    int c, tmp,                          //temp int for characterinput
        i, character;                    // i for the while loop later. character to have a modifiable value for the function that prints the letters.
    int counter[27];                     //counter array.
    memset(counter, 0, sizeof(counter)); //clear the memory since we are using += later. fixses some troubles where mem is not clear
    printf("\n");
    if (in == NULL) //exit if pointer isn't passed.
    {
        printf("File Not found");
        exit(1);
    }
    while ((c = fgetc(in)) != EOF) //get character by character
    {
        tmp = toupper(c);          //convert and tmp save the character in uppercase.
        tmp = tmp - 'A';           //take the tmp and decrement value with A (65)
        if (tmp >= 0 && tmp <= 26) //check if the resulting value is alpha
            counter[tmp] += 1;     //increment the value in the letters place in the array.
    }

    for (i = 0; i < 26; i += 2) //print array
    {
        character = i;
        printf("%c = ", character + 'A'); //print the letters
        printf("%d\t", counter[i]);       //print the value stored on the appropriate place in the array
        printf("%c = ", character + 'A');
        printf("%d\n", counter[i + 1]);
    }
}
