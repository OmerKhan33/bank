#include<iostream>
#include <iostream>
#include <string>

using namespace std;

// Base class: Package
class Package {
protected:
    string senderName;
    string senderAddress;
    string senderCity;
    string senderState;
    string senderZIP;
    string recipientName;
    string recipientAddress;
    string recipientCity;
    string recipientState;
    string recipientZIP;
    double weight; // in ounces
    double costPerOunce; // cost per ounce

public:
    // Constructor to initialize data members
    Package(const string& sender, const string& senderAddr, const string& senderCity,
            const string& senderState, const string& senderZIP,
            const string& recipient, const string& recipientAddr, const string& recipientCity,
            const string& recipientState, const string& recipientZIP,
            double weight, double costPerOunce)
        : senderName(sender), senderAddress(senderAddr), senderCity(senderCity),
          senderState(senderState), senderZIP(senderZIP),
          recipientName(recipient), recipientAddress(recipientAddr), recipientCity(recipientCity),
          recipientState(recipientState), recipientZIP(recipientZIP),
          weight(weight), costPerOunce(costPerOunce) 
    {
        if (weight <= 0 || costPerOunce <= 0) 
        {
            cerr << "Error: Weight and cost per ounce must be positive values." << endl;
            exit(1);
        }
    }

    // Calculate shipping cost
    double calculateCost() const {
        return weight * costPerOunce;
    }
};

// Derived class: TwoDayPackage
class TwoDayPackage : public Package {
private:
    double flatFee; // additional flat fee for two-day delivery

public:
    // Constructor to initialize TwoDayPackage
    TwoDayPackage(const string& sender, const string& senderAddr, const string& senderCity,
                  const string& senderState, const string& senderZIP,
                  const string& recipient, const string& recipientAddr, const string& recipientCity,
                  const string& recipientState, const string& recipientZIP,
                  double weight, double costPerOunce, double flatFee)
        : Package(sender, senderAddr, senderCity, senderState, senderZIP,
                  recipient, recipientAddr, recipientCity, recipientState, recipientZIP,
                  weight, costPerOunce),
          flatFee(flatFee) {}

    // Override calculateCost for TwoDayPackage
    double calculateCost() const {
        return Package::calculateCost() + flatFee;
    }
};

// Derived class: OvernightPackage
class OvernightPackage : public Package {
private:
    double additionalFeePerOunce; // additional fee per ounce for overnight delivery

public:
    // Constructor to initialize OvernightPackage
    OvernightPackage(const string& sender, const string& senderAddr, const string& senderCity,
                     const string& senderState, const string& senderZIP,
                     const string& recipient, const string& recipientAddr, const string& recipientCity,
                     const string& recipientState, const string& recipientZIP,
                     double weight, double costPerOunce, double additionalFee)
        : Package(sender, senderAddr, senderCity, senderState, senderZIP,
                  recipient, recipientAddr, recipientCity, recipientState, recipientZIP,
                  weight, costPerOunce),
          additionalFeePerOunce(additionalFee) {}

    // Override calculateCost for OvernightPackage
    double calculateCost() const {
        return Package::calculateCost() + (additionalFeePerOunce * weight);
    }
};

int main() {
    // Create objects of each type of package
    TwoDayPackage twoDay("John", "123 Main St", "CityA", "StateA", "12345",
                         "Alice", "456 Elm St", "CityB", "StateB", "67890",
                         10.5, 0.5, 5.0);

    OvernightPackage overnight("Bob", "789 Oak St", "CityC", "StateC", "54321",
                               "Eve", "987 Pine St", "CityD", "StateD", "98765",
                               8.0, 0.6, 2.0);

    // Calculate and display shipping costs
    cout << "Two-Day Package Cost: $" << twoDay.calculateCost() << endl;
    cout << "Overnight Package Cost: $" << overnight.calculateCost() << endl;

    return 0;
}
