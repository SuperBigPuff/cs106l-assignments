#include <iostream>
#include "class.h"

BankAccount::BankAccount(){
    AccountName = "Default Account";
    balance = 0;
}

BankAccount::BankAccount(int initialBalance){
    if(isValid(initialBalance)){
        balance = initialBalance;
    } else {
        balance = 0;
    }   
}

bool BankAccount::isValid(int balance){
    return balance >= 0;
}

void BankAccount::setAccountName(std::string name){
    AccountName = name;
}

std::string BankAccount::getAccountName() const{
    return AccountName;
}

int BankAccount::getBalance() const{
    return balance;
}

void BankAccount::deposit(int amount){
    if(isValid(amount)){
        balance += amount;
    } else {
        std::cout << "Invalid deposit amount." << std::endl;
    }
}

void BankAccount::withdraw(int amount){
    if(isValid(amount) && balance >= amount){
        balance -= amount;
    } else {
        std::cout << "Invalid withdrawal amount or insufficient funds." << std::endl;
    }
}
