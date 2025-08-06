// Become familiar wih C syntax
// Learn to debug buggy code

#include <cs50.h>
#include <stdio.h> // Also have to add this header file to use printf like functions.

int main(void)
{

    // Original Code

    /*

    // Ask for your name and where live
    name = get_string("What is your name? ")
    location = get_string("Where do you live? ")

    // Say hello
    print("Hello, %i, from %i!", name, location)

    */

    // Corrected Code

    string name     = get_string("What is your name? "); // Added string data type & put a semicolon at last of statement.
    string location = get_string("Where do you live? "); // Same as above.

    printf("Hello, %s, from %s!\n", name, location); // Change %i to %s as bcz name, location are
                                                     // strings instead of integers.
}
