#include <stdio.h>
#include <stdlib.h>

//global variable declaration
extern int message_size;
extern int itemName_size;

struct delivery
{
    int item_id;
    char item_name[50];
    int quantity;
    double price;
};

//enter item details
void input_item(char *input_item_name[itemName_size], double *input_price, int *input_quantity)
{
    char message[message_size];
    char item_name[itemName_size];
    struct delivery stock_details;
    int choice = 0;

    add_itemName_again:

    printf("   * Enter the ITEM name             :");
    scanf("%s",&input_item_name);
    *item_name = input_item_name;


    /**< ---------  item name validation  ------------ */

    //set file Pointer
    FILE *stock;

    //Open the stock file
    stock=fopen("stock.dat","r+");

    //sets the file position to the beginning of the file of the given stream
    //scan the stock file
    rewind(stock);
    while(fscanf(stock,"%d %s %lf %d",&stock_details.item_id,stock_details.item_name,&stock_details.price,&stock_details.quantity)!=EOF)
    {
        if(strcmp(item_name,stock_details.item_name))
        {
            printf("\n\t this item name early day exist.\n\n");

            printf("1.enter item name again \n");
            printf("2.go to update stock item quantity\n");

            Invalid_input:

            //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
            strcpy(message,"\n   * enter your choice ");
            choice = int_input(message);

            if(choice == 1)
            {
                // goto recapture input to Line 72
                goto add_itemName_again;
            }
            else if (choice == 2)
            {
                //update stock
                update_stock();
            }
            else
            {
                //if the user enter invalid input, delay few seconds and navigate again to get the user input
                // goto recapture input to Line 72
                printf("\nInvalid input... ");
                goto Invalid_input;
            }

        }
    }
    //close the stock file
    file_closer(stock);


    printf("   * Enter the amount to ITEM (Rs.)  :");
    scanf("%lf",input_price);

    //get the quantity from user
    //Call the int_input() function in the additional.c file to set a validate integer into the input_quantity variable
    strcpy(message,"   * Enter the quantity of item      ");
    *input_quantity = int_input(message);
}


void add_item()
{
    //variable declaration
    int i;
    int choice;
    char message[message_size];

    //pointer to stock file
    FILE *stock;

    //get user input again
    //goto() function call in Line 105
    add_item_again:

    //open the stock file for reading and appending.
    stock = fopen("stock.dat","a+");

    struct delivery stock_details;


    system("cls");
    system("COLOR 06");

    //display panel
    printf("\n\n\n");
    printf("\n                             *********************************** ");
    printf("\n                             *       ADD ITEM TO STOCK         * ");
    printf("\n                             *********************************** \n");

    //generate new item id
    stock_details.item_id = fileLine_count(stock) + 1;
    printf("\n\n\n     Item id is                      :%d\n",stock_details.item_id);

    //calling input_item() function and get the item name,item price and quantity
     input_item(&stock_details.item_name,&stock_details.price,&stock_details.quantity);

    //write the above details in the "stock" file
    fprintf(stock,"%d %s %lf %d\n",stock_details.item_id,stock_details.item_name,stock_details.price,stock_details.quantity);
    printf("\n  ITEM added successfully!");

    //close stock file
    fclose(stock);

    //get user input again
    //goto() function call in Line 105
    Invalid_input:

        printf("\n\n\t 1. add new item again");
        printf("\n\t 2. go to stock");
        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n   * enter your choice ");
        choice = int_input(message);

        if(choice == 1)
        {
            // goto recapture input to Line 72
            goto add_item_again;
        }
        else if (choice == 2)
        {
            //view stock
            display_stock();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            // goto recapture input to Line 72
            printf("\nInvalid input... ");
            goto Invalid_input;
        }
}


void update_stock()
{
    //variable declaration and create array
    int input_item_id = 0 ;
    int input_quantity = 0 ;
    int count = 0;
    int i =0;
    int choice = 0;
    char message[message_size];

    //set file Pointer
    FILE *stock;

    //Open the stock file
    stock=fopen("stock.dat","r+");

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

    update_item_again:

    system("cls");
    system("COLOR 3");

    //display the loading panel
    printf("\n\n                            ***********************************");
    printf(  "\n                            *        Update Stock Item        *");
    printf(  "\n                            *********************************** \n\n");

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

    //check item is exists
    for(int j=0; j<count; j++)
    {
        if(stockDetails[j].item_id == input_item_id)
        {
            printf("\n   * item name is                    :%s\n",stockDetails[j].item_name);
            goto get_quantity;
        }
    }

    //if user enter an invalid input,navigate again to get the user input
    //goto recapture item id to Line 126
    printf("wrong item id\n");
    goto try_again;

    get_quantity:

    //get quantity from the user
    //Call int_input() function in the additional.c file to check whether the input is an integer
    strcpy(message,"\n   * Enter the item quantity                   ");
    input_quantity = int_input(message);

    //Call the file_closer() and file_remover() function in the additional.c file for close and delete the file
    //file_closer(stock);
    file_remover("stock.dat",stock);

    //Open the load file
    stock = fopen("stock.dat","a+");

    //update stock details
    for(int j=0; j<count; j++)
    {
        //add quantity
        if(stockDetails[j].item_id == input_item_id)
        {
            stockDetails[j].quantity += input_quantity;
        }
        //write the updated stock data stock file
        fprintf(stock,"%d %s %lf %d\n",stockDetails[j].item_id,stockDetails[j].item_name,stockDetails[j].price,stockDetails[j].quantity);
    }

    //close the load file
    file_closer(stock);
    printf("\n  ITEM quantity update successfully!");

    //get user input again
    //goto() function call in Line 105
    Invalid_input:

        printf("\n\n\t 1. update item quantity again");
        printf("\n\t 2. go to back");
        //Call the int_input() function in the additional.c file to set a validate integer into the choice variable
        strcpy(message,"\n\n   * enter your choice ");
        choice = int_input(message);

        if(choice == 1)
        {
            // goto recapture input
            goto update_item_again;
        }
        else if (choice == 2)
        {
            //view stock
            display_stock();
        }
        else
        {
            //if the user enter invalid input, delay few seconds and navigate again to get the user input
            // goto recapture input
            printf("\nInvalid input... ");
            goto Invalid_input;
        }

}


