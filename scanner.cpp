//
// Created by Austin Wildgrube on 2/25/21.
//
#include <iostream>
#include <string>
#include <cstdio>

#include "scanner.h"

using namespace std;

char tokenArray[23] = {
    '_',
    'a',
    '1',
    '=',
    '>',
    '<',
    ':',
    '+',
    '-',
    '*',
    '/',
    '%',
    '.',
    '(',
    ')',
    ',',
    '{',
    '}',
    ';',
    '[',
    ']',
};

int stateTable[22][22] = {
        /*
            -3  : Part of long token ignore
            -2  : Incorrect start token
            -1  : Incorrect next token

            1001: Keyword
            1002: Identifier
            1003: Number

            1004: =
            1005: =>
            1006: =<
            1007: ==
            1008: :
            1009: :=
            1010: +
            1011: -
            1012: *
            1013: /
            1014: %
            1015: .
            1016: (
            1017: )
            1018: ,
            1019: {
            1020: }
            1021: ;
            1022: [
            1023: ]
        */
     // { _   a     1     =     >     <     :   +   -   *   /   %   .   (   )   ,   {   }   ;   [   ]   ws   }
        { 1,  2,    3,    4,    5,    6,    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22   }, // State 0

        { -1, 1002, 1002, -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2   }, // _
        { -1, 2,    3,    -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1002 }, // a
        { -1, -1,   3,    -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1003 }, // 1
        { -1, -1,   -1,   1007, 1005, 1006, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1004 }, // =
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2   }, // >
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2   }, // <
        { -1, -1,   -1,   1009, -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1008 }, // :
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1010 }, // +
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1011 }, // -
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1012 }, // *
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1013 }, // /
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1014 }, // %
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1015 }, // .
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1016 }, // (
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1017 }, // )
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1018 }, // ,
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1019 }, // {
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1020 }, // }
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1021 }, // ;
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1022 }, // [
        { -1, -1,   -1,   -1,   -1,   -1,   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1023 }, // ]
};

void Scanner::scan() {
    FILE *file;
    string tempString;
    char character, lookAhead;
    int token, column;
    int state = 0;
    int lineNumber = 1;

    file = fopen("temp_data.txt", "r");

    do {
        // Grab our character
        character = getc(file);
        lookAhead = getc(file);

        // Check for comments
        if (character == '$' && lookAhead == '$') {
           //keep getting character if char is $ then look ahead
           do {
               character = getc(file);

               if (character == '$') {
                   lookAhead = getc(file);

                   if (lookAhead != '$') {
                       character = getc(file);
                   }
               }
           } while (character != '$');

            character = getc(file);
        } else
            ungetc(lookAhead, file);

        // We need to begin checking for keywords
        if (isalpha(character) || character == '_') {
            // start a string array to check against keywords
            string word;
            word.push_back(character);
            character = getc(file);

            while (!isspace(character) && character != '\n' && (isalpha(character) || isdigit(character))) {
                // Add to string
                word.push_back(character);
                character = getc(file);
            }

            // Check to see if the words are keywords
            if (checkKeywords(word))
                Scanner::getPrintStatement(1001, word, lineNumber);
            else
                Scanner::getPrintStatement(1002, word, lineNumber);

            ungetc(character, file);
        } else {
            if (character != EOF) {
                // Get columns
                if (isdigit(character))
                    column = 2;
                else
                    column = Scanner::getColumn(character);

                if (column == -99 && character != '\n' && !isspace(character)) {
                    string cToS(1, character);
                    Scanner::getErrorStatement(cToS, lineNumber);
                } else {

                    // Search token
                    token = Scanner::searchTokens(state, column);

                    // If the states is not 0 and there is a space or new line just
                    // get the token without the look a head.
                    if (state != 0 && (character == '\n' || isspace(character))) {
                        token = Scanner::searchTokens(state, 21);

                        Scanner::getPrintStatement(token, tempString, lineNumber);

                        tempString.clear();
                        state = 0;
                    } else {
                        // Token search returned another state
                        if (token > 0 && token <= 22) {
                            state = token;

                            tempString.push_back(character);

                            // We reached a final token
                        } else if (token >= 1000 && token <= 1023) {
                            if (!tempString.empty()) {
                                tempString.push_back(character);
                                Scanner::getPrintStatement(token, tempString, lineNumber);
                                tempString.clear();
                            } else {
                                string characterToString(1, character);
                                Scanner::getPrintStatement(token, characterToString, lineNumber);
                            }

                            state = 0;

                            // There was no white space between tokens and the two did not go together
                        } else if (token == -1) {
                            token = Scanner::searchTokens(state, 21);

                            Scanner::getPrintStatement(token, tempString, lineNumber);
                            tempString.clear();

                            // Reset our state and put back the look ahead character
                            state = 0;
                            ungetc(character, file);
                        } else if (token == -2) {
                            Scanner::getErrorStatement(tempString, lineNumber);
                            tempString.clear();
                        }
                    }
                }
            }
        }

        // Increase line number if we reach a new row
        if (character == '\n')
            lineNumber++;

    } while (character != EOF);
}

int Scanner::getColumn(char character) {
    // Loop through valid tokens
    for (int i = 0; i < sizeof(tokenArray) / sizeof(tokenArray[0]); i++) {
        // Check if token is in array and return if found
        if (tokenArray[i] == character)
            return i;
    }

    // Not found
    return -99;
}

int Scanner::searchTokens(int state, int column) {
    // return state or token
    return stateTable[state][column];
}

bool Scanner::checkKeywords(const string &word) {
    string keywordArray[20] = {
        "begin",
        "end",
        "loop",
        "whole",
        "void",
        "exit",
        "getter",
        "outter",
        "main",
        "if",
        "then",
        "assign",
        "data",
        "proc"
    };

    // Loop through valid keywords
    for (auto &i : keywordArray) {
        // Check if keywords is in array and return if found
        if (i == word)
            return true;
    }

    // Not found
    return false;
}

void Scanner::getPrintStatement(int tokenNumber, const string& userInput, int lineNumber) {
    string tokenID[] {
        "KW_tk",
        "ID_tk",
        "NUM_tk",
        "OP_tk",
        "DEL_tk"
    };

    struct Token {
        string id;
        int successId = 0;
        string userInput;
        int lineNumber = 0;
    };

    Token token;
    token.successId = tokenNumber;
    token.userInput = userInput;
    token.lineNumber = lineNumber;

    if (tokenNumber == 1001)
       token.id = tokenID[0];
    else if (tokenNumber == 1002)
        token.id = tokenID[1];
    else if (tokenNumber == 1003)
        token.id = tokenID[2];
    else if (tokenNumber >= 1004 && tokenNumber <= 1014)
        token.id = tokenID[3];
    else if (tokenNumber >= 1015)
        token.id = tokenID[4];

    cout << token.id << " " << token.successId << " " << token.userInput << " " << token.lineNumber << endl;
}

void Scanner::getErrorStatement(const string& userInput, int lineNumber) {
    cout << endl;
    cout << "SCANNER ERROR" << endl;
    cout << "Line Number " << lineNumber << endl;
    cout << "Invalid Syntax " << userInput << endl;
    cout << endl;
}