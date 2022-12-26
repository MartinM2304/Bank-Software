#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
int main();
void login();
void registration();
void passwordHasher(std::string password);
bool passwordChecker(std::string password);
int passwordLength(std::string password);
int Hasher(std::string &password);

#endif