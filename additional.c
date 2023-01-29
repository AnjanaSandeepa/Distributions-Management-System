#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

//global variable declaration
extern int message_size;

struct delivery
{
    int item_id;
    char item_name[50];
    int quantity;
    char salesman_name[50];
    char vehicele_id[50];
    double price;
    double subtotal;
};

//for use to delay the user in few seconds
void waiting()
{
    for(int i=0; i<=5; i++)
    {
        Sleep(500);
        printf(". ");
    }
    printf("\n");
}

//for use to get date
void get_date(int *year, int *month, int *day)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year +1900;
    *month = tm.tm_mon + 1;
    *day = tm.tm_mday;
}

/*
//for use to check whether the user input is a double
double double_input(char message[message_size])
{
    char buffer[100];
    double value;
    char *endptr;

    printf("%s:",message);
	value = scanf("%lf", &input);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return -1;
    //Unexpected error
    }
    value = strtod(buffer, &endptr);

    if ((*endptr == '\0') || (isspace(*endptr) != 0))
    {
        printf("It's float: %f\n", value);
    }
    else
    {
        printf("It's NOT float ...\n");
    }
}
*/

//for use to check whether the user input is an integer
int int_input(char message[message_size])
{
	int input, temp, status;

	printf("%s:",message);
	status = scanf("%d", &input);
	while(status!=1){
		while((temp=getchar()) != "" && temp != '\n');
		printf("Invalid input... \n\n  * please enter valid number: ");
		status = scanf("%d", &input);
	}
	return input;
}

//for use to count the lines of the files
int fileLine_count( FILE *const fin )
{
    int ch = 0;
    int lines =0;

    while(!feof(fin))
    {
        ch = fgetc(fin);
        if(ch == '\n')
        {
            lines++;
        }
    }
    return lines;
}

//for use to check the file is closed
//if not, close the files
void file_closer(const FILE *file)
{
    char message[message_size];
    int input = 0;

    fclose(file);

    try:

    input = 0;

    if (ftell(file) >= 0 )
    {
        printf(" -> File can't closed\n ");

        printf("\t try again closing     -   1 \n");
        printf("\t exit                  -   0 \n");

        strcpy(message,"\n\n   * enter your choice ");
        input = int_input(message);

        if(input == 1)
        {
            fclose(file);
            file = NULL;
            Sleep(10);
        }
        else if(input == 0)
        {
            exit(0);
        }
        else
        {
            printf("\n invalid input...\n");
            Sleep(10);
            goto try;
        }
        goto try;
    }
    else
    {
        file = NULL;
    }
}

//for use to check the file is removed
//if not, remove the files
void file_remover(const char *filename, const FILE *file)
{
    char message[message_size];
    int input;

    fclose(file);
    file_closer(file);

    remove(filename);

    check:

    input = 0;

    if(access(filename, F_OK) == 0)
    {
        try:

        printf("\t\n some error... can't update file\n\n");

        printf("\t try again removing                -   1 \n");
        printf("\t try again file close              -   2 \n");
        printf("\t exit (it can damage your file)    -   0 \n");

        strcpy(message,"\n\n   * enter your choice ");
        input = int_input(message);

        if(input == 1)
        {
            remove(filename);
            Sleep(10);
        }
        else if(input == 2)
        {
            file_closer(file);
        }

        else if(input == 0)
        {
            exit(0);
        }
        else
        {
            printf("\n invalid input...\n");
            Sleep(10);
            goto try;
        }
        goto check;
    }
    else
    {
        filename = NULL;
    }
}

void exit_system()
{
    system("cls");
    system("COLOR 03");

    printf("thanks");

    //call the exit() function to exit the system
    exit(0);

}




