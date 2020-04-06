//********************************************************************
// Program will create a file named by user and will generate        *
// a sequentially numbered list using two numbers chosen by          *
// the user.                                                         *
//********************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

void getFilename(std::ofstream &, std::string);
void getNumbers(int &, int &);
void writeToFile(std::ofstream &, int, int);
void programRestart(bool &);

int main()
{
    // Variables
    bool running = true; // Controls program running status
    int minNum, maxNum;  // These hold the smallest and largest numbers,
                         // setting the range of numbers
    std::string filename;
    std::ofstream outFile(filename); // File to be opened/created and written to

    while (running) // Begin program loop
    {
        getFilename(outFile, filename);
        getNumbers(minNum, maxNum);
        writeToFile(outFile, minNum, maxNum);
        programRestart(running);
    }
}

//**************************
//  Function definitions
//**************************

void getFilename(std::ofstream &outFile, std::string filename)
{
    do
    {
        std::cout << "Enter the filename of the file including the filetype extention: ";
        std::cin >> filename;
        std::cin.ignore(100, '\n');

        outFile.open(filename); // Opens/creates file

        if (!outFile) // Varifies file was opened/created, reprompts
        {
            std::cout << "ERROR: Cannot open file.\n";
            std::cin.clear();
        }
    } while (!outFile);
}

void getNumbers(int &minNum, int &maxNum)
{
    do // Grab minNum and verify
    {
        std::cout << "\nWhat is the first number to print? ";
        std::cin >> minNum;
        std::cin.ignore(100, '\n');
        if (!minNum)
        {
            std::cout << "ERROR: That is not a number.\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
    } while (!minNum);
    do // Grab maxNum and verify
    {
        std::cout << "What is the last number to print? ";
        std::cin >> maxNum;
        std::cin.ignore(100, '\n');
        if (!maxNum)
        {
            std::cout << "ERROR: That's not a number.\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (maxNum && maxNum < minNum)
        {
            std::cout << "ERROR: Last number must be greater than the first.\n";
            std::cin.clear();
        }
    } while (!maxNum || maxNum < minNum);
}

void writeToFile(std::ofstream &outFile, int minNum, int maxNum)
{
    std::cout << "\nWriting to file. . .\n"
              << "--------------------\n";

    // Being writing to file, adding 1 to minNum every interation until equal to maxNum
    for (int i = minNum; i <= maxNum; i++)
    {
        outFile << i << ".\t\n\n";
        std::cout << i << ".\t\n\n";
    }
    std::cout << "--------------------\n"
              << "Operation complete.\n";

    outFile.close(); // Close file
}

void programRestart(bool &running)
{
    char choice; // Stores user's choice to restart or terminate program
    do           // Prompt user to restart or terminate program
    {
        std::cout << "\nWould you like to create another file? (Y/N): ";
        std::cin >> choice;
        std::cin.ignore(100, '\n');
        choice = toupper(choice);
        if (choice == 'Y' || choice == 'N')
        {
            if (choice == 'Y')
            {
                std::cout << "\n";
                choice = 1;
                running = true;
            }
            else
            {
                std::cout << "\nQuitting program...\n";
                choice = 1;
                running = false;
            }
        }
        else
        {
            std::cout << "ERROR: Not a valid choice.\n";
            std::cin.clear();
        }
    } while (choice != 1);
}