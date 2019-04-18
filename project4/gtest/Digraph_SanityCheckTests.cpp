// Digraph_SanityCheckTests.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is a set of "sanity checking" unit tests for your Digraph 
// implementation, provided primarily as a mechanism for ensuring
// that your implementation is compatible with the unit tests we'll
// be using to test your implementation during graph.  The goal here
// is to ensure that you have all of the necessary member functions,
// and that their type declarations are as they should be.
//
// All of the tests are initially commented out, because none of them
// links initially.  (Interestingly, they all compile successfully,
// because Digraph.hpp declares all of the necessary member functions,
// but they will all result in link errors, since there are no
// implementations of any of Digraph's member functions until you write
// them.)
//
// As you implement member functions, you can start uncommenting unit
// tests, as you did in the previous project.  Once again, try to get
// a sense for which tests you can successfully uncomment as you make
// changes to your Digraph template class.
//
// Note, too, that some of these tests attempt to seemingly unnecessary
// things, like getting a vector back from Digraph and then immediately
// clearing it.  This is a simple mechanism to avoid compiler warnings
// about unused variables, while preserving the ability to declare those
// variables (and their types) to ensure that the return types of your
// member functions are correct.

#include <gtest/gtest.h>
#include "Digraph.hpp"
#include <iostream>


TEST(Digraph_SanityChecks, canConstructWithNoArguments)
{
   Digraph<int, int> d1;
   Digraph<std::string, std::string> d2;
}


TEST(Digraph_SanityChecks, canCopyConstructToCompatibleType)
{
   Digraph<unsigned int, std::string> d1;
   Digraph<unsigned int, std::string> d2{d1};
}


TEST(Digraph_SanityChecks, canAssignToCompatibleType)
{
   Digraph<std::string, double> d1;
   Digraph<std::string, double> d2;
   d1 = d2;
}


TEST(Digraph_SanityChecks, canGetAllVertexNumbers)
{
   Digraph<std::string, std::string> d1;
   const Digraph<std::string, std::string>& d = d1;
   std::vector<int> v = d.vertices();
   v.clear();
}


TEST(Digraph_SanityChecks, canGetAllEdges)
{
   Digraph<double, double> d1;
   const Digraph<double, double>& d = d1;
   std::vector<std::pair<int, int>> e = d.edges();
   e.clear();
}


TEST(Digraph_SanityChecks, canGetAllEdgesForExistingVertex)
{
   Digraph<double, double> d1;
   d1.addVertex(1, 3.5);
   d1.addVertex(2, 4.75);
   d1.addEdge(1, 2, -1.5);
   const Digraph<double, double>& d = d1;
   std::vector<std::pair<int, int>> e = d.edges(1);
   e.clear();
}


TEST(Digraph_SanityChecks, canGetVertexInfoForExistingVertex)
{
   Digraph<std::string, std::string> d1;
   d1.addVertex(1, "Boo");
   const Digraph<std::string, std::string>& d = d1;
   std::string vinfo = d.vertexInfo(1);
   vinfo += "Boo";
}


TEST(Digraph_SanityChecks, canGetEdgeInfoForExistingEdge)
{
   Digraph<std::string, std::string> d1;

   d1.addVertex(1, "Boo");

   d1.addVertex(2, "Bear");

   d1.addEdge(1, 2, "go");
   const Digraph<std::string, std::string>& d = d1;
   std::string einfo = d.edgeInfo(1, 2);
   einfo += "Hello";
}


TEST(Digraph_SanityChecks, canAddVertex)
{
   Digraph<int, int> d1;
   d1.addVertex(1, 10);
}


TEST(Digraph_SanityChecks, canAddEdge)
{
   Digraph<int, int> d1;
   d1.addVertex(1, 10);
   d1.addVertex(2, 9);
   d1.addEdge(1, 2, -1);
}


TEST(Digraph_SanityChecks, canRemoveExistingVertex)
{
   Digraph<std::string, std::string> d1;

   d1.addVertex(1, "Boo");
   d1.removeVertex(1);
}


TEST(Digraph_SanityChecks, canRemoveExistingEdge)
{
   Digraph<float, float> d1;
   d1.addVertex(1, 3.5);
   d1.addVertex(2, 4.75);
   d1.addEdge(1, 2, -1.5);
   d1.removeEdge(1, 2);
}


TEST(Digraph_SanityChecks, canGetVertexCount)
{
   const Digraph<int, int> d1;
   int vcount = d1.vertexCount();
   ++vcount;
}


TEST(Digraph_SanityChecks, canGetTotalEdgeCount)
{
   const Digraph<int, int> d1;
   int ecount = d1.edgeCount();
   ++ecount;
}


TEST(Digraph_SanityChecks, canGetEdgeCountForExistingVertex)
{
   Digraph<int, int> d1;
   d1.addVertex(1, 10);
   const Digraph<int, int>& d = d1;
   int ecount = d.edgeCount(1);
   ++ecount;
}


TEST(Digraph_SanityChecks, canFindShortestPaths)
{
   Digraph<std::string, std::string> d1;
   d1.addVertex(1, "Boo");
   d1.addVertex(2, "Bear");
   d1.addEdge(1, 2, "hello");
   const Digraph<std::string, std::string>& d = d1;

   std::function<double(const std::string&)> edgeWeightFunc =
       [](const std::string& edgeInfo)
       {
           return static_cast<double>(edgeInfo.length());
       };

   std::map<int, int> paths = d.findShortestPaths(1, edgeWeightFunc);
   paths.clear();
}


TEST(Digraph_SanityChecks, canDetermineStrongConnectedness)
{
   Digraph<int, int> d1;
   bool connected = d1.isStronglyConnected();
   connected = !connected;
}

