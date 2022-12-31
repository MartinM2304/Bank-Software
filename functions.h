#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
int main();
void Menu(int lineIndex);
void Login();
void Registration();
bool isUsernameFree(std::string username);
void Deposit(int lineIndex);
void Withdraw(int lineIndex);
void Transfer(int lineIndex);
void DeleteAccount(int lineIndex);
void passwordHasher(std::string password);
bool passwordChecker(std::string password);
int passwordLength(std::string password);
unsigned stringToInt(std::string str);
double stringToDouble(std::string str);
void overwriteFile(std::string name, std::string tempName,int lineIndex);
void separateTheLine(std::string line, std::string &username,std::string &password,std::string &balance);
std::string intToString(int n);

#endif