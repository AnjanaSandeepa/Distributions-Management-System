#include <stdio.h>
#include <stdlib.h>

//global variable declaration
int YEAR,MONTH,DAY;
const int message_size = 50;
const int itemName_size = 50;
const int salesmanName_size = 50;
const int vehicleId_size = 50;


//function declaration
//login.c
void login();
//menu.c
void menu();
//stock.c
void input_item(char *input_item_name[itemName_size], double *input_price, int *input_quantity);
void add_item();
//load.c
void input_loading_details(char *vehicele_id[vehicleId_size], char *salesman_name[salesmanName_size], int *item_id, char *item_name[itemName_size], double *price, int *quantity);
void loading();
//unload.c
void input_unloading_details(char *vehicele_id[vehicleId_size], int *item_id,int *quantity);
void unloading();
//report.c
void report_menu();
void display_stock();
void full_sales_repoat();
void monthly_sales_report();
void progress_of_item();
void progress_of_vehicle();
//additional.c
void waiting();
void get_date(int *year, int *month, int *day);
int int_input(char message[message_size]);
int fileLine_count(FILE *const fin );
void file_closer(const FILE *file);
void file_remover(const char *filename, const FILE *file);


//main function
int main()
{

    //Call the get_date function to set a date to the global variable
    get_date(&YEAR, &MONTH, &DAY);

    //Call the login function to log into the system
    login();

    //Call the menu function to Display main menu
    menu();



    return 0;
}


