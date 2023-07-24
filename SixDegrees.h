#ifndef __SIXDEGREES__
#define __SIXDEGREES__

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "CollabGraph.h"
using namespace std;

class SixDegrees {

public:
    SixDegrees();
    ~SixDegrees();

    void populate_graph(string dataFile);
    void depthFirstSearch(string artistA, string artistB, string outputFile);
    void breadthFirstSearch(string artistA, string artistB, string outputFile);
    void excl(string artistA, string artistB, vector<string> notArtists, string outputFile);


private:
    CollabGraph c;
    bool customContains(vector<string> notArtists, string artist);
    void customPrint(stack<Artist> path, string outputFile);

};

#endif