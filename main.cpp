#include <iostream>
#include <fstream>
#include "functions.h"
using  namespace  std;

const string centerTabs = "\t\t\t\t\t\t   ";
const string FILE_NAME = "users.txt";
int fileLengthInLines =0;

int main(){

    char choice;
    fileLengthInLines = fileLength();

    string *usernames = new string[fileLengthInLines+1];
    string *passwords = new string[fileLengthInLines+1];
    double *balances = new double[fileLengthInLines+1];
    fillInformation(usernames,passwords,balances);

    cout << endl;
    cout << centerTabs << "Please choose one of the following:" << endl;
    cout << centerTabs << "L - login" << endl;
    cout << centerTabs << "R - register" << endl;
    cout << centerTabs << "Q -quit" << endl;

    cin >> choice;

    switch (choice)
    {
        case 'L':
            Login(usernames,passwords,balances);
            break;
        case 'l':
            Login(usernames,passwords,balances);
            break;
        case 'R':
            Registration(usernames,passwords,balances);
            break;
        case 'r':
            Registration(usernames,passwords,balances);
            break;
        case 'Q':
            cout << "Thank you for the use!";
            break;
        case 'q':
            cout << "Thank you for the use!";
            break;
        default:
            cout << "Enter valid letter";
            main();
            break;
    }
    exitApp(usernames,passwords,balances);

    delete[] usernames;
    delete[] passwords;
    delete[] balances;

    return 0;
}
void Menu(int userIndex,string*usernames,string*passowords,double*balances){

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
            Deposit(userIndex,usernames,passowords,balances);
            break;
        case 'd':
            Deposit(userIndex,usernames,passowords,balances);
            break;
        case 'W':
            Withdraw(userIndex,usernames,passowords,balances);
            break;
        case 'w':
            Withdraw(userIndex,usernames,passowords,balances);
            break;
        case 'T':
            Transfer(userIndex,usernames,passowords,balances);
            break;
        case 't':
            Transfer(userIndex,usernames,passowords,balances);
            break;
        case 'C':
            DeleteAccount(userIndex,usernames,passowords,balances);
            break;
        case 'c':
            DeleteAccount(userIndex,usernames,passowords,balances);
            break;
        case 'L':
            exitApp(usernames,passowords,balances);
            main();
            break;
        case 'l':
            exitApp(usernames,passowords,balances);
            main();
            break;
        default:
            cout<<"Enter a valid letter";
            Menu(userIndex,usernames,passowords,balances);
    }
}
//Register and Login
void Login(string*usernames,string*passowords,double*balances){


    string username,password;
    string fileUsername,filePassword,fileBalance;
    bool match;
    int userIndex;
    hash<string>hasher;

    cout<<"Enter your username"<<endl;
    cin>>username;
    cout<<"Enter your password"<<endl;
    cin>>password;
    string hashedPassword = to_string(hasher(password));
    for(int i=0;i<fileLengthInLines;i++){
        fileUsername = usernames[i];
        filePassword= passowords[i];
        if(username==fileUsername){
            if(filePassword== hashedPassword){
                cout<<"Login succesful";
                userIndex =i;
                Menu(userIndex,usernames,passowords,balances);
            }else{
                cout<<"Wrong password,try again"<<endl;
                Login(usernames,passowords,balances);
            }
        }
    }
    cout<<"Username doesnt exist, please try again"<<endl;
    Login(usernames,passowords,balances);


}
void Registration(string*usernames,string*passowords,double*balances){

    system("cls");
    string username,password,repeatPassword;
    hash<string> hasher;

    cout<<centerTabs<<"Enter the username you want to use: "<<endl;
    cin>>username;
    while (!isUsernameFree(username)){
        cout<<centerTabs<<"Username is taken, try another"<<endl;
        cin>>username;
    }
    cout<<centerTabs<<"Enter the password you want to use:"<<endl;
    cin>>password;

    while (!passwordChecker(password))
    {
        cout << "Your password must be at least 5 characters long and have at least 1 Capital letter, 1 lowerCase letter and 1 symbol " << endl;
        cin >> password;
    }
    cout << centerTabs << "Repeat the password: " << endl;
    cin >> repeatPassword;
    while (password != repeatPassword)
    {
        cout << "The second password doesnt match" << endl;
        cin >> repeatPassword;
    }
    usernames[fileLengthInLines]= username;
    passowords[fileLengthInLines] = to_string(hasher(password));
    balances[fileLengthInLines] = 0;
    fileLengthInLines++;

    system("cls");
    cout<<centerTabs<<"Registration is succesful!"<<endl;
    exitApp(usernames,passowords,balances);
    main();
}

//Menu Functions
void Deposit(int userIndex,string*usernames,string*passowords,double*balances){

    double balance= balances[userIndex];
    double depositAmount;
    cout<<"Enter the amount you want to deposit"<<endl;
    cin>>depositAmount;
    while (depositAmount<=0){
        cout<<"Enter a valid amount"<<endl;
        cin>>depositAmount;
    }
    balance+=depositAmount;
    balances[userIndex] = balance;
    Menu(userIndex,usernames,passowords,balances);
}
void Withdraw(int userIndex,string*usernames,string*passowords,double*balances){

    double balance= balances[userIndex];
    double withdrawAmount;
    cout<<"Enter the amount you want to withdraw"<<endl;
    cin>>withdrawAmount;
    while (withdrawAmount<=0){
        cout<<"Enter a valid amount"<<endl;
        cin>>withdrawAmount;
    }
    while (balance+10000<withdrawAmount){
        cout<<"You dont have that much money."<<endl;
        cin>>withdrawAmount;
    }
    balance-=withdrawAmount;
    balances[userIndex] = balance;
    Menu(userIndex,usernames,passowords,balances);

}
void Transfer(int userIndex,string*usernames,string*passowords,double*balances){

    double transferAmount=0;
    string transferUsername,transferBalance;
    double balanceOfUser = balances[userIndex];
    double balanceOfReciever;
    string UsernameYouWantToTransfer;

    cout<<"Enter the account you want to transfer money"<<endl;
    cin>>UsernameYouWantToTransfer;

    for(int i=0;i<fileLengthInLines;i++){
        transferUsername = usernames[i];

        if(UsernameYouWantToTransfer == transferUsername){
            balanceOfReciever= balances[i];

            cout<<"Enter the amount you want to transfer."<<endl;
            cin>>transferAmount;

            while (transferAmount<=0){
                cout<<"Enter a correct amount"<<endl;
                cin>>transferAmount;
            }
            while (balanceOfUser+10000<transferAmount)
            {
                cout<<"You can't transfer that much. Enter a valid ammount"<<endl;
                cin>>transferAmount;
            }
            balanceOfUser-= transferAmount;
            balanceOfReciever+= transferAmount;

            balances[i] = balanceOfReciever;
            balances[userIndex]= balanceOfUser;

            cout<<"The transfer was succesful"<<endl;
            Menu(userIndex,usernames,passowords,balances);


        }
    }
    cout<<"The username doesnt exist, try again";
    Menu(userIndex,usernames,passowords,balances);

}
void DeleteAccount(int userIndex,string*usernames,string*passowords,double*balances){

    hash<string > hasher;

    string password = passowords[userIndex];
    string enteredPassword;
    cout<<"Enter your password"<<endl;
    cin>>enteredPassword;
    string hashedPassword = to_string(hasher(enteredPassword));

    if(hashedPassword!=password){
        cout<<"Wrong password"<<endl;
        Menu(userIndex,usernames,passowords,balances);
    }

    string *tempUsernames = new string[fileLengthInLines];
    string *tempPasswords = new string[fileLengthInLines];
    double *tempBalances = new double [fileLengthInLines];

    for(int i=0,j=0;i<fileLengthInLines;i++){
        if(i==userIndex){

        }else{
            tempUsernames[j]=usernames[i];
            tempPasswords[j] = passowords[i];
            tempBalances[j]= balances[i];
            j++;
        }
    }
    fileLengthInLines--;
    for(int i=0;i<fileLengthInLines;i++){
        usernames[i]=tempUsernames[i];
        passowords[i]=tempPasswords[i];
        balances[i]=tempBalances[i];
    }
    main();

}

//File Handling
void fillInformation(string*usernames,string*passwords,double*balances){
    ifstream file(FILE_NAME);
    string line;
    string tempUsername,tempPassword,tempBalance;
    double balance;

    for(int i=0;i<fileLengthInLines;i++){
        getline(file,line);

        separateTheLine(line,tempUsername,tempPassword,tempBalance);
        balance = stringToDouble(tempBalance);
        usernames[i]=tempUsername;
        passwords[i] = tempPassword;
        balances[i] = balance;
    }
    file.close();
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
        }
        if (counterOfTwoDots == 1)
        {
            password.push_back(temp);
            j++;
        }
        if (counterOfTwoDots == 2)
        {
            balance.push_back(temp);
            j++;
        }
    }
}
int fileLength(){
    int counterOfLines =0;

    ifstream file(FILE_NAME);
    string line;
    while (getline(file,line)){
        counterOfLines++;
    }
    return counterOfLines;
}
void exitApp(string*usernames,string*passwords,double*balances){
    ofstream file(FILE_NAME);
    for(int i=0;i<fileLengthInLines;i++){
        file<<usernames[i]<<':'<<passwords[i]<<':'<<balances[i]<<endl;
    }
    file.close();
}

//for numbers
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



//For passwords:
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

    ifstream file1(FILE_NAME);
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