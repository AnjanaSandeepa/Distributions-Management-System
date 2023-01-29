#include <stdio.h>
#include <stdlib.h>

//global variable declaration
extern int YEAR,MONTH,DAY;
extern int message_size;
extern int itemName_size;
extern int salesmanName_size;
extern int vehicleId_size;


struct delivery
{
    int item_id;
    char item_name[50];
    int quantity;
    char salesman_name[50];
    double price;
};

void input_loading_details(char *salesman_name[salesmanName_size], int *item_id, char *item_name[itemName_size], double *price, int *quantity)
{

    //variable declaration and create array
    int input_item_id = 0 ;
    int input_quantity = 0 ;
    int count = 0;
    int i =0;
    char message[message_size];

    //set file Pointer
    FILE *stock;

    //Open the stock file
    stock=fopen("stock.dat","r");

    //Call the fileLine_count() function in the additional.c file
    //then set the number of lines in the STOCK_FILE, to the count variable
    count = fileLine_count(stock);

    //create arrays
    struct delivery stockDetails[count];

    struct delivery stock_details;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and fill data to array
    rewind(stock);
    while(fscanf(stock,"%d %s %lf %d",&stock_details.item_id,stock_details.item_name,&stock_details.price,&stock_details.quantity)!=EOF)
    {
        stockDetails[i].item_id      = stock_details.item_id;
        strcpy(stockDetails[i].item_name,stock_details.item_name);
        stockDetails[i].price        = stock_details.price;
        stockDetails[i].quantity     = stock_details.quantity;
        i++;
    }
    //close the stock file
    file_closer(stock);

    system("cls");
    system("COLOR 3");

    //display the loading panel
    printf("\n\n                            ***********************************");
    printf(  "\n                            *              load               *");
    printf(  "\n                            *********************************** \n\n");

    //capture salesman name
    printf("  * Enter the salesmen name   :");
    scanf("%s",salesman_name);

    //display available items and their quantities
    printf("\n\n                   ... stock available items ...\n");
    printf("\n            _________________________________________________");
    printf("\n            |    item Id    |   item name   | Item Quantity |");
    printf("\n            |_______________|_______________|_______________|");

    for(int j=0; j<count; j++)
    {
        printf("\n            |%10d     |%10s     |%10d     |",stockDetails[j].item_id,stockDetails[j].item_name,stockDetails[j].quantity);
    }
        printf("\n            |_______________|_______________|_______________|   \n\n");



    /**< ---------  item id validation  ------------ */

    //if user enter an invalid input,navigate again to get the user input
    //goto function call in Line 122
    try_again:

    //get item_id from the user
    //Call int_input() function in the additional.c file to check whether the input is an integer
    strcpy(message,"\n   * Enter item ID                   ");
    input_item_id = int_input(message);
    *item_id = input_item_id;

    //check item is exists
    for(int j=0; j<count; j++)
    {
        if(stockDetails[j].item_id == input_item_id)
        {
            printf("\n   * item name is                    :%s\n",stockDetails[j].item_name);

            strcpy(item_name , stockDetails[j].item_name);
            *price = stockDetails[j].price;

            //if item found, skip to quantity
            //goto recapture quantity to Line 126
            goto get_quantity;
        }
    }

    //if user enter an invalid input,navigate again to get the user input
    //goto recapture item id to Line 126
    printf("wrong item id\n");
    goto try_again;



    /**< ---------  quantity validation  ------------ */

    //if item found, skip to quantity
    //goto function call in Line 115
    //enter and get quantity
    get_quantity:

    //get user input quantity
    //Call int_input() function in the additional.c file to set a validate integer into the variable
    strcpy(message,"\n   * Enter the quantity of item      ");
    input_quantity = int_input(message);
    *quantity = input_quantity;

    //check quantity validity
    for(int j=0; j<count; j++)
    {
        //check item
        if(stockDetails[j].item_id == input_item_id)
        {
            //validate availability of stock quantity and input quantity
            if(stockDetails[j].quantity < input_quantity)
            {
                // if item Invalid Quantity, navigate again get user input
                //call goto_function  to Line 133
                printf("Invalid Quantity,stock not enough!\n");
                goto get_quantity;
            }
        }
    }
}




void loading()
{
    //variable declaration and create array
    int choice;
    int count= 0;
    int i =0;
    char message[message_size];

    //set file Pointers
    FILE *stock,*load;

    //Open the stock file
    stock = fopen("stock.dat","r");

    //Call fileLine_count() function in the additional.c file to set the number of lines in the STOCK_FILE, to the count variable
    count = fileLine_count(stock);

    //create arrays
    struct delivery stockDetails[count];
    struct delivery stock_details;
    struct delivery load_details;

    stockDetails[0].item_id    = 0;

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file and get data to array
    rewind(stock);
    while(fscanf(stock,"%d %s %lf %d",&stock_details.item_id,stock_details.item_name,&stock_details.price,&stock_details.quantity)!=EOF)
    {
            stockDetails[i].item_id      = stock_details.item_id;
            strcpy(stockDetails[i].item_name,stock_details.item_name);
            stockDetails[i].price        = stock_details.price;
            stockDetails[i].quantity     = stock_details.quantity;
         i++;
    }
    //close the stock file
    //file_closer(stock);

    /**< ---------   loading calculation     ------------ */

    //to load again
    //goto function call in Line 256
    load_again:

    // call input_loading_details() function and get data
    input_loading_details(&load_details.salesman_name, &load_details.item_id, &load_details.item_name, &load_details.price, &load_details.quantity);

    /** meka metenta danne uda class karanwa witarai
     *  why nawata nawata load karaddi stock file eka update wenna ona
     */
    //Call the file_closer() and file_remover() function in the additional.c file for close and delete the file
    //file_closer(stock);
    file_remover("stock.dat",stock);

    //Open the load file
    load = fopen("load.dat","a+");

    //write the loading data load file
    fprintf(load,"%d %d %d %s %d %s %lf %d\n",YEAR,MONTH,DAY,load_details.salesman_name,load_details.item_id,load_details.item_name,load_details.price,load_details.quantity);

    //close the load file
    file_closer(load);

    /**< update the "stock" file after loading  */

    //Open the load file
    stock = fopen("stock.dat","a+");

    //update stock details
    for(int j=0; j<count; j++)
    {
        if(stockDetails[j].item_id == load_details.item_id)
        {
            stockDetails[j].quantity = (stockDetails[j].quantity - load_details.quantity);
        }
        //write the updated stock data stock file
        fprintf(stock,"%d %s %lf %d\n",stockDetails[j].item_id,stockDetails[j].item_name,stockDetails[j].price,stockDetails[j].quantity);
    }

    //close the load file
    file_closer(stock);

    /**< ----------  navigation section  ------------ */

    printf("\n\n\t 1. load new item again");
    printf("\n\t 0. go to menu");

    //get user input again
    //goto function call in Line 273
    try_again:

    //Call int_input() function in the additional.c file to check whether the input is integer
    strcpy(message,"\n\n   * enter your choice ");
    choice = int_input(message);

    if (choice == 1)
    {
        goto load_again;
    }
    else if(choice == 0)
    {
        menu();
    }
    else
    {
        // if invalid input, navigate again to get the user input
        // goto recapture input to Line 247
        printf("Invalid input !\a");
        goto try_again;
    }
}
