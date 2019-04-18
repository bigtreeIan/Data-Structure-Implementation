// InputReader.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic

#include "InputReader.hpp"


namespace
{
    void trimRight(std::string& s)
    {
        if (s.size() == 0)
        {
            return;
        }

        std::string::iterator i = s.end() - 1;

        while (i >= s.begin() && std::isspace(*i))
        {
            --i;
        }

        s.erase(i + 1, s.end());
    }
}


std::string InputReader::readLine()
{
    std::string line;

    while (true)
    {
        std::getline(in_, line);
        trimRight(line);

        if (line.length() > 0 && line[0] != '#')
        {
            return line;
        }
    }
}


int InputReader::readIntLine()
{
    std::string line = readLine();
    return std::stoi(line);
}


