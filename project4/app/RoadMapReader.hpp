// RoadMapReader.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// The RoadMapReader class provides an object that knows how to read a
// RoadMap from the standard input, using the format given in the
// project write-up.

#ifndef ROADMAPREADER_HPP
#define ROADMAPREADER_HPP

#include "RoadMap.hpp"
#include "InputReader.hpp"



class RoadMapReader 
{
public:
    // readRoadMap() reads a RoadMap from the given InputReader.  The
    // RoadMap is expected to be described in the format given in the
    // project write-up.
    RoadMap readRoadMap(InputReader& in);
};



#endif // ROADMAPREADER_HPP

