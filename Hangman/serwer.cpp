#include "serwer.h"

Serwer::Serwer()
{
    encoded = "";
    loadPasswords();
    srand(time(NULL));
    haslo = lines[rand()%lines.size()];
}

void Serwer::encode()
{
    for (int i =0; i< haslo.length(); i++)
    {
        if (haslo[i] == ' ') encoded += ' ';
        else if (haslo[i]<= 'Z' && haslo[i]>='A') encoded += '-';
    }
}

void Serwer::Reset()
{
    haslo = lines[rand()%lines.size()];
    encoded ="";
    steps2die = 0;
}

std::string Serwer::getLine()
{
    return encoded;
}

void Serwer::loadPasswords()
{
    std::ifstream infile(passpath);
    std::string line;
    while(getline(infile, line)) {
        lines.push_back(line);
    }
}

bool Serwer::checkWon()
{
    if (haslo == encoded) return true;
    return false;
}

bool Serwer::decode(char c)
{
    std::string str = "";
    bool ans = false;
    for (int i = 0; i < haslo.length(); i++)
    {
        if (haslo[i] == c) {str += haslo[i]; ans = true;}
        else str += encoded[i];
    }
    //qDebug() << QString::fromStdString(str);
    encoded = str;
    return ans;
}

