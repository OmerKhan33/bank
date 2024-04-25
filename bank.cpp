#include <iostream>
using namespace std;

// Base class for bank accounts
class Account {
public:
    //constructor
    explicit Account(double initialBalance) 
    {
        if (initialBalance < 0.0) 
        {
            balance = 0.0;
            // Display an error message if initial balance is negative
            cerr << "Error: Initial balance cannot be negative. Set balance to 0.0." << endl;
        } 
        else 
        {
            balance = initialBalance;
        }
    }

    void credit(double amount) 
    {
        // Add the given amount to the account balance
        balance += amount;
    }

    bool debit(double amount) 
    {
        if (amount <= balance) 
        {
            // Subtract the given amount from the account balance
            balance -= amount;
            return true;
        } 
        else 
        {
            // Display an error message if debit amount exceeds balance
            cerr << "Debit amount exceeded account balance." << endl;
            return false;
        }
    }

    double getBalance() const 
    {
        // Return the current account balance
        return balance;
    }

private:
    double balance; // Data member to store account balance
};

// Derived class for savings accounts
class SavingsAccount : public Account 
{
public:
    explicit SavingsAccount(double initialBalance, double interestRate)
        : Account(initialBalance), interestRate(interestRate) {}

    double calculateInterest() const 
    {
        // Calculate interest earned based on interest rate
        return getBalance() * interestRate / 100.0;
    }

private:
    double interestRate; // Data member for interest rate
};

// Derived class for checking accounts
class CheckingAccount : public Account 
{
public:
    explicit CheckingAccount(double initialBalance, double transactionFee)
        : Account(initialBalance), transactionFee(transactionFee) {}

    void credit(double amount)  
    {
        // Adjust balance after deducting transaction fee
        Account::credit(amount - transactionFee);
    }

    bool debit(double amount) 
    {
        if (Account::debit(amount)) 
        {
            // Charge transaction fee for successful debit
            Account::debit(transactionFee);
            return true;
        }
        return false;
    }

private:
    double transactionFee; // Data member for transaction fee
};

int main() 
{
    // Example usage
    SavingsAccount savings(1000.0, 2.5); // Initial balance of $1000 and 2.5% interest rate
    savings.credit(savings.calculateInterest()); // Add interest
    cout << "Savings account balance: $" << savings.getBalance() << endl;

    CheckingAccount checking(500.0, 1.0); // Initial balance of $500 and $1 transaction fee
    checking.credit(200.0); // Deposit $200
    checking.debit(100.0); // Withdraw $100
    cout << "Checking account balance: $" << checking.getBalance() << endl;

    return 0;
}

