// Author: Austin Wildgrube <akwwb6@mail.umsl.edu>
// Date: 03/08/2021

#include <iostream>
#include <fstream>
#include <string>

#include "scanner.h"

using namespace std;

/**
 * This is the main function of our program where we collect command line arguments
 * and the call the function to build and print the tree.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv) {
    string inputString;
    string fileName;

    // If one argument we need to read data to a temporary text file
    if (argc == 1) {
        fileName = "temp_data.txt";
        ofstream tempFile("temp_data.txt");

        cout << "Enter a string and type quit to stop: " << endl;

        // Collect content and place in file until quit is entered
        while (getline(cin, inputString)) {
            if (inputString == "quit")
                break;
            else
                tempFile << inputString << endl;
        }
        // There is two arguments which means a file was provided
    } else if (argc == 2) {
        fileName = argv[1];

        if (fileName.substr(fileName.find_last_of('.') + 1) != "fs") {
            cout << "[Error]: File names must have extension .fs" << endl;
            return 0;
        }

    // Too many arguments were entered
    } else {
        // TODO: Change output
        cout << "[Error] Too many arguments were entered!" << endl;
        cout << "[Info] Usage: ./P0" << endl;
        cout << "[Info] Usage: ./P0 [fileName]" << endl;
        cout << "[Info] Usage: ./P0 < fileName.sp2020" << endl;
        return 0;
    }

    auto back_to_cstr = fileName.c_str();
    Scanner::scan(back_to_cstr);

    return 0;
}
