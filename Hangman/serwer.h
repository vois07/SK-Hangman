#ifndef SERWER_H
#define SERWER_H

#include <string>
#include <QtDebug>
#include <QtGui>
#include <fstream>
#include <cstdlib>


class Serwer
{
    std::string haslo;
    std::string encoded;
    std::vector<std::string> lines;
    std::string passpath = "/home/paulina/Desktop/Studia/SK/Hangman/passwords";

public:
    Serwer();
    void encode();
    std::string getLine();
    bool decode(char);
    bool checkWon();
    int steps2die = 0;
    void loadPasswords();
    void Reset();
};

#endif // SERWER_H
