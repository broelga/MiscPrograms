// Array practice with input validation

#include <iostream>
using namespace std;

void input(/* in */ int[], /* in */ int &);
bool inputValidation(/* in */ int[], /* in */ int);
void output(/* in */ int[], /* in */ int);

int main()
{
    int NUM_EMPLOYEES = 20;
    int hours[NUM_EMPLOYEES];

    input(hours, NUM_EMPLOYEES);
    output(hours, NUM_EMPLOYEES);
}

void input(/* in */ int array[], /* inOut */ int &NUM_EMPLOYEES)
{
    for (int index = 0; index < NUM_EMPLOYEES; index++)
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
            array[index] = 0;
            NUM_EMPLOYEES = index;
            break;
        }
    }
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

void output(/* in */ int array[], /* in */ int limit)
{
    for (int index = 0; index < limit; index++)
    {
        cout << "Employee #" << (index + 1) << " worked a total of " << array[index] << " hours.\n";
    }
}