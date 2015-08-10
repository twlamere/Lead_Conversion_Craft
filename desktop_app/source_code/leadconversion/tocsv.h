#ifndef TOCSV_H
#define TOCSV_H

/*
    Traye LaMere
    21 July 2015

    This program is intended for use by Craft and Associates, Inc. in order to
    assist with converting marketing lead csv's to an xml usable by ebureau to
    look up lead scores and then deconverting to a usable format.

    This is the companion file to "toXML.cpp"
*/

/******************************************************************************/
//                                  INCLUDES                                  //
/******************************************************************************/

#include <string>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

/******************************************************************************/
//                                   STRUCTS                                  //
/******************************************************************************/

struct csvStruct
{
    string escore;
    string first;
    string last;
    string addr;
    string city;
    string zip;
    string phone;
    string leaddate;
};

/******************************************************************************/
//                              HELPER FUNCTIONS                              //
/******************************************************************************/

inline string getAttr(int ind, string &temp, string &toParse);
inline void printCSV(csvStruct &toPrint, stringstream &ss);
void parseXML(const string &fname, stringstream &ss);

/******************************************************************************/
//                                    MAIN                                    //
/******************************************************************************/

/*
    Main function, reads in filenames and sends them to the respective helpers
    to parse them.

    Expected program call:
        [program] [input.xml] > [output_file.csv]
*/
void tocsv_main(string xml, string saveas);

#endif // TOCSV_H

