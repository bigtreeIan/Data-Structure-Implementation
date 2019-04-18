// InputReader.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// An InputReader wraps an istream (such as std::cin) and allows you to read
// lines of text from it, skipping lines that are not a meaningful part of
// the input.  In this project, that means blank lines, lines containing
// only spaces, and lines that begin with a '#' character.

#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <istream>
#include <string>



class InputReader
{
public:
    // Initializes an InputReader so that it reads from the given input
    // stream.  For example, pass std::cin as a parameter to the constructor
    // if you want to read input from std::cin.
    InputReader(std::istream& in): in_{in} { }

    // readLine() reads a line of input from the input stream associated
    // with this InputReader, skipping non-meaningful lines.
    std::string readLine();

    // readLineInt() reads a line of input from the input stream associated
    // with this InputReader, assuming that the line of input contains an
    // integer value (e.g., "7").
    int readIntLine();

private:
    std::istream& in_;
};



#endif // INPUTREADER_HPP

