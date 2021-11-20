#include <bits/stdc++.h>
#include <Windows.h>

#define NL endl

using namespace std;


int i = 0;

char path[] = "foodData.txt";
int customer_total_cost = 0;

class Menu
{
public:
  int foodcode;
  char foodname[1000];
  int price;
  int count;
};

class Menu menu[1000];

void readMenuDataFromFile()
{
  FILE *file;
  file = fopen("foodData.txt", "r");
  if (file == NULL)
  {
    i = 0;
    return;
  }
  else
  {
    while (fscanf(file, "%d", &menu[i].foodcode) != EOF)
    {
      fscanf(file, " %[^\n]", menu[i].foodname);
      fscanf(file, "%d", &menu[i].price);
      fscanf(file, "%d", &menu[i].count);
      i++;
      
    }
    fclose(file);
  }
  return;
}

void saveMenuInDatabase()
{
  FILE *file;
  file = fopen("foodData.txt", "w");
  for (int j = 0; j < i; j++)
  {
    fprintf(file, "%d\n", menu[j].foodcode);
    fprintf(file, "%s\n", menu[j].foodname);
    fprintf(file, "%d\n", menu[j].price);
    fprintf(file, "%d\n", menu[j].count);
    //i++;
  }
  fclose(file);
  return;
}

void showMenu()
{
  if (i == 0)
  {
    cout << "\tSorry there is no food on menu\n";
    return;
  }

  else
  {
    for (int j = 0; j < i; j++)
    {
      cout << NL << "\t|-------------------------------" << NL;
      cout << "\t| Serial: " << j + 1 << NL;
      cout << "\t| Item code: " << menu[j].foodcode << NL;
      cout << "\t| Item: " << menu[j].foodname << NL;
      cout << "\t| Price: " << menu[j].price << NL;
      cout << "\t| Available in stock: " << menu[j].count << NL;
      cout << "\t|-------------------------------" << NL;
    }
  }
}

void addNewFoodItem()
{
  int n;
  cout << "\tEnter number of new food items: ";
  cin >> n;
  while (n--)
  {
    //Data will be added in menu array but not in database
    cout << "\tEnter Food Name : ";
    fflush(stdin);
    gets(menu[i].foodname);
    cout << "\tEnter Food Price : ";
    fflush(stdin);
    cin >> menu[i].price;
    cout << "\tEnter How many Food in stock : ";
    fflush(stdin);
    cin >> menu[i].count;
    menu[i].foodcode = i + 1;
    i++;
    cout<<"\tSuccessfully added in the menu";
    cout << NL;
    
  }
  return;
}

void UpdateExistingMenu()
{
  cout << NL << "\tFor showing specific Menu and edit Menu Enter Food Code : ";
  int foodcode, option, flag = 0;
  cin >> foodcode;
  for (int j = 0; j < i; j++)
  {
    if (menu[j].foodcode == foodcode)
    {
      flag = 1;
      cout << NL << "\tSelected food code     : " << menu[j].foodcode;
      cout << NL << "\tSelected food name     : " << menu[j].foodname;
      cout << NL << "\tSelected food price     : " << menu[j].price;
      cout << NL << "\tSelected food quantity in stock : " << menu[j].count << NL << NL;
      //cout<<NL<<NL<<"\t\tPress 1 for edit food information and Press 0 for exit : ";
      cout << "\t1)Edit food name" << NL;
      cout << "\t2)Edit food code" << NL;
      cout << "\t3)Edit Quantity of the food" << NL;
      cout << "\t4)Edit price of the food" << NL;
      cout << "\t5) cancel operation" << NL;
      cout << "\tselect your option: ";
      cin >> option;
      if (option == 1)
      {
        cout << NL << "\tEnter new food name: ";
        getchar();
        gets(menu[j].foodname);
      }

      else if (option == 2)
      {
        cout << NL << "\tEnter new food code (must be an unique code) : ";
        cin >> menu[j].foodcode;
      }

      else if (option == 3)
      {
        cout << NL << "\tEnter new food quantity in stock : ";
        cin >> menu[j].count;
      }

      else if (option == 4)
      {
        cout << NL << "\tEnter new price for this food : ";
        cin >> menu[j].price;
      }
      else if (option == 5)
        return;
    }
  }
  if (flag == 0)
  {
    cout << "No such food code matched in the menu" << NL;
    return;
  }
  cout << NL << NL << "\tSuccesfully Updated" << NL;
}

void selectFoodForOrder()
{
  cout << NL << "\tEnter Food Code : ";
  int c, n;
  cin >> c;
  c--;
  for (int j = 0; j < i; j++)
  {
    if (j == c)
    {
      cout << NL << "\tEnter Food Amount : ";
      cin >> n;
      if (n > menu[j].count)
      {
        cout << NL << "Sorry You selected more than maximum food in stock" << NL;
        break;
      }
      else
      {
        cout << NL << "\t\tSelected Food Code : " << menu[j].foodcode;
        cout << NL << "\t\tSelected Food name : " << menu[j].foodname;
        cout << NL << "\t\tFood Amount : " << n;
        menu[i - 1].count = menu[j].count - n;
        int b = menu[j].price * n;
        cout << NL << "\t\tYour Bill is : " << b << "TAKA" << NL << NL;
        break;
      }
    }
  }
}

int ownerAccess()
{
  int select2;
  while (1)
  {
    system("cls");
    cout << "\tWelcome Owner\n";
    cout << "\tpress following numbers\n";
    cout << "\t1)View Menu item\n";
    cout << "\t2)Add food to Menu\n";
    cout << "\t3)Update Existing menu\n";
    cout << "\t4)Go back to main menu\n";
    cout << "\t5)Exit the app\n";
    cout << "\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showMenu();
      cout << "\tpress enter to continue...";
      getchar();
      getchar();
      system("cls");
    }
    else if (select2 == 2)
    {
      addNewFoodItem();
      cout << "\tpress enter to continue...";
      getchar();
      getchar();
      system("cls");
    }
    else if (select2 == 3)
    {
      UpdateExistingMenu();
      cout << "\tpress enter to continue...";
      getchar();
      getchar();
      system("cls");
    }

    else if (select2 == 4)
    {
      return 0;
    }

    else if (select2 == 5)
      return 1;
  }
}

int CustomerAccess()
{
  int select2, option;
  while (1)
  {
    system("cls");
    cout << "\tWelcome Customer\n";
    cout << "\tpress following numbers\n";
    cout << "\t1)View Menu item and order\n";
    cout << "\t2)Go back to main menu\n";
    cout << "\t3)Exit the app\n";
    cout << "\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showMenu();
      cout << "\tEnter 1 to order and  2 to return to main menu\n";
      cout << "\tEnter your option: ";
      cin >> option;
      if (option == 2)
        return 0;
      else
      {
        selectFoodForOrder();
        cout << "\tpress enter to continue...";
        getchar();
        getchar();
        system("cls");
      }
    }
    else if (select2 == 2)
    {
      return 0;
    }
    else
      return 1;
  }
}

int main()
{
  //saving data from database
  readMenuDataFromFile();
  
  //startup first page of program from here..
  int select, ex = -1;
  while (1)
  {
    system("cls");
    cout << "\tWelcome to Food menu app:\n";
    cout << "\tSelect the option below:\n";
    cout << "\t1) Press 1 to access as a Owner\n";
    cout << "\t2) Press 2 to Access as a Customer\n";
    cout << "\t3) Press 3 to exit the app\n";
    cout << "\tGive your option: ";
    cin >> select;
    if (select == 1)
    {
      //accessing as owner
      ex = ownerAccess();
      if (ex == 1)
        break;
    }
    else if (select == 2)
    {
      //accessing as customer
      ex = CustomerAccess();
      if (ex == 1)
        break;
    }
    else
      break;
  }
  saveMenuInDatabase();
  return 0;
}