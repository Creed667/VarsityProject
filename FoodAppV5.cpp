#include <bits/stdc++.h>
#include <Windows.h>

#define NL endl

using namespace std;

//-------> global memory storage <--------
int menuIndex = 0;
int ownerIndex = 0;
char path[] = "foodData.txt";
char path2[] = "OwnerInfo.txt";
int customer_total_cost = 0;
map<string, pair<string, int>> verifyUser;
bool checkOwnerExist = false;
int userProfileIndex;

//--------------------------> Class declaration <-------------------------------------
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
  void setMenuData(cloneMenuData temp)
  {
    this->foodcode = temp.foodcode;
    this->foodname = temp.foodname;
    this->price = temp.price;
    this->stockCount = temp.stockCount;
  }

  cloneMenuData getMenuData(cloneMenuData temp)
  {
    temp.foodcode = this->foodcode;
    temp.foodname = this->foodname;
    temp.price = this->price;
    temp.stockCount = this->stockCount;
    return temp;
  }

  void showMenu()
  {
    cout << NL << "\t|```````````````````````````" << NL;
    cout << "\t| Item code : " << foodcode << NL;
    cout << "\t| Item : " << foodname << NL;
    cout << "\t| Price : " << price << NL;
    cout << "\t| Available in stock : " << stockCount << NL;
    cout << "\t'```````````````````````````" << NL;
  }
};

struct cloneOwnerData
{
  string username, mobileNum, password;
  bool isOwner = false;
};

class Owner : public FoodMenu
{
private:
  string username, mobileNum, password;
  bool isOwner = false;

public:
  bool getUserPosition()
  {
    return isOwner;
  }
  void setOwnerData(cloneOwnerData temp)
  {
    this->username = temp.username;
    this->mobileNum = temp.mobileNum;
    this->password = temp.password;
    this->isOwner = temp.isOwner;
  }

  cloneOwnerData getOwnerData(cloneOwnerData temp)
  {
    temp.username = this->username;
    temp.password = this->password;
    temp.mobileNum = this->mobileNum;
    temp.isOwner = this->isOwner;
    return temp;
  }

  void showOwnerData()
  {
    isOwner ? cout << "\n\tPosition in Restaurant: Owner\n"
            : cout << "\n\tPosition in Restaurant: Partner\n";
    cout << "\tUser name: " << this->username << NL;
    cout << "\tMobile number: " << this->mobileNum << NL;
  }
};

class FoodMenu mainMenuArray[1000]; //main array holding all the food info
class Owner ownerInfoArray[1000];   //main array holding owner/partner info

//------------------------> end of Class declaration <------------------------------

//-------------------------> File writing and reading <-----------------------

//Food Menu file
void readMenuDataFromFile()
{
  ifstream file(path);
  if (file.fail())
  {
    menuIndex = 0;
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
      mainMenuArray[menuIndex].setMenuData(tempObject);
      menuIndex++;
    }
  }
  file.close();
  return;
}

//Owner Info File
void readOwnerInfoFile()
{

  ifstream file(path2);
  if (file.fail())
  {
    ownerIndex = 0;
    return;
  }
  else
  {
    cloneOwnerData tempObject;

    while (file >> tempObject.username)
    {
      file >> tempObject.password;
      file >> tempObject.mobileNum;
      file >> tempObject.isOwner;

      if (tempObject.username != "")
        verifyUser[tempObject.username] = {tempObject.password, ownerIndex};
      if (tempObject.isOwner == true)
        checkOwnerExist = true;
      ownerInfoArray[ownerIndex].setOwnerData(tempObject);
      ownerIndex++;
    }
  }
  file.close();
}

void saveOwnerInfoInFile()
{
  ofstream file(path2);
  cloneOwnerData tempObject;
  for (int j = 0; j < ownerIndex; j++)
  {
    tempObject = ownerInfoArray[j].getOwnerData(tempObject);
    file << tempObject.username << NL;
    file << tempObject.password << NL;
    file << tempObject.mobileNum << NL;
    file << tempObject.isOwner << NL;
  }
  file.close();
  return;
}

void saveMenuInFile()
{
  ofstream file(path);
  cloneMenuData tempObject;
  for (int j = 0; j < menuIndex; j++)
  {
    tempObject = mainMenuArray[j].getMenuData(tempObject);
    file << tempObject.foodcode << NL;
    file << tempObject.foodname << NL;
    file << tempObject.price << NL;
    file << tempObject.stockCount << NL;
  }
  file.close();
  return;
}

//---------------------------------> end of File writing<----------------------------------

// ------------------------> Functions for Food Menu interface <------------------------

//to show the full menu list saved in menu array
void showMainMenu()
{
  system("cls");
  cout << "\n=============== Menu Items List ===============\n\n";

  if (menuIndex == 0)
  {
    cout << "\tSorry there is no food on menu\n";
    return;
  }
  else
  {
    for (int j = 0; j < menuIndex; j++)
    {
      mainMenuArray[j].showMenu();
    }
  }
  return;
}

//for adding new item to menu, only accessible by the owner
void addNewFoodItem()
{
  system("cls");
  cout << "\n=============== Add new food Item ===============\n\n";
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
    tempObject.foodcode = menuIndex + 1;
    mainMenuArray[menuIndex].setMenuData(tempObject);
    menuIndex++;
    cout << NL << "\tSuccessfully added in the menu";
    cout << NL;
  }
  return;
}

//updating a single food data, only accssible by the owner
void UpdateExistingMenu()
{
  system("cls");
  cout << "\n=============== Update Menu Items ===============\n\n";
  cout << NL << "\tFor showing specific Menu and edit Menu Enter Food Code : ";
  int foodcode, option;
  cin >> foodcode;

  int index = (foodcode - 1);
  if (index < menuIndex)
  {
    cloneMenuData tempObject;
    tempObject = mainMenuArray[index].getMenuData(tempObject);
    cout << NL << "\tSelected food code      : " << tempObject.foodcode;
    cout << NL << "\tSelected food name      : " << tempObject.foodname;
    cout << NL << "\tSelected food price     : " << tempObject.price;
    cout << NL << "\tSelected food quantity in stock : " << tempObject.stockCount << NL << NL;
    cout << "\t1) Edit food name" << NL;
    cout << "\t2) Edit Quantity of the food" << NL;
    cout << "\t3) Edit price of the food" << NL;
    cout << "\t4) Edit the all the info of this food" << NL;
    cout << "\t5) cancel operation" << NL;
    cout << "\tselect your option: ";
    cin >> option;
    //option for changing name only
    if (option == 1)
    {
      cout << NL << "\tEnter new food name: ";
      cin.ignore();
      getline(cin, tempObject.foodname);
      mainMenuArray[index].setMenuData(tempObject);
    }

    //option for changing quantity in stock
    else if (option == 2)
    {
      cout << NL << "\tEnter new food quantity in stock : ";
      cin >> tempObject.stockCount;
      mainMenuArray[index].setMenuData(tempObject);
    }

    //option for changing food price
    else if (option == 3)
    {
      cout << NL << "\tEnter new price for this food : ";
      cin >> tempObject.price;
      mainMenuArray[index].setMenuData(tempObject);
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
      mainMenuArray[index].setMenuData(tempObject);
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
  cout << NL << "\tEnter Food Code : ";
  int foodcode, amount;
  cin >> foodcode;
  int index = (foodcode - 1);
  if (index < menuIndex)
  {
    cloneMenuData tempObject;
    tempObject = mainMenuArray[index].getMenuData(tempObject);
    system("cls");
    cout << "\n\tSelected Item: \n";
    mainMenuArray[index].showMenu();
    cout << NL << "\tEnter Food Amount : ";
    cin >> amount;
    if (amount > tempObject.stockCount)
    {
      cout << NL << "\tSorry You selected more than maximum food in the stock" << NL;
    }
    else
    {
      cout << NL << "\tSelected Food Code : " << tempObject.foodcode;
      cout << NL << "\tSelected Food name : " << tempObject.foodname;
      cout << NL << "\tSelected Food price : " << tempObject.price;
      cout << NL << "\tFood Amount : " << amount;
      cout << NL << "\tCost : " << (tempObject.price * amount);
      char confirm;
      cout << NL << "\tConfirm order? [y/n] : ";
      cin >> confirm;
      if (confirm == 'n' || confirm != 'y')
      {
        cout << "\n\tYou've canceled the order...\n\n";
        return;
      }
      tempObject.stockCount -= amount;
      int sum = tempObject.price * amount;
      customer_total_cost += sum;
      cout << NL << "\tYou have ordered " << sum << " Taka food in this session";
      cout << NL << "\tYour total bill is : " << customer_total_cost << " Taka" << NL << NL;
      mainMenuArray[index].setMenuData(tempObject);
      cout << NL << "\tpress 1 to order again, any other number to return to cutomer menu: ";
      int option;
      cin >> option;
      if (option == 1)
        selectFoodForOrder();
      else
        return;
    }
  }
  else
    cout << "\tInvalid Food code" << NL;
}

//-------------------------------------> End of Food Menu interface<-------------------------------------------

//----------------------> User Profile & Customer interface functions <--------------------------
void clearScreen()
{
  cout << "\tpress enter to continue...";
  getchar();
  getchar();
  system("cls");
}

int AdministrationLogin()
{
  int select, option;
  string username, password;
  while (1)
  {
    system("cls");
    cout << "\n=============== Welcome to Administration Panel ===============\n\n";
    cout << "\t1) Login" << NL;
    cout << "\t2) Register" << NL;
    cout << "\t3) Go back to main menu\n";
    cout << "\t4) Exit the app\n";
    cout << "\n\tGive your option: ";

    cin >> select;
    if (select == 1)
    {
      system("cls");
      cout << "\n=============== Login to your account ===============\n\n"
           << NL;
      cout << "\n\tEnter your username: ";
      cin >> username;
      if (verifyUser[username].first == "")
      {
        cout << "\n\tUsername doesn't exist, please register an account...\n";
        clearScreen();
        continue;
      }
      else
      {
        cout << "\tEnter your password: ";
        cin >> password;
      }
      if (verifyUser[username].first == password)
      {
        userProfileIndex = verifyUser[username].second;
        ownerInfoArray[userProfileIndex].showOwnerData();
        return 1;
        //returning 1 for login success
      }
      else
      {
        cout << "\n\tSorry username and pasword didn't match\n";
        clearScreen();
        return 0;
        //returning 0 for login failure
      }
    }
    else if (select == 2)
    {
      system("cls");
      cloneOwnerData tempObject;
      cout << "\n=============== Ragister for administration ===============\n\n"
           << NL << NL;
      cout << "\t(username must be unique without space)" << NL;
      cout << "\tEnter your username: ";
      cin >> tempObject.username;
      if (verifyUser[tempObject.username].first != "")
      {
        cout << "\n\tSorry this user name already exist....";
        clearScreen();
        continue;
      }
      cout << "\n\tEnter your password: ";
      cin >> tempObject.password;
      cout << "\n\tEnter your mobile number: ";
      cin >> tempObject.mobileNum;

      if (checkOwnerExist == true)
      {
        cout << "\n\tYou're registered as partner...\n\n";
        tempObject.isOwner = false;
      }
      else
      {
        cout << "\n\tChoose your poosition [1]Owner\\[2]Partner";
        cout << "\n\tNote: Only a single user can be owner\n";
        cout << "\n\tGive your option: ";
        int position;
        cin >> position;
        if (position == 1)
        {
          cout << "\n\tYou're registered as owner...\n\n";
          checkOwnerExist = true;
          tempObject.isOwner = true;
        }
        else
        {
          cout << "\n\tYou're registered as partner...\n\n";
          tempObject.isOwner = false;
        }
      }
      ownerInfoArray[ownerIndex].setOwnerData(tempObject);

      verifyUser[tempObject.username] = {tempObject.password, ownerIndex};

      userProfileIndex = ownerIndex;
      ownerIndex++;
      clearScreen();
    }

    else if (select == 3)
      return 3; //returning 3 for going back to main menu
    else
      return 4; //return 4 to exit the app
  }
}

// showing user profile
void showUserProfile()
{
  int option;
  system("cls");
  cout << "\n=============== User Profile ===============\n\n";
  ownerInfoArray[userProfileIndex].showOwnerData();
  cout << NL;
}

// stuff/partner list only accessible by Owner
void showUserList()
{
  //system("cls");
  cout << "\n=============== User List ===============\n\n";
  for (int i = 0; i < ownerIndex; i++)
  {
    cout << "\t___________________________________\n";
    cout << "\n\tSerial: " << i + 1;
    ownerInfoArray[i].showOwnerData();
    cout << "\t___________________________________\n\n";
  }
}

//Only owner can remove users and himself
void removeUser()
{
  int option, serial;
  system("cls");
  cout << "\n=============== Action center ===============\n\n";
  showUserList();
  cout << "\n\t1) Remove a user";
  cout << "\n\t2) Cancel operation";
  cout << "\n\tGive your option: ";
  cin >> option;
  if (option == 1)
  {

    cout << "\n\tEnter user's serial number: ";
    cin >> serial;
    serial--;
    cloneOwnerData tempObject;
    tempObject = ownerInfoArray[serial].getOwnerData(tempObject);
    cout << "\n\tRemove " << tempObject.username << " from the user list? [y/n]: ";
    char confirm;
    cin >> confirm;
    if (confirm == 'n' || confirm != 'y')
    {
      cout<<"\n\tOperation canceled...\n\n";
      return;
    }
    ownerIndex--;
    for(int i=serial;i<ownerIndex;i++)
    {
      tempObject = ownerInfoArray[i+1].getOwnerData(tempObject);
      ownerInfoArray[i].setOwnerData(tempObject);
    }
    cout<<"\n\tUser has been successfully removed..\n\n";
  }
  else 
  {
    cout<<NL;
    return;
  }
}

//partner section and options
int partnerAccess()
{
  int select;
  int select2;
  while (1)
  {
    system("cls");
    cout << "\n=============== Welcome to Partner Section ===============\n\n";
    cout << "\n\tpress following numbers\n";
    cout << "\t1) View My Profile\n";
    cout << "\t2) View Menu item\n";
    cout << "\t3) Add food to Menu\n";
    cout << "\t4) Update Existing menu\n";
    cout << "\t5) Go back to main menu\n";
    cout << "\t6) Exit the app\n";
    cout << "\tGive your option: ";
    cin >> select2;
    if (select2 == 1)
    {
      showUserProfile();
      clearScreen();
    }
    else if (select2 == 2)
    {
      showMainMenu();
      clearScreen();
    }
    else if (select2 == 3)
    {
      addNewFoodItem();
      clearScreen();
    }
    else if (select2 == 4)
    {
      UpdateExistingMenu();
      clearScreen();
    }
    else if (select2 == 5)
    {
      return 0;
    }
    else if (select2 == 6)
      return 1;
  }
}

//owner sections and options
int ownerAccess()
{
  int select2;
  while (1)
  {
    system("cls");
    cout << "\n=============== Welcome to Owner Section ===============\n\n";
    cout << "\tpress following numbers\n";
    cout << "\t1) View My Profile\n";
    cout << "\t2) View Owner & Partner List\n";
    cout << "\t3) Remove User\n";
    cout << "\t4) View Menu item\n";
    cout << "\t5) Add food to Menu\n";
    cout << "\t6) Update Existing menu\n";
    cout << "\t7) Go back to main menu\n";
    cout << "\t8) Exit the app\n";
    cout << "\tGive your option: ";
    cin >> select2;

    if (select2 == 1)
    {
      showUserProfile();
      clearScreen();
    }
    else if (select2 == 2)
    {
      system("cls");
      showUserList();
      clearScreen();
    }
    else if(select2 == 3)
    {
      removeUser();
      clearScreen();
    }
    else if (select2 == 4)
    {
      showMainMenu();
      clearScreen();
    }
    else if (select2 == 5)
    {
      addNewFoodItem();
      clearScreen();
    }
    else if (select2 == 6)
    {
      UpdateExistingMenu();
      clearScreen();
    }
    else if (select2 == 7)
    {
      return 0;
    }
    else if (select2 == 8)
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
    cout << "\n=============== Welcome to Customer section ===============\n\n";
    cout << "\tpress following numbers\n";
    cout << "\t1) View Menu item and order\n";
    cout << "\t2) Go back to main menu\n";
    cout << "\t3) Exit the app\n";
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
//-----------------------> End of User Profile section<-----------------------

// ----------------------------> Starting of the App <---------------------------
int main()
{

  //saving data from database
  readMenuDataFromFile();
  readOwnerInfoFile();

  //startup of first page of program from here..
  int select, ex = -1;
  bool isLoginPageUsed = false;
  while (1)
  {
    system("cls");
    cout << "\n=============== Welcome to Food Menu App ===============\n";
    cout << "\n\t\tSelect the option below\n";
    cout << "\t\t1) Access into Administration\n";
    cout << "\t\t2) Access as a Customer\n";
    cout << "\t\t3) Exit the app\n";
    cout << "\t\tGive your option: ";
    cin >> select;

    //accessing as administration
    if (select == 1)
    {
      //checking if already logged in ot not
      isLoginPageUsed ? ex = 1 : ex = AdministrationLogin();
      if (ex == 4) //exiting the app from login page
        break;
      if (ex == 1) //if login successful
      {
        isLoginPageUsed = true;

        int ownerAccessValue;
        ownerInfoArray[userProfileIndex].getUserPosition() ? ownerAccessValue = ownerAccess()
                                                           : ownerAccessValue = partnerAccess();
        if (ownerAccessValue == 1)
          break; //exiting the app from owner page
      }
    }

    //accessing as customer
    else if (select == 2)
    {

      ex = CustomerAccess();
      if (ex == 1)
        break;
    }
    else
      break;
  }
  //saving all the array data to file before closing
  saveMenuInFile();
  saveOwnerInfoInFile();
  return 0;
}

// ----------------------------> End of the App <----------------------------