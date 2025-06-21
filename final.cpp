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

using namespace std;

void displayMenu(double priceArr[], string burgerArr[]) {
    cout << "1. De Anza Burger - $5.25 \n"
    << "2. Bacon Cheese Burger - $5.75\n"
    << "3. Mushroom Swiss Burger - $5.95\n"
    << "4. Western Burger - $5.95\n"
    << "5. Don Cali Burger - $5.95\n"
    << "6. End Order" << endl;
}


bool getInputs(string burgerArr[], int orderArr[], int arrSize) {
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
                    orderArr[0] += userQuantity;
                    break;
                case 2:
                    orderArr[1] += userQuantity;
                    break;
                case 3:
                    orderArr[2] += userQuantity;
                    break;
                case 4:
                    orderArr[3] += userQuantity;
                    break;
                case 5:
                    orderArr[4] += userQuantity;
                    break;
            }
        }
        return false;
}

void printBill(double priceArr[], int orderArr[], double totalPriceArr[], double subTotal, double taxAmount, double finalBill) {
    cout << fixed << showpoint << setprecision(2);

    // Displaying the cost of each burger individually
    cout << "\nCost Per Item: " << endl;
    cout << "De Anza Burger: $5.25 x " << orderArr[0]  << " = $" << totalPriceArr[0] << endl;
    cout << "Bacon Cheese Burger: $5.75 x " << orderArr[1] << " = $" << totalPriceArr[1] << endl;
    cout << "Mushroom Swiss Burger: $5.95 x " << orderArr[2] << " = $" << totalPriceArr[2] << endl;
    cout << "Western Burger: $5.95 x " << orderArr[3] << " = $" << totalPriceArr[3] << endl;
    cout << "Don Cali Burger: $5.95 x " << orderArr[4] << " = $" << totalPriceArr[4] << endl;

    // Displaying the subtotal of each burger (cost of all items before tax)
    cout << "\nTotal Before Tax: $" << subTotal << endl;

    // Display the amount of tax
    cout << "\nTax Amount: $" << taxAmount << endl;

    // Display the final total
    cout << "\nFinal Total: $" << (subTotal + taxAmount) << endl;
}

void calculate(double priceArr[], int orderArr[], double totalPriceArr[], int arrSize, double &subTotal, double &taxAmount, double &finalBill, int customerType) {
    for(int i = 0; i < arrSize; i++) {
        totalPriceArr[i] = (priceArr[i] * orderArr[i]);
        subTotal += totalPriceArr[i];
    }
    if(customerType == 2) {
        taxAmount = (subTotal * .09);
    }

    finalBill = subTotal + taxAmount;

}

int userInputLoop(double priceArr[], string burgerArr[], int orderArr[], int arrSize) {
    bool orderEnded = false;
    while(!orderEnded) {
        displayMenu(priceArr, burgerArr);
        orderEnded = getInputs(burgerArr, orderArr, arrSize);
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

int main() {

    double PRICE_ARRAY[5] = {5.25, 5.75, 5.95, 5.95, 5.95};
    string BURGER_ARRAY[5] = { "De Anza Burger", "Bacon Cheese", "Mushroom Swiss", "Western Burger", "Don Cali Burger" };
    int orderArray[5] = {0, 0, 0, 0, 0}; // To track quantities ordered
    double totalPriceArray[5] = {0, 0, 0, 0, 0};
    double subTotal = 0, taxAmunt = 0, finalBill = 0;
    int customerType = userInputLoop(PRICE_ARRAY, BURGER_ARRAY, orderArray, 5);

    // DEBUG
    cout << "EXITED FUNCTION" << endl;
    cout << customerType << endl;

    for(int i = 0; i < 5; i++) {
        cout << BURGER_ARRAY[i] << " " << orderArray[i] << endl;
    }


    //Display numbered list of menu items.
    /*

    int quantity1 = 0, quantity2 = 0, quantity3 = 0, quantity4 = 0, quantity5 = 0;
    int userQuantity;
    int burgerSelection;
    bool orderEnded = false;
    cout << "1. De Anza Burger - $5.25 \n"
         << "2. Bacon Cheese Burger - $5.75\n"
         << "3. Mushroom Swiss Burger - $5.95\n"
         << "4. Western Burger - $5.95\n"
         << "5. Don Cali Burger - $5.95\n"
         << "6. End Order" << endl;

    // User input loop for burger selection.
    while(!orderEnded) {
        cout << "\nPlease choose a burger option, or select 6 to end order: ";
        cin >> burgerSelection;

        // Input validation for the option selection.
        while(burgerSelection < 1 || burgerSelection > 6) {
            cout << "Please choose a valid option (1-6): ";
            cin >> burgerSelection;
        }

        // break out of the while loop if the order is supposed to end
        if(burgerSelection == 6) {
            orderEnded = true;
            break;
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
                    quantity1 += userQuantity;
                    break;
                case 2:
                    quantity2 += userQuantity;
                    break;
                case 3:
                    quantity3 += userQuantity;
                    break;
                case 4:
                    quantity4 += userQuantity;
                    break;
                case 5:
                    quantity5 += userQuantity;
                    break;
            }
        }

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




    // Displaying the quantity of each burger that is ordered.
    cout << "\nOrdered Items and Quantities:" << endl;
    cout << "De Anza Burger Quantity Ordered: " << quantity1 << endl;
    cout << "Bacon Cheese Burger Quantity Ordered: " << quantity2 << endl;
    cout << "Mushroom Swiss Burger Quantity Ordered: " << quantity3 << endl;
    cout << "Western Burger Quantity Ordered: " << quantity4 << endl;
    cout << "Don Cali Burger Quantity Ordered: " << quantity5 << endl;

    // Calculations for the cost of each type of burger separately.
    double costQuantity1 = 5.25 * quantity1;
    double costQuantity2 = 5.75 * quantity2;
    double costQuantity3 = 5.95 * quantity3;
    double costQuantity4 = 5.95 * quantity4;
    double costQuantity5 = 5.95 * quantity5;

    // Output formatting, in fixed point notation, always show point and two decimal points
    // The reason why I didn't put the formatting higher up is because it
    // wouldn't make sense to have a decimal number of burgers ordered.
    cout << fixed << showpoint << setprecision(2);

    // Displaying the cost of each burger individually
    cout << "\nCost Per Item: " << endl;
    cout << "De Anza Burger: $5.25 x " << quantity1 << " = $" << costQuantity1 << endl;
    cout << "Bacon Cheese Burger: $5.75 x " << quantity2 << " = $" << costQuantity2 << endl;
    cout << "Mushroom Swiss Burger: $5.95 x " << quantity3 << " = $" << costQuantity3 << endl;
    cout << "Western Burger: $5.95 x " << quantity4 << " = $" << costQuantity4 << endl;
    cout << "Don Cali Burger: $5.95 x " << quantity5 << " = $" << costQuantity5 << endl;


    // Calculation for the subTotal (cost of all burgers ordered)
    double subTotal = costQuantity1 + costQuantity2 + costQuantity3 + costQuantity4 + costQuantity5;

    // Displaying the subtotal of each burger (cost of all items before tax)
    cout << "\nTotal Before Tax: $" << subTotal << endl;


    // Declaring and initializing a variable to represent tax
    double taxAmount = 0;

    // If the customer is a staff member, calculate tax amount.
    if(userCustomerType == 2) {
        taxAmount = subTotal * .09;
    }

    // Display the amount of tax
    cout << "\nTax Amount: $" << taxAmount << endl;

    // Display the final total
    cout << "\nFinal Total: $" << (subTotal + taxAmount) << endl;


    // Make an ofstream object and open a new output.txt file
    ofstream outputFile;
    outputFile.open("output.txt");

    // If file successfully opened, write the monetary value of the final bill
    if(outputFile) {

        outputFile << "Ordered Items and Quantities:" << endl;
        outputFile << "De Anza Burger Quantity Ordered: " << quantity1 << endl;
        outputFile << "Bacon Cheese Burger Quantity Ordered: " << quantity2 << endl;
        outputFile << "Mushroom Swiss Burger Quantity Ordered: " << quantity3 << endl;
        outputFile << "Western Burger Quantity Ordered: " << quantity4 << endl;
        outputFile << "Don Cali Burger Quantity Ordered: " << quantity5 << endl;
        outputFile << endl;

        outputFile << fixed << showpoint << setprecision(2);
        // Writing the cost per item
        outputFile << "Cost Per Item: " << endl;
        outputFile << "De Anza Burger: $5.25 x " << quantity1 << " = $" << costQuantity1 << endl;
        outputFile << "Bacon Cheese Burger: $5.75 x " << quantity2 << " = $" << costQuantity2 << endl;
        outputFile << "Mushroom Swiss Burger: $5.95 x " << quantity3 << " = $" << costQuantity3 << endl;
        outputFile << "Western Burger: $5.95 x " << quantity4 << " = $" << costQuantity4 << endl;
        outputFile << "Don Cali Burger: $5.95 x " << quantity5 << " = $" << costQuantity5 << endl;

        // Writing the sub total
        outputFile << "\nTotal Before Tax: $" << subTotal << endl;

        // Displaying the tax amount
        outputFile << "\nTax Amount: $" << taxAmount << endl;

        // Displaying the final bill
        outputFile << "\nFinal Bill: $" << (subTotal + taxAmount) << endl;
        outputFile.close();
    }

    // Trailing-else displays an error message if file did not open properly.
    else {
        cout << "There was an issue opening the file." << endl;
    }
    */

    return 0;
}
