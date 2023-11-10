/* project1_Strength_ods0005
 * Owen Strength
 * 8/29/2023
 *
 * compiled using g++
 * 
 * This program takes user input for a loan amount, intrest rate, and monthly payment.
 * The program returns a table of monthly payments indicating how much intrest is paid.
 * The program also returns the number of months it takes to pay off the loan and the total amount paid.
 *
 * References:
 * Hints provided by Dr. Li on Canvas
 * bolding text: https://www.w3schools.blog/c-bold-text-2
 * number formatting: https://codereview.stackexchange.com/questions/209063/function-that-adds-commas-between-groups-of-3-digits-in-a-string
 * input and output: https://isocpp.org/wiki/faq/input-output
 */

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
using namespace std;
int main()
{
    // VARIABLE INITIALIZATION
    double loan, interestRate, interestRateC, monthlyPaid, currLoanInterest, prevBalance;
    double interestTotal = 0.0;
    double principal = 0.0;
    int currentMonth = 0;
    bool isValidIn = false; // bit to detirmine if the current input is valid. reused for each input
    std::string interestRateIn;

    // CURRENCY FORMATTING
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    std::cout.imbue(std::locale("")); // adds comma to numbers when needed

    // USER INPUT

    // program will not move forward until a positive loan amount is entered
    while (!isValidIn)
    {
        loan = -1;
        cout << "Loan Amount: ";
        cin >> loan;
        if (loan > 0)
        {
            isValidIn = true;
        }
        else
        {
            cout << "Loan amount must be a positive number. Please try again. \n";
            // clear the input. ignore any alpha characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    isValidIn = false;

    // program will not move forward until a positive interest rate is entered
    while (!isValidIn)
    {
        cout
            << "Interest Rate (% per year): ";
        cin >> interestRateIn;

        // validation for interest rate
        isValidIn = true;
        for (int i = 0; i < interestRateIn.size(); i++)
        {
            char c = interestRateIn[i];
            if (!isdigit(c) && c != '.')
            {
                cout << "Interest Rate must be a positive number. Please try again. \n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                isValidIn = false;
                break;
            }
        }
        if (!isValidIn)
        {
            continue;
        }

        interestRate = atof(interestRateIn.c_str());
        if (interestRate >= 0)
        {
            isValidIn = true;
        }
        else
        {
            cout << "Intrest Rate must be a positive number. Please try again. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    isValidIn = false;

    //  GET PROPER INTEREST RATES FOR CALCULATIONS
    interestRate /= 12;
    interestRateC = interestRate / 100;

    // program will not move forward until a monthly payment is sufficient
    while (!isValidIn)
    {
        cout << "Monthly Payments: ";
        cin >> monthlyPaid;
        if (monthlyPaid <= 0)
        {
            cout << "Monthly Payment must be a positive number. Please try again. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (loan * (interestRateC) < monthlyPaid)
        {
            isValidIn = true;
        }
        else
        {
            cout << "Monthly Payment is too small. Monthly Payment must be greater that $" << loan * (interestRateC) << " Please try again. \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    cout
        << endl;

    // AMORTIZATION TABLE
    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

    // LOOP TO FILL TABLE
    while (loan > 0)
    {
        if (currentMonth == 0)
        {
            cout << currentMonth++ << "\t$" << loan;
            if (loan < 1000)
                cout << "\t"; // Formatting MAGIC
            cout << "\t"
                 << "N/A\tN/A\tN/A\t\tN/A\n";
            prevBalance = loan;
        }
        else
        {
            // Properly calculate and display �montlypaid� and �principal� when(1) loan * (1 + interestRateC) < monthlyPaid and (2) loan * (1 + interestRateC) >= monthlyPaid
            currLoanInterest = loan * interestRateC;
            interestTotal += currLoanInterest;
            loan += currLoanInterest;
            loan -= monthlyPaid;
            if (loan < 0)
            {
                monthlyPaid += loan;
                loan = 0.0;
            }
            principal = prevBalance - loan;
            cout << currentMonth++ << "\t$" << loan << "\t";
            if (loan < 1000)
                cout << "\t";
            cout << "$" << monthlyPaid << "\t";
            cout << interestRate << "\t$" << currLoanInterest << "\t\t$" << principal;
            cout << "\n";

            prevBalance = loan;
        }
    }

    // Final summary output
    cout << "****************************************************************\n";
    std::cout << "\nIt takes "
              << "\x1b[1m" << --currentMonth << " \x1b[0mmonths to pay off "
              << "the loan.\n"
              << "Total interest paid is: \x1b[1m$" << interestTotal << "\x1b[0m";
    cout << endl
         << endl;
    return 0;
}
