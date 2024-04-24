#include <iostream>
using namespace std;

class Account {
public:
    explicit Account(double initialBalance) 
    {
        if (initialBalance < 0.0) 
        {
            balance = 0.0;
            cerr << "Error: Initial balance cannot be negative. Set balance to 0.0." <<endl;
        } 
        else 
        {
            balance = initialBalance;
        }
    }

    void credit(double amount) 
    {
        balance += amount;
    }

    bool debit(double amount) 
    {
        if (amount <= balance) 
        {
            balance -= amount;
            return true;
        } 
        else 
        {
            cerr << "Debit amount exceeded account balance." <<endl;
            return false;
        }
    }

    double getBalance() const 
    {
        return balance;
    }

private:
    double balance;
};

class SavingsAccount : public Account 
{
public:
    explicit SavingsAccount(double initialBalance, double interestRate)
        : Account(initialBalance), interestRate(interestRate) {}

    double calculateInterest() const 
    {
        return getBalance() * interestRate / 100.0;
    }

private:
    double interestRate;
};

class CheckingAccount : public Account 
{
public:
    explicit CheckingAccount(double initialBalance, double transactionFee)
        : Account(initialBalance), transactionFee(transactionFee) {}

    void credit(double amount)  
    {
        Account::credit(amount - transactionFee);
    }

    bool debit(double amount) 
    {
        if (Account::debit(amount)) 
        {
            Account::debit(transactionFee);
            return true;
        }
        return false;
    }

private:
    double transactionFee;
};

int main() 
{
    // Example usage
    SavingsAccount savings(1000.0, 2.5); // Initial balance of $1000 and 2.5% interest rate
    savings.credit(savings.calculateInterest()); // Add interest
    cout << "Savings account balance: $" << savings.getBalance() <<endl;

    CheckingAccount checking(500.0, 1.0); // Initial balance of $500 and $1 transaction fee
    checking.credit(200.0); // Deposit $200
    checking.debit(100.0); // Withdraw $100
    cout << "Checking account balance: $" << checking.getBalance() <<endl;

    return 0;
}
