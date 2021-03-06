//
// Created by Austin Wildgrube on 2/25/21.
//

#ifndef SCANNER_H
#define SCANNER_H

class Scanner {
    public:
    static void scan(const char*);
//        static void scan(const std::string&);
    private:
        static int getColumn(char);
        static int searchTokens(int, int);
        static bool checkKeywords(const std::string&);
        static void getPrintStatement(int, const std::string&, int);
        static void getErrorStatement(const std::string&, int);
};

#endif //SCANNER_H