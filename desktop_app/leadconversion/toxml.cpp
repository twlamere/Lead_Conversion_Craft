#ifndef TOXML_CPP
#define TOXML_CPP

/*
    Traye LaMere
    21 July 2015

    Modified from console application: 31 July 2015

    This program is intended for use by Craft and Associates, Inc. in order to
    assist with converting marketing lead csv's to an xml usable by ebureau to
    look up lead scores.

    In the future the plan is to create an application that will be usable for
    more purposes such as but not limited to, specifying a number of files,
    converting both to xml and from xml after ebureau looks it up, being able to
    use custom csvs so the program isn't limited to its usage for South College,
    push the file to ftp itself and pull the result (and converting it to the
    desired format immediately thus eliminating all in between human steps).

    However, for now this file will simply convert Asheville and Knoxville csv's
    from South College to an xml. And another file will convert the output xml
    to the desired final csv.
*/

#define KNOX_HEADERS 19
#define ASH_HEADERS 20

/******************************************************************************/
//                                  INCLUDES                                  //
/******************************************************************************/

#include "toxml.h"

using namespace std;

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
inline void printXML(xml &toPrint, stringstream &ss)
{
    ss << "<transaction><input><account><account>" + toPrint.leadid +
        "</account></account><home><first>" + toPrint.first + "</first><last>"
        + toPrint.last + "</last><address>" + toPrint.addr + "</address><city>" +
        toPrint.city + "</city>" + toPrint.state + "<zip>" + toPrint.zip
        + "</zip><phone>" + toPrint.phone + "</phone></home><leaddate>" +
        toPrint.leaddate + "</leaddate>/education</input></transaction>\n";
}

/*
    Changes format of date from mm/dd/yyyy to yyyymmdd
*/
inline string convertDate(string &temp)
{
    return temp.substr(6,4) + temp.substr(0,2) + temp.substr(3,2);
}

/*
    Scrubs phone number input of extraneous characters
*/
inline string cleanPhone(string &temp)
{
    string toRet = temp;
    if (toRet.find('-') != string::npos)
    {
        toRet.erase(toRet.find('-'),1);
    }
    if (toRet.find('-') != string::npos)
    {
        toRet.erase(toRet.find('-'),1);
    }
    if (toRet.find(' ') != string::npos)
    {
        toRet.erase(toRet.find(' '),1);
    }
    if (toRet.find('(') != string::npos)
    {
        toRet.erase(toRet.find('('),1);
    }
    if (toRet.find(')') != string::npos)
    {
        toRet.erase(toRet.find(')'),1);
    }
    return toRet;
}

inline void cleanInput(string &temp, ifstream &in)
{
    //In case commas within quotes
    if (temp.size() && temp[0] == '"')
    {
        string temp2 = "";
        do
        {
            getline(in, temp2, ',');
            temp = temp + temp2;
        }
        while (temp[temp.size() - 1] != '"');

        temp.erase(0, 1);
        temp.erase(temp.size()-1, 1);
    }

    //Get rid of < and > input that will interfere with XML
    int tempInd1 = temp.find('>');
    int tempInd2 = temp.find('<');
    while (tempInd1 >= 0 || tempInd2 >= 0)
    {
        if (tempInd1 >= 0)
        {
            temp.replace(tempInd1, 1, " ");
        }
        if (tempInd2 >= 0)
        {
            temp.replace(tempInd2, 1, " ");
        }

        tempInd1 = temp.find('>');
        tempInd2 = temp.find('<');
    }
}

/*
    Parses a South College knoxville.csv and sends xml output to ss

    expected input:
        leadId,captureDate,profile,first_name,last_name,email,address1,address2,
        city,state,Zip_code,main_phone,alt_phone,TimeStamp,source,
        program_of_interest,education_level,hs_grad_year,comments
*/
void parseKnox(const string &fname, stringstream &ss)
{
    xml toPrint;

    ifstream in(fname);
    if (in.fail())
    {
        throw invalid_argument("Knoxville file open error");
    }

    bool ran = false; //skips header lines
    while(!in.eof())
    {
        for (int i = 0; i < KNOX_HEADERS - 1; ++i)
        {
            string temp = "";
            getline(in, temp, ',');

            cleanInput(temp, in);

            if (ran)
            {
                switch (i)
                {
                    case 0: //leadid
                        if (temp.size() < 1) return;
                        toPrint.leadid = temp;
                        break;
                    case 1: //captureDate
                        toPrint.leaddate = convertDate(temp);
                        break;
                    case 3: //first
                        toPrint.first = temp;
                        break;
                    case 4: //last
                        toPrint.last = temp;
                        break;
                    case 6: //address1
                        toPrint.addr = temp;
                        break;
                    case 7: //address2
                        toPrint.addr = toPrint.addr + " " + temp;
                        break;
                    case 8: //city
                        toPrint.city = temp;
                        break;
                    case 9: //state
                        toPrint.state = temp;
                        break;
                    case 10: //zip
                        toPrint.zip = temp;
                        break;
                    case 11: //phone
                        toPrint.phone = cleanPhone(temp);
                        break;
                    default: //else do nothing
                        break;
                } //end switch
            } //end if (ran)
        } //end for
        string temp = "";
        getline(in, temp);
        if (ran) printXML(toPrint, ss);
        ran = true;
    } //end while
}

/*
    Parses a South College ashville.csv and sends xml output to ss

    expected input:
        leadId,captureDate,profile,first_name,last_name,address1,address2,city,
        state,Zip_Code,email,main_phone,alt_phone,TimeStamp,source,
        program_of_interest,education_level,hs_grad_year,comments,age
*/
void parseAsh(const string &fname, stringstream &ss)
{
    xml toPrint;

    ifstream in(fname);
    if (in.fail())
    {
        throw invalid_argument("Ashville file open error");
    }

    bool ran = false; //skips header lines
    while(!in.eof())
    {
        for (int i = 0; i < ASH_HEADERS - 1; ++i)
        {
            string temp = "";
            getline(in, temp, ',');

            cleanInput(temp, in);

            if (ran)
            {
                switch (i)
                {
                    case 0: //leadid
                        if (temp.size() < 1) return;
                        toPrint.leadid = temp;
                        break;
                    case 1: //captureDate
                        toPrint.leaddate = convertDate(temp);
                        break;
                    case 3: //first
                        toPrint.first = temp;
                        break;
                    case 4: //last
                        toPrint.last = temp;
                        break;
                    case 5: //address1
                        toPrint.addr = temp;
                        break;
                    case 6: //address2
                        toPrint.addr = toPrint.addr + " " + temp;
                        break;
                    case 7: //city
                        toPrint.city = temp;
                        break;
                    case 8: //state
                        toPrint.state = temp;
                        break;
                    case 9: //zip
                        toPrint.zip = temp;
                        break;
                    case 11: //phone
                        toPrint.phone = cleanPhone(temp);
                        break;
                    default: //else do nothing
                        break;
                } //end switch
            } //end if (ran)
        } //end for
        string temp = "";
        getline(in, temp);
        if (ran) printXML(toPrint, ss);
        ran = true;
    } //end while
}

/******************************************************************************/
//                                    MAIN                                    //
/******************************************************************************/

/*
    Main function, reads in filenames and sends them to the respective helpers
    to parse them.
*/

void toxml_main(string knox_fname, string ash_fname, string saveas_fname)
{
    stringstream ss;

    if (knox_fname != "") parseKnox(knox_fname, ss);
    if (ash_fname != "") parseAsh(ash_fname, ss);

    ofstream out(saveas_fname);
    if (out.fail())
    {
        throw invalid_argument("Save as file error");
    }
    out << ss.str();
}

#endif
