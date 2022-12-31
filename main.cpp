#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include "functions.h"
using namespace std;

const string centerTabs = "\t\t\t\t\t\t\t   ", halfOfCenterTabs = "\t\t\t\t\t   ";

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
        Login();
        break;
    case 'l':
        Login();
        break;
    case 'R':
        Registration();
        break;
    case 'r':
        Registration();
        break;
    case 'Q':
        cout << "Thank you for the use!";
        return 0;
    case 'q':
        cout << "Thank you for the use!";
        return 0;
    default:
        cout << "Enter valid letter";
        main();
        break;
    }
}
void Menu(int lineIndex)
{
    char choice;

    cout << endl;
    cout << centerTabs << "Please choose one of the following:" << endl;
    cout << centerTabs << "D - deposit" << endl;
    cout << centerTabs << "W - withdraw" << endl;
    cout << centerTabs << "T -transfer" << endl;
    cout << centerTabs << "C -cancel account" << endl;
    cout << centerTabs << "L -logout" << endl;

    cin >> choice;

    switch (choice)
    {
    case 'D':
        Deposit(lineIndex);
        break;
    case 'd':
        Deposit(lineIndex);
        break;
    case 'W':
        Withdraw(lineIndex);
        break;
    case 'w':
        Withdraw(lineIndex);
        break;
    case 'T':
        Transfer(lineIndex);
        break;
    case 't':
        Transfer(lineIndex);
        break;
    case 'C':
        DeleteAccount(lineIndex);
        break;
    case 'c':
        DeleteAccount(lineIndex);
        break;
    case 'L':
        main();
        break;
    case 'l':
        main();
        break;
    }
}

void Login()
{
    system("cls");
    ifstream input("users.txt");
    string line;

    string userId, password, fileId, filePass;
    string balance;
    bool match;
    hash<string> hasher;

    cout << centerTabs << "Please enter your username " << endl;
    cin >> userId;
    cout << centerTabs << "Please enter your  password" << endl;
    cin >> password;

    string hashedPassword = to_string(hasher(password));
    //this is the index of the line with the users information
    int lineIndex =0;

    while (getline(input, line))
    {
        separateTheLine(line, fileId, filePass, balance);

        // cout<< fileId<<endl<<filePass<<endl;
        // cout<< hashedPassword<<endl;

        if (userId == fileId)
        {
            if (hashedPassword == filePass)
            {
                cout << "Login succesful";
                input.close();
                Menu(lineIndex);
            }
        }
        lineIndex++;
    }
    cout << "Wrong password, try again";
    Login();
}
void Registration()
{

    system("cls");
    string userId, password, password2, rId, rPass;
    hash<string> hasher;

    cout << centerTabs << "Enter the username you want to use: " << endl;
    cin >> userId;

    while (!isUsernameFree(userId))
    {
        cout << "Username is taken, try another";
        cin >> userId;
    }

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

    ofstream input("users.txt");
    input << userId << ':' << hasher(password) << ':' << "0" << endl;
    input.close();

    system("cls");
    cout << centerTabs << " Registration is succesful !" << endl;
    main();
}
void Deposit(int lineIndex)
{

    string username,password,tempBalance;
    fstream file("users.txt");
    fstream temp("temp.txt");
    string line;

    double deposit;
    cout << "Enter the ammount of money you want to deposit" << endl;
    cin >> deposit;

    for(int i=0 ;i<=lineIndex;i++){
        getline(file,line);

        if(i == lineIndex){
        
            separateTheLine(line, username,password,tempBalance);
            line.clear();
            double balance = stringToDouble(tempBalance);
            balance+= deposit;

            //cout<<username<<":"<< password<<":"<<balance<<endl;
            temp<<username<<":"<< password<<":"<<balance<<endl;
        }else{
            temp<<line<<endl;
        }
    }

    overwriteFile("users.txt","temp.txt",lineIndex);
    cout<<"The deposit was succesful";

    Menu(lineIndex);
}
void Withdraw(int lineIndex)
{
    string username,password,tempBalance;
    fstream file("users.txt");
    fstream temp("temp.txt");
    string line;

    double deposit;
    cout << "Enter the ammount of money you want to withdraw" << endl;
    cin >> deposit;

    for(int i=0 ;i<=lineIndex;i++){
        getline(file,line);

        if(i == lineIndex){

            separateTheLine(line, username,password,tempBalance);
            line.clear();
            double balance = stringToDouble(tempBalance);
            balance-= deposit;

            //cout<<username<<":"<< password<<":"<<balance<<endl;
            temp<<username<<":"<< password<<":"<<balance<<endl;
        }else{
            temp<<line<<endl;
        }
    }

    overwriteFile("users.txt","temp.txt",lineIndex);
    cout<<"The deposit was succesful";

    Menu(lineIndex);
}
void Transfer(int lineIndex)
{
}
void DeleteAccount(int lineIndex)
{
}
void overwriteFile(string name, string tempName,int lineIndex){
    ofstream file(name);
    fstream temp(tempName);
    string line;

    for(int i=0 ; i<= lineIndex;i++){
        getline(temp,line);
        file<<line;
        
    }
    file.close();
    temp.close();
}

unsigned stringToInt(string str)
{
    unsigned result = 0;
    for (char ch : str)
    {
        result = result * 10 + ch - '0';
    }
    return result;
}
int numbersAfterComa(string str){
    bool coma = false;
    int counter =0;
    for(int i=0;str[i]!='\0';i++){
        if(coma){
            counter++;
        }
        if(str[i]==','||str[i]=='.' ){
            coma = true;
        }
    }

    return  counter;
}
double stringToDouble(string str)
{
    double number =0;

    for(int i=0;str[i]!='\0';i++){
        if(str[i] == '.'|| str[i] == ','){
            continue;
        }
        number=number*10+ (str[i]-'0')*10;
    }
    int digitsAfterComa= numbersAfterComa(str);
    digitsAfterComa++;

    while (digitsAfterComa>0){
        number/=10;
        digitsAfterComa--;
    }

    return number;

}

string intToString(int n)
{
    string str = to_string(n);
    return str;
}


void separateTheLine(string line, string &username, string &password, string &balance)
{
    username.clear();
    password.clear();
    balance.clear();

    int counterOfTwoDots = 0;

    for (int i = 0, j = 0; line[i] != '\0'; i++)
    {
        char temp = line[i];
        if (temp == ':')
        {
            counterOfTwoDots++;
            j = 0;
            continue;
        }
        if (counterOfTwoDots == 0)
        {
            username.push_back(temp);
            // username[i] = temp;
        }
        if (counterOfTwoDots == 1)
        {
            password.push_back(temp);
            // password[j] = temp;
            j++;
        }
        if (counterOfTwoDots == 2)
        {
            balance.push_back(temp);
            // balance[j] = temp;
            j++;
        }
    }
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
        else if (temp >= '0' && temp <= '9')
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
bool isUsernameFree(string username)
{

    ifstream file1("users.txt");
    string fileUsername, password, balance;
    string line;
    while (getline(file1, line))
    {
        separateTheLine(line, fileUsername, password, balance);
        if (fileUsername == username)
        {
            return false;
        }
    }
    return true;
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