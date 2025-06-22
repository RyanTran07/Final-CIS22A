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

// Function prototypes
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

/*
 * This function continuously displays a menu and a prompt asking whether
 * they would like to order more burgers. It returns the type of customer
 * that the user is (staff or student). It calls the getBurgerInputs() function
 * for each while loop iteration.
 *
 * Called in main.
 *
 * Receives: N/A
 * Returns: An integer (1 or 2) representing if the user is a student or staff member.
 * Uses: N/A
 * Output: Displays the menu and input prompts for the menu selection and
 *         customer type selection.
 */
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
     cout << ">";
     cin.ignore();
     cin >> userCustomerType;

     // Input validation for customer type (student or staff)
     while(userCustomerType != 1 && userCustomerType != 2) {
         cout << "Please enter a correct customer type: ";
         cin >> userCustomerType;
     }

     return userCustomerType;
}

/*
 * This function displays the menu in the format:
 * 1. [burger name] - $ [burger price]
 *
 * Purpose: This function is called for every time the user chooses to
 * continue ordering in the burgerCustomerInput function.
 *
 * Receives: N/A
 *
 * Returns: N/A
 *
 * Uses: BURGER_ARRAY - Global array storing the burger names.
 *       PRICE_ARRAY - Global array storing the prices of each burger.
 * Output: A menu of burgers.
 */
void displayMenu() {
    for(int i = 0; i < ARR_SIZE; i++) {
        cout << i + 1 << ". " << BURGER_ARRAY[i] << " - $" << PRICE_ARRAY[i] << endl;
    }

}


/*
 * This function collects input on what burger the user wants to order, how many
 * of each burger, and adds it to their order by modifying the global orderArray
 * array.
 *
 * It is called in the burgerCustomerInput() function, in a while loop to allow
 * the user to continue ordering until they choose option 6 (end order)
 *
 * Receives: N/A
 *
 * Returns: True - User chooses to end their order.
 *          False - User wants to continue ordering.
 *
 * Uses: BURGER_ARRAY - Global array storing burger name
 *       orderArray - Global array storing the quantities of each burger.
 *
 * Output: Adds the user's desired number of burgers of their selected burger to
 *         their order in orderArray.
 */

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
            cout << "\nHow many " << BURGER_ARRAY[burgerSelection-1] << "'s would you like? : ";
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


/*
 * This function calculates and modifies the arguments passed into the subTotal,
 * taxAmount, and finalBill parameters, thus appropriately storing the
 * calculated values for the sub total, amount of tax, and what the final bill
 * is in main.
 *
 * Receives: subTotal - A reference variable (type double) representing the sub total of the order.
 *           taxAmount - A reference variable (type double) representing the amount of tax charged in the order.
 *           finalBill - A reference variable (type double) representing the final total (sub total + tax) of the order.abort
 *           customerType - A variable representing what type of customer the user is.
 * Returns: N/A
 *
 * Uses: PRICE_ARRAY - Global array storing the burger prices.
 *       orderArray - Global array storing the quantities of each burger.
 *
 * Output: Modifies the arguments passed into subTotal, taxAmount, and finalBill
 *         with the calculations for sub total, the tax amount, and the final bill
 *         respectively.
 */

void calculate(double &subTotal, double &taxAmount, double &finalBill, int customerType) {

    // Modifying the subTotal parameter by adding the quantity of burgers ordered * price of eacch burger
    for(int i = 0; i < ARR_SIZE; i++) {
        subTotal += (PRICE_ARRAY[i] * orderArray[i]);
    }

    // Modifying the taxAmount param if the customer type is an employee/staff member
    if(customerType == 2) {
        taxAmount = (subTotal * .09);
    }

    // Modifying the final bill parameter with subTotal + taxAmount
    finalBill = subTotal + taxAmount;

}

/*
 * This function accepts parameters that represent the subTotal, taxAmount, and
 * final bill of the order, and displays the values alongside the quantity
 * of each burger that is ordered, and the total price for each burger
 * that is selected. It writes the bill to a randomly generated .txt file by
 * calling a helper function saveBillToFile.
 *
 *
 *
 * Receives: subTotal - A variable (type double) representing the sub total.
 *           taxAmount - A variable (type double) representing the tax charge on the order.
 *           finalBill - A variable (type double) representing the total charge for the order.
 * Returns: Nothing
 *
 * Uses: PRICE_ARRAY - Global array storing the burger prices.
 *       orderArray - Global array storing the quantities of each burger.
 *       BURGER_ARRAY - Global array storing burger names.
 *
 * Output: Displays the bill to the screen and writes the bill to a file.
 */
void printAndSaveBill(double subTotal, double taxAmount, double finalBill) {

    //Output formatting
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

    // Calling the function to write the bill to the file.
    saveBillToFile(subTotal, taxAmount, finalBill);

}

/*
 * This function accepts parameters that represent the subTotal, taxAmount, and
 * final bill of the order, and writes the values alongside the quantity
 * of each burger that is ordered, and the total price for each burger
 * that is selected to a randomly generated text file.
 *
 * Called by the printAndSaveBill function.
 *
 * Receives: subTotal - A variable (type double) representing the sub total.
 *           taxAmount - A variable (type double) representing the tax charge on the order.
 *           finalBill - A variable (type double) representing the total charge for the order.
 *
 * Returns: Nothing
 *
 * Uses: PRICE_ARRAY - Global array storing the burger prices.
 *       orderArray - Global array storing the quantities of each burger.
 *       BURGER_ARRAY - Global array storing burger names.
 *
 * Output: Writes the bill to a randomly generated text file
 */
void saveBillToFile(double subTotal, double taxAmount, double finalBill) {
    ofstream outputFile;

    // To generate a unique number for the text file every single run
    unsigned seed = time(0);
    srand(seed);

    // Generating a random number between 1000 and 2000
    int randomNumber = rand() % 1001 + 1000;

    // Creating and opening a random file name using the random number
    string fileName = to_string(randomNumber) + ".txt";
    outputFile.open(fileName);

    // If the file is successfully opened, begin writing to it
    if(outputFile) {
        // Formatting for the output file
        outputFile << fixed << showpoint << setprecision(2);

        outputFile << endl;

        // Writing the quantity ordered to the file
        for(int i = 0; i < ARR_SIZE; i++) {
            outputFile << BURGER_ARRAY[i] << " Quantity Ordered: " << orderArray[i] << endl;
        }

        // Writing the total cost of each item ordered
        outputFile << "\nCost Per Item: " << endl;
        for(int i = 0; i < ARR_SIZE; i++) {
            outputFile << BURGER_ARRAY[i] << ": $" << PRICE_ARRAY[i] << " x " << orderArray[i] << " = $" << (orderArray[i] * PRICE_ARRAY[i]);
            outputFile << endl;
        }

        // Writing the subtotal of all ordered items (cost of all items before tax)
        outputFile << "\nTotal Before Tax: $" << subTotal << endl;

        // Writing the amount of tax to the file
        outputFile << "\nTax Amount: $" << taxAmount << endl;

        // Writing the final bill to the file.
        outputFile << "\nFinal Total: $" << (subTotal + taxAmount) << endl;

        // Closing the file after it is done
        outputFile.close();

    }
}
