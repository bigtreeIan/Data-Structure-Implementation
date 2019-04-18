// RoadMapWriter.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic

#include "RoadMapWriter.hpp"


void RoadMapWriter::writeRoadMap(std::ostream& out, const RoadMap& roadMap)
{
    out << "LOCATIONS" << std::endl;

    for (int vertex : roadMap.vertices())
    {
        out << "    " << vertex << ": " << roadMap.vertexInfo(vertex) << std::endl;
    }

    out << std::endl;
    out << "ROAD SEGMENTS" << std::endl;

    for (std::pair<int, int> edge : roadMap.edges())
    {
        out << "    " << edge.first << "," << edge.second << ": ";

        RoadSegment segment = roadMap.edgeInfo(edge.first, edge.second);
        out << segment.miles << "miles; " << segment.milesPerHour << "mph";

        out << std::endl;
    }

    out << std::endl;
}

