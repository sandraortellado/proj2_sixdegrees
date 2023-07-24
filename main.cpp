/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Sandra Ortellado, 11/13/2022
 */
#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include "SixDegrees.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc == 1 || argc > 4) {
        cerr << "Usage: ./SixDegrees dataFile [commandFile] [outputFile]" << endl;
        return 1;
    }
    string dataFile = argv[1];
    string outputFile = "";
    string artistA;
    string artistB;

    if (argc > 3 && argv[3]) {
        outputFile = argv[3];
        ifstream in;
        in.open(outputFile); 

        if (not in.is_open()) {
            cerr << outputFile << " cannot be opened.\n";
            return 1; 
        }
        in.close();
    }

    if (argc > 2 && argv[2]) {
        string commandsFile = argv[2];
        ifstream in;
        in.open(commandsFile);
        if (not in.is_open()) {
            cerr << commandsFile << " cannot be opened.\n";
            return 1; 
        }
        SixDegrees s = SixDegrees();
        s.populate_graph(dataFile);

        string dp;
        while (getline(in, dp)) {
            if (dp == "dfs") {
                getline(in, dp);
                artistA = dp;
                getline(in, dp);
                artistB = dp;
                s.depthFirstSearch(artistA, artistB, outputFile);

            }
            else if (dp == "bfs") {
                getline(in, dp);
                artistA = dp;
                getline(in, dp);
                artistB = dp;
                s.breadthFirstSearch(artistA, artistB, outputFile);

            }
            else if (dp == "not") {
                getline(in, dp);
                artistA = dp;
                getline(in, dp);
                artistB = dp;
                vector<string> notArtists;
                getline(in, dp);
                string notArtist = dp;
                while (notArtist != "*") {
                    notArtists.push_back(notArtist);
                    getline(in, dp);
                    notArtist = dp;
                }

                s.excl(artistA, artistB, notArtists, outputFile);
            }
            else if (dp == "quit") {
                return 0;
            }
            else {
                cout << dp << " is not a command. Please try again." << endl;
            }
        }
        in.close();
    } else {

        SixDegrees s = SixDegrees();
        s.populate_graph(dataFile);

        string input;
        while (getline(cin,input)) {
            if (input == "dfs") {
                getline(cin, input);
                artistA = input;
                getline(cin, input);
                artistB = input;
                s.depthFirstSearch(artistA, artistB, outputFile);

            }
            else if (input == "bfs") {
                getline(cin, input);
                artistA = input;
                getline(cin, input);
                artistB = input;
                s.breadthFirstSearch(artistA, artistB, outputFile);

            }
            else if (input == "not") {
                getline(cin, input);
                artistA = input;
                getline(cin, input);
                artistB = input;
                vector<string> notArtists;
                string notArtist;
                getline(cin, input);
                notArtist = input;
                while (notArtist != "*") {
                    notArtists.push_back(notArtist);
                    getline(cin,input);
                    notArtist = input;
                }

                s.excl(artistA, artistB, notArtists, outputFile);
            }
            else if (input == "quit") {
                return 0;
            }
            else {
                cout << input << " is not a command. Please try again." << endl;
            }
        }

    }
    
    

    

    // accept the args
    return 0;
}
