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
    else if (n1 == n2) //value here must be zero
        return 0;
        
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


    cerr << "ALL TESTS PASSED" << endl;

    
    
}

