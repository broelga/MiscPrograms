// Array practice with input validation

#include <iostream>
using namespace std;

int input(/* in */ int[], /* in */ const int);
bool inputValidation(/* in */ int[], /* in */ int);
void output(/* in */ const int[], /* in */ int);

int main()
{
    const int NUM_EMPLOYEES = 20;
    int hours[NUM_EMPLOYEES];

    int numOfEmployeesWorked = input(hours, NUM_EMPLOYEES);
    output(hours, numOfEmployeesWorked);
}

int input(/* in */ int array[], /* in */ int limit)
{
    for (int index = 0 ; index < limit; index++)
    {
        cout << "Enter number of hours worked for employed #" << (index + 1) << ", enter -1 to quit: ";
        cin >> array[index];
        cin.ignore(100, '\n');

        if (array[index] != -1)
        {
            if (!inputValidation(array, index))
            {
                cout << "Incorrect value.\n";
                index--;
                cin.clear();
                cin.ignore(100, '\n');
            }
            else
                continue;
        }
        else
        {
            limit = index;
        }
    }
    return limit;
}

bool inputValidation(/* in */ int array[], /* in */ int index)
{
    bool isValid = true;

    if (array[index] > 0 && array[index] < 100)
    {
        isValid = true;
        return isValid;
    }
    else
    {
        isValid = false;
        return isValid;
    }
}

void output(/* in */ const int array[], /* in */ int limit)
{
    for (int index = 0; index < limit; index++)
    {
        cout << "Employee #" << (index + 1) << " worked a total of " << array[index] << " hours.\n";
    }
}
