#include <stdio.h>
#include <stdlib.h>

//global variable declaration
extern int message_size;

void login()
{
    //variable declaration and create an array
    const char inbuilt_password[10] = "sjp";
    char message[message_size];
    char user_password[10];
    int choice = 0;

    //goto_FUNCTION call in Line 60
    //if invalid password,navigate again to get user input
    log_again:

    system("cls");
    system("COLOR 03");

    printf("\n\n");
    printf("\t\t\t\t\t  *****************************************\n");
    printf("\t\t\t\t\t  ***         XYZ DISTRIBUTORS         ****\n");
    printf("\t\t\t\t\t  *****************************************\n");


    printf("\n\nTEST PROGRAM PASSWORD IS : sjp \n\n");
    printf("\n\n\n\t ENTER LOGIN PASSWORD : ");

    //get the password from user
    scanf("%s",user_password);

    //compare password
    if (strcmp(user_password,inbuilt_password) == 0)
    {
        printf("\n\n   Password Match !");
        printf("\n\n\t\t\t\t\t    WELCOME TO  XYZ DISTRIBUTORS   !");

        //Call the waiting function in the additional.c file to delay few seconds
        waiting();

        //Call the menu() function to Display main menu
        menu();
    }
    else
    {
        printf("\n\n    Wrong password!!\n\n\n\n");

        printf("\n      Enter 1 to try again   ");
        printf("\n      Enter 0 to exit     \n\n");

        //goto function call
        //if the user enter the invalid input, navigate again to get the user input
        try_again:

        //Call int_input() function in the additional.c file to check whether the input is integer
        strcpy(message,"\n    * enter your choice ");
        choice = int_input(message);

        if(choice == 1)
        {
            //call goto_function
            goto log_again;
        }
        else if(choice == 0)
        {
            //call the exit_system() function in the additional.c file to exit the system
            exit_system();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            printf("Invalid input...\n ");

            //Call the waiting function in the additional.c file to delay few seconds
            //waiting();

            //call goto_function
            goto try_again;
        }
    }
}
