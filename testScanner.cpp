//
// Created by Austin Wildgrube on 2/25/21.
//
#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>

#include "testScanner.h"
#include "scanner.h"

using namespace std;

void TestScanner::testDriver(const char* fileName) {
    FILE *file;
    char character, lookAhead;

    file = fopen(fileName, "r");

    do {
        // Grab our character
        character = getc(file);
        lookAhead = getc(file);

        Scanner::scan(file, character, lookAhead);
    } while (character != EOF);

//    getPrintStatement(1000, "", lineNumber);
}