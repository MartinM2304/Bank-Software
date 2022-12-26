#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include "functions.h"
using namespace std;

const string centerTabs = "\t\t\t\t\t\t\t   ",halfOfCenterTabs ="\t\t\t\t\t   " ;

int main()
{

    char choice;

    cout << endl;
    cout << centerTabs << "Please choose one of the following:" << endl;
    cout << centerTabs << "L - login" << endl;
    cout << centerTabs << "R - register" << endl;
    cout << centerTabs << "Q -quit" << endl;

    cin >> choice;

    switch (choice)
    {
    case 'L':
        login();
        break;
    case 'l':
        login();
        break;
    case 'R':
        registration();
        break;
    case 'r':
        registration();
        break;
    case 'Q':
        cout << "Thank you for the use!";
        return 0;
    case 'q':
        cout << "Thank you for the use!";
        return 0;
        break;

    default:
        break;
    }
}
void Menu()
{
}

void login()
{
    system("cls");
    ifstream input("users.txt");
    hash<string> hash_obj;

    string userId, password, fileId, filePass;
    bool match;

    cout << centerTabs << "Please enter your username "<<endl;
    cin >> userId;
    cout << centerTabs << "Please enter your  password"<<endl;
    cin >> password;

    while (input>>fileId>>filePass)
    {
        getline(input, fileId, ':');
        if (userId == fileId)
        {
            getline(input, filePass, ':');

            Hasher(password);
            
            if ( password == filePass)
            {
                Menu();
            }
        }
    }
    cout <<centerTabs<< "Wrong password"<<endl
         <<centerTabs<<"Do u want to continue?";
}
void registration()
{

    system("cls");
    string userId, password, password2, rId, rPass;

    cout << centerTabs << "Enter the username you want to use: " << endl;
    cin >> userId;
    cout << centerTabs << "Enter the password you want to use: " << endl;
    cin >> password;

    while (!passwordChecker(password))
    {
        cout << "Your password must be at least 5 characters long and have at least 1 Capital letter, 1 lowerCase letter and 1 symbol " << endl;
        cin >> password;
    }

    cout << centerTabs << "Repeat the password: " << endl;
    cin >> password2;
    while (password != password2)
    {
        cout << "The second password NE SUVPADA S PURVATA" << endl;
        cin >> password2;
    }

    ofstream f1("users.txt", ios::app);
    f1 << userId << ':' << Hasher(password) << ':' << "0" << endl;

    system("cls");
    cout << centerTabs << " Registration is succesful !" << endl;
    main();
}

int Hasher(string& password)
{
    unsigned int hashedPassword;

    for(unsigned int ch:password){
        hashedPassword = ch + (hashedPassword<<5)+(hashedPassword<<10)- hashedPassword;
    }


    return hashedPassword;
}


bool passwordChecker(string password)
{

    if (passwordLength(password) < 5)
    {
        return false;
    }

    int lowerCaseCounter = 0, upperCaseCounter = 0, symbolCounter = 0;
    int i = 0;
    while (password[i] != '\0')
    {
        char temp = password[i];
        if (temp >= 'a' && temp <= 'z')
        {
            lowerCaseCounter++;
        }
        else if (temp >= 'A' && temp <= 'Z')
        {
            upperCaseCounter++;
        }
        else if (temp == '!' || temp == '@' || temp == '#' || temp == '$' || temp == '%' || temp == '^' || temp == '&' || temp == '*')
        {
            symbolCounter++;
        }
        else if(temp>='0'&& temp<='9')
        {

        }
        else
        {
            return false;
        }
        i++;
    }
    if (lowerCaseCounter > 0 && upperCaseCounter > 0 && symbolCounter > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int passwordLength(string password)
{
    int length = 0;
    for (int i = 0; password[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}