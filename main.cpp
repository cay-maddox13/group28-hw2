#include <iostream> 
using namespace std; 

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3

int main( int argc, char * argv[] ) // Entry point of the program; argc is argument count, argv holds argument strings
{
    // Check if user passed more than 3 arguments (argc > 4 because argv[0] is the program name itself)
    if (argc > 4) 
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl; 
        return -1; // Exit with error code -1
    }

    int i = 1; // Counter to iterate through command-line arguments starting from index 1
    double loan_amount, yearly_interest_rate, monthly_payment; // Variables to store final numeric inputs
    double arguments [3]; // Fixed-size array to hold up to 3 parsed numerical arguments

    // If at least one argument was passed beyond the executable name
    if (argc > 1) 
    {
        while ( i < argc ) // Loop through all passed command-line arguments
        {
            try 
            {
                // Convert string argument to double and store in arguments array
                arguments[i-1] = stod(argv[i]); 
            } 
            catch(const std::invalid_argument&) // Catch conversion errors if input isn't a valid double
            {
                // Print specific error messages depending on which argument failed
                if(i==1) 
                    cout << "(Invalid loan amount): " << argv[i] << endl;
                else if (i==2) 
                    cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
                else 
                    cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
                
                return -2; // Exit with error code -2 on invalid input
            }
            i++; // Move to next argument
        }
    }

    // Assign the converted array values to their corresponding variables
    loan_amount = arguments[0];
    yearly_interest_rate = arguments[1];
    monthly_payment = arguments[2];

    // Print the parsed values separated by spaces
    cout << loan_amount << " " << yearly_interest_rate << " " << monthly_payment << endl;

    return 0; // Return 0 indicating successful execution
}
