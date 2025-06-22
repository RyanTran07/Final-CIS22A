/*
 * Names: Ryan Tran, Eliab Tedros, Yong Doo Kim, Trung Tran, Khin Yadanar Kyaw
 * Team Name: Boolean Bunch
 *
 * Description: This program is a menu-based system where a user has the choice
 *              to select a multitude of different burgers and select a valid
 *              quantity of that burger that they would like to add to their
 *              burger. They then select whether they are a student or a
 *              staff member. The program performs input validation on all
 *              inputted values to ensure that they are reasonable and valid.
 *              The program then writes and displays values such as the
 *              quantities of each burger that is ordered, the cost per item,
 *              the total before tax, the tax amount, and then the final total
 *              to the screen and a text file.
 *
 * Note: For input validation, the implementation made sure that the range of
 *       inputted values of correct. While we wanted to implement checks to
 *       prevent different invalid types from being entered, we haven't learned some
 *       of those concepts yet. However, we could use istringstream
 *       as well as .fail() to ensure input is correct, however, we haven't
 *       covered that, so we stuck with our normal implementation.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Global variables
const int ARR_SIZE = 5;
double PRICE_ARRAY[5] = {5.25, 5.75, 5.95, 5.95, 5.95};
string BURGER_ARRAY[5] = { "De Anza Burger", "Bacon Cheese", "Mushroom Swiss", "Western Burger", "Don Cali Burger" };
int orderArray[5] = {0, 0, 0, 0, 0}; // To track quantities ordered

int burgerCustomerInput();
void displayMenu();
bool getBurgerInputs();
void calculate(double &subTotal, double &taxAmount, double &finalBill, int customerType);
void printAndSaveBill(double subTotal, double taxAmount, double finalBill);
void saveBillToFile(double subTotal, double taxAmount, double finalBill);



int main() {
    double subTotal = 0, taxAmount = 0, finalBill = 0;
    int customerType = burgerCustomerInput();

    // Calculates and sets the values of sub total, amount of tax, and final bill.
    calculate(subTotal, taxAmount, finalBill, customerType);

    // Writes the final bill to display and saves it into a text file.
    printAndSaveBill(subTotal, taxAmount, finalBill);

    return 0;
}

int burgerCustomerInput() {

    bool orderEnded = false;
    while(!orderEnded) {
        displayMenu();
        cout << "6. End Order" << endl;
        orderEnded = getBurgerInputs();
    }

     // Customer type input selection
     int userCustomerType;
     cout << "\nAre you a student or staff?" << endl;
     cout << "1. Student\n" << "2. Staff\n";
     cin.ignore();
     cin >> userCustomerType;

     // Input validation for customer type (student or staff)
     while(userCustomerType != 1 && userCustomerType != 2) {
         cout << "Please enter a correct customer type: ";
         cin >> userCustomerType;
     }

     return userCustomerType;
}


void displayMenu() {
    for(int i = 0; i < ARR_SIZE; i++) {
        cout << i + 1 << ". " << BURGER_ARRAY[i] << " - $" << PRICE_ARRAY[i] << endl;
    }

}


bool getBurgerInputs() {
    int burgerSelection = 0;
    int userQuantity = 0;
    cout << "\nPlease choose a burger option, or select 6 to end order: ";
        cin >> burgerSelection;

        // Input validation for the option selection.
        while(burgerSelection < 1 || burgerSelection > 6) {
            cout << "Please choose a valid option (1-6): ";
            cin >> burgerSelection;
        }

        // Break out of the function if the user wants to end their order.
        if(burgerSelection == 6) {
            return true;
        }

        // Trailing-else if a burger is selected.
        else {

            // User input selection for the number of burgers selected
            cout << "\nHow many burgers would you like? : ";
            cin >> userQuantity;

            // Input validation, only allows non-negative input for # of burgers
            while(userQuantity < 0) {
                cout << "Please enter a non-negative number of burgers to order: ";
                cin >> userQuantity;
            }

            // Switch cases user selection, adds inputted quantity to selected burger
            switch(burgerSelection) {
                case 1:
                    orderArray[0] += userQuantity;
                    break;
                case 2:
                    orderArray[1] += userQuantity;
                    break;
                case 3:
                    orderArray[2] += userQuantity;
                    break;
                case 4:
                    orderArray[3] += userQuantity;
                    break;
                case 5:
                    orderArray[4] += userQuantity;
                    break;
            }
        }
        return false;
}


void calculate(double &subTotal, double &taxAmount, double &finalBill, int customerType) {
    for(int i = 0; i < ARR_SIZE; i++) {
        subTotal += (PRICE_ARRAY[i] * orderArray[i]);
    }

    if(customerType == 2) {
        taxAmount = (subTotal * .09);
    }

    finalBill = subTotal + taxAmount;

}

void printAndSaveBill(double subTotal, double taxAmount, double finalBill) {
    cout << fixed << showpoint << setprecision(2);

    cout << endl;

    // Quantity Ordered Display
    for(int i = 0; i < ARR_SIZE; i++) {
        cout << BURGER_ARRAY[i] << " Quantity Ordered: " << orderArray[i] << endl;
    }

    // Displaying the cost of each burger individually
    cout << "\nCost Per Item: " << endl;
    for(int i = 0; i < ARR_SIZE; i++) {
        cout << BURGER_ARRAY[i] << ": $" << PRICE_ARRAY[i] << " x " << orderArray[i] << " = $" << (orderArray[i] * PRICE_ARRAY[i]);
        cout << endl;
    }

    // Displaying the subtotal of each burger (cost of all items before tax)
    cout << "\nTotal Before Tax: $" << subTotal << endl;

    // Display the amount of tax
    cout << "\nTax Amount: $" << taxAmount << endl;

    // Display the final total
    cout << "\nFinal Total: $" << (subTotal + taxAmount) << endl;

    saveBillToFile(subTotal, taxAmount, finalBill);

}

void saveBillToFile(double subTotal, double taxAmount, double finalBill) {
    ofstream outputFile;

    unsigned seed = time(0);
    srand(seed);

    int randomNumber = rand() % 1001 + 1000;
    string fileName = to_string(randomNumber) + ".txt";
    outputFile.open(fileName);

    if(outputFile) {
        outputFile << fixed << showpoint << setprecision(2);

        outputFile << endl;

        // Quantity Ordered Display
        for(int i = 0; i < ARR_SIZE; i++) {
            outputFile << BURGER_ARRAY[i] << " Quantity Ordered: " << orderArray[i] << endl;
        }

        // Displaying the cost of each burger individually
        outputFile << "\nCost Per Item: " << endl;
        for(int i = 0; i < ARR_SIZE; i++) {
            outputFile << BURGER_ARRAY[i] << ": $" << PRICE_ARRAY[i] << " x " << orderArray[i] << " = $" << (orderArray[i] * PRICE_ARRAY[i]);
            outputFile << endl;
        }

        // Displaying the subtotal of each burger (cost of all items before tax)
        outputFile << "\nTotal Before Tax: $" << subTotal << endl;

        // Display the amount of tax
        outputFile << "\nTax Amount: $" << taxAmount << endl;

        // Display the final total
        outputFile << "\nFinal Total: $" << (subTotal + taxAmount) << endl;
        outputFile.close();

    }
}
