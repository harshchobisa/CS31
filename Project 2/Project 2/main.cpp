//
//  main.cpp
//  Project 2
//
//  Created by Harsh Chobisa on 10/10/18.
//  Copyright © 2018 Harsh Chobisa. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    //all variables that have values inputted by the user
    int odomStart;
    int odomEnd;
    int rentalDays;
    int month;
    string name;
    string luxury;
    
    //input of data and checking that data is valid
    cout << "Odometer at start: ";
    cin >> odomStart;
    if (odomStart < 0) {
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Odometer at end: ";
    cin >> odomEnd;
    if (odomEnd < odomStart)
    {
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        return 1;
    }
    
    cout << "Rental days: ";
    cin >> rentalDays;
    if (rentalDays <= 0)
    {
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;
        return 1;
    }
    
    cin.ignore(10000, '\n');
    cout << "Customer name: ";
    getline(cin, name);
    if (name == "") {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    cout << "Luxury car? (y/n): ";
    getline(cin, luxury);
    if (luxury != "y" && luxury != "n")
    {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return 1;
    }
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    if (month > 12 || month < 1)
    {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }
    
    // calculation of charge
    double charge;
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    if (luxury == "y")
    {
        charge = rentalDays * 61;
    }
    else
    {
        charge = rentalDays * 33;
    }
    
    int totalMiles = odomEnd - odomStart;
    
    //after calculating for more than 400 miles, subtract off miles to calculate for 400-101 miles,
    //then subtract to calculate for less than 101 miles
    if (totalMiles > 400)
    {
        int chargedMiles = totalMiles - 400;
        charge = charge + (chargedMiles * 0.19);
        totalMiles = totalMiles - chargedMiles;
        
    }
    if ((totalMiles <= 400) && (totalMiles >= 101))
    {
        double rate;
        if (month == 12 || month <= 3)
        {
            rate = 0.27;
        }
        else
        {
            rate = 0.21;
        }
        
        int chargedMiles = totalMiles - 100;
        charge = charge + (chargedMiles * rate);
        totalMiles = totalMiles - chargedMiles;
        
    }
    charge = charge + 0.27 * totalMiles;
    cout << "---" << endl;
    cout << "The rental charge for " << name << " is $" << charge << endl;
    return 0;
}
