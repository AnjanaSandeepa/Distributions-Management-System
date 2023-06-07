#include <stdio.h>
#include <stdlib.h>

//global variable declaration
extern int salesmanName_size;
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

void input_unloading_details(char *salesman_name[salesmanName_size], int *item_id,int *quantity)
{
    //variable declaration and create array
    char message[message_size];
    int count=0;
    int i=0;
    int temp_item_id=0;
    int temp_quantity = 0;

    //set file Pointer
    FILE *load;

    //Open the load file
    load = fopen("load.dat","a+");

    //Call the fileLine_count() function in the additional.c file
    //then set the number of lines in the LOAD_FILE, to the count variable
    count = fileLine_count(load);

    //create structure array and variables
    struct delivery loadDetails[count];
    struct delivery load_details;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and fill data to array
    rewind(load);
    while(fscanf(load,"%d %d %d %s %d %s %lf %d\n",&load_details.year,&load_details.month,&load_details.day,load_details.salesman_name,&load_details.item_id,load_details.item_name,&load_details.price,&load_details.quantity)!=EOF)
    {
            loadDetails[i].year        = load_details.year;
            loadDetails[i].month       = load_details.month;
            loadDetails[i].day         = load_details.day;
            strcpy(loadDetails[i].salesman_name,load_details.salesman_name);
            loadDetails[i].item_id     = load_details.item_id;
            strcpy(loadDetails[i].item_name,load_details.item_name);
            loadDetails[i].price       = load_details.price;
            loadDetails[i].quantity    = load_details.quantity;
         i++;
    }
    //close the stock file
    file_closer(load);

    system("cls");
    system("COLOR 0");

    //display the loading panel
    printf("\n\t\t                    ***********************************");
    printf("\n\t\t                    *            Unload               *");
    printf("\n\t\t                    ***********************************\n\n");

    printf("\n             ... LOADING DITAILES ...  \n");
    printf("\n\t\t          ______________________________________________________________");
    printf("\n\t\t         | salesman name |   Item Id    |   Item name   | load quantity |");
    printf("\n\t\t         |_______________|______________|_______________|_______________|");


    //Display loading item details
    for(int j=0; j<count; j++)
    {
        printf("\n\t\t         |%10s     |%10d    |%10s     |%10d     |",loadDetails[j].salesman_name,loadDetails[j].item_id,loadDetails[j].item_name,loadDetails[j].quantity);
    }
    printf("\n\t\t         |_______________|______________|_______________|_______________|\n");
    printf("                         unload quantity must be less than or equal loading quantity \n\n");

    /**< ---------  salesman validation  ------------ */

        // if salesman not found, navigate again to get the user input
        //goto function call in Line 110
        try_again:

        //get user input and set it to salesman_name variable
        printf("  * Enter the salesman name      :");
        scanf("%s",salesman_name);

        //check salesman is exists
        for(int j=0; j<count; j++)
        {
            //check salesman exist in loading details
            if(strcmp(loadDetails[j].salesman_name,salesman_name)==0)
            {
                goto select_item;
            }
        }

        //salesman does not exist, navigate again to get the user input
        //goto recapture salesman to Line 88
        printf("  wrone salesman name\n");
        goto try_again;


    /**< ---------  item id validation  ------------ */

        //if salesman found, skip to item
        //goto function call in Line 106
        //enter and select item
        select_item:

        //get a user input for item_id
        //Call int_input() function in the additional.c file to check whether the input is integer
        strcpy(message,"  * Enter the item ID            ");
        temp_item_id = int_input(message);
        *item_id = temp_item_id;

        //check item validity
        for(int j=0; j<count; j++)
        {
            //check the salesman is exist
            if(strcmp(loadDetails[j].salesman_name,salesman_name)==0)
            {
                //check item is exist
                if(loadDetails[j].item_id == temp_item_id)
                {
                    //if item found, skip to get the quantity from user
                    //goto recapture quantity to Line 158
                    printf("  * Item name is                 :%s\n",loadDetails[j].item_name);
                    goto get_quntity;
                }
            }
        }
        // if item not found, navigate again to get the user input
        //goto recapture item id to Line 122
        printf("  wrong item id\n");
        goto select_item;


    /**< ---------  quantity validation  ------------ */

        //enter and check quantity
        get_quntity:

        //get a user input for item_id
        //Call int_input() function in the additional.c file to check whether the input is integer
        strcpy(message,"  * Enter the quantity of ITEM   ");
        temp_quantity = int_input(message);
        *quantity = temp_quantity;

    //check quantity
    for(int j=0; j < count; j++)
    {
        //check item id
        if(strcmp(loadDetails[j].salesman_name,salesman_name)==0)
        {
            //check item
            if(loadDetails[j].item_id== temp_item_id)
            {
                //unload quantity must be less than or equal loading quantity
                if(loadDetails[j].quantity < temp_quantity)
                {
                    // if the entered quantity does not exist, navigate again to get the user input
                    //call goto_function  to Line 154
                    printf("Invalid Quantity... \n\n");
                    goto get_quntity;
                }
            }
        }
    }
}


void unloading()
{
    //variable declaration
    int stock_count = 0;
    int Load_count = 0;
    double subtotal = 0.0;
    char message[message_size];
    int i=0;
    int k=0;
    int j=0;
    int option,choice;

    //set file Pointer
    FILE *load, *stock, *sales;

    //Open the stock and load files
    stock=fopen("stock.dat","r");
    load=fopen("load.dat","a+");

    //Call the fileLine_count() function in the additional.c file
    //then set the number of lines in the stock and load files, to the stock_count and load_count variables
    stock_count = fileLine_count(stock);
    Load_count = fileLine_count(load);

    //structure to store unloading and stock details and create arrays
    struct delivery unload_ditails;
    struct delivery stock_details;
    struct delivery sell_details;
    struct delivery load_details;
    struct delivery stockDitails[stock_count];
    struct delivery unloadDitails[Load_count];
    struct delivery loadDetails[Load_count];

    stockDitails[0].item_id      =0;
    unloadDitails[0].quantity    =0;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and get data to array
    rewind(stock);
    while(fscanf(stock,"%d %s %lf %d",&stock_details.item_id,stock_details.item_name,&stock_details.price,&stock_details.quantity)!=EOF)
    {
            stockDitails[i].item_id      = stock_details.item_id;
            strcpy(stockDitails[i].item_name,stock_details.item_name);
            stockDitails[i].price        = stock_details.price;
            stockDitails[i].quantity     = stock_details.quantity;
         i++;
    }
    //close the stock file
    file_closer(stock);


    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and fill data to array
    rewind(load);
    while(fscanf(load,"%d %d %d %s %d %s %lf %d\n",&load_details.year,&load_details.month,&load_details.day,load_details.salesman_name,&load_details.item_id,load_details.item_name,&load_details.price,&load_details.quantity)!=EOF)
    {
            loadDetails[j].year        = load_details.year;
            loadDetails[j].month       = load_details.month;
            loadDetails[j].day         = load_details.day;
            strcpy(loadDetails[j].salesman_name,load_details.salesman_name);
            loadDetails[j].item_id     = load_details.item_id;
            strcpy(loadDetails[j].item_name,load_details.item_name);
            loadDetails[j].price       = load_details.price;
            loadDetails[j].quantity    = load_details.quantity;
         j++;
    }
    //close the load file
    file_closer(load);



    /**< ---------    unloading calculation     ------------ */

    //to unload again
    //goto function call in Line 281
    unload_again:

    // call the input_unloading_details() function and get data
    input_unloading_details(&unload_ditails.salesman_name, &unload_ditails.item_id, &unload_ditails.quantity);

    //unloading details stores to the unloadDetails[] array
    strcpy(unloadDitails[k].salesman_name,unload_ditails.salesman_name);
    unloadDitails[k].item_id      = unload_ditails.item_id;
    unloadDitails[k].quantity     = unload_ditails.quantity;
    /** meke nawata nawata unload karaddi k wadi wewi array ekata data da gannawa
     */
    k++;

    //update the stock details array
    for(int j=0; j<k; j++)
    {
        for(int i=0; i< stock_count; i++)
        {
            if(unloadDitails[j].item_id== stockDitails[i].item_id)
            {
                //edit the stock item quantity
                stockDitails[i].quantity = (stockDitails[i].quantity + unloadDitails[j].quantity);
            }
        }
    }


    /**< ---------   unloading sub menu     ------------ */

    //get user input again
    //goto function call in Line 353
    try_again:

    //display unloading sub menu
    printf("\n\n\n\t\tEnter 0 unload item again\n");
    printf("\n\n\n\t\tEnter 1 unload complete\n");

    //get the user input for item_id
    //Call int_input() function in the additional.c file to check whether the input is an integer
    strcpy(message,"Enter your choice");
    option = int_input(message);

    if(option ==0)
    {
        goto unload_again;
    }

    else if(option == 1)
    {
        /**
        *  calculate_sales_report
        *  updated stock file generat
        *  sales report is generated
        *  unloading files will be deleted
        */

        //Call the file_closer() and file_remover() function in the additional.c file for close the file and delete the file
        file_remover("load.dat",load);

        //Call the file_remover() functions in the additional.c file for close the files and delete the files
        file_remover("stock.dat",stock);

        //Open the stock file to read and append
        stock=fopen("stock.dat","a+");

        //update stock details
        for(int i=0; i< stock_count; i++)
        {
            //write the updated stock data stock file
            fprintf(stock,"%d %s %lf %d\n",stockDitails[i].item_id,stockDitails[i].item_name,stockDitails[i].price,stockDitails[i].quantity);
        }

        //close the stock file
        file_closer(stock);


        //Open the stock and load file
        sales=fopen("sales.dat","a+");

        //using the load array and get data
         for(int n=0; n<Load_count; n++)
         {
            printf("3");
            //get unload details
            for(int j=0; j< k; j++)
            {
                //check salesman id, item id in salesman details and load details
                if(strcmp(loadDetails[n].salesman_name,unloadDitails[j].salesman_name)==0 && loadDetails[n].item_id==unloadDitails[j].item_id )
                {
                    //calculate the the quantity by deducting unloading quantity by loading quantity
                    sell_details.quantity = loadDetails[n].quantity - unloadDitails[j].quantity;
                }
                else
                {
                    //otherwise, quantity is same
                    sell_details.quantity = loadDetails[n].quantity;
                }
            }
            //calculate sub total
            subtotal=sell_details.quantity*loadDetails[n].price;

            //sales details saved to sales file
            fprintf(sales,"%d %d %d %s %d %s %lf %d %lf\n",loadDetails[n].year,loadDetails[n].month,loadDetails[n].day, loadDetails[n].salesman_name,loadDetails[n].item_id,loadDetails[n].item_name,loadDetails[n].price,sell_details.quantity,subtotal);
        }
        //close the sales files
        fclose(sales);

        printf("\n unloding successfully");
    }

    else
    {
        // if it is an invalid input, navigate again to get the user input
        //goto recapture input to Line 271
        printf("\nInvalid input !\a");
        goto try_again;
    }

    /**< ----------  navigation section  ------------ */

    //get user input again
    //goto function call in Line 376
    retry:

    printf("\n\t 0. go to menu");

    //Call int_input() function in the additional.c file to check whether the input is integer
    strcpy(message,"\n\n   * enter your choice ");
    choice = int_input(message);

    if(choice == 0)
    {
        menu();
    }
    else
    {
        // if invalid input, navigate again to get the user input
        // goto recapture input to Line 247
        printf("\nInvalid input !\a");
        goto retry;
    }
}
