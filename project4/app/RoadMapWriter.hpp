// RoadMapWriter.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// The RoadMapWriter class is capable of writing a RoadMap to an output
// stream in a format that allows you to see information about it.  This
// is provided purely as a debugging aid; you don't actually need it to
// solve the problem at hand.

#ifndef ROADMAPWRITER_HPP
#define ROADMAPWRITER_HPP

#include <ostream>
#include "RoadMap.hpp"



class RoadMapWriter
{
public:
    // writeRoadMap() writes a RoadMap to the given output stream (e.g.,
    // you could pass std::cout to write it to the console) in a format
    // that's designed to assist in debugging.
    void writeRoadMap(std::ostream& out, const RoadMap& roadMap);
};



#endif // ROADMAPWRITER_HPP

