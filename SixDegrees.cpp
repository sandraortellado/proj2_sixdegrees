/*
 * SixDegrees.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Sandra Ortellado, 11/13/2022
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <queue>
#include <stack>

#include "CollabGraph.h"
#include "SixDegrees.h"

using namespace std;


SixDegrees::SixDegrees() {

}

SixDegrees::~SixDegrees() {

}

void SixDegrees::populate_graph(string dataFile) {

    ifstream in;
    in.open(dataFile); 
    string dp;

	if (not in.is_open()) {
        cerr << dataFile << " cannot be opened.\n";
        exit(EXIT_FAILURE); 
    }

    vector<Artist> allArtists;
    CollabGraph artistCollab = CollabGraph();


    while (getline(in, dp)) {
        Artist a = Artist(dp);
        getline(in, dp);
        while (dp != "*" && dp != "") {
            a.add_song(dp);
            getline(in, dp);
        }
        allArtists.push_back(a);
    }

    in.close();


    int aSize = allArtists.size();

    for (int i = 0; i < aSize; i++) {
        artistCollab.insert_vertex(allArtists[i]);
    }

    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < aSize; j++) {
            if (i == j) continue;
            string collabSong = allArtists[i].get_collaboration(allArtists[j]);
            if (collabSong == "") {
                continue;
            }
            artistCollab.insert_edge(allArtists[i], 
                allArtists[j], collabSong);
        }
    }
    this->c = artistCollab;
}

void SixDegrees::depthFirstSearch(string artistA, string artistB, string outputFile) {

    c.clear_metadata();

    if (!c.is_vertex(Artist(artistA))) {
        if (outputFile == "") {
            cout << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }
    if (!c.is_vertex(Artist(artistB))) {
        if (outputFile == "") {
            cout << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }

    stack<Artist> s;
    Artist first = Artist(artistA);
    s.push(first);
    
    while (!s.empty()) {
        Artist top = s.top();
        s.pop();
        c.mark_vertex(top);
        vector<Artist> n;
        n = c.get_vertex_neighbors(top);
        for (Artist a : n) {
            if (!c.is_marked(a)) {
                c.set_predecessor(a, top);
                if (a.get_name() == artistB) {  
                    stack<Artist> s = c.report_path(artistA, artistB);
                    this->customPrint(s, outputFile);
                    return;
                } else {
                    s.push(a);
                }
            }
        }
    }

    if (outputFile == "") {
        cout << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
    } else {
        ofstream MyFile;
        MyFile.open(outputFile);
        MyFile << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
        MyFile.close();
    }


}

void SixDegrees::breadthFirstSearch(string artistA, string artistB, string outputFile) {

    c.clear_metadata();

    if (!c.is_vertex(Artist(artistA))) {
        if (outputFile == "") {
            cout << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }
    if (!c.is_vertex(Artist(artistB))) {
        if (outputFile == "") {
            cout << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }

    queue<Artist> q;
    Artist first = Artist(artistA);
    q.push(first);
    

    while (!q.empty()) {
        Artist top = q.front();
        q.pop();
        c.mark_vertex(top);
        vector<Artist> n;
        n = c.get_vertex_neighbors(top);
        for (Artist a : n) {
            if (!c.is_marked(a)) {
                c.set_predecessor(a, top);
                q.push(a);
                if (a.get_name() == artistB) {
                    stack<Artist> s = c.report_path(artistA, artistB);
                    this->customPrint(s, outputFile);
                    return;
                }
            }
        }
    }
    if (outputFile == "") {
        cout << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
    } else {
        ofstream MyFile;
        MyFile.open(outputFile);
        MyFile << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
        MyFile.close();
    }
    
}

bool SixDegrees::customContains(vector<string> notArtists, string artist) {
    for (string s : notArtists) {
        if (s == artist) {
            return true;
        }
    }
    return false;

}

void SixDegrees::customPrint(stack<Artist> path, string outputFile) {
    while (path.size() >= 2) {
        Artist aClass = path.top();
        path.pop();
        Artist bClass = path.top();
        string collabSong = aClass.get_collaboration(bClass);

        if (outputFile == "") {
            cout << "\"" << aClass.get_name() << "\"" << " collaborated with " << "\"" << bClass.get_name() << "\"" << " in " << "\"" << collabSong << "\"" << "." << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile << "\"" << aClass.get_name() << "\"" << " collaborated with " << "\"" << bClass.get_name() << "\"" << " in " << "\"" << collabSong << "\"" << "." << endl;
            MyFile.close();
        }
    }

}

void SixDegrees::excl(string artistA, string artistB, vector<string> notArtists, string outputFile) {   

    c.clear_metadata();

    if (!c.is_vertex(Artist(artistA))) {
        if (outputFile == "") {
            cout << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistA << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }
    if (!c.is_vertex(Artist(artistB))) {
         if (outputFile == "") {
                cout << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
        } else {
            ofstream MyFile(outputFile);
            MyFile  << "\"" << artistB << "\"" << " was not found in the dataset :(" << endl;
            MyFile.close();
        }
        return;
    }

    for (int i = 0; i < notArtists.size(); i++) {
        if (!c.is_vertex(notArtists[i])) {
            cout << "\"" << notArtists[i] << "\"" << " was not found in the dataset :(" << endl;
            return;
        }
        if (notArtists[i] == artistA || notArtists[i] == artistB) {
            
            if (outputFile == "") {
                cout << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
            } else {
                ofstream MyFile(outputFile);
                MyFile  << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
                MyFile.close();
                
            }
            return;
        }
    }


    queue<Artist> q;
    Artist first = Artist(artistA);
    q.push(first);
    

    while (!q.empty()) {
        Artist top = q.front();
        q.pop();
        c.mark_vertex(top);
        vector<Artist> n;
        n = c.get_vertex_neighbors(top);
        for (Artist a : n) {
            if (!c.is_marked(a) && !this->customContains(notArtists, a.get_name())) {
                c.set_predecessor(a, top);
                q.push(a);
                if (a.get_name() == artistB) {
                    stack<Artist> s = c.report_path(artistA, artistB);
                    this->customPrint(s, outputFile);
                    return;
                }
            }
        }
    }
    if (outputFile == "") {
        cout << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
    } else {
        ofstream MyFile(outputFile);
        MyFile << "A path does not exist between " << "\"" << artistA << "\"" << " and " << "\"" << artistB << "\"" << "." << endl;
        MyFile.close();
        
    }
}






