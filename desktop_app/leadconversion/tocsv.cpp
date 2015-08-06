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

#include "tocsv.h"

using namespace std;

/******************************************************************************/
//                              HELPER FUNCTIONS                              //
/******************************************************************************/

inline string getAttr(int ind, string &temp, string &toParse)
{
    temp = toParse.substr(ind);
    toParse.erase(ind, toParse.size() - ind);
    string toRet = toParse.substr(toParse.rfind('>')+1);
    toParse = temp;
    return toRet;
}

inline void printCSV(csvStruct &toPrint, stringstream &ss)
{
        ss << toPrint.escore + ", " + toPrint.first + ", " + toPrint.last + ", "
            + toPrint.addr + ", " + toPrint.city + ", "+ toPrint.zip + ", " +
            toPrint.phone + ", " + toPrint.leaddate + "\n";
}

void parseXML(const string &fname, stringstream &ss)
{
    ifstream in(fname);
    if (in.fail())
    {
        throw invalid_argument("E-bureau xml file open error");
    }

    ss << "E-Score, First Name, Last Name, Address, City, Zip, Phone, Lead Date\n"; //header

    csvStruct csv;
    string firstHalf = "";
    string toParse = "";
    string temp = "";
    int ind = 0;
    while (getline(in, toParse))
    {
        /**********************************************************************/
        //Retrieve inputted data and score:
        /**********************************************************************/

        //escore
        ind = toParse.find("</score>");
        firstHalf = toParse.substr(0, ind); //to check if better data
        csv.escore = getAttr(ind, temp, toParse);

        //first name
        ind = toParse.find("</first>");
        csv.first = getAttr(ind, temp, toParse);

        //last name
        ind = toParse.find("</last>");
        csv.last = getAttr(ind, temp, toParse);

        //address
        ind = toParse.find("</address>");
        csv.addr = getAttr(ind, temp, toParse);

        //city
        ind = toParse.find("</city>");
        csv.city = getAttr(ind, temp, toParse);

        //zip
        ind = toParse.find("</zip>");
        csv.zip = getAttr(ind, temp, toParse);

        //phone
        ind = toParse.find("</phone>");
        csv.phone = getAttr(ind, temp, toParse);

        //leaddate
        ind = toParse.find("</leaddate>");
        csv.leaddate = getAttr(ind, temp, toParse);

        /**********************************************************************/
        //Check for better data returned: ( everything before verify )
        /**********************************************************************/
        toParse = firstHalf;
        ind = firstHalf.find("<verify>");
        toParse = toParse.substr(0, ind);

        //first name
        ind = toParse.find("</first>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.first = temp;
        }

        //last name
        ind = toParse.find("</last>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.last = temp;
        }

        //address
        ind = toParse.find("</address>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.addr = temp;
        }

        //city
        ind = toParse.find("</city>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.city = temp;
        }

        //zip
        ind = toParse.find("</zip>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.zip = temp.substr(0, 5);
        }

        //phone
        ind = toParse.find("</phone>");
        if (ind >= 0)
        {
            temp = getAttr(ind, temp, toParse);
            if (temp != "no match") csv.phone = temp;
        }

        printCSV(csv, ss);
    }
}

/******************************************************************************/
//                                    MAIN                                    //
/******************************************************************************/

/*
    Main function, reads in filenames and sends them to the respective helpers
    to parse them.

    Expected program call:
        [program] [input.xml] > [output_file.csv]
*/
void tocsv_main(string xml, string saveas)
{
    stringstream ss;
    parseXML(xml, ss);

    ofstream out(saveas);
    if (out.fail())
    {
        throw invalid_argument("Save as file error");
    }
    out << ss.str();
}
