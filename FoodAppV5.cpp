#include <bits/stdc++.h>
#include <Windows.h>

#define NL endl

using namespace std;



int ObjIndex = 0;
int OwnerObjIndex = 0;
char path[] = "foodData.txt";
char path2[] = "OwnerInfo.txt";
int customer_total_cost = 0;
map<string, int> CheckUserExistence;
vector<pair<string, int>> OwnerUsernames;
struct cloneMenuData
{
  int foodcode;
  string foodname;
  int price;
  int stockCount;
};

class FoodMenu
{
protected:
  int foodcode;
  string foodname;
  int price;
  int stockCount;

public:
  void setMenuInfo(cloneMenuData temp)
  {
    this->foodcode = temp.foodcode;
    this->foodname = temp.foodname;
    this->price = temp.price;
    this->stockCount = temp.stockCount;
  }

  cloneMenuData getMenuInfo(cloneMenuData temp)
  {
    temp.foodcode = this->foodcode;
    temp.foodname = this->foodname;
    temp.price = this->price;
    temp.stockCount = this->stockCount;
    return temp;
  }
  // void AddOrChangeData(cloneMenuData temp)
  // {
  //   this->foodname = temp.foodname;
  //   this->price = temp.price;
  //   this->stockCount = temp.stockCount;
  //   this->foodcode = temp.foodcode;
  // }

  void showMenu(int j)
  {
    cout << NL << "\t|```````````````````````````" << NL;
    //cout << "\t| Serial: " << j + 1 << NL;
    cout << "\t| Item code : " << foodcode << NL;
    cout << "\t| Item : " << foodname << NL;
    cout << "\t| Price : " << price << NL;
    cout << "\t| Available in stock : " << stockCount << NL;
    cout << "\t'```````````````````````````" << NL;
  }
};

struct cloneOwnerData
{
  string username, MobileNum, Password;
  bool isOwner = false;
};

class Owner : protected FoodMenu
{
protected:
  string username, MobileNum, Password;
  bool isOwner = false;

public:

  void RegisterNewUser(cloneOwnerData temp)
  {
    this->username = temp.username;
    this->MobileNum = temp.MobileNum;
    this->Password = temp.Password;
    this->isOwner = temp.isOwner;
  }

  void getOwnerData(cloneOwnerData temp)
  {
    temp.username = this->username;
    temp.MobileNum = this->MobileNum;
    temp.Password = this->Password;
    temp.isOwner = this->isOwner;
  }
};

class FoodMenu MainMenuArray[1000]; //main array holding all the food info
class Owner OwnerInfoArray[1000];
//vector<pair<int, int>> foodcodesData; //only foodcodes for searching in binary later

void readDataFromDatabase()
{
  ifstream file(path);
  if (file.fail())
  {
    ObjIndex = 0;
    return;
  }
  else
  {
    cloneMenuData tempObject;
    while (file >> tempObject.foodcode)
    {
      file.ignore();
      getline(file, tempObject.foodname);
      file >> tempObject.price;
      file >> tempObject.stockCount;
      MainMenuArray[ObjIndex].setMenuInfo(tempObject);
      ObjIndex++;
    }
  }
  file.close();
  return;
}

void saveMenuInDatabase()
{
  ofstream file(path);
  cloneMenuData tempObject;
  for (int j = 0; j < ObjIndex; j++)
  {
    tempObject = MainMenuArray[j].getMenuInfo(tempObject);
    file << tempObject.foodcode << NL;
    file << tempObject.foodname << NL;
    file << tempObject.price << NL;
    file << tempObject.stockCount << NL;
  }
  file.close();

  return;
}

int binarySearchByUsernames(string x)
{
  sort(OwnerUsernames.begin(), OwnerUsernames.end());

  int left = 0, right = OwnerUsernames.size() - 1, mid = 0;

  while (left <= right)
  {
    mid = (left + right) / 2;

    if (OwnerUsernames[mid].first == x)
    {
      return OwnerUsernames[mid].second;
    }
    else if (OwnerUsernames[mid].first < x)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

//to show the full menu list saved in menu array
void showMainMenu()
{
  if (ObjIndex == 0)
  {
    cout << "\tSorry there is no food on menu\n";
    return;
  }
  else
  {
    for (int j = 0; j < ObjIndex; j++)
    {
      MainMenuArray[j].showMenu(j);
    }
  }
}

//for adding new item to menu, only accessible by the owner
void addNewFoodItem()
{
  int n;
  cout << NL << "\tEnter number of new food items: ";
  cin >> n;
  cloneMenuData tempObject;
  while (n--)
  {
    //Data will be added in menu array but not in database before closing the program
    cout << NL << "\tEnter Food Name : ";
    cin.ignore();
    getline(cin, tempObject.foodname);

    cout << NL << "\tEnter Food Price : ";

    cin >> tempObject.price;
    cout << NL << "\tEnter How many Food in stock : ";
    fflush(stdin);
    cin >> tempObject.stockCount;

    tempObject.foodcode = ObjIndex + 1;
    //foodcodesData.push_back({tempObject.foodcode, ObjIndex});
    MainMenuArray[ObjIndex].setMenuInfo(tempObject);
    ObjIndex++;
    cout << NL << "\tSuccessfully added in the menu";
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

  int index = (foodcode - 1);
  if (index < ObjIndex)
  {
    cloneMenuData tempObject;
    tempObject = MainMenuArray[index].getMenuInfo(tempObject);
    cout << NL << "\tSelected food code      : " << tempObject.foodcode;
    cout << NL << "\tSelected food name      : " << tempObject.foodname;
    cout << NL << "\tSelected food price     : " << tempObject.price;
    cout << NL << "\tSelected food quantity in stock : " << tempObject.stockCount << NL << NL;
    cout << "\t1)Edit food name" << NL;
    cout << "\t2)Edit Quantity of the food" << NL;
    cout << "\t3)Edit price of the food" << NL;
    cout << "\t4)Edit the all the info of this food" << NL;
    cout << "\t5) cancel operation" << NL;
    cout << "\tselect your option: ";
    cin >> option;
    //option for changing name only
    if (option == 1)
    {
      cout << NL << "\tEnter new food name: ";
      cin.ignore();
      getline(cin, tempObject.foodname);
      MainMenuArray[index].setMenuInfo(tempObject);
    }

    //option for changing quantity in stock
    else if (option == 2)
    {
      cout << NL << "\tEnter new food quantity in stock : ";
      cin >> tempObject.stockCount;
      MainMenuArray[index].setMenuInfo(tempObject);
    }

    //option for changing food price
    else if (option == 3)
    {
      cout << NL << "\tEnter new price for this food : ";
      cin >> tempObject.price;
      MainMenuArray[index].setMenuInfo(tempObject);
    }

    //option for change entire food info
    else if (option == 4)
    {
      cout << NL << "\tEnter new food name: ";
      cin.ignore();
      getline(cin, tempObject.foodname);
      cout << NL << "\tEnter new food quantity in stock : ";
      cin >> tempObject.stockCount;
      cout << NL << "\tEnter new price for this food : ";
      cin >> tempObject.price;
      MainMenuArray[index].setMenuInfo(tempObject);
    }
    else if (option == 5)
      return;
  }

  // if food code doesn't exist
  else
  {
    cout << NL << "\tNo such food code of food item exist in the menu" << NL;
    return;
  }
  cout << NL << NL << "\tSuccessfully Updated" << NL;
}

//ordering food from the menu stock, accessible by the customer
void selectFoodForOrder()
{
  // cout << NL << "\tEnter Food Code : ";
  // int foodcode, amount;
  // cin >> foodcode;
  // int index = binarySearchByFoodCode(foodcode);
  // if (index != -1)
  // {
  //   cout << NL << "\tEnter Food Amount : ";
  //   cin >> amount;
  //   if (amount > menu[index].count)
  //   {
  //     cout << NL << "\tSorry You selected more than maximum food in the stock" << NL;
  //   }
  //   else
  //   {
  //     cout << NL << "\tSelected Food Code : " << menu[index].foodcode;
  //     cout << NL << "\tSelected Food name : " << menu[index].foodname;
  //     cout << NL << "\tSelected Food price : " << menu[index].price;
  //     cout << NL << "\tFood Amount : " << amount;
  //     menu[index].count -= amount;
  //     int sum = menu[index].price * amount;
  //     customer_total_cost += sum;
  //     cout << NL << "\tYou have ordered " << sum << " Taka food in this session";
  //     cout << NL << "\tYour total bill is : " << customer_total_cost << " Taka" << NL << NL;

  //     cout << NL << "\tpress 1 to order again, any other number to return to cutomer menu: ";
  //     int option;
  //     cin >> option;
  //     if (option == 1)
  //       selectFoodForOrder();
  //     else
  //       return;
  //   }
  // }
  // else
  //   cout << "\tInvalid Food code" << NL;
}

void clearScreen()
{
  cout << "\tpress enter to continue...";
  getchar();
  getchar();
  system("cls");
}

int OwnerLogin()
{
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
      showMainMenu();
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
    cout << "\n\tYour total bill untill now: " << customer_total_cost << " Taka." << NL;
    cout << "\n\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showMainMenu();
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
    cout << "\t1) Press 1 to log in as an Owner\n";
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

  //saving all the array data to file before closing
  saveMenuInDatabase();
  return 0;
}