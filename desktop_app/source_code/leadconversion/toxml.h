#ifndef TOXML_H
#define TOXML_H

/******************************************************************************/
//                                  INCLUDES                                  //
/******************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

/******************************************************************************/
//                                   STRUCTS                                  //
/******************************************************************************/

struct xml
{
    string leadid = "";
    string first = "";
    string last = "";
    string addr = "";
    string city = "";
    string state = "";
    string zip = "";
    string phone = "";
    string leaddate = "";
};

/******************************************************************************/
//                              HELPER FUNCTIONS                              //
/******************************************************************************/

/*
    Prints struct to stringstream object

    output:
        <transaction><input><account><account>[leadid]</account></account><home>
        <first>[first]</first><last>[last]</last><address>[addr]</address><city>
        [city]</city>[state]<zip>[zip]</zip><phone>[phone]</phone></home>
        <leaddate>[leaddate]</leaddate>/education</input></transaction>
*/
inline void printXML(xml &toPrint, stringstream &ss);

/*
    Changes format of date from mm/dd/yyyy to yyyymmdd
*/
inline string convertDate(string &temp);

/*
    Scrubs phone number input of extraneous characters
*/
inline string cleanPhone(string &temp);

inline void cleanInput(string &temp, ifstream &in);

/*
    Parses a South College knoxville.csv and sends xml output to ss

    expected input:
        leadId,captureDate,profile,first_name,last_name,email,address1,address2,
        city,state,Zip_code,main_phone,alt_phone,TimeStamp,source,
        program_of_interest,education_level,hs_grad_year,comments
*/
void parseKnox(const string &fname, stringstream &ss);

/*
    Parses a South College ashville.csv and sends xml output to ss

    expected input:
        leadId,captureDate,profile,first_name,last_name,address1,address2,city,
        state,Zip_Code,email,main_phone,alt_phone,TimeStamp,source,
        program_of_interest,education_level,hs_grad_year,comments,age
*/
void parseAsh(const string &fname, stringstream &ss);

/******************************************************************************/
//                                    MAIN                                    //
/******************************************************************************/

/*
    Main function, reads in filenames and sends them to the respective helpers
    to parse them.

    Expected program call:
        [program] [knox_filename | "none"] [ash_filename | "none"] > [output_file]
*/

void toxml_main(string knox_fname, string ash_fname, string saveas_fname);

#endif // TOXML_H

