// main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include "Digraph.hpp"
#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include "Trip.hpp"
#include "TripMetric.hpp"
#include "RoadMap.hpp"
#include "RoadSegment.hpp"
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <iomanip>



double distancefunc(const RoadSegment& edgeInfo){
	return edgeInfo.miles;
}

double timefunc(const RoadSegment& edgeInfo){
	return edgeInfo.miles/edgeInfo.milesPerHour;
}

void generatetimepath(RoadMap road, int& from_v, int& to_v, std::map<int, int> m, double& total_time){
	if(from_v == to_v){
		return;
	}
	else{
		int start_v = m[to_v];
		double curr_speed = road.edgeInfo(start_v, to_v).milesPerHour;
		double curr_dis = road.edgeInfo(start_v, to_v).miles;
		double curr_time = curr_dis / curr_speed;
		total_time += curr_time;
		generatetimepath(road, from_v, start_v, m, total_time);
		int hour_part = curr_time;
		int min_part = curr_time * 60;
		double sec_part = (curr_time * 60 - min_part) * 60;
		std::cout << "  Continue to " << road.vertexInfo(to_v) 
		<< " (" << curr_dis << " miles @ " << curr_speed << " mph = ";
		if(hour_part <= 0 and min_part == 0){
			std::cout << std::setprecision(3) << sec_part << " secs" << ")" <<std::endl;
		}
		else if(hour_part <= 0 and min_part > 0){
			std::cout << min_part << " mins " << std::setprecision(3) << sec_part << " secs"<< ")" <<std::endl;
		}
		else if(hour_part == 1){
			std::cout << hour_part << " hr " << min_part << " mins " << std::setprecision(3) << sec_part << " secs"<< ")" <<std::endl;
		}
		else{ 
			std::cout << hour_part << " hrs " << min_part << " mins " << std::setprecision(3) << sec_part << " secs"<< ")" <<std::endl;
		}
	}
}

void generatedispath(RoadMap road, int& from_v, int& to_v, std::map<int, int> m, double& total_dis){
	if(from_v == to_v){
		return;
	}
	else{
		total_dis += road.edgeInfo(m[to_v], to_v).miles;
		generatedispath(road, from_v, m[to_v], m, total_dis);
		std::cout << "  Continue to " << road.vertexInfo(to_v) 
		<< "(" << road.edgeInfo(m[to_v], to_v).miles << " miles)" << std::endl;
	}
}


int main()
{
	InputReader inputdata(std::cin);
	RoadMap road = RoadMapReader().readRoadMap(inputdata);
	if(road.isStronglyConnected() == false){
		std::cout << "Disconnected Map" << std::endl;
		return 0;
	}
	std::vector<Trip> trip = TripReader().readTrips(inputdata);
	for(auto it = trip.begin(); it != trip.end(); it++){
		if(it->metric == TripMetric::Distance){
       		std::map<int, int> shortestmap = road.findShortestPaths(it->startVertex, distancefunc);
       		std::cout<< "Shortest distance from " 
       		<< road.vertexInfo(it->startVertex)
       		<< " to " 
       		<< road.vertexInfo(it->endVertex) << std::endl;
       		std::cout << "  Begin at " << road.vertexInfo(it->startVertex) << std::endl;
       		double total_dis = 0;
       		generatedispath(road, it->startVertex, it->endVertex, shortestmap, total_dis);
			std::cout << "Total distance: " << total_dis << " miles" << std::endl;
			std::cout << "\n";
       	}
		else{
       		std::map<int, int> shortestmap = road.findShortestPaths(it->startVertex, timefunc);
       		std::cout<< "Shortest driving time from " 
       		<< road.vertexInfo(it->startVertex)
       		<< " to " 
       		<< road.vertexInfo(it->endVertex) << std::endl;
       		std::cout << "  Begin at " << road.vertexInfo(it->startVertex) << std::endl;
       		double total_time = 0;
       		generatetimepath(road, it->startVertex, it->endVertex, shortestmap, total_time);
			int hour_part = total_time;
			int min_part = total_time * 60;
			double sec_part = (total_time * 60 - min_part) * 60;
			if(hour_part <= 0 and min_part == 0){
				std::cout << "Total time: " << std::setprecision(3) << sec_part << " secs " << std::endl;
				std::cout << "\n";
				}
			else if(hour_part <= 0 and min_part > 0){
				std::cout << "Total time: " << min_part << " mins " << std::setprecision(3) << sec_part << "secs"<< std::endl;
				std::cout << "\n";
				}
			else if(hour_part == 1){
				std::cout << "Total time: " << hour_part << " hr " << min_part << " mins " << std::setprecision(3) << sec_part << " secs"<< std::endl;
				std::cout << "\n";
				}
			else{ 
				std::cout << "Total time: " << hour_part << " hrs " << min_part << " mins " << std::setprecision(3) << sec_part << " secs"<< std::endl;
				std::cout << "\n";
			}		
		}
	}
	return 0;
}

