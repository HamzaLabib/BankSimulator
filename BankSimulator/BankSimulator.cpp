// BankSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include<stdlib.h>
#include<time.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::fixed;
//arrays are decalred gobaly so it can be accesed from anywhere
const int MAX_ACCOUNTS_LIMIT = 100;
string firstNames[MAX_ACCOUNTS_LIMIT];
string lastNames[MAX_ACCOUNTS_LIMIT];
int accountNumbers[MAX_ACCOUNTS_LIMIT];
double balances[MAX_ACCOUNTS_LIMIT];
//function decalrations
int getUserInt();
int getUserIntInLimits(int min, int max);
double getUserDouble();
string getUserString();
bool getUserBool();
int searchArray(int toSearch[], int arraySize, int searchAccount);
int randomAccountNumbers();
void swapInt(int intArray[], int index1, int index2);
void swapDoubles(double doubleArray[], int index1, int index2);
void swapString(string stringArray[], int index1, int index2);
int addAccount();
void removeAccount(int accountNumber);
int clientInformation(int accountNumber);
double depositMoney(double depositAmount, int accountNumber);
double withdrawMoney(double withdrawlAmount, int accountNumber);
void sortByBalance(double arrayToSort[], int arraySize);
void displaySortedInfo();
double averageBalance(int arraySize);
double totalBalance(int arraySize);
bool exit();

int main()
{
    //assigning a bool variable for the exit function to exit from application or go back to main menu
    bool close = true;
    //assigning a bool variable for the while loop to run again
    bool goAgain = true;
    while (goAgain)
    {
        //A series of output strings for the user to understand the choices
        system("Color F2");
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "                       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BANKING SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2" << endl;;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << " Main Menu:" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << " 1.Start a New Bank Account" << endl << endl;
        cout << " 2.Remove A Bank Account" << endl << endl;
        cout << " 3.View The Information of An Account" << endl << endl;
        cout << " 4.Deposit Money into an Account" << endl << endl;
        cout << " 5.Withdraw Money From an Account" << endl << endl;
        cout << " 6.View all The Account in Order" << endl << endl;
        cout << " 7.Calculate the Average Balance value of all Accounts" << endl << endl;
        cout << " 8.Calculate the Total Balance value of all  Accounts" << endl << endl;
        cout << " 9.Exit The Application" << endl;
        cout << endl;
        // Assigning a variable which registers the input for the switch case
        int choice = getUserIntInLimits(1, 9);
        //The Switch
        switch (choice)
        {
            // A addAccount Function is called to start a new account and it returns an Account Number for the client
        case 1:
        {

            cout << "The New Account Number:" << addAccount() << endl;
            cout << "------------------------------" << endl;
            break;
        }
        //A removeAccount function is called to remove an account and it takes an Account Number as parameter
        case 2:
        {
            cout << "Enter the Acoount number of the client to remove account" << endl;
            int acctNumber = getUserIntInLimits(100000, 999999);
            removeAccount(acctNumber);
            break;
        }
        //A clientInformation fuction is called to display the details of a specfic client when a client's Account Number is given as input
        case 3:
        {
            cout << "Enter the account number of the client you wish to see the information" << endl;
            int acctNumber = getUserIntInLimits(100000, 999999);
            clientInformation(acctNumber);
            break;
        }
        //A depositMoney function is called to deposit a given amount to the specified account
        case 4:
        {
            cout << "Enter the account Number to Deposit an Amount" << endl;
            int acctNumber = getUserIntInLimits(100000, 999999);
            //this function is called to display the details of the selected client
            acctNumber = clientInformation(acctNumber);
            cout << "Enter the amount to be Deposited:";
            double depositAmt = getUserDouble();
            cout << endl;
            double newBalance = depositMoney(depositAmt, acctNumber);
            cout << "The Deposit Successful" << endl << endl;
            cout << "------------------------------" << endl;
            cout << "The New Balance:" << newBalance << endl;
            cout << "------------------------------" << endl;
            break;
        }
        //A withdrawMoney function is called to withdraw a specifed amount from the specifed client account
        case 5:
        {
            cout << "Enter the account Number to Withdraw from" << endl;
            int acctNumber = getUserIntInLimits(100000, 999999);
            acctNumber = clientInformation(acctNumber);
            cout << "Enter the amount to be Withdrawn:";
            double withdrawlAmt = getUserDouble();
            cout << endl;
            //withdrawMoney function takes withdrawl amount and the client account number as parameters
            double newBalance = withdrawMoney(withdrawlAmt, acctNumber);
            cout << "The Withdrawl Successful" << endl << endl;
            cout << "------------------------------" << endl;
            cout << "The New Balance:" << newBalance << endl;
            cout << "------------------------------" << endl;
            break;
        }
        //A sortByBalance fuction is called to sort all the balance in ascending order
        case 6:
        {
            //this fuction takes an array of acount balances and the maximum array length as parameters
            sortByBalance(balances, MAX_ACCOUNTS_LIMIT);
            //this function is used to display the sorted array
            displaySortedInfo();
            break;
        }
        //this case calls a function to display the averages of all the balances of all the accounts just takes the maximum length of the array as parameter
        case 7:
        {
            cout << "-----------------------------------------" << endl;
            cout << fixed << "The Average of all the Account Balances:" << averageBalance(MAX_ACCOUNTS_LIMIT) << endl;
            cout << "-----------------------------------------" << endl;
            break;
        }
        //this case calls a fucntion the calculates total of all the balances in the accounts by taking the array length as parameter
        case 8:
        {
            cout << "-----------------------------------------" << endl;
            cout << fixed << "The Total of all the Acoount Balances:" << totalBalance(MAX_ACCOUNTS_LIMIT) << endl;
            cout << "-----------------------------------------" << endl;
            break;
        }
        //this case exits the application
        case 9:
        {
            close = exit();
            break;
        }

        }
        if (choice == 9 && close == 1) //this allows you to quit the program
            goAgain = 0;
        else if (choice == 9 && close == 0) //this allows you to continue the program
            goAgain = 1;
        else
        {
            //this allows you to continue or quit the program
            cout << "Would like to choose another fuction to run 0-NO||1-Yes:";
            goAgain = getUserBool();
        }
    }
    return 0;

}
//input validiation for getting an integer input from the user
int getUserInt()
{
    int userInt;
    cin >> userInt;
    while (cin.fail() || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: " << endl;
        cin >> userInt;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return userInt;
}
//input valditaion for getting an integer input within the specified limits
int getUserIntInLimits(int min, int max)
{
    int userInt;
    do
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Please enter number between " << min << " and " << max << endl;
        userInt = getUserInt();
        cout << "--------------------------------------------------------------------------------" << endl;
    } while (userInt < min || userInt > max);

    return userInt;
}
//input validation to get a double input from the user
double getUserDouble()
{
    double userInt;
    cin >> userInt;
    while (cin.fail() || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: " << endl;
        cin >> userInt;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return userInt;
}
//input validation to get a string input from the user
string getUserString()
{
    string userString;
    getline(cin, userString);
    return userString;
}
//input validation to get a bool input from the user
bool getUserBool()
{
    int userInput;
    cin >> userInput;

    while (userInput != 1 && userInput != 0)
    {
        cout << "Invalid. Please try again by enter " << 1 << " or " << 0 << endl;
        cin >> userInput;
    }
    return userInput == true;
}
//takes an array and it size and search parameter to check if the element exist in the specifed array or not
int searchArray(int toSearch[], int arraySize, int searchAccount)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (toSearch[i] == searchAccount)
            return i;
    }
    return -1;
}
//this function generates a random number within the specified range 
int randomAccountNumbers()
{
    int randomNumber;
    srand(time(0));
    randomNumber = 100000 + (rand() % 999999);

    return randomNumber;
}
//this function swaps the elements of an integer array
void swapInt(int intArray[], int index1, int index2)
{

    int temp = intArray[index1];
    intArray[index1] = intArray[index2];
    intArray[index2] = temp;
}
//this function swaps the elements of a  array of doubles
void swapDoubles(double doubleArray[], int index1, int index2)
{
    double temp = doubleArray[index1];
    doubleArray[index1] = doubleArray[index2];
    doubleArray[index2] = temp;
}
//this function swaps a string array
void swapString(string stringArray[], int index1, int index2)
{
    string temp = stringArray[index1];
    stringArray[index1] = stringArray[index2];
    stringArray[index2] = temp;
}
//this function adds new account details
int addAccount()
{

    for (int i = 0; i < MAX_ACCOUNTS_LIMIT; i++)
    {
        //checking condition to see new information is added to and empty memory location 
        if (firstNames[i] == "" && lastNames[i] == "" && accountNumbers[i] == 0 && balances[i] == 0)
        {
            cout << "Please enter the First Name of the New Account Holder:";
            string fName = getUserString();
            firstNames[i] = fName;
            cout << endl;
            cout << "Please enter the Last Name of the New Account Holder:";
            string lName = getUserString();
            lastNames[i] = lName;
            cout << endl;
            cout << "Please enter an Opening Balance:";
            double openingBalance = getUserDouble();
            balances[i] = openingBalance;
            //a random number is generated using randomAccountNumber function and its assigned to the client
            accountNumbers[i] = randomAccountNumbers();
            cout << "-----------------------------------------" << endl;
            cout << "New Account Opening Successful" << endl;
            cout << "-----------------------------------------" << endl;
            return accountNumbers[i];
        }
    }
}
//to display the information of a specific client and return the right account number if the user enter wrong for one time
int clientInformation(int accountNumber)
{
    int acctNumber = accountNumber;
    //search to see if the client is valid 
    int clientInfoId = searchArray(accountNumbers, MAX_ACCOUNTS_LIMIT, accountNumber);
    while (clientInfoId == -1)
    {
        cout << "The requested Account Number Not found" << endl;
        acctNumber = accountNumber = getUserIntInLimits(100000, 999999);
        clientInfoId = searchArray(accountNumbers, MAX_ACCOUNTS_LIMIT, accountNumber);
    }
    cout << "Client information:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "First name: " << firstNames[clientInfoId] << endl;
    cout << "Last name: " << lastNames[clientInfoId] << endl;
    cout << "Account number: " << accountNumbers[clientInfoId] << endl;
    cout << "Balance: " << balances[clientInfoId] << endl;
    cout << "-----------------------------------------" << endl;

    return acctNumber;
}
//this function removes the information of a client informatiom from the arrays
void removeAccount(int accountNumber)
{
    int clientDelId = searchArray(accountNumbers, MAX_ACCOUNTS_LIMIT, accountNumber);
    if (clientDelId == -1)
    {
        cout << "The requested Account Number Not found" << endl;
    }
    else
    {
        //sets the arrays element at the point to the intial positions
        firstNames[clientDelId] = "";
        lastNames[clientDelId] = "";
        accountNumbers[clientDelId] = 0;
        balances[clientDelId] = 0;
        cout << "The Account has been removed" << endl;
    }
}
//this function takes a depositAmount and account number as parameters and deposits that amount to the respective account number
double depositMoney(double depositAmount, int accountNumber)
{
    int clientDepositId = searchArray(accountNumbers, MAX_ACCOUNTS_LIMIT, accountNumber);
    balances[clientDepositId] += depositAmount;
    return balances[clientDepositId];

}
//this function takes a in a widrawlAmount and account number as parameters and withdraws the specified amount from the account number
double withdrawMoney(double withdrawlAmount, int accountNumber)
{
    int clientWithdrawlId = searchArray(accountNumbers, MAX_ACCOUNTS_LIMIT, accountNumber);
    //checking condition to see if the withdraw amount is less the balance avilable
    while (withdrawlAmount > balances[clientWithdrawlId])
    {
        cout << "Not Enough Balance in the acoount|||Enter a lesser Amount:";
        withdrawlAmount = getUserDouble();
    }
    if (balances[clientWithdrawlId] >= withdrawlAmount)
    {
        balances[clientWithdrawlId] -= withdrawlAmount;
        return balances[clientWithdrawlId];
    }

}
// function sorts the balance array using bubblesort it also sorts other corresponding arrays so as to get indivdual data of the client in the initilized order
void sortByBalance(double arrayToSort[], int arraySize)
{

    for (int i = 0; i < arraySize - 1; i++)
    {
        for (int j = 0; j < (arraySize - 1) - i; j++)
        {
            if (arrayToSort[j] > arrayToSort[j + 1])
            {
                swapDoubles(arrayToSort, j, j + 1);
                swapString(firstNames, j, j + 1);
                swapString(lastNames, j, j + 1);
                swapInt(accountNumbers, j, j + 1);
            }
        }
    }

}
//this function is used to just display the information in the arrays 
void displaySortedInfo()
{
    cout << "All The Accounts" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < MAX_ACCOUNTS_LIMIT; i++)
    {
        if (accountNumbers[i] != 0)
        {

            cout << "First Name:" << firstNames[i] << endl;
            cout << "Last Name:" << lastNames[i] << endl;
            cout << "Account Number:" << accountNumbers[i] << endl;
            cout << "Account Balance:" << balances[i] << endl;
            cout << "------------------------------------------------------------------" << endl;
        }

    }
}
//this function calculates the average of the balances in all the accounts
double averageBalance(int arraySize)
{
    double sum = 0;
    int count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (balances[i] > 0)
        {
            sum += balances[i];
            count++;
        }

    }

    if (count < 1)
        return sum / 1;
    else
        return sum / (double)count;
}
//this function returns the total balance from all the accounts
double totalBalance(int arraySize)
{
    double total = 0;
    for (int i = 0; i < arraySize; i++)
    {
        total += balances[i];
    }
    return total;
}

//this function to exit from the application
bool exit()
{
    bool closeProgram;
    cout << endl << "Are you sure you want to close the program? 0-NO||1-Yes:" << endl;
    closeProgram = getUserBool();
    return closeProgram;
}