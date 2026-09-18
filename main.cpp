#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Example:
// ./a.out 1000 18 50

int main(int argc, char* argv[])
{
    // =====================================================
    // PART 1: VALIDATE AND CONVERT COMMAND-LINE INPUT
    // =====================================================

    if (argc > 4)
    {
        cout << "Too many arguments. Cannot pass in more than three."
             << endl;
        return -1;
    }

    double loan_amount;
    double yearly_interest_rate;
    double monthly_payment;

    // Check and convert the loan amount.
    if (argc < 2)
    {
        cout << "(Invalid loan amount)" << endl;
        return -2;
    }

    try
    {
        loan_amount = stod(argv[1]);
    }
    catch (const invalid_argument&)
    {
        cout << "(Invalid loan amount): " << argv[1] << endl;
        return -2;
    }
    catch (const out_of_range&)
    {
        cout << "(Invalid loan amount): " << argv[1] << endl;
        return -2;
    }

    if (loan_amount <= 0)
    {
        cout << "(Invalid loan amount): " << argv[1] << endl;
        return -2;
    }

    // Check and convert the interest rate.
    if (argc < 3)
    {
        cout << "(Invalid interest rate)" << endl;
        return -2;
    }

    try
    {
        yearly_interest_rate = stod(argv[2]);
    }
    catch (const invalid_argument&)
    {
        cout << "(Invalid interest rate): "
             << argv[1] << " " << argv[2] << endl;
        return -2;
    }
    catch (const out_of_range&)
    {
        cout << "(Invalid interest rate): "
             << argv[1] << " " << argv[2] << endl;
        return -2;
    }

    // Zero interest is valid.
    if (yearly_interest_rate < 0)
    {
        cout << "(Invalid interest rate): "
             << argv[1] << " " << argv[2] << endl;
        return -2;
    }

    // Check and convert the monthly payment.
    if (argc < 4)
    {
        cout << "(Invalid payment)" << endl;
        return -2;
    }

    try
    {
        monthly_payment = stod(argv[3]);
    }
    catch (const invalid_argument&)
    {
        cout << "(Invalid payment): "
             << argv[1] << " "
             << argv[2] << " "
             << argv[3] << endl;
        return -2;
    }
    catch (const out_of_range&)
    {
        cout << "(Invalid payment): "
             << argv[1] << " "
             << argv[2] << " "
             << argv[3] << endl;
        return -2;
    }

    if (monthly_payment <= 0)
    {
        cout << "(Invalid payment): "
             << argv[1] << " "
             << argv[2] << " "
             << argv[3] << endl;
        return -2;
    }

    // =====================================================
    // PART 2: INITIALIZE LOAN VARIABLES
    // =====================================================

    double balance = loan_amount;

    // Example: 18% yearly becomes 1.5% monthly.
    double monthly_interest_percent =
        yearly_interest_rate / 12.0;

    // Example: 1.5% becomes 0.015 for calculations.
    double monthly_interest_rate =
        monthly_interest_percent / 100.0;

    double monthly_interest = 0.0;
    double principal_paid = 0.0;
    double actual_payment = 0.0;
    double total_interest = 0.0;

    int month = 0;

    // =====================================================
    // PART 3: CHECK FOR AN INSUFFICIENT PAYMENT
    // =====================================================

    double first_month_interest =
        balance * monthly_interest_rate;

    if (monthly_payment <= first_month_interest)
    {
        cout << "Insufficient payment. The monthly payment "
             << "must be greater than the monthly interest."
             << endl;

        return -3;
    }

    // =====================================================
    // PART 4: FORMAT THE OUTPUT
    // =====================================================

    cout << fixed << showpoint << setprecision(2);

    cout << "\nLoan Amount: " << loan_amount << endl;
    cout << "Interest Rate (% per year): "
         << yearly_interest_rate << endl;
    cout << "Monthly Payments: "
         << monthly_payment << endl;
    cout << endl;

    // =====================================================
    // PART 5: PRINT THE AMORTIZATION TABLE
    // =====================================================

    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

    // Month zero represents the balance before any payments.
    cout << month
         << "\t$" << balance;

    if (balance < 1000)
    {
        cout << "\t";
    }

    cout << "\tN/A\tN/A\tN/A\t\tN/A\n";

    // =====================================================
    // PART 6: CALCULATE EACH MONTH
    // =====================================================

    while (balance > 0)
    {
        month++;

        // Calculate interest using the balance at the
        // beginning of this month.
        monthly_interest =
            balance * monthly_interest_rate;

        /*
         * Determine whether the normal payment is greater
         * than the entire amount currently owed, including
         * this month's interest.
         */
        if (balance + monthly_interest < monthly_payment)
        {
            // Final payment
            principal_paid = balance;
            actual_payment =
                principal_paid + monthly_interest;

            balance = 0.0;
        }
        else
        {
            // Regular payment
            actual_payment = monthly_payment;

            principal_paid =
                actual_payment - monthly_interest;

            balance =
                balance - principal_paid;
        }

        // Add this month's interest to the running total.
        total_interest =
            total_interest + monthly_interest;

        // Print this month's row.
        cout << month
             << "\t$" << balance
             << "\t\t$" << actual_payment
             << "\t" << monthly_interest_percent
             << "\t$" << monthly_interest
             << "\t\t$" << principal_paid
             << endl;
    }

    // =====================================================
    // PART 7: FINAL SUMMARY
    // =====================================================

    cout << "*****************************************************************\n";

    cout << "\nIt takes "
         << month
         << " months to pay off the loan.\n"
         << "Total interest paid is: $"
         << total_interest
         << endl;

    return 0;
}
