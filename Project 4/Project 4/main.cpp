//
//  main.cpp
//  Project 4
//
//  Created by Harsh Chobisa on 11/2/18.
//  Copyright © 2018 Harsh Chobisa. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
//2,5,8
using namespace std;

//this function is for testing only. it prints out whatever array is inputted
void printArray(const string a[], int n)
{
    for (int x = 0; x < n ; x++)
    {
        cerr << a[x] << " ";
    }
    cerr << endl;
}

//this function appends the string value to all the string in array z
int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    
    for (int x = 0; x < n ; x++)
    {
        a[x] = a[x] + value;
    }
    return n;
}

//this function returns the positions of target in a, and will return -1 if it is not found
int lookup(const string a[], int n, string target)
{
    if (n <= 0)
        return -1;
    
    for (int x = 0; x < n ; x++)
    {
        if (a[x] == target)
        {
            return x;
        }
    }
    return -1;
}

//this function returns the position of the largest value in the array
int positionOfMax(const string a[], int n)
{
    if ( n <= 0)
        return -1;
    
    string largest = a[0];
    int posLargest = 0;
    for (int x = 0; x < n ; x++)
    {
        if (a[x] > largest)
        {
            largest = a[x];
            posLargest = x;
        }
    }
    return posLargest;
}

//this function rotates all values of the array into the position one below the current position
//and the value in position zero is shifted to the last position in the array
int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0)
        return -1;
    if (pos >= n || pos < 0)
        return -1;
    
    string temp = a[pos];
    for (int x = pos; x < n - 1 ; x++)
    {
        a[x] = a[x+1];
    }
    a[n-1] = temp;
    return pos;
}

//this function counts how many individual runs of values there are in the array
int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    
    if (n == 0) //there can not be any runs if there is an empty array
        return 0;

    int counter = 1;
    for (int x = 0; x < n-1; x++)
    {
        if (a[x] != a[x+1])
        {
            counter++;
        }
        
    }
    
    return counter;
}

//this function flips the array by reversing the order of the elements in the array
int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    
    for (int x = 0; x < (n/2); x++)
    {
        string temp = a[x];
        a[x] = a[n-x-1];
        a[n-x-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    int limit;
    if (n2 > n1) //the smaller one has to be the limit or we will go out of bounds
    {
        limit = n1;
    }
    else
        limit = n2;
    
    for (int x = 0; x < limit; x++)
    {
        if (a1[x] != a2[x])
        {
            return x;
        }
    }
    
    return limit;
    
}

//converts a character to an integer
int charToInt(char ch)
{
    return ch - '0';
}

//finds the first position of where all the values in a[2] subsequently are found in a1
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;
    else if (n2 == 0)
        return 0;
    
    
    int returnvalue = -1;
    string positions = "";
    for (int x = 0; x < n1 ; x++) //finds the indexes of the values in a1 that match a2[0], the first value in the a2 and stores them in a string
    {
//        cerr<<"HELLO"<<endl;
        if (a1[x] == a2[0])
        {
//            cerr << "HELLO2"<<endl;
            positions += to_string(x);
        }
    }
    
//    cerr << positions << endl;
    
    for (int x = 0; x < positions.size(); x++) //check for every value in positions
    {
        int pos = charToInt(positions[x]); //convert the char position into an int
        int storePos = pos;
        for (int y = 0; (y < n2 && y < (n1)); y++) //loop through and check if all the values are consecutively in a subsequence
        {
            if (pos == n1)
                return -1;
            if (a1[pos] != a2[y])
            {
                returnvalue = -1;
                break;
            }
            returnvalue = storePos;
            
//            if (pos == n2)
//            {
//                return returnvalue;
//            }
            pos++;
            
        }
        if (returnvalue != -1)
            return returnvalue;
    }
    
    return returnvalue;
    
}

//find the first value in a1 that matches with a string in a2 and return its position
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    int posFirst = -1;;
    
    int storeY = 0;
    for (int x = 0; x < n1; x++)
    {
        for (int y = 0; y < n2; y++)
        {
            if (a1[x] == a2[y])
            {
                posFirst = x;
                storeY = y;
                break;
            }
        }
        
        if (a1[x] == a2[storeY])
            break;
    }
    return posFirst;
}

bool isSorted(string a[], int n) //returns true if the array is sorted
{
    for (int x=0; x < n-1; x++)
    {
        if (a[x] > a[x+1])
            return false;
    }
    
    return true;
}

int divide(string a[], int n, string divider)
{
    if (n < 0)
        return -1;
    
    while (!(isSorted(a, n))) //this loop sorts the array
    {
        for (int x = 0; x < n-1; x++)
        {
            if (a[x] > a[x+1]) {
                string temp = a[x];
                a[x] = a[x+1];
                a[x+1] = temp;
            }
        }
    }
    for (int x = 0; x < n; x++) //find where exactly divider would fit in in a sorted array
    {
        if (a[x] >= divider)
            return x;
        if (x==n-1 && a[x] < divider)
            return n;
    }
    
    return 0;
    
}

int main()
{
    string a[] = { "dianne", "fiona", "ed", "xavier", "greg" };
    assert(appendToAll(a, 2, "!!!") == 2 && a[0] == "dianne!!!" && a[1] == "fiona!!!");
    assert(appendToAll(a, 4, "!!!") == 4);
    assert(appendToAll(a, -1, "!!!") == -1);


    assert(lookup(a, 5, "greg") == 4);
    assert(lookup(a, 5, "Greg") == -1);
    assert(lookup(a, -1, "Greg") == -1);
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);


    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(a, 4) == 3);
    string b[] = { "dianne", "fiona", "ed", "xavier", "yellow" };
    assert(positionOfMax(b, 5) == 4);
    assert(positionOfMax(b, 4) == 3);



    assert(rotateLeft(b, 5, -1)==-1);
    assert(rotateLeft(b, 5, 5)==-1);
    assert(rotateLeft(b, 5, 6)==-1);
    assert(rotateLeft(b, 5, 0) == 0 && b[4] == "dianne" && b[0] == "fiona" && b[1] == "ed"
           && b[2] == "xavier" && b[3] == "yellow");



    string d[9] = {
        "xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"
    };
    assert(countRuns(d, 9) == 5);
    string e[9] = {
        "xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "james"
    };
    assert(countRuns(e, 9) == 6);
    string f[9] = {
        "betty", "betty", "john", "john", "ed", "ed", "ed", "john", "john"
    };
    assert(countRuns(f, 9) == 4);
    string g[9] = {
        "a", "b", "c", "d", "ed", "f", "g", "h", "i"
    };
    assert(countRuns(g, 9) == 9);
    assert(countRuns(g, 0) == 0);



    string folks[5] = { "betty", "john", "hello", "james", "wanda"};
    assert(flip(folks, 5) == 5 && folks[0] == "wanda" && folks[1] == "james" && folks[2] == "hello"
           && folks[3] == "john" && folks[4] == "betty");



    string folks2[6] = { "betty", "john", "dianne", "", "xavier", "bill" };
    string group[6] = { "betty", "john", "dianne", "", "xavier", "chill" };
    assert(differ(folks2, 6, group, 5)==5);
    assert(differ(folks2, 6, group, 6)==5);
    assert(differ(folks2, 2, group, 1)==1);



    string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string names1[10] = { "gavin", "kevin", "greg" };
    assert(subsequence(names, 6, names1, 3)==1);  // returns 1
    string names2[10] = { "eleni", "greg" };
    assert(subsequence(names, 5, names2, 2)==-1);
    string names3[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    assert(subsequence(names, 6, names3, 6)==0);
    string e2[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(h, 7, e2, 4) == 2);
    string nba[] = {"clippers", "celtics", "lakers", "twolves", "warriors", "celtics", "lakers", "rockets", "heat"};
    string nba2[]= {"celtics", "lakers", "rockets"};
    assert(subsequence(nba, 9, nba2, 3) == 5);
    string arr[6] = {"a", "b", "c", "d", "e", "f"};
    string arr3[4] = {"d", "e", "f", "g"};
    assert(subsequence(arr, 6, arr3, 4) == -1);


    string namez[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string set1[10] = { "dianne", "betty", "greg", "gavin" };
    assert(lookupAny(namez, 6, set1, 4)==1);
    string set2[10] = { "xavier", "ed", "fiona" };
    assert(lookupAny(namez, 6, set2, 2)==-1);

    string candidate2[8] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty", "james", "dianne" };
    string candidate[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
//    printArray(candidate, 6);
    divide(candidate, 6, "eleni");
//    printArray(candidate, 6);
    assert(divide(candidate, 6, "eleni")==3);  //  returns 3
    assert(divide(h, 7, "fiona") == 3);
    assert(divide(h, 7, "a") == 1);
    string ddd[7] = {"alex", "bryan", "fiona", "curt", "gavin", "george", "xavier"};
    assert(divide(ddd, 7, "fiona") == 3);
    assert(divide(h, 7, "fiona") == 3);

    string zero[0] = {};
    string t[3] = {"e", "f", "g"};
//    cout << differ(zero, 0, t, 3)<< endl;
    assert(differ(zero, 0, t, 3) == 0);

    string finaltest[3] = {"rahul", "swapna", "kiran"};
    assert(lookup(a, -1, "Greg") == -1);
    assert(lookup(zero, 0, "james") == -1);
    assert(countRuns(zero, 0) == 0);
    assert(countRuns(zero, -1) == -1);
    assert(subsequence(finaltest, 3, zero, 0) == 0);
    assert(subsequence(finaltest, 3, zero, -1) == -1);
    assert(subsequence(finaltest, -1, zero, 0) == -1);
    assert(subsequence(finaltest, 0, zero, 1) == -1);
    assert(subsequence(zero, 0, finaltest, 0) == 0);
    assert(divide(finaltest, -1, "") == -1);
    assert(divide(finaltest, 0, "") == 0);


    string teams[4] = {"niners","raiders","patriots","chiefs"};

    //    rotate to left
    assert(rotateLeft(teams, 4, 3) == 3 && teams[0] == "niners" && teams[1] == "raiders" && teams[2] == "patriots" && teams[3] == "chiefs");
    assert(rotateLeft(teams, 4, 0) == 0 && teams[0] == "raiders" && teams[1] == "patriots" && teams[2] == "chiefs" && teams[3] == "niners");
    assert(rotateLeft(teams, 4, -1) == -1);
    assert(rotateLeft(teams, -1, -3) == -1);
    assert(rotateLeft(teams, 4, 6) == -1);
    assert(rotateLeft(zero, 0, 1) == -1);
    //    differ
    string nwa[4] = {"lakers","celtics","warriora","rockets"};
    string nTeams[2] = {"lakers", "jazz"};
    string nbaTeams[7] = {"lakers","celtics","warriora","rockets", "jazz", "pelicans", "knicks"};
    assert(differ(nwa, 4, nTeams, 2) == 1);
    assert(differ(nwa, 4, zero, 0) == 0);
    assert(differ(nwa, -1, nwa, 4) == -1);
    assert(differ(nwa, 4, nTeams, -2) == -1);
    assert(differ(nwa, 4, nbaTeams, 7) == 4);
    assert(differ(nbaTeams, 7, nwa, 4) == 4);
    assert(differ(zero, 0, teams, 4) == 0);
    //append to all edge cases
    string nflTeams[4] = {"niners","raiders","patriots","chiefs"};
    assert(appendToAll(nflTeams, 4, "!!") == 4 && nflTeams[0] == "niners!!" && nflTeams[1] == "raiders!!" && nflTeams[2] == "patriots!!" && nflTeams[3] == "chiefs!!");
    assert(appendToAll(zero, 0, "!!") == 0);
    assert(appendToAll(nflTeams, -1, "!!") == -1);

    assert(positionOfMax(zero, 0) == -1);
    string bob[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(positionOfMax(bob, 5) == 3);
    string dod[2] = { "GAVIN", "gavin"};
    assert(positionOfMax(dod, 2) == 1);
    string tot[2] = { "gavin", "gavin"};
    assert(positionOfMax(tot, 2) == 0);
    string hhh[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    string test[3] = { "fiona", "ed", "john" };
    assert(flip(test, 3) == 3 && test[0] == "john" && test[2] == "fiona");
    string bok[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    assert(flip(bok, 4) == 4 && bok[0] == "xavier" && bok[2] == "john");
    assert(flip(zero, -3) == -1);
    assert(flip(bok, -3) == -1);
    string uwu[5] = {"tyrone", "jamie", "sansa", "arya", "jon"};
    assert(flip(uwu, 5) == 5 && uwu[0] == "jon" && uwu[1] == "arya" && uwu[2] == "sansa" && uwu[3] == "jamie" && uwu[4] == "tyrone");
    string yeet[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string yote[10] = { "dianne", "betty", "greg", "gavin" };
    assert(lookupAny(yeet, 6, yote, 4) == 1);  // returns 1 (a1 has "gavin" there)
    string yeeted[10] = { "xavier", "ed" };
    assert(lookupAny(yeet, 6, yeeted, 2) == -1);  // returns -1 (a1 has none)
    assert(lookupAny(hhh, 7, test, 3) == 2);
    assert(lookupAny(yeet, 0, yote, 0) == 0);
    assert(lookupAny(yeet, -4, yeeted, 2) == -1);
    assert(lookupAny(yeet, 8, yeeted, -2) == -1);

    string yeett[3] = {"hi", "bye", "hi"};
    string yeetedt[3] = {"hi", "bye", "hi"};
    assert(differ(yeett, 3, yeetedt, 3) == 3);

    
    
    
    
    string array[5]={"Allison","Juan", "Matt","Jeff","The Study"};
    //thoroughly test appendToAll
    assert(appendToAll(array,-3,"hi")==-1); //neg n value
    assert(appendToAll(array,0,"hi")==0);   //n value=0
    assert(appendToAll(array,5,"hi")==5);   //it works

    string a1[6] = {"Allison","Juan", "Matt","Jeff","The Study","Juan"};
    //test lookup
    assert(lookup(a1,-3,"The Study")==-1);  //neg n value
    assert(lookup(a1,0,"The Study")==-1);   //n is 0
    assert(lookup(a1,3,"The Study")==-1);   //value we want is outside range
    assert(lookup(a1,3,"alliSON")==-1);     //not same upper/lowercase ness
    assert(lookup(a1,5,"Jeff")==3);         //returns position of word "Jeff"
    assert(lookup(a1,6,"Juan")==1);         //returns first instance of "Juan"

    string a2[7]={"Homies", "Wholesome", "Leo","Karan","Amy","Hendy","Wholesome"};
    //test positionOfMax
    assert(positionOfMax(a2,-5)==-1);       //neg n value
    assert(positionOfMax(a2,0)==-1);        //n=0
    assert(positionOfMax(a2,7)==1);         //two of the same are greatest
    assert(positionOfMax(a2,1)==0);         //test with just one element
    assert(positionOfMax(a2,6)==1);         //works as intended

    //test rotateLeft
    string a3[7]={"table","phone","icecream","mintchip", "sneakers","ipad","foot"};
    assert(rotateLeft(a3 ,-4, 3)==-1);      //negative n value
    assert(rotateLeft(a3 ,0, 3)==-1);       // n is 0
    assert(rotateLeft(a3 ,0, 0)==-1);       //both n and pos are 0
    assert(rotateLeft(a3 ,4, 6)==-1);       //n < pos
    assert(rotateLeft(a3 ,4, 4)==-1);       //n and pos have equal values
    assert(rotateLeft(a3 ,3, -3)==-1);      //pos is negative
    assert(rotateLeft(a3 ,7, 6)==6);        //pos is last element
    string a4[7]={"table","phone","icecream","mintchip", "sneakers","ipad","foot"};
    assert(rotateLeft(a4 ,7, 3)==3);        //works as intended
    /*
     for (int i=0; i<7; i++)                 //print both arrays
     cout <<a3[i] <<" ";
     for (int i=0; i<7; i++)
     cout <<a4[i] <<" ";
     */

    //test countRuns
    string a5[8]={"table","phone","icecream","mintchip", "sneakers","ipad","foot","foot"};
    assert(countRuns(a5,-5)==-1);           //n value shouldn't be neg
    assert(countRuns(a5,0)==0);             // n=0 assumes no run of elements
    assert(countRuns(a5,6)==6);             //each item is unique, six runs
    assert(countRuns(a5,8)==7);             //even though same letters, foot!
    //=FooT
    string a6[7]={"table","icecream","icecream","mintchip", "sneakers","sneakers","sneakers"};
    assert(countRuns(a6,5)==4);             //should work as intended
    assert(countRuns(a6,7)==4);             //should work as intended

    //test flip
    string a7[7]={"table","phone","icecream","mintchip", "sneakers","ipad","foot"};
    assert(flip(a7,-4)==-1);                //n shouldn't be neg
    assert(flip(a7,0)==0);                  //n=0 -> array unchanged, returns0
    assert(flip(a7,6)==6);                  //even number of elements
    /*
     for (int i=0; i<7; i++)
     cout <<a7[i] <<" ";
     */
    string a8[7]={"table","phone","icecream","mintchip", "sneakers","ipad","foot"};
    assert(flip(a8,7)==7);                  //odd number of elements
    /*
     for (int i=0; i<7; i++)
     cout <<a8[i] <<" ";
     */

    //test differ function
    string a9[7]={"table","phone","icecream","mintchip", "sneakers","ipad","foot"};
    string a10[7]={"table","phone","icecream","mintchocolatechip", "sneakers","ipad","foot"};
    string a11[5]={"bottle","apple","speaker","lotion", "shoes"};
    assert(differ(a9,-4,a10,4)==-1);            //n1<0
    assert(differ(a9,4,a10,-4)==-1);            //n2<0
    assert(differ(a9,0,a10,4)==0);              //n1=0
    assert(differ(a9,4,a10,0)==0);              //n2=0
    assert(differ(a9,3,a10,3)==3);              //strings are the same
    assert(differ(a9,3,a10,5)==3);              //strings are the same until a1 ends
    assert(differ(a9,5,a10,2)==2);              //strings are the same until a2 ends
    assert(differ(a9,7,a11,5)==0);              //completely different
    assert(differ(a9,7,a10,7)==3);              //differ at some point in middle

    //test subsequence function
    string a12[10]={"table","phone","icecream","mintchip", "sneakers","ipad","foot","phone","icecream","mintchip"};
    string a13[3]={"phone","icecream","mintchip"};
    assert(subsequence(a12,-5,a13,3)==-1);      //n1<0
    assert(subsequence(a12,5,a13,-3)==-1);      //n2<0
    assert(subsequence(a12,1,a13,3)==-1);       //n1<n2
    assert(subsequence(a12,0,a13,3)==-1);       //n1=0
    assert(subsequence(a12,4,a13,0)==0);        //n2=0
    assert(subsequence(a12,0,a13,0)==0);        //n1 and n2=0
    assert(subsequence(a12,3,a13,3)==-1);       //subsequence not found
    assert(subsequence(a12,5,a13,3)==1);        //subsequence occurs 1x
//    cout << subsequence(a12,10,a13,3);
    assert(subsequence(a12,10,a13,3)==1);       //subsequence occurs 2x

    //test lookupAny
    string a14[7]={"drink","food", "waterbottle","chair","lounge","jellybeans","round"};
    string a15[3]={"lounge","chair","food"};
    assert(lookupAny(a14,-9,a15,2)==-1);        //n1<0
    assert(lookupAny(a14,2,a15,-9)==-1);        //n2<0
    assert(lookupAny(a14,0,a15,2)==-1);         //n1=0
    assert(lookupAny(a14,4,a15,0)==-1);         //n2=0
    assert(lookupAny(a14,3,a15,2)==-1);         //none of a2 found in a1
    assert(lookupAny(a14,4,a15,1)==-1);         //none of a2 found in a1
    assert(lookupAny(a14,7,a15,3)==1);          //multiple of a2 elements in a1
    assert(lookupAny(a14,7,a15,2)==3);          //multiple of a2 elements in a1
    assert(lookupAny(a14,4,a15,2)==3);          //1 instance of a2 element in a1

    //test divide
    string a16[7]={"keyboard","phone","plastic","savetheearth","top","paper","bruins"};
    assert(divide(a16,-7,"quilt")==-1);         //n<0
    assert(divide(a16,0,"quilt")==0);           //n=0
    assert(divide(a16,7,"quilt")==5);          //some lower, some higher than divider
    /*
     for (int i=0; i<7; i++)
     cout <<a16[i] << " ";
     */
    string a17[7]={"keyboard","phone","plastic","savetheearth","top","paper","bruins"};
    assert(divide(a17,7,"bruins")==0);           //all words >=divider
    string a18[7]={"keyboard","phone","plastic","savetheearth","top","paper","bruins"};
    assert(divide(a18,5,"trying")==5);           //all words <divider
    /*
     for (int i=0; i<7; i++)
     cout <<a18[i] << " ";
     */
    string a19[7]={"keyboard","Phone","plastic","savetheearth","Top","Paper","bruins"};
    assert(divide(a19,7,"monopoly")==5);        //somewords start with uppercase
    /*
     for (int i=0; i<7; i++)
     cout <<a19[i] << " ";
     */

    string aaa[6] = {"apple", "banana", "watermelon", "orange", "grape", ""};
    assert(appendToAll(aaa, 6, "g") == 6 && aaa[0] == "appleg" && aaa[5] == "g");
    assert(appendToAll(aaa, 0, "g") == 0 && aaa[0] == "appleg" && aaa[5] == "g");

    string bbb[6] = {"apple", "watermelon", "watermelon", "orAnGe", "grape", "orange"};
    assert(lookup(bbb, 6, "grape") == 4);
    assert(lookup(bbb, 6, "watermelon") == 1);
    assert(lookup(bbb, 6, "orange") == 5);
    assert(lookup(bbb, 6, "peach") == -1);

    string c[7] = {"apple", "banana", "watermelon", "orange", "grape", "peach", "watermelon"};
    assert(positionOfMax(c, 6) == 2);
    assert(positionOfMax(c, 7) == 2);
    assert(positionOfMax(c, 0) == -1);

    string m[6] = {"apple", "banana", "watermelon", "orange", "grape", ""};
    assert(rotateLeft(m, 6, 5) == 5 && m[1] == "banana" && m[3] == "orange" && m[5] == "");
    assert(rotateLeft(m, 6, 1) == 1 && m[1] == "watermelon" && m[3] == "grape" && m[5] == "banana");

    string n[7] = {"apple", "banana", "banana", "watermelon","WaTerMelon", "orange", "grape"};
    assert(countRuns(n, 4) == 3);
    assert(countRuns(n, 7) == 6);

    string p[6] = {"apple", "banana", "watermelon", "orange", "grape", "peach"};
    assert(flip(p, 6) == 6 && p[0] == "peach" && p[2] == "orange" && p[4] == "banana");
    flip(p,6);
    assert(flip(p, 5) == 5 && p[0] == "grape" && p[2] == "watermelon" && p[3] == "banana");
    flip(p, 5);
    string q[6] = {"apple", "banana", "orange", "watermelon", "grape", "peach"};
    assert(differ(p, 6, q, 6) == 2);
    assert(differ(p, 1, q, 2) == 1);

    string r[9] = {"banana", "orange", "watermelon", "apple", "banana", "watermelon", "orange", "grape", "peach"};
    assert(subsequence(q, 6, r, 3) == 1);
    assert(subsequence(q, 6, r, 7) == -1);

    string s[4] = {"apple", "banana", "watermelon", "orange"};
    assert(lookupAny(r, 6, s, 4) == 0);
    assert(lookupAny(r, 6, s, 1) == 3);

    assert(divide(q, 6, "man") == 3);
    assert(divide(q, 6, "zombie") == 6);


    string aa[] = { "dianne", "fiona", "ed", "xavier", "greg" };
    //    int z = appendToAll(a, -1, "YO");
    //    printArray(a, 5);
    //    cerr << z << endl;
    assert(appendToAll(aa, 4, "!!!") == 4);
    assert(appendToAll(aa, -1, "!!!") == -1);
    assert(appendToAll(aa, 0, "!!!")== 0);


    assert(lookup(aa, 5, "greg") == 4);
    assert(lookup(aa, 5, "Greg") == -1);
    assert(lookup(aa, -1, "Greg") == -1);


    assert(positionOfMax(aa, 4) == 3);
    string bb[] = { "dianne", "fiona", "ed", "xavier", "yellow" };
    assert(positionOfMax(bb, 5) == 4);
    assert(positionOfMax(bb, 4) == 3);

    assert(rotateLeft(bb, 5, -1)==-1);
    assert(rotateLeft(bb, 5, 5)==-1);
    assert(rotateLeft(bb, 5, 6)==-1);



    //    string folks[7] = { "betty", "john", "hello", "xavier", "kevin", "dianne", "james" };
    //    printArray(folks, 7);
    //    flip(folks, 7);
    //    printArray(folks, 7);
    //    string folkss[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    //    printArray(folkss, 6);
    //    flip(folkss, 4);
    //    printArray(folkss, 6);

    string aaaa[] = {
              "alpha", "beta", "gamma", "gamma", "beta", "delta"
        };
    string bbbb[] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };

    cout << bbbb + 2;
    cout << lookupAny(aaaa, 2, bbbb+2, 2);
    
    cerr << "ALL TESTS PASSED" << endl;

    
    
}

