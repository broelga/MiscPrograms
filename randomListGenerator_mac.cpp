//********************************************************************
// Program will create a file named by user and will generate        *
// a sequentially numbered list using two numbers chosen by          *
// the user.                                                         *
//********************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sys/stat.h>
using namespace std;

void header();
void getFilename(fstream &, string &, unsigned &);
bool fileExists(const string &);
void getMinMaxNums(int &, int &, int &);
void getNumAndVerify(int[], int, int, int);
void readFromFile(fstream &, string, int[], int);
void writeToFile(fstream &, string, int[], int);
void sortAscending(int[], int);
void sortDescending(int[], int);
void swap(int &, int &);
void printArray(int[], int);

int main()
{
    // Variables
    bool running = true;
    bool isValid;
    int minNum = 0, maxNum = 0;
    int arraySize = 1000;
    int array[arraySize];
    string filename;
    fstream myFile(filename);
    unsigned choice = 0;
    unsigned programCounter = 0;

    system("clear");
    while (running) // Begin program loop
    {

        while (programCounter == 0)
        {
            getFilename(myFile, filename, programCounter);
            system("clear");
        }

        system("clear");

        // Display menu and get input
        header();
        
        cout << "1. Enter filename\n"
             << "2. Generate random numbers\n"
             << "3. Print all the numbers.\n"
             << "4. Write to file.\n"
             << "5. Read from file.\n"
             << "6. Sort numbers in ascending order.\n"
             << "7. Sort numbers in descending order.\n"
             << "8. Quit program.\n\n";

        do
        {
            isValid = true;

            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(100, '\n');
            cout << "\n";

            if (choice > 0 && choice < 9)
            {

                switch (choice)
                {
                case 1:
                    system("clear");
                    getFilename(myFile, filename, programCounter);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 2:
                    system("clear");
                    getMinMaxNums(minNum, maxNum, arraySize);
                    getNumAndVerify(array, arraySize, minNum, maxNum);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 3:
                    system("clear");
                    printArray(array, arraySize);
                    cout << "\nPress enter to continue...";
                    cin.get();
                    break;
                case 4:
                    system("clear");
                    writeToFile(myFile, filename, array, arraySize);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 5:
                    system("clear");
                    readFromFile(myFile, filename, array, arraySize);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 6:
                    system("clear");
                    sortAscending(array, arraySize);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 7:
                    system("clear");
                    sortDescending(array, arraySize);
                    cout << "Press enter to continue...";
                    cin.get();
                    break;
                case 8:
                    system("clear");
                    header();
                    cout << "Goodbye!";
                    running = false;
                    break;
                }
            }
            else
            {
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                }
                cout << "Invalid choice. Please choose options 1 - 6.\n\n";
                isValid = false;
            }
        } while (!isValid);
    }
}

//***************************
//  Function definitions    *
//***************************

void header()
{
    cout << "---------------------------------------------------\n"
         << "           Random Number Generator\n"
         << "---------------------------------------------------\n\n";
}

void getFilename(fstream &myFile, string &filename, unsigned &programCounter)
{
    char choice;
    bool openFile = true,
         fnGood = true;

    header();

    do
    {
        do
        {
            if (programCounter == 0)
                cout << "Enter the filename of the file including the filetype extention (enter -1 to quit): ";
            else
                cout << "Enter the filename of the file including the filetype extention (enter -1 to return to the menu): ";

            cin >> filename;
            cin.ignore(100, '\n');

            if (programCounter == 0 && filename == "-1")
                exit(0);

            else if (programCounter > 0 && filename == "-1")
            {
                system("clear");
                return;
            }

            if (filename.substr(filename.find_last_of(".") + 1) == "txt")
                fnGood = true;

            else if (filename.substr(filename.find_last_of(".") + 1) == "csv")
                fnGood = true;

            else if (filename.substr(filename.find_last_of(".") + 1) == "doc")
                fnGood = true;

            else
            {
                fnGood = false;
                cout << "File name is incorrect.\n\n"
                     << "Press enter to contiue...";
                cin.get();
                return;
            }
        } while (!fnGood);

        if (fileExists(filename))
        {
            cout << "File already exists. Would you like to overwrite? (Y/N): ";
            cin >> choice;
            cin.ignore(100, '\n');
            choice = toupper(choice);

            if (choice == 'Y' || choice == 'N')
            {
                if (choice == 'Y')
                {
                    cout << "\n";
                    openFile = true;
                }
                else
                {
                    openFile = false;
                }
            }
            else
            {
                cout << "ERROR: Not a valid choice.\n";
                cin.clear();
            }
        }
        else
        {
            myFile.open(filename, fstream::out); // Opens/creates file

            if (myFile.eof())
            {
                myFile.clear();
                myFile.seekg(0);
            }
            else if (myFile.fail()) // Varifies file was opened/created, reprompts
            {
                for (int i = 0; i < 4; i++)
                {
                    cout << "." << flush;
                    this_thread::sleep_for(chrono::milliseconds(400));
                }
                cout << " ERROR: Something went wrong. Try again.\n";
                cin.clear();
                this_thread::sleep_for(chrono::milliseconds(1250));
                system("clear");
                cout << ".... ERROR: Something went wrong. Try again.\n";
            }
            else
                myFile.seekg(0);
        }
    } while (myFile.fail() && !openFile);

    myFile.close();
    programCounter++;
}

bool fileExists(const string &filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

void getNumAndVerify(int someArray[], int arraySize, int minNum, int maxNum)
{
    int num1 = 0,
        num2 = 0,
        counter = 0;
    bool dupDigit = false;
    srand(time(0));

    for (int i = 0; i < arraySize; i++)
    {
        dupDigit = false;
        counter = 0;

        // Assign random digit between 0 and arraySize to array[i]
        if (minNum < 0)
            someArray[i] = rand() % arraySize + minNum;

        else
            someArray[i] = rand() % arraySize + minNum;

        // linear search for duplicate numbers
        while (!dupDigit && counter < i)
        {
            num1 = someArray[i];
            num2 = someArray[counter];

            if (num1 == num2)
            {
                dupDigit = true;
                i--;
            }
            counter++;
        }
    }

    for (int i = 0; i < arraySize; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(1));
        cout << someArray[i] << " "
             << flush;
    }
    cout << "\n\n";
}

void getMinMaxNums(int &minNum, int &maxNum, int &arraySize)
{
    header();

    do
    {
        cout << "What is lowest number? ";
        cin >> minNum;
        cin.ignore(100, '\n');
        if (!minNum)
        {
            cout << "ERROR: That is not a number.\n";
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (!minNum);

    do
    {
        cout << "What is the highest number? ";
        cin >> maxNum;
        cin.ignore(100, '\n');
        if (!maxNum)
        {
            cout << "ERROR: That's not a number.\n";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (maxNum && maxNum < minNum)
        {
            cout << "ERROR: Last number must be greater than the first.\n";
            cin.clear();
        }
    } while (!maxNum || maxNum < minNum);

    if (minNum < 0)
        arraySize = ((maxNum + 1) + (minNum * -1));

    else
        arraySize = ((maxNum + 1) - minNum);

    cout << "\n";
}

void printArray(int someArray[], int arraySize)
{
    header();

    for (int i = 0; i < arraySize; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(3));
        cout << someArray[i] << " " << flush;
    }
    cout << "\n";
}

void writeToFile(fstream &myFile, string filename, int someArray[], int size)
{
    header();

    myFile.open(filename, fstream::out);

    if (myFile.fail())
    {
        cout << "File did not open.\n";
        return;
    }

    cout << "Writing to file" << flush;
    this_thread::sleep_for(chrono::milliseconds(400));

    for (int i = 0; i < 4; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(300));
        cout << "." << flush;
    }

    for (int i = 0; i < size; i++)
    {
        myFile << someArray[i] << " ";
    }

    this_thread::sleep_for(chrono::milliseconds(300));
    cout << " Operation complete!\n\n"
         << flush;

    myFile.seekg(0);
    myFile.close();
}

void readFromFile(fstream &myFile, string filename, int someArray[], int size)
{
    int contents = 0;

    header();

    myFile.open(filename, fstream::in);

    if (myFile.eof())
    {
        myFile.clear();
        myFile.seekg(0);
    }

    if (myFile.is_open())
    {
        cout << "Reading from file" << flush;
        this_thread::sleep_for(chrono::milliseconds(400));

        for (int i = 0; i < 4; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(300));
            cout << "." << flush;
        }

        cout << "\n";

        for (int i = 0; i < 101; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(7));
            cout << "\r" << i << "%" << flush;
        }

        this_thread::sleep_for(chrono::milliseconds(300));
        cout << " Operation complete!\n\n"
             << flush;

        this_thread::sleep_for(chrono::milliseconds(250));

        for (int iter = 0; iter < size; iter++)
        {
            myFile >> contents;
            this_thread::sleep_for(chrono::milliseconds(3));
            cout << contents << " " << flush;
        }
    }

    cout << "\n\n";

    myFile.clear();
    myFile.seekg(0);
    myFile.close();
}

void sortAscending(/* in */ int someArray[], /* in */ int size)
{
    int start = 0,
        minIndex = 0,
        minValue = 0;

    while (start < size)
    {
        // Begin function loop
        for (; start < size; start++)
        {
            system("clear");

            header();

            // Assign start and array[index] values
            minIndex = start,
            minValue = someArray[start];

            // Sort function starting at array[1]
            for (unsigned index = start + 1; index < size; index++)
            {
                if (someArray[index] < minValue)
                {
                    minValue = someArray[index];
                    minIndex = index;
                }
            }
            // Swaps index of maxValue with start index
            swap(someArray[minIndex], someArray[start]);

            for (int i = 0; i < size; i++)
            {
                cout << someArray[i] << " "
                     << flush;
            }
        }
    }
    cout << "\n\n";
}

void sortDescending(/* in */ int someArray[], /* in */ int size)
{
    int start = 0,
        maxIndex = 0,
        maxValue = 0;

    while (start < size)
    {

        // Begin function loop
        for (; start < size; start++)
        {
            system("clear");

            header();

            // Assign start and array[index] values
            maxIndex = start,
            maxValue = someArray[start];

            // Sort function starting at array[1]
            for (unsigned index = start + 1; index < size; index++)
            {
                if (someArray[index] > maxValue)
                {
                    maxValue = someArray[index];
                    maxIndex = index;
                }
            }
            // Swaps index of maxValue with start index
            swap(someArray[maxIndex], someArray[start]);

            for (int i = 0; i < size; i++)
            {
                cout << someArray[i] << " "
                     << flush;
            }
        }
    }
    cout << "\n\n";
}

void swap(/* inOut */ int &element1, /* inOut */ int &element2)
{
    // Pre:     Temporary file is created assigned to the value of element1.
    // Post:    Both element1 and element2 have swapped value and values are returned.
    int temp = element1;

    element1 = element2;
    element2 = temp;
}