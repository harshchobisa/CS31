//
//  main.cpp
//  CS 31 Project 3
//
//  Created by Harsh Chobisa on 10/22/18.
//  Copyright © 2018 Harsh Chobisa. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;



// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//Returns true is pollData has proper syntax, returns false otherwise
bool hasProperSyntax(string pollData)
{
    if (pollData[pollData.size()-1] != ',') //comma is appended so we can more easily find the end of
        //the string
    {
        pollData += ',';
    }
    
    for (int i = 0; i < pollData.size(); i++)
    {
        pollData[i] = toupper(pollData[i]);
    }
    
    string stateCode;
    
    int x = 0;
    
    while (x < pollData.size())
    {
        while (pollData[x] != ',' ) //need to restart check after hitting a comma
        {
            
            stateCode += pollData[x];
            x++;
            stateCode += pollData[x];
            
            if (!(isValidUppercaseStateCode(stateCode)))
            {
                return false;
            }
            stateCode = "";
            
            x++;
            
            while (pollData[x] != ',') // end the check when we hit a comma
            {
                if (!(isdigit(pollData[x])))
                {
                    return false;
                }
                
                int z = 2; //ensures that we only approve 1 or two digit numbers
                while (isdigit(pollData[x]) && z > 0)
                {
                    x++;
                    z--;
                }
                
                if (!(isalpha(pollData[x])))
                {
                    return false;
                }
                
                x++;
            }
            
        }
        
        while (pollData[x] == ',') //move on to the next part past the comma
        {
            x++;
        }
    }
    return true;
    
}

int seatTally = 0;

//sets seatTally to the number of seats predicted party will win by the pollData
int tallySeats(string pollData, char party, int& seatTally)
{
    //check for user errors
    if (!(hasProperSyntax(pollData))) {
        return 1;
    }
    if (!(isalpha(party)))
    {
        return 2;
    }
    
    party = toupper(party);
    for (int i = 0; i < pollData.size(); i++)
    {
        pollData[i] = toupper(pollData[i]);
    }
    
    seatTally = 0;
    
    //algorithm for adding up values before the party letter
    for (int i = 0; i < pollData.size(); i++)
    {
        
        if (pollData[i] == party)
        {
            int originali = i;
            i--;
            int multiplier = 1;
            while (isdigit(pollData[i])) {
                int x = pollData[i] - '0';
                seatTally += x * multiplier;
                multiplier = multiplier * 10;
                i--;
            }
            i = originali;
            
        }
    }
    
    return 0;
}

int main()
{
    assert(hasProperSyntax(""));
    assert(hasProperSyntax("NY"));
    assert(hasProperSyntax("NY9D"));
    assert(hasProperSyntax("NY19D"));
    //check that 3+ digit number will not be accepted
    assert(hasProperSyntax("NY190D") == false);
    assert(hasProperSyntax("NY19045D") == false);
    
    assert(hasProperSyntax("NY1D33R"));
    assert(hasProperSyntax("NY9R17D1I,Vt,NJ3d5r4D,KS4R"));
    
    //check for input errors
    assert((tallySeats(" ", 'D', seatTally) == 1));
    assert((tallySeats("CAA99D", 'D', seatTally) == 1));
    assert((tallySeats("CAA99DD", 'D', seatTally) == 1));
    assert(tallySeats("MA9D", '@', seatTally) == 2);
    assert(tallySeats("MA9@", 'D', seatTally) == 1);
    
    
    assert((tallySeats("CA99D", '2', seatTally) == 2));
    
    assert((tallySeats("", 'D', seatTally) == 0) && seatTally==0);
    assert((tallySeats("NY", 'D', seatTally) == 0) && seatTally==0);
    assert((tallySeats("NY1d", 'D', seatTally) == 0) && seatTally==1);
    assert((tallySeats("CA99D", 'D', seatTally) == 0) && seatTally==99);
    assert((tallySeats("NY1D33R", 'R', seatTally) == 0) && seatTally==33);
    assert((tallySeats("NY12R1D33R", 'R', seatTally) == 0) && seatTally==45);
    assert((tallySeats("NY9R17D1I,Vt,NJ3d5r4D,KS4R", 'D', seatTally) == 0) && seatTally==24);
    assert((tallySeats("NY9R17D1I,Vt,NJ3d5r4D,KS4R,NY9R17D1I,NJ3d5r4D,KS4R", 'D', seatTally) == 0) && seatTally==48);
    
    

        assert(!hasProperSyntax(","));
        assert(!hasProperSyntax(",WY1R"));
        assert(!hasProperSyntax("WY1R,"));
        
    cout << "all tests passed" << endl;
    
    
}



