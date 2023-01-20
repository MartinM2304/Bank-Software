/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Martin Petrov Matinkov
* @idnumber 5MI0600202
* @compiler gcc (I use CLion)
*
* Bank software
*
*/


#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

const string CENTERING_TABS = "\t\t\t\t\t\t   ";
const string FILE_NAME = "users.txt";
int fileLengthInLines = 0;
const string ENTER_MINUS_1_TO_EXIT = "Enter -1 if you want to go back";


void startingMenu() {

    string *usernames = new string[fileLengthInLines + 1];
    string *passwords = new string[fileLengthInLines + 1];
    double *balances = new double[fileLengthInLines + 1];
    fillInformation(usernames, passwords, balances);

    char choice;

    while (choice != 'q' && choice != 'Q') {

        system("cls");
        cout << CENTERING_TABS << "Please choose one of the following: " << endl;
        cout << CENTERING_TABS << "L - login" << endl;
        cout << CENTERING_TABS << "R - register" << endl;
        cout << CENTERING_TABS << "Q - quit" << endl;

        cin >> choice;

        switch (choice) {
            case 'L':
                Login(usernames, passwords, balances);
                break;
            case 'l':
                Login(usernames, passwords, balances);
                break;
            case 'R':
                Registration(usernames, passwords, balances);
                break;
            case 'r':
                Registration(usernames, passwords, balances);
                break;
            case 'q':
                cout << "Thank you for the use! "<< endl;
                break;
            case 'Q':
                cout << "Thank you for the use! "<< endl;
                break;
            default:
                cout << "Enter Valid letter " << endl;
        }


    }
    exitApp(usernames, passwords, balances);

    delete[] usernames;
    delete[] passwords;
    delete[] balances;

    exit(0);

}

int main() {

    fileLengthInLines = fileLength();

    cout << CENTERING_TABS << "#      #         #####           ####" << endl;
    cout << CENTERING_TABS << "#     #          #    #         #    #" << endl;
    cout << CENTERING_TABS << "#    #           #    #         #" << endl;
    cout << CENTERING_TABS << "#   #            #    #         #" << endl;
    cout << CENTERING_TABS << "#  #             #   #          #" << endl;
    cout << CENTERING_TABS << "# #              #  #           #" << endl;
    cout << CENTERING_TABS << "#                # #            #" << endl;
    cout << CENTERING_TABS << "# #              #  #           #" << endl;
    cout << CENTERING_TABS << "#  #             #   #          #" << endl;
    cout << CENTERING_TABS << "#   #            #    #         #" << endl;
    cout << CENTERING_TABS << "#    #           #    #         #" << endl;
    cout << CENTERING_TABS << "#     #          #    #         #    #" << endl;
    cout << CENTERING_TABS << "#      #         #####           ####" << endl;

    startingMenu();


    return 0;

}

void Menu(int userIndex, string *usernames, string *passowords, double *balances) {

    char choice;

    cout << endl;
    cout << CENTERING_TABS << "Please choose one of the following:" << endl;
    cout << CENTERING_TABS << "D - deposit" << endl;
    cout << CENTERING_TABS << "W - withdraw" << endl;
    cout << CENTERING_TABS << "T - transfer" << endl;
    cout << CENTERING_TABS << "C - cancel account" << endl;
    cout << CENTERING_TABS << "L - logout" << endl;

    cin >> choice;

    switch (choice) {
        case 'D':
            Deposit(userIndex, usernames, passowords, balances);
            break;
        case 'd':
            Deposit(userIndex, usernames, passowords, balances);
            break;
        case 'W':
            Withdraw(userIndex, usernames, passowords, balances);
            break;
        case 'w':
            Withdraw(userIndex, usernames, passowords, balances);
            break;
        case 'T':
            Transfer(userIndex, usernames, passowords, balances);
            break;
        case 't':
            Transfer(userIndex, usernames, passowords, balances);
            break;
        case 'C':
            DeleteAccount(userIndex, usernames, passowords, balances);
            break;
        case 'c':
            DeleteAccount(userIndex, usernames, passowords, balances);
            break;
        case 'L':
            exitApp(usernames, passowords, balances);
            startingMenu();
            break;
        case 'l':
            exitApp(usernames, passowords, balances);
            startingMenu();
            break;
        default:
            cout << "Enter a valid letter";
            Menu(userIndex, usernames, passowords, balances);
    }
}

//Register and Login
void Login(string *usernames, string *passwords, double *balances) {

    system("cls");

    cout << CENTERING_TABS << ENTER_MINUS_1_TO_EXIT << endl;

    hash<string> hasher;
    string username, password;
    string fileUsername, filePassword, fileBalance;
    int userIndex;

    cout << "Enter your username" << endl;
    cin >> username;

    if (username == "-1") {
        return;
    }
    cout << "Enter your password" << endl;
    cin >> password;
    if (password == "-1") {
        return;
    }
    string hashedPassword = to_string(hasher(password));

    for (int i = 0; i < fileLengthInLines; i++) {
        fileUsername = usernames[i];
        filePassword = passwords[i];
        if (username == fileUsername) {
            if (filePassword == hashedPassword) {
                cout << "Login succesful"<<endl;
                userIndex = i;
                Menu(userIndex, usernames, passwords, balances);
            } else {
                cout << "Wrong password,try again" << endl;
                Login(usernames, passwords, balances);
            }
        }
    }
    cout << "Username doesnt exist, please try again" << endl;
    Login(usernames, passwords, balances);


}

void Registration(string *usernames, string *passowords, double *balances) {

    system("cls");
    string username, password, repeatPassword;
    hash<string> hasher;


    cout << CENTERING_TABS << "Enter the username you want to use: " << endl;
    cout << CENTERING_TABS << "The username cant contain spaces " << endl;
    cin >> username;

    if (username == "-1") {
        return;
    }

    while (usernameContainOnlySpaces(username) || username==""){
        cout<<"Enter a valid username"<<endl;
        cin>>username;
    }
    while (!isUsernameFree(usernames, username)) {
        cout << CENTERING_TABS << "Username is taken, try another" << endl;
        cin >> username;
    }
    cout << CENTERING_TABS << "Enter the password you want to use:" << endl;
    cin >> password;

    while (!passwordChecker(password)) {
        cout
                << "Your password must be at least 5 characters long and have at least 1 Capital letter, 1 lowerCase letter and 1 symbol "
                << endl;
        cin >> password;
    }
    cout << CENTERING_TABS << "Repeat the password: " << endl;
    cin >> repeatPassword;
    while (password != repeatPassword) {
        cout << "The second password doesnt match" << endl;
        cin >> repeatPassword;
    }
    usernames[fileLengthInLines] = username;
    passowords[fileLengthInLines] = to_string(hasher(password));
    balances[fileLengthInLines] = 0;
    fileLengthInLines++;

    system("cls");
    cout << CENTERING_TABS << "Registration is succesful!" << endl;

    exitApp(usernames, passowords, balances);

    startingMenu();

}

//Menu Functions
void Deposit(int userIndex, string *usernames, string *passowords, double *balances) {

    double balance = balances[userIndex];
    double depositAmount;
    cout << "Enter the amount you want to deposit" << endl;
    cin >> depositAmount;
    depositAmount = roundNumber(depositAmount);


    while (depositAmount <= 0) {
        cout << "Enter a valid amount" << endl;
        cin >> depositAmount;
    }
    balance += depositAmount;
    balances[userIndex] = balance;
    cout << "The deposit was succesful."<<endl;
    cout<< "You deposited "<<depositAmount<<endl;
    Menu(userIndex, usernames, passowords, balances);
}

void Withdraw(int userIndex, string *usernames, string *passowords, double *balances) {

    double balance = balances[userIndex];
    double withdrawAmount;
    cout << "Enter the amount you want to withdraw" << endl;
    cin >> withdrawAmount;

    withdrawAmount = roundNumber(withdrawAmount);

    while (withdrawAmount <= 0) {
        cout << "Enter a valid amount" << endl;
        cin >> withdrawAmount;
    }
    if (balance + 10000 < withdrawAmount) {
        cout << "You dont have that much money." << endl;
        Menu(userIndex, usernames, passowords, balances);
    }
    balance -= withdrawAmount;
    balances[userIndex] = balance;
    cout << "The withdraw was succesful!";
    Menu(userIndex, usernames, passowords, balances);

}

void Transfer(int userIndex, string *usernames, string *passowords, double *balances) {

    double transferAmount = 0;
    string transferUsername, transferBalance;
    double balanceOfUser = balances[userIndex];
    double balanceOfReciever;
    string UsernameYouWantToTransfer;

    cout << "Enter the account you want to transfer money" << endl;
    cin >> UsernameYouWantToTransfer;

    for (int i = 0; i < fileLengthInLines; i++) {
        transferUsername = usernames[i];

        if (UsernameYouWantToTransfer == transferUsername) {
            balanceOfReciever = balances[i];

            cout << "Enter the amount you want to transfer." << endl;
            cin >> transferAmount;
            transferAmount = roundNumber(transferAmount);

            while (transferAmount <= 0) {
                cout << "Enter a correct amount" << endl;
                cin >> transferAmount;
            }
            while (balanceOfUser + 10000 < transferAmount) {
                cout << "You can't transfer that much. Enter a valid ammount" << endl;
                cin >> transferAmount;
            }
            balanceOfUser -= transferAmount;
            balanceOfReciever += transferAmount;

            balances[i] = balanceOfReciever;
            balances[userIndex] = balanceOfUser;

            cout << "The transfer was succesful" << endl;
            Menu(userIndex, usernames, passowords, balances);


        }
    }
    cout << "The username doesnt exist, try again";
    Menu(userIndex, usernames, passowords, balances);

}

void clearArray(double *arr) {
    for (int i = 0; i < fileLengthInLines; i++) {
        arr[i] = 0;
    }
}

void clearArray(string *arr) {
    for (int i = 0; i < fileLengthInLines; i++) {
        arr[i] = "";
    }
}

void DeleteAccount(int userIndex, string *usernames, string *passowords, double *balances) {

    hash<string> hasher;

    string password = passowords[userIndex];
    string enteredPassword;
    cout << "Enter your password" << endl;
    cin >> enteredPassword;
    string hashedPassword = to_string(hasher(enteredPassword));

    if (hashedPassword != password) {
        cout << "Wrong password" << endl;
        Menu(userIndex, usernames, passowords, balances);
    }

    string *tempUsernames = new string[fileLengthInLines + 1];
    string *tempPasswords = new string[fileLengthInLines + 1];
    double *tempBalances = new double[fileLengthInLines + 1];

    for (int i = 0, j = 0; i < fileLengthInLines; i++) {
        if (i == userIndex) {

        } else
        {
            tempUsernames[j] = usernames[i];
            tempPasswords[j] = passowords[i];
            tempBalances[j] = balances[i];
            j++;
        }
    }
    clearArray(usernames);
    clearArray(passowords);
    clearArray(balances);

    fileLengthInLines--;
    for (int i = 0; i < fileLengthInLines; i++) {
        usernames[i] = tempUsernames[i];
        passowords[i] = tempPasswords[i];
        balances[i] = tempBalances[i];
    }
    exitApp(usernames, passowords, balances);
    main();

}

//File Handling
void fillInformation(string *usernames, string *passwords, double *balances) {
    ifstream file(FILE_NAME);
    string line;
    string tempUsername, tempPassword, tempBalance;
    double balance;

    for (int i = 0; i < fileLengthInLines; i++) {
        getline(file, line);

        separateTheLine(line, tempUsername, tempPassword, tempBalance);
        balance = stringToDouble(tempBalance);
        usernames[i] = tempUsername;
        passwords[i] = tempPassword;
        balances[i] = balance;
    }
    file.close();
}


void separateTheLine(string line, string &username, string &password, string &balance) {
    username.clear();
    password.clear();
    balance.clear();

    int counterOfTwoDots = 0;

    for (int i = 0, j = 0; line[i] != '\0'; i++) {
        char temp = line[i];
        if (temp == ':') {
            counterOfTwoDots++;
            j = 0;
            continue;
        }
        if (counterOfTwoDots == 0) {
            username.push_back(temp);
        }
        if (counterOfTwoDots == 1) {
            password.push_back(temp);
            j++;
        }
        if (counterOfTwoDots == 2) {
            balance.push_back(temp);
            j++;
        }
    }
}

int fileLength() {
    int counterOfLines = 0;

    ifstream file(FILE_NAME);
    string line;
    while (getline(file, line)) {
        counterOfLines++;
    }
    return counterOfLines;
}

void exitApp(string *usernames, string *passwords, double *balances) {
    ofstream file(FILE_NAME);
    for (int i = 0; i < fileLengthInLines; i++) {
        file << usernames[i] << ':' << passwords[i] << ':' << balances[i] << endl;
    }
    file.close();
}

//for numbers
int numbersAfterComa(string str) {
    bool coma = false;
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (coma) {
            counter++;
        }
        if (str[i] == ',' || str[i] == '.') {
            coma = true;
        }
    }

    return counter;
}

double stringToDouble(string str) {
    double number = 0;


    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.' || str[i] == ',' || str[i] == '-') {
            continue;
        }
        number = number * 10 + (str[i] - '0') * 10;
    }

    int digitsAfterComa = numbersAfterComa(str);
    digitsAfterComa++;

    while (digitsAfterComa > 0) {
        number /= 10;
        digitsAfterComa--;
    }

    if (str[0] == '-') {
        return -number;
    } else
    {
        return number;
    }
}

double roundNumber(double a) {

    int c = (int) (a * 100 + 0.5);
    float b = c / 100.0;
    return b;
}


//For password and username:
bool passwordChecker(string password) {

    if (passwordLength(password) < 5) {
        return false;
    }

    int lowerCaseCounter = 0, upperCaseCounter = 0, symbolCounter = 0;
    int i = 0;
    while (password[i] != '\0') {
        char temp = password[i];
        if (temp >= 'a' && temp <= 'z') {
            lowerCaseCounter++;
        }
        else if (temp >= 'A' && temp <= 'Z') {
            upperCaseCounter++;
        }
        else if (temp == '!' || temp == '@' || temp == '#' || temp == '$' || temp == '%' || temp == '^' ||
                   temp == '&' || temp == '*' || temp == '_') {
            symbolCounter++;
        }
        else if (temp >= '0' && temp <= '9') {
        }
        else {
            return false;
        }
        i++;
    }
    if (lowerCaseCounter > 0 && upperCaseCounter > 0 && symbolCounter > 0) {
        return true;
    } else
    {
        return false;
    }
}

bool isUsernameFree(const string *usernames, const string username) {

    for (int i = 0; i < fileLengthInLines; i++) {
        if (usernames[i] == username) {
            return false;
        }
    }
    return true;
}
bool usernameContainOnlySpaces(string username){
    for(char ch:username){
        if(ch !=' '){
            return false;
        }
    }
    return true;
}

int passwordLength(string password) {
    int length = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        length++;
    }
    return length;
}