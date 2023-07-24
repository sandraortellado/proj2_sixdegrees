/*
 * unit_testing.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Sandra Ortellado, 11/13/2022
 */

#include "CollabGraph.h"
#include "SixDegrees.h"
#include <cassert>

void report_path_test() {
    CollabGraph g = CollabGraph();
    Artist a1 = Artist("Rihanna");
    a1.add_song("Love the way you lie");
    Artist a2 = Artist("Eminem");
    a1.add_song("Love the way you lie");
    Artist a3 = Artist("Dr. Dre");
    a2.add_song("I need a doctor");
    g.insert_vertex(a1);
    g.insert_vertex(a2);
    g.insert_vertex(a3);
    g.insert_edge(a1, a2, "Love the way you lie");
    g.insert_edge(a2, a3, "I need a doctor");

    stack<Artist> s = g.report_path(a1, a2);
    int sSize = s.size();
    assert(sSize == 1);

}

void get_vertex_neighbors_test() {
    CollabGraph g = CollabGraph();
    Artist a1 = Artist("Rihanna");
    a1.add_song("Love the way you lie");
    Artist a2 = Artist("Eminem");
    a2.add_song("Love the way you lie");
    g.insert_vertex(a1);
    g.insert_vertex(a2);
    g.insert_edge(a1, a2, "Love the way you lie");

    vector<Artist> neighs = g.get_vertex_neighbors(a1);
    int nSize = neighs.size();
    assert(nSize == 1);
}

//until I build out more of the six degrees class,
//I can only check that this function doesn't crash
//ran out of time to do more
void populate_graph_test() {

    SixDegrees s = SixDegrees();
    s.populate_graph("artists.txt");

}

void bfs_test() {
    SixDegrees s = SixDegrees();
    s.populate_graph("artists.txt");
    //should print path of length 3, shortest path
    s.breadthFirstSearch("Beyonce", "Rihanna", "");
    //should print no path error message
    s.breadthFirstSearch("Beyonce", "Alex", "");

}

void dfs_test() {
    SixDegrees s = SixDegrees();
    s.populate_graph("artists.txt");
    //should print any path from Beyonce to Rihanna
    s.depthFirstSearch("Beyonce", "Rihanna", "");
    //should print no path error message
    s.depthFirstSearch("Beyonce", "Alex", "");

}

void not_test() {
    SixDegrees s = SixDegrees();
    s.populate_graph("artists.txt");
    vector<string> notArtists;
    notArtists.push_back("Drake");
    notArtists.push_back("Alicia Keys");
    //should print path that does not include drake or alicia keys
    s.excl("Beyonce","Rihanna", notArtists);
    //should print no path error message
    s.exl("Beyonce", "Alex", notArtists);

}

int main() {

    report_path_test();
    get_vertex_neighbors_test();
    populate_graph_test();
    bfs_test();
    dfs_test();
    not_test();

}