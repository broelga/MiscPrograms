/* 
Program description: A simple program that generates a random list of numbers. The numbers contain a possibility of containing both positive 
    and negative numbers. If any numbers in the list are negative, each negative number will be replaced with its absolute value. if no
    negative numbers are in the list, a message will be displayed and the program will end.

Instructions:
    Write a function named noNegatives(). It should accept an array of integers and a size argument. It should return true if none
    of the values are negative. If any of the values are negative it should return false

    bool noNegatives(const int array[], int size); 

    Write a function named absoluteValues(). It should accept an array of integers and a size argument. It should replace any negative
    values with the corresponding positive value.

    void absoluteValues(int array[], int size);
*/

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// Declare global constant
const int ARR_SIZE = 10;

// Function prototypes
void generateArray(int[], int);     // Initialize array with random numbers
bool noNegatives(const int[], int); // Step through array and count the number (if any) of negative numbers.
void absoluteValues(int[], int);    // Find any negative numbers in the array. If any are found, it is replaced by its absolute value: √x(squared)

int main()
{
    // Declare array variable
    int array[ARR_SIZE];

    // Call functions
    generateArray(array, ARR_SIZE);
    
    if (!noNegatives(array, ARR_SIZE))
    {
        cout << "There are negative numbers in this list.\n\n";
        absoluteValues(array, ARR_SIZE);
    }
    else
        cout << "There are no negative numbers in this list.\n";

    return 0;
}

// Function definitions
/////////////////////////////////////////////////////////////////////////////////////////////

// Initialize array with random numbers
void generateArray(int array[], int arrSize)
{
    // Seed rand()
    srand(time(0));

    // Declare local variables
    int randMin = -20, randMax = 20;

    cout << "The list contains the following numbers:\n";

    // Begin loop and intitalize array with random numbers
    for (int i = 0; i < arrSize; i++)
    {
        array[i] = (rand() % (randMax - (randMin) + 1) + (randMin));
        cout << array[i] << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Step through array and count the number (if any) of negative numbers.
bool noNegatives(const int array[], int arrSize)
{
    // Declare local variable
    unsigned negNums = 0;
    bool noNegatives = true;

    for (int i = 0; i < arrSize; i++)
    {
        if (array[i] < 0)
            negNums++;
    }

    // If there are any negative numbers in the array, set flag to true.
    if (negNums > 0)
        noNegatives = false;

    return noNegatives;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Find any negative numbers in the array. If any are found, it is replaced by its absolute value: √x(squared)
void absoluteValues(int array[], int arrSize)
{
    cout << "The list now contains all positive numbers:\n";
    for (int i = 0; i < arrSize; i++)
    {
        if (array[i] < 0)
            array[i] = sqrt(array[i] * array[i]);
        cout << array[i] << endl;
    }
}

/* Sample Output:

The list contains the following numbers:
6
17
-8
-5
-13
-16
-11
-3
-16
4
There are negative numbers in this list.

The list now contains all positive numbers:
6
17
8
5
13
16
11
3
16
4
*/
