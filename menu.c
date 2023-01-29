//global variable declaration
extern int message_size;

void menu()
{
    system("cls");
    system("COLOR 11");

    //display logo
    printf("\n\n\n\n\n\n");
    printf(" \t\t\t\t\t     __    __ __    __  ______       \n");
    printf(" \t\t\t\t\t     \\ \\  / / \\ \\  / / |____  |  \n");
    printf(" \t\t\t\t\t      \\ \\/ /   \\ \\/ /      / /   \n");
    printf(" \t\t\t\t\t       |  |     \\  /      / /       \n");
    printf(" \t\t\t\t\t      / /\\ \\     | |     / /___    \n");
    printf(" \t\t\t\t\t     /_/  \\_\\    |_|    |______|   \n");

    printf("\n");
    printf("       _______   ______   _____   _______  _____   _______   _______   _     _  _______  _______   _____   ___    _    \n");
    printf("      |_  __  | |__  __| | ____| |__   __||  _  | |__   __| |_  __  | | |   | ||__   __||__   __| |  _  | |   \\  | |  \n");
    printf("        | | | |    | |   | |___     | |   | |_| |    | |     | |__| | | |   | |   | |      | |    | | | | | |\\ \\ | | \n");
    printf("        | | | |    | |   |____ |    | |   |  _  |    | |     |  __  | | |   | |   | |      | |    | | | | | | \\ \\| | \n");
    printf("       _| |_| |  __| |__  ___| |    | |   | | \\ \\  __| |__  _| |__| | | |___| |   | |    __| |__  | |_| | | |  \\   |\n");
    printf("      |_______| |_______||_____|    |_|   |_|  \\_\\|_______| |_______| |_______|   |_|   |_______| |_____| |_|   \\__|\n");
    printf("\n                                **********************************************************\n");



    //variable declaration
    int choice;
    char message[message_size];

    //display Menu list
    printf("\n\n                     ...MAIN MENU...\n\n");

    printf("\n         1. Manage stock");
    printf("\n         2. Loading");
    printf("\n         3. Unloading");
    printf("\n         4. Sales report ");
    printf("\n         5. LOg out");
    printf("\n\n");

    //goto function call
    //if user enter an invalid input,navigate again to get the user input
    try_again:

    //Call int_input() function in the additional.c file to check whether the input is integer
    strcpy(message," \n  * enter your choice ");
    choice = int_input(message);

    switch(choice)
    {
        case 1:
            //Call the waiting function in the additional.c file to delay few seconds
            printf("\t\t\t\t\t\t\t");
            //waiting();

            //Manage stock
            display_stock();
            break;

        case 2:
            //Call the waiting function in the additional.c file to delay few seconds
            printf("\t\t\t\t\t\t\t");
            //waiting();

            //handle loading
            loading();
            break;

        case 3:
            //Call the waiting function in the additional.c file to delay few seconds
            printf("\t\t\t\t\t\t\t");
            //waiting();

            //handle unloading
            unloading();
            break;

        case 4:
            //Call the waiting function in the additional.c file to delay few seconds
            printf("\t\t\t\t\t\t\t");
            //waiting();

            //report options menu
            report_menu();
            break;

        case 5:
            //call the exit_system() function in the additional.c file to exit the system
            exit_system();
            break;

        default:
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            printf("Invalid input...\n ");

            //call goto_function
            goto try_again;
            break;
    }
}

