#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int main();
void Menu(int lineIndex);
void Login(std::string*usernames,std::string*passowords,double*balances);
void Registration(std::string*usernames,std::string*passowords,double*balances);

void fillInformation(std::string*usernames,std::string*passwords,double*balances);
void exitApp(std::string*usernames,std::string*passwords,double*balances);

void Deposit(int userIndex,std::string*usernames,std::string*passowords,double*balances);
void Withdraw(int userIndex,std::string*usernames,std::string*passowords,double*balances);
void Transfer(int userIndex,std::string*usernames,std::string*passowords,double*balances);
void DeleteAccount(int userIndex,std::string*usernames,std::string*passowords,double*balances);

void separateTheLine(std::string line, std::string &username,std::string &password,std::string &balance);
double stringToDouble(std::string str);
int fileLength();

int numbersAfterComa(std::string str);
double roundNumber(double a);

bool passwordChecker(std::string password);
bool isUsernameFree(std::string username);
int passwordLength(std::string password);

#endif
