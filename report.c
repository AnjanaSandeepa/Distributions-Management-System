#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//global variable declaration
extern int YEAR,MONTH,DAY;
extern int message_size;

struct delivery
{
    int item_id;
    char item_name[50];
    int quantity;
    char salesman_name[50];
    double price;
    double subtotal;
    int year;
    int month;
    int day;
};

// display report sub menu, and reports
void report_menu()
{
    system("cls");
    system("COLOR 06");

    int choice;
    char message[message_size];

    printf("\n\n\n");
    printf("\n                                      *********************************** ");
    printf("\n                                      *       XYZ DISTRIBUTIONS         * ");
    printf("\n                                      *********************************** \n");

    //capture report options
    printf("\n                   ... Sales Reports ...\n\n");

    printf("\n         1.Display stock");
    printf("\n         2.daily sales report");
    printf("\n         3.Monthly sales Report");
    printf("\n         4.Progress of item");
    printf("\n         5.Progress of salesman");
    printf("\n         6.go to back");
    printf("\n\n");

    //goto function call
    //if user enter an invalid input,navigate again to get the user input
    try_again:

    //Call int_input() function in the additional.c file to check whether the input is integer
    strcpy(message,"\n    * enter your choice ");
    choice = int_input(message);

    switch(choice)
    {
        case 1:
            //display stock items
            display_stock();
            break;

        case 2:
            //display sales by all date
            full_sales_repoat();
            break;

        case 3:
            //display monthly sales by salesman vehicle id and date
            monthly_sales_report();
            break;
        case 4:
            //display progress of sales item using tabular and graphical (bar charts)
             progress_of_item();
            break;

        case 5:
            //display progress of salesman using tabular and graphical (bar charts)
            progress_of_salesman();
            break;

        case 6:
            //Call the menu function to Display main menu
            menu();
            break;

        default:
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            printf("Invalid input...\n ");

            //call goto_function
            goto try_again;
    }
}



void display_stock()
{
    system("cls");
    system("COLOR 06");

    int choice;
    char message[message_size];

    //delivery structure use to capture and store
    struct delivery view;

    //pointer to stock file
    FILE *stock;

    //open stock file(Open for reading.)
    stock = fopen("stock.dat","r+");

    printf("\n");
    printf("\n                             *********************************** ");
    printf("\n                             *       XYZ DISTRIBUTIONS         * ");
    printf("\n                             *********************************** \n\n");

    printf("\n                ...MAIN STOCK DITAILS...\n\n");

    printf("\n         ________________________________________________________________");
    printf("\n         |    item Id    |   item name   |   Item price  | Item Quantity |");
    printf("\n         |_______________|_______________|_______________|_______________|");


    //read the stock and display
    rewind(stock);
    while(fscanf(stock,"%d %s %lf %d\n",&view.item_id,view.item_name,&view.price,&view.quantity)!=EOF)
    {
        printf("\n         |%10d     |%10s     |   %10.2lf  | %10d    |",view.item_id,view.item_name,view.price,view.quantity);
    }
        printf("\n         |_______________|_______________|_______________|_______________|");


    //close stock file
    fclose(stock);

    printf("\n\n\t 1. item add to stock");
    printf("\n\t 2. update stock item quantity");
    printf("\n\t 3. go to back");

    try_again:

    //Call the int_input() function in the additional file to set a validate integer number to the variable
    strcpy(message,"\n\n   * enter your choice ");
    choice = int_input(message);

    if(choice == 1)
    {
        add_item();
    }
    else if(choice == 2)
    {
        update_stock();
    }
    else if(choice == 3)
    {
        //menu options menu
        menu();
    }
    else
    {
        //if the user enter invalid input, delay few seconds and navigate again to get the user input
        printf("Invalid input... ");

        //call goto_function
        goto try_again;
    }
}



//Implementation of "daily_sales_report" function
void full_sales_repoat()
{
    system("cls");
    system("COLOR 06");

    int choice;
    int year,month,day;

    char message[message_size];
    struct delivery sel;

    FILE *sales;

    sales=fopen("sales.dat","r+");

        printf("\n");
        printf("\n                             *********************************** ");
        printf("\n                             *       XYZ DISTRIBUTIONS         * ");
        printf("\n                             *********************************** \n\n");

        printf("\n          ...DAILY SALES DITAILS...\n\n");

        printf("    ____________________________________________________________________________________________________\n");
        printf("    |year/month/day|salesman name|   Item ID   |  item name  |  Item price |Item Quantity|    total    |\n");
        printf("    |______________|_____________|_____________|_____________|_____________|_____________|_____________|\n");

        while(fscanf(sales,"%d %d %d %s %d %s %lf %d %lf\n",&year,&month,&day,sel.salesman_name,&sel.item_id,sel.item_name,&sel.price,&sel.quantity,&sel.subtotal)!=EOF)
        {
            printf("    |  %0.4d/%0.2d/%0.2d  |%10s   |%10d   |%10s   | %10.2lf  |%10d   | %10.2lf  |\n",year,month,day,sel.salesman_name,sel.item_id,sel.item_name,sel.price,sel.quantity,sel.subtotal);
            printf("    |______________|_____________|_____________|_____________|_____________|_____________|_____________|\n");
        }

    fclose(sales);

    /**< ----------  navigation section  ------------ */

    printf("\n\t 1. go to Report menu");

    //get user input again
    //goto() function call
    Invalid_input:

    //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
    strcpy(message,"\n\n   * enter your choice ");
    choice = int_input(message);

    if(choice == 1)
    {
        report_menu();
    }
    else
    {
        //if the user enter invalid input, navigate again to get the user input
        // goto recapture input
        printf("Invalid input... ");
        goto Invalid_input;
    }
}


void monthly_sales_report()
{
    int count =0;
    int check_year=0;
    int check_month=0;
    char input_salesman_name[50];
    char message[message_size];
    int choice;
    double total = 0.0;

    //set file Pointer
    FILE *sales ;

    //Open the sale file
    sales=fopen("sales.dat","r+");

    //Call the fileLine_count() function in the additional_FILE to to set a SIZE OF STOCK_FILE to the COUNT variable
    count = fileLine_count(sales);

    //create struct arrays
    struct delivery selesDetails[count];
    struct delivery seles_details;
    int i=0;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and get data to array
    rewind(sales);
    while(fscanf(sales,"%d %d %d %s %d %s %lf %d %lf\n",&seles_details.year,&seles_details.month,&seles_details.day,seles_details.salesman_name,&seles_details.item_id,seles_details.item_name,&seles_details.price,&seles_details.quantity,&seles_details.subtotal)!=EOF)
    {

        selesDetails[i].year       = seles_details.year;
        selesDetails[i].month      = seles_details.month;
        selesDetails[i].day        = seles_details.day;
        strcpy(selesDetails[i].salesman_name,seles_details.salesman_name);
        selesDetails[i].item_id    = seles_details.item_id;
        strcpy(selesDetails[i].item_name,seles_details.item_name);
        selesDetails[i].price      = seles_details.price;
        selesDetails[i].quantity   = seles_details.quantity;
        selesDetails[i].subtotal   = seles_details.subtotal;

        i++;
    }
    //close the stock file
    fclose(sales);

    getDateAgin:

    //get user input again
    //goto() function call in Line 105
    Invalid_input2:


    system("cls");
    system("COLOR 06");

    printf("\n\n");
    printf("                              ***********************************\n");
    printf("                              *         XYZ DISTRIBUTORS        *\n");
    printf("                              ***********************************\n\n");

     //input date
     printf("\t...monthly sales report ...\n\n");

     //Call the int_input() function in the additional_FILE to set a integer number to the variable
     printf("\t ENTER DATE...\n\n");
     strcpy(message,"  * year(YYYY)");
     check_year = int_input(message);

     strcpy(message,"  * month(MM) ");
     check_month = int_input(message);

    system("cls");
    system("COLOR 06");

    //display sales report availeble vehicle
    printf("\n\n");
    printf("                              ***********************************\n");
    printf("                              *         XYZ DISTRIBUTORS        *\n");
    printf("                              ***********************************\n\n\n");


        printf("        ...Availeble vehicle...\n\n");

        printf("                          _________________\n");
        printf("                          | salesman name |\n");
        printf("                          |_______________|\n");

    //read sales file and show vehicle id's with salesman name
    for(int j=0; j<count; j++)
    {
        if(selesDetails[j].year ==check_year && selesDetails[j].month == check_month)
        {
            printf("                          |%10s     |\n", selesDetails[j].salesman_name);
            break;
        }
    }
        printf("                          |_______________|\n");
        printf("\n           IF NOT DATA IN TABLE PLEACE ENTER VALID DATE !\n\n");



    /**< ----------  navigation section  ------------ */

    printf("\n\t 1. enter date again");
    printf("\n\t 2. go to next");
    printf("\n\t 3. go to back");

    Invalid_input_1:

    //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
    strcpy(message,"\n\n  * enter your choice ");
    choice = int_input(message);

    if(choice == 1)
    {
        goto getDateAgin;
    }
    if(choice == 2)
    {
        //enter and check vehicle id
        salesman_again:

        printf("  * Enter the salesman name :");
        scanf("%s",input_salesman_name);

        //read sales file
        for(int j=0; j<count; j++)
        {
            //check vehicle id exist
            if(strcmp(selesDetails[j].salesman_name,input_salesman_name)==0)
            {
                //stop reading sales file
                goto next;
            }
        }

        //get vehicle id again
        printf("wrone salesman name\n");
        goto salesman_again;
    }
    if(choice == 3)
    {
        report_menu();
    }
    else
    {
        //if the user enter invalid input, navigate again to get the user input
        // goto recapture input
        printf("Invalid input... ");
        goto Invalid_input_1;
    }

    next:

    invalid:


    system("cls");
    system("COLOR 06");

    printf("\n                               ********************************** ");
    printf("\n                               *   ...monthly sales report...   * ");
    printf("\n                               ********************************** \n");

    printf("\n  Salesman name is   :%s",input_salesman_name);
    printf("\n  Date               :%d /%d",check_year,check_month);

                printf("\n                                                                                                        ");
                printf("\n         ______________________________________________________________________________________________ ");
                printf("\n         |    Day    |    Item ID    |   item name   |   Item price  | Item Quantity |   subtotal     |");
                printf("\n         |___________|_______________|_______________|_______________|_______________|________________|");

    for(int j=0; j<count; j++)
    {
        //check year and month
        if(check_year == selesDetails[j].year && check_month == selesDetails[j].month)
        {
            //check vehicle id's are equal
            if(strcmp(input_salesman_name,selesDetails[j].salesman_name)==0)
            {
                //get grand total by calculating sub total of sales item
                total += selesDetails[j].subtotal;

                printf("\n         | %5d     |%10d     |%10s     |  %10.2lf   |%10d     |%15.2lf |",selesDetails[j].day,selesDetails[j].item_id,selesDetails[j].item_name,selesDetails[j].price,selesDetails[j].quantity,selesDetails[j].subtotal);
                printf("\n         |___________|_______________|_______________|_______________|_______________|________________|");

            }
        }
    }
                 printf("\n         |                                       TOTAL                               |%15.2lf |",total);
                 printf("\n         |__________________________________________________________________________ |________________|");



    /**< ----------  navigation section  ------------ */

    printf("\n\n 1. go to back");

    //get user input again
    //goto() function call in Line 105
    Invalid_input_2:

    //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
    strcpy(message,"\n\n   * enter your choice ");
    choice = int_input(message);

    if(choice == 1)
    {
        report_menu();
    }
    else
    {
        //if the user enter invalid input, delay few seconds and navigate again to get the user input
        // goto recapture input to Line 72
        printf("Invalid input... ");
        goto Invalid_input_2;
    }
}














//display sales by item in tabular and graphical format
void progress_of_item()
{
    int seles_count = 0;
    int stock_count = 0;
    bool has_items ;
    int total_quantity = 0;
    int n=0;
    int option,choice1,choice2;
    char message[message_size];

    //set file Pointer
    FILE *sales, *stock;

    //Open the stock file
    stock=fopen("stock.dat","a+");

    //Open the sale file
    sales=fopen("sales.dat","a+");

    //Call the fileLine_count() function in the additional_FILE to to set a SIZE OF Sales_FILE to the COUNT variable
    seles_count = fileLine_count(sales);

    //Call the fileLine_count() function in the additional_FILE to to set a SIZE OF STOCK_FILE to the COUNT variable
    stock_count = fileLine_count(stock);

    //close the stock file
    fclose(stock);

    //create struct arrays
    struct delivery item_data[stock_count];
    struct delivery selesDetails[seles_count];

    struct delivery seles_details;
    int i=0;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and get data to array
    rewind(sales);
    while(fscanf(sales,"%d %d %d %s %d %s %lf %d %lf\n",&seles_details.year,&seles_details.month,&seles_details.day,seles_details.salesman_name,&seles_details.item_id,seles_details.item_name,&seles_details.price,&seles_details.quantity,&seles_details.subtotal)!=EOF)
    {
        selesDetails[i].year      = seles_details.year;
        selesDetails[i].month      = seles_details.month;
        selesDetails[i].day      = seles_details.day;
        strcpy(selesDetails[i].salesman_name,seles_details.salesman_name);
        selesDetails[i].item_id      = seles_details.item_id;
        strcpy(selesDetails[i].item_name,seles_details.item_name);
        selesDetails[i].price        = seles_details.price;
        selesDetails[i].quantity      = seles_details.quantity;
        selesDetails[i].subtotal        = seles_details.subtotal;

        i++;
    }
    //close the stock file
    fclose(sales);

    for(int m = 0; m < seles_count; m++)
    {
        bool found = false;

        //check if item exist in array
        for (int k = 0; k < stock_count; k++)
        {
            if(item_data[k].item_id == selesDetails[m].item_id)
            {
                //edit records, if item already exist
                item_data[k].quantity = item_data[k].quantity + selesDetails[m].quantity;
                found = true;
                break;
            }
        }
        //add sales details to array
        if (found == false)
        {
            item_data[n].item_id = selesDetails[m].item_id;
            strcpy(item_data[n].item_name,selesDetails[m].item_name);
            item_data[n].quantity = selesDetails[m].quantity;
            n++;
        }

         total_quantity = total_quantity + selesDetails[m].quantity;
    }

    system("cls");
    system("COLOR 06");

    printf("\n                              ***********************************");
    printf("\n                              *      progress of a item         *");
    printf("\n                              ***********************************");

    printf("\n\n\n         1.progress of a item in tabular form.   ");
    printf("\n         2.progress of a item in graphs.");
    printf("\n         3.go to back");

    next:

    //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
    strcpy(message,"\n\n   * enter your choice ");
    option = int_input(message);


    if(option==1)
    {
        system("cls");
        system("COLOR 06");

        printf("\n                               ***********************************");
        printf("\n                               *        progress of a item       *");
        printf("\n                               ***********************************");

        printf("\n\n     progress of a item in tabular form ...\n");

        printf("\n              _________________________________________________");
        printf("\n              |    Item id    |   item name   | Total quantity |");
        printf("\n              |_______________|_______________|________________|");

        for (i = 0; i < stock_count; i++)
        {
            printf("\n              |%10d     |%10s     |  %10.0d    |", item_data[i].item_id, item_data[i].item_name, item_data[i].quantity);
        }
            printf("\n              |_______________|_______________|________________|\n\n\n");


        /**< ----------  navigation section 1 ------------ */

        printf("    1.go to back:");

        //get user input again
        //goto() function call in Line 105
        Invalid_input1:

        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n   * enter your choice ");
        choice1 = int_input(message);

        if(choice1 == 1)
        {
            progress_of_item();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            // goto recapture input to Line 72
            printf("Invalid input...");
            goto Invalid_input1;
        }
    }
    else if(option == 2)
    {
        system("cls");
        system("COLOR 06");

        printf("\n                               ***********************************");
        printf("\n                               *       progress of a item        *");
        printf("\n                               ***********************************");

        printf("\n\n\t progress of a item in graph");

        printf("\n\n\n\t    0            25            50            75           100");
        printf("\n            \xDA\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\x3E  PERCENTAGE");


        for (int i = 0; i< stock_count; i++)
        {
            printf("\n %10s \xB3",item_data[i].item_name);

             double v = 0;
             v = (double)item_data[i].quantity/total_quantity;

            //calculate the percentage of quantity
            for (int j = 0; j < v*100; j++)
            {
                printf("\xb2");
            }
            printf("\n            \xB3");
        }
        printf("\n         ITEM NAME\n\n");

        /**< ----------  navigation section 2 ------------ */

        printf("    1.go to back:");


        //get user input again
        //goto() function call in Line 105
        Invalid_input2:

        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n   * enter your choice ");
        choice2 = int_input(message);

        if(choice2 == 1)
        {
            progress_of_item();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            // goto recapture input to Line 72
            printf("Invalid input... ");
            goto Invalid_input2;
        }
    }
    else if(option == 3)
    {
        report_menu();
    }
    else
    {
        //if the user enter invalid input, delay few seconds and navigate again to get the user input
        // goto recapture input to Line 506
        printf("Invalid input... ");
        goto next;;
    }
}






















//display salesman progress
//display in tabular and graphical format
void progress_of_salesman()
{

    int sales_count = 0;
    bool found;
    double total_subtotal = 0.0;
    int n= 0;
    int i=0;
    int option,choice1,choice2 = 0;
    char message[message_size];
    double percentage = 0.0;

    //set file Pointer
    FILE *sales;

    //Open the sale file
    sales=fopen("sales.dat","r+");

    //Call the fileLine_count() function in the additional_FILE to to set a SIZE OF Sales_FILE to the COUNT variable
    sales_count = fileLine_count(sales);

    //create structure arrays
    struct delivery salesman_data[sales_count];
    struct delivery selesDetails[sales_count];

    struct delivery seles_details;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and get data to array
    rewind(sales);
    while(fscanf(sales,"%d %d %d %s %d %s %lf %d %lf\n",&seles_details.year,&seles_details.month,&seles_details.day,seles_details.salesman_name,&seles_details.item_id,seles_details.item_name,&seles_details.price,&seles_details.quantity,&seles_details.subtotal)!=EOF)
    {
        selesDetails[i].year      = seles_details.year;
        selesDetails[i].month     = seles_details.month;
        selesDetails[i].day       = seles_details.day;
        strcpy(selesDetails[i].salesman_name,seles_details.salesman_name);
        selesDetails[i].item_id   = seles_details.item_id;
        strcpy(selesDetails[i].item_name,seles_details.item_name);
        selesDetails[i].price     = seles_details.price;
        selesDetails[i].quantity  = seles_details.quantity;
        selesDetails[i].subtotal  = seles_details.subtotal;

        i++;
    }
    //close the stock file
    fclose(sales);

    for(int m = 0; m < sales_count; m++)
    {
        found = false;

        //check if item exist in array
        for (int k = 0; k < sales_count; k++)
        {
            if(strcmp(salesman_data[k].salesman_name,selesDetails[m].salesman_name)== 0)
            {
                //edit records, if item already exist
                salesman_data[k].subtotal = salesman_data[k].subtotal + selesDetails[m].subtotal;
                found = true;
                break;
            }
        }
        //add sales details to array
        if (found == false)
        {
            strcpy(salesman_data[n].salesman_name,selesDetails[m].salesman_name);
            salesman_data[n].subtotal = selesDetails[m].subtotal;
            n++;
        }
        total_subtotal = total_subtotal + selesDetails[m].subtotal;
    }

     system("cls");
     system("COLOR 06");


     printf("\n                               ***********************************");
     printf("\n                               *      progress of a salesman     *");
     printf("\n                               ***********************************");

     printf("\n\n\t1. progress of a salesman in tabular form.   ");
     printf("\n\t2. progress of a salesman in graphs.");
     printf("\n\t3. go to back");

     next:

     //Call int_input() function in the additional.c file to check whether the input is integer
     strcpy(message,"\n\n   * enter your choice ");
     option = int_input(message);



     if(option==1)
     {
        system("cls");
        system("COLOR 06");

        printf("\n                               ***********************************");
        printf("\n                               *        progress of a salesman   *");
        printf("\n                               ***********************************");

        printf("\n\n progress of a salesman in tabular form ...\n");

        printf("\n              __________________________________");
        printf("\n              | salesman name |   Total price  |");
        printf("\n              |_______________|________________|");

        for (int j = 0; j < n; j++)
        {
            printf("\n              |%10s     |  %10.2lf    |", salesman_data[j].salesman_name, salesman_data[j].subtotal);
        }
        printf("\n              |_______________|________________|\n");


        /**< ----------  navigation section 1 ------------ */

        printf("\n      1.go to back:\n");

        //get user input again
        //goto() function call
        Invalid_input1:

        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n* enter your choice ");
        choice1 = int_input(message);

        if(choice1 == 1)
        {
            progress_of_salesman();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            // goto recapture input
            printf("Invalid input... ");
            goto Invalid_input1;
        }
    }
    else if(option == 2)
    {
        system("cls");
        system("COLOR 06");

        printf("\n                               ***********************************");
        printf("\n                               *       progress of a salesman        *");
        printf("\n                               ***********************************");

        printf("\n\n progress of a salesman in graph ...");

        printf("\n\n\t                                                                                                   PERCENTAGE(%%)\n");
        printf("\n\t    00                       25                       50                       75                      100");
        printf("\n            \xDA\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\x3E");


        for(int i = 0; i< n; i++)
        {
            printf("\n %10s \xB3",salesman_data[i].salesman_name);

             percentage = salesman_data[i].subtotal/total_subtotal;

            //calculate the percentage of quantity
            for (int j = 0; j < percentage*100; j++)
            {
                printf("\xb2");
            }
            printf("\n            \xB3");
        }
        printf("\n         SALESMAN NAME");

        /**< ----------  navigation section 2 ------------ */

        printf("\n\n1.go to back:");

        //get user input again
        //goto() function call in Line 105
        Invalid_input2:

        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n   * enter your choice ");
        choice2 = int_input(message);

        if(choice2 == 1)
        {
            progress_of_salesman();
        }
        else
        {
            //if the user enter invalid input, navigate again to get the user input
            // goto recapture input
            printf("Invalid input... ");
            goto Invalid_input2;
        }
    }
    else if(option == 3)
    {
        report_menu();
    }
    else
    {
        //if the user enter invalid input,navigate again to get the user input
        // goto recapture input
        printf("Invalid input... ");
        goto next;
    }
}


