/*  This program uses functions to generate a rocket using values given by the user. The rocket
    will either be hollow or filled-in depending of the height is odd or even. */

#include <iostream>
using namespace std;

/* Function prototypes */
void getDimensions(/*out*/ int &, /*out*/ int &, /*out*/ int &); /* Function to get dimentions of rocket from user */
void drawRocket(/*in*/ int &, /*in*/ int &, /*in*/ int &);       /* Draws complete rocket using other functions */
bool inputValidation(/*in*/ int &, /*in/out*/ bool &);           /* Function to validate input */
void drawCone(/*in*/ int &);                                     /* Function to draw nose cone of rocket (top) */
void drawEvenBox(/*in*/ int &, /*in*/ int &, /*in*/ int &);      /* Function to draw hollow box if number is even */
void drawOddBox(/*in*/ int &, /*in*/ int &, /*in*/ int &);       /* Function to draw filled-in box if number is odd */
void drawBooster(/*in*/ int &);                                  /* Function to draw the booster of the rocket */

int main()
{
    /* Declare local variable */
    int height = 0, width = 0, stages = 0;

    /* Functions used to prompt for input and generate rocket */
    getDimensions(height, width, stages);
    drawRocket(height, width, stages);
}

//**********************************************
//  Function definitions
//**********************************************

//**********************************************
//  Function to get dimensions for rocket.
//  The user will be prompted for the
//  dimensions they would like to use to
//  generate their rocket. Input will be
//  validated after each input.
//**********************************************
void getDimensions(/*out*/ int &height, /*out*/ int &width, /*out*/ int &stages)
{
    /* Pre:     Prompts, gets, and validates each input */
    /* Post:    Returns all validated input to system */
    bool isValid = true; /* Boolean used to validate input */
    int userInput;       /* To store user input */

    do
    {
        /* Prompt for and get input */
        cout << "Please enter three postitive numbers to represent height, width and number of stages for the rocket:\n"
             << "Height: ";
        cin >> userInput;
        inputValidation(userInput, isValid); /* Input validation */

        if (isValid) /* Proceed if previous input was valid */
        {
            height = userInput; /* Stores validated value */
            cout << "Width: ";
            cin >> userInput;
            inputValidation(userInput, isValid); /* Input validation */

            if (isValid) /* Proceed if previous input was valid */
            {
                width = userInput; /* Stores validated value */
                cout << "Stages: ";
                cin >> userInput;
                inputValidation(userInput, isValid); /* Input validation */
                stages = userInput;                  /* Stores value */
            }
        }
    } while (!isValid); /* If any validation fails loop restarts */
}

//**********************************************
//  Function to validate input.
//  The height and width must be between
//  3 and 15 and stages must be greater than 0.
//  If validation fails the user will be
//  prompted again for more input.
//**********************************************

bool inputValidation(/*in*/ int &userInput, /*in/out*/ bool &isValid)
{
    /* Pre:     Validates input coming from getDimensions using specific conditions */
    /* Post:    Returns boolean to getDimensions stating the input is or is not valid */
    static int counter = 1; /* Static counter used for input validation: 1 = height, 2 = width, 3 = stages */

    if (!cin)
    {
        cout << "Invalid input.\n";
        isValid = false;
        counter = 1;
    }
    else if (counter < 3) /* Validation conditions for steps 1 and 2 */
    {
        if (userInput < 3 || userInput > 15)
        {
            cout << "Invalid input.\n";
            isValid = false;
            counter = 1; /* Counter reset to 1 ready for validation step #1 */
        }
        else
        {
            isValid = true;
            counter++; /* Increment counter for next validation step #2 and/or #3 */
        }
    }
    else if (counter == 3) /* Validation conditions for step 3 */
    {
        if (userInput < 0)
        {
            cout << "Invalid input.\n";
            isValid = false;
            counter = 1; /* Counter reset to 1 ready for next validation */
        }
        else
        {
            isValid = true;
            counter = 1; /* Counter reset to 1 ready for program restart */
        }
    }
    cin.clear();
    cin.ignore(100, '\n'); /* Keyboard buffer any errors cleared before continuing */

    return isValid; /* Validation status returned to previous function */
}

//**********************************************
//  Function to draw the completed rocket.
//  This function contains all of the functions
//  necessary to draw the rocket.
//**********************************************

void drawRocket(/*in*/ int &height, /*in*/ int &width, /*in*/ int &stages)
{
    /* Pre:     Uses input from user to generate rocket */
    /* Post:    Prints rocket to console */
    drawCone(width);

    if (height % 2 == 0) /* Condition determines whether to make odd or even rocket box */
        drawEvenBox(height, width, stages);
    else
        drawOddBox(height, width, stages);

    drawBooster(width);
}

//**********************************************
//  Function to draw nose cone.
//  The algorithm of the cone dimensions are
//  adjusted depending on whether the value
//  is odd or even.
//**********************************************

void drawCone(/*in*/ int &width)
{
    /* Pre:     Takes user input and generates rocket nose cone */
    /* Post:    Prints rocket nose cone to console */
    /* Declare local variables */
    int maxRows,
        row,
        numStars,
        numSpaces;

    for (int row = 1; row <= maxRows; row++) // Starts the loop
    {
        cout << endl; /* Starts new line */
        /* If width is even variables are assigned */
        if (width % 2 == 0)
        {
            maxRows = (width / 2);
            numStars = 2 * row;                 // Computes the number of stars needed for each row
            numSpaces = ((width)-numStars) / 2; // Computes the number of external whitespaces
        }
        /* If width is odd variables are assigned */
        else
        {
            maxRows = (width / 2) + 1;
            numStars = 2 * row - 1;                   // Computes the number of stars needed for each row
            numSpaces = ((width + 1) - numStars) / 2; // Computes the number of external whitespaces
        }
        if (row <= maxRows) // This sets the left slope of triangle
        {
            for (int col = 1; col <= numSpaces; col++)
            {
                cout << ' ';

                for (; col == numSpaces; col++)
                {
                    cout << '*';

                    if (row == 1 && width % 2 == 0) /* If width is even, two stars are used in the first row */
                        cout << '*';
                }
            }
        }
        if (row > 1 && row <= maxRows) // This is right slope of the triangle
        {
            numSpaces = (numStars % width) - 2;        // Computes the number internal whitespaces
            for (int col = 1; col <= numSpaces; col++) // Sets the interal whitespaces and the stars on the right slope
            {
                cout << ' ';

                for (; col == numSpaces; col++)
                    cout << '*'; /* Sets the far right star */
            }
        }
    }
}

//**********************************************
//  Function to draw the rocket box if the
//  height value given by user is even. This
//  function will draw a hollow box as well
//  as adding the number of stages determined
//  by user.
//**********************************************

void drawEvenBox(/*in*/ int &height, /*in*/ int &width, /*in*/ int &stages)
{
    /* Pre:     Takes user input and generates rocket body */
    /* Post:    Prints rocket body to console */
    for (int counter = 0; counter < stages; counter++)
    {
        for (int row = 1; row <= height; row++)
        {
            if (row == 1 || row == height)
            {
                for (int col = 1; col <= width; col++)
                    cout << '*';
            }
            if (row > 1 && row < height)
            {
                cout << '*';

                for (int col = 1; col <= width - 2; col++)
                    cout << ' ';

                cout << '*';
            }
            cout << endl;
        }
    }
}

//**********************************************
//  Function to draw the rocket box if the
//  height value given by user is odd. This
//  function will draw a filled-in box as well
//  as adding the number of stages determined
//  by user.
//**********************************************

void drawOddBox(/*in*/ int &height, /*in*/ int &width, /*in*/ int &stages)
{
    /* Pre:     Takes user input and generates rocket body */
    /* Post:    Prints rocket body to console */
    for (int counter = 0; counter < stages; counter++)
    {
        for (int row = 1; row <= height; row++)
        {
            for (int col = 1; col <= width; col++)
                cout << '*';

            cout << endl;
        }
    }
}

//**********************************************
//  Function to draw rocket booster.
//  The algorithm of the booster dimensions are
//  adjusted depending on whether the value
//  is odd or even. The rows are adjusted further
//  depending on the size of the rocket.
//**********************************************

void drawBooster(int &width)
{
    /* Pre:     Takes user input and generates rocket booster */
    /* Post:    Prints rocket booster to console */
    /* Declare local variables */
    int maxRows,
        row,
        numStars,
        numSpaces;

    if (width < 5) // Initializes number of rows based on the number input by user
        row = 1;
    else if (width < 11)
        row = 2;
    else if (width < 15)
        row = 3;
    else
        row = 4;

    for (; row <= maxRows; row++) // Starts the loop
    {
        /* If width is even variables are assigned */
        if (width % 2 == 0)
        {
            maxRows = (width / 2);
            numStars = 2 * row;                 // Computes the number of stars needed for each row
            numSpaces = ((width)-numStars) / 2; // Computes the number of external whitespaces
        }
        /* If width is odd variables are assigned */
        else
        {
            maxRows = (width / 2) + 1;
            numStars = 2 * row - 1;                   // Computes the number of stars needed for each row
            numSpaces = ((width + 1) - numStars) / 2; // Computes the number of external whitespaces
        }
        if (row < maxRows) // This sets the left slope of rhombus
        {
            for (int col = 1; col <= numSpaces; col++)
            {
                cout << ' ';

                for (; col == numSpaces; col++)
                {
                    cout << '*';

                    if (row == 1 && width % 2 == 0) /* If width is even and is less than 8, two stars are used in the top row*/
                        cout << '*';
                }
            }
        }
        if (row > 1 && row != maxRows) // This is right slope of the rhombus
        {
            numSpaces = (numStars % width) - 2;        // Computes the number internal whitespaces
            for (int col = 1; col <= numSpaces; col++) // Sets the interal whitespaces and the stars on the right slope
            {
                cout << ' ';

                for (; col == numSpaces; col++)
                    cout << '*';
            }
        }
        if (row == maxRows) // Outputs the base of the rhombus after the body of the booster is complete
        {
            for (int col = 1; col <= width; col++)
                cout << '*';

            cout << endl;
        }
        cout << endl; /* Starts a new line */
    }
}
