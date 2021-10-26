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
vector<pair<int, int>> foodcodesData;

void readDataFromDatabase()
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
      foodcodesData.push_back({menu[i].foodcode, i});
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

int binarySearchByFoodCode(int x)
{
  sort(foodcodesData.begin(), foodcodesData.end());

  int left = 0, right = foodcodesData.size() - 1, mid = 0;

  while (left <= right)
  {
    mid = (left + right) / 2;

    if (foodcodesData[mid].first == x)
    {
      return foodcodesData[mid].second;
    }
    else if (foodcodesData[mid].first < x)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

// to show the full menu list saved in menu array
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

// for adding new item to menu, only accessible by the owner
void addNewFoodItem()
{
  int n;
  cout << "\tEnter number of new food items: ";
  cin >> n;
  while (n--)
  {
    //Data will be added in menu array but not in database before closing the program
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
    foodcodesData.push_back({menu[i].foodcode, i});
    i++;
    cout << "\tSuccessfully added in the menu";
    cout << NL;
  }
  return;
}

//updating a single food data, only accssible by the owner
void UpdateExistingMenu()
{
  cout << NL << "\tFor showing specific Menu and edit Menu Enter Food Code : ";
  int foodcode, option;
  cin >> foodcode;

  int index = binarySearchByFoodCode(foodcode);
  if (index != -1)
  {
    cout << NL << "\tSelected food code     : " << menu[index].foodcode;
    cout << NL << "\tSelected food name     : " << menu[index].foodname;
    cout << NL << "\tSelected food price     : " << menu[index].price;
    cout << NL << "\tSelected food quantity in stock : " << menu[index].count << NL << NL;
    cout << "\t1)Edit food name" << NL;
    cout << "\t2)Edit Quantity of the food" << NL;
    cout << "\t3)Edit price of the food" << NL;
    cout << "\t4)Edit the all the info of this food" << NL;
    cout << "\t5) cancel operation" << NL;
    cout << "\tselect your option: ";
    cin >> option;
    if (option == 1)
    {
      cout << NL << "\tEnter new food name: ";
      getchar();
      gets(menu[index].foodname);
    }

    else if (option == 2)
    {
      cout << NL << "\tEnter new food quantity in stock : ";
      cin >> menu[index].count;
    }

    else if (option == 3)
    {
      cout << NL << "\tEnter new price for this food : ";
      cin >> menu[index].price;
    }
    else if (option == 4)
    {
      cout << NL << "\tEnter new food name: ";
      getchar();
      gets(menu[index].foodname);
      cout << NL << "\tEnter new food quantity in stock : ";
      cin >> menu[index].count;
      cout << NL << "\tEnter new price for this food : ";
      cin >> menu[index].price;
    }
    else if (option == 5)
      return;
  }
  else
  {
    cout << "\tNo such food code matched in the menu" << NL;
    return;
  }
  cout << NL << NL << "\tSuccesfully Updated" << NL;
}

//ordering food from the menu stock, accssible by the customer
void selectFoodForOrder()
{
  cout << NL << "\tEnter Food Code : ";
  int foodcode, amount;
  cin >> foodcode;
  int index = binarySearchByFoodCode(foodcode);
  if (index != -1)
  {
    cout << NL << "\tEnter Food Amount : ";
    cin >> amount;
    if (amount > menu[index].count)
    {
      cout << NL << "\tSorry You selected more than maximum food in the stock" << NL;
    }
    else
    {
      cout << NL << "\tSelected Food Code : " << menu[index].foodcode;
      cout << NL << "\tSelected Food name : " << menu[index].foodname;
      cout << NL << "\tSelected Food price : " << menu[index].price;
      cout << NL << "\tFood Amount : " << amount;
      menu[index].count -= amount;
      int sum = menu[index].price * amount;
      customer_total_cost += sum;
      cout << NL << "\tYou have ordered " << sum << " Taka food in this session";
      cout << NL << "\tYour total bill is : " << customer_total_cost << " Taka" << NL << NL;

      cout<<NL<<"\tpress 1 to order again, any other number to return to cutomer menu"<<NL;
      int option;
      cin>>option;
      if(option==1) selectFoodForOrder();
      else return;
    }
  }
  else
    cout << "\tInvalid Food code" << NL;
}

void clearScreen()
{
  cout << "\tpress enter to continue...";
  getchar();
  getchar();
  system("cls");
}

//owner sections and options
int OwnerAccess()
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
      clearScreen();
    }
    else if (select2 == 2)
    {
      addNewFoodItem();
      clearScreen();
    }
    else if (select2 == 3)
    {
      UpdateExistingMenu();
      clearScreen();
    }
    else if (select2 == 4)
    {
      return 0;
    }
    else if (select2 == 5)
      return 1;
  }
}

//Customer section and options
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
    cout << "\n\tYour total bill untill now: " << customer_total_cost <<" Taka." <<NL;
    cout << "\n\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showMenu();
      cout << "\tEnter 1 to order and  2 to return to Customer menu\n";
      cout << "\tEnter your option: ";
      cin >> option;
      if (option == 2)
        continue;
      else
      {
        selectFoodForOrder();
        clearScreen();
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
  readDataFromDatabase();

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
      ex = OwnerAccess();
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