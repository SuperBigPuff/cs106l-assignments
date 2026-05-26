# include <iostream>
class BankAccount{
    private:
    std::string AccountName;
    int balance;
    bool isValid(int balance);
    public:
    BankAccount();
    BankAccount(int initialBalance);
    void setAccountName(std::string name);
    std::string getAccountName() const;
    int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
};