#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print();

// Setup structure to store student data.
typedef struct student {

    char FullName[52];

    char studentID[11];

    int MemYear;

} student;

// Abstraction -> break down functionality into functions.
int dataInput();

int dataDelete();

void printDetails();

void saveData();


int main(void) {
    // setup a const for input format.
    const char* inputFormat = "(%[^,], %s , %d)\n";

    // initialise pointer with ten size.
    int peoplecount = 10;

    // initialise variable to keep counts.
    int filecount = 0;


    int input = 0;

    int save;

    // malloc enough size to store 10 structs.
    student* person = malloc(sizeof(student) * peoplecount);

    // open file to read
    FILE* file;
    file = fopen("Data.txt", "r");

    // check if file is empty.
    if (file == NULL) {
        printf("The file contains nothing \n");
    }

    // loop through the file and input into the structure.
    while (feof(file) == 0) {

        //Followed the following guide to help me scan data from the file into structs
        //https://www.youtube.com/watch?v=QrKpqdBiFRI&ab_channel=CodeVault
        
        //scan from the file into the structure.
        fscanf(file, inputFormat, person[filecount].FullName, person[filecount].studentID, &person[filecount].MemYear);

        // increment filecount to store each person as a different array.
        filecount++;

        //malloc more space if people count exceeds 10.
        if (filecount == peoplecount) {
            person = realloc(person, sizeof(student) * filecount);
        }



    }

    fclose(file);

    while (input != 4) {
        // Print options for user
        print();

        //input validate if there is a character at the end of a number
        char inputValidation;

        // Input validation.
        while (scanf(" %d%c", &input, &inputValidation) != 2 || inputValidation != '\n') {
            fflush(stdin);
            printf("You input is invalid, try again!\n");
            print();
        }

        // Open data input function.
        if (input == 1) {

            system("clear");
            filecount = dataInput(person, &person, filecount);


        }

        // Open data delete function.
        if (input == 2) {

            system("clear");
            filecount = dataDelete(person, &person, filecount);



        }

        // Open data print function.
        if (input == 3)
        {
            system("clear");
            printDetails(person, filecount);
        }
    }

    //input validate if there is a character at the end of a number
    char inputValidation;

    // Allow user to save changes.
    printf("Do you wish to save the changes (1/0) ?");

    // Input validation.
    while (scanf(" %d%c", &save, &inputValidation) != 2 || inputValidation != '\n') {
        fflush(stdin);
        system("clear");
        printf("You input is invalid, try again!\n");
        printf("Do you wish to save the changes (1/0) ?");
    }

    if (save == 1) {
        // Save data function.
        saveData(person, filecount);
    }

    // Free memory
    free(person);


    return 0;
}

// Use a function to print the Home Menu
void print() {
    // Print Home Menu for Database

    printf("\n");

    printf("Hello, Welcome to the Programming Club Database!\n\n");

    printf("1 -> Enter some student data \n");

    printf("2 -> Remove some student data \n");

    printf("3 -> Print student data \n");

    printf("4 -> Exit Program \n \n");


    return;
}

// Use this function to input student data.
int dataInput(student* person, student** off_array, int count) {

    //input validate if there is a character at the end of a number
    char inputValidation;

    // Use to start initialise loop.
    int confirm = 1;

    // While user is not finished,keep entering data.
    while (confirm != 0) {

        // Reallocate memory when student size increases.
        // This is done for memory efficiency.
        person = realloc(person, sizeof(student) * (count + 1));

        printf("Enter name: ");

        scanf(" %[^\n]s", person[count].FullName);

        printf("Enter student ID: ");

        scanf(" %[^\n]s", person[count].studentID);

        printf("Enter year of membership: ");

        // Input validation.
        while (scanf(" %d%c", &person[count].MemYear, &inputValidation) != 2 || inputValidation != '\n') {
            fflush(stdin);
            printf("You input is invalid, try again!\n");
            printf("Enter year of membership: ");
        }

        // Prompt user if they want to add more
        printf("Do you wish to add another student (1/0) ?\n");

        // Input validation.
        while (scanf(" %d%c", &confirm, &inputValidation) != 2 || inputValidation != '\n') {
            fflush(stdin);
            printf("You input is invalid, try again!\n");
            printf("Do you wish to add another student (1/0) ?\n");
        }
        // Clear terminal for visibility.
        system("clear");


        // Update student count.
        if (confirm == 1) {
            count = count + 1;
        }
    }

    *off_array = person;

    system("clear");

    // Return updated student count.
    return count + 1;
}



int dataDelete(student* person, student** realPer, int count) {
    int confirm = 1;
    int i = 0;
    int j = 0;
    int occCount = count;
    char compare[11];
    int rem = 0;
    int remYear;

    //input validate if there is a character at the end of a number
    char inputValidation;


    // Repeat until user specifies they no longer want to delete.
    while (confirm != 0) {


        printf("Do you wish to remove students by ID or Year (1/2)?");

        // Input validation.
        while (scanf(" %d%c", &rem, &inputValidation) != 2 || inputValidation != '\n') {
            fflush(stdin);
            printf("You input is invalid, try again!\n");
            printf("Do you wish to remove students by ID or Year (1/2)?");
        }

        // Remove by ID
        if (rem == 1) {

            printf("Enter the student id for the student you wish to remove: ");
            scanf(" %10s", compare);

            // If student ID occurs, we set ID to "0".
            for (i = 0;i < count;i++) {
                if (strcmp(person[i].studentID, compare) == 0) {
                    occCount--;
                    strcpy(person[i].studentID, "0");

                }

            }
        }

        // Remove by Year
        if (rem == 2) {

            printf("Enter the year to remove: ");

            // Input validation.
            while (scanf(" %d%c", &remYear, &inputValidation) != 2 || inputValidation != '\n') {
                fflush(stdin);
                printf("You input is invalid, try again!\n");
                printf("Enter the year to remove: ");
            }


            // If choosen year occurs, we set year to 0. 
            for (i = 0;i < count;i++) {
                if (person[i].MemYear == remYear) {
                    occCount--;
                    person[i].MemYear = 0;;

                }

            }
        }


        // Ask user if they wish to delete.
        printf("Do you wish to delete more (1/0) ?: ");

        // Input validation.
        while (scanf(" %d%c", &confirm, &inputValidation) != 2 || inputValidation != '\n') {
            fflush(stdin);
            printf("You input is invalid, try again!\n");
            printf("Do you wish to delete more (1/0) ?: ");
        }

        // Clear for visibility
        system("clear");

    }

    // Create temporary pointer
    student* temp = malloc(sizeof(student) * (occCount));

    // Loop through structure and copy only those structures which do not have id = 0 or memyear = 0.
    for (i = 0;i < count;i++) {
        if (strcmp(person[i].studentID, "0") != 0 && person[i].MemYear != 0) {
            strcpy(temp[j].studentID, person[i].studentID);
            strcpy(temp[j].FullName, person[i].FullName);
            temp[j].MemYear = person[i].MemYear;
            j++;
        }

    }

    // free our old memory.
    free(person);
    // Point our old pointer at the new temp.
    *realPer = temp;
    // Clear for visibility
    system("clear");
    // Return updated student count.
    return occCount;
}

void printDetails(student* person, int count) {
    int i = 0;
    // Loop through structure and print.
    printf("-------------------Student Details-------------------\n");

    for (i = 0;i < count;i++) {
        printf("%s               %10s               %d\n", person[i].FullName, person[i].studentID, person[i].MemYear);
    }

}

void saveData(student* person, int count) {
    int i;
    const char* outputFormat = "(%s, %s , %d)\n";
    FILE* file;
    file = fopen("Test.txt", "w+");
    // Output to file.
    for (i = 0;i < count;i++) {
        fprintf(file, outputFormat, person[i].FullName, person[i].studentID, person[i].MemYear);
    }

    fclose(file);




}
