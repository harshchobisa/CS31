//
//  main.cpp
//  Project 5
//
//  Created by Harsh Chobisa on 11/7/18.
//  Copyright © 2018 Harsh Chobisa. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;


//for testing, this function prints a cstring array
void printCStringArray(const char word1[][MAX_WORD_LENGTH+1], int n)
{
    for (int x = 0; x < n ; x++)
    {
        cerr << word1[x];
        cerr << " ";
    }
    cerr << endl;
}

//for testing, this function prints a cstring
void printCString(const char a[])
{
    for (int x = 0; a[x] != '\0' ; x++)
    {
        cerr << a[x];
    }
    cerr << endl;
}

//for testing, this function print an array of ints
void printArray(const int a[], int n)
{
    for (int x = 0; x < n ; x++)
    {
        cerr << a[x] << " ";
    }
    cerr << endl;
}

//this function makes a cstring lowercase
void makeLowerCase(char s[])
{
    for (int x = 0; s[x] != '\0'; x++)
    {
        s[x] = tolower(s[x]);
    }
    
}

//returns true if a cstring is comprised of only letter characters
bool isWord(char s[])
{
    if (strcmp(s, "") == 0)
        return false;
    for (int x = 0; s[x] != '\0'; x++)
    {
        if (!(isalpha(s[x])))
            return false;
    }
    return true;
}

//deletes an element of the array, shifts all array values to the left, and shortens the length of the warray
void removeElement(char s[], int position)
{
    for (int x = position; s[x] != '\0'; x++)
    {
        s[x] = s[x+1];
    }
}


// removes an entire pattern entry
int deleteElement(char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int separation[], int r, int position)
{


    
    if (r - 1 == position)
    {
        r--;
    }
    else{
        for (int x = position; x < r-1; x++)
        {
            separation[x] = separation[x+1];
            strcpy(word1[x],word1[x+1]);
            strcpy(word2[x],word2[x+1]);
        }
        
        r--;
    }
    return r;
}

//makes patters proper as specified by the spec
int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns)
{
    if (nPatterns < 0)
        return 0;
    int r = nPatterns;
    for (int x = 0; x < nPatterns; x++)
    {
        makeLowerCase(word1[x]);
        makeLowerCase(word2[x]);
    }
    
    //removes words that are not words and have negative separation
    for (int x = 0; x < r; x++)
    {
        if(separation[x] < 0 || (!(isWord(word1[x]))) || (!(isWord(word2[x]))))
        {
            r = deleteElement(word1, word2, separation, r, x);
            // cerr << "position is " << x << endl;
            // cerr << "r is " << r << endl;
            //printCStringArray(word1, r);
            //printCStringArray(word2, r);
            //printArray(separation, r);
            //cerr << endl;
            
            if (!(x==r)) //IF THE ELEMENT IN THE LAST POSITION HAS BEEN DELETED, DONT DECREMENT X
                x--;
            if (x > r)
                break;
        }
    }
    //cerr<< "R AT CHECKPOINT: " << r << endl;
    if (r == -1)
        r = 0;
    //   cerr << "r at checkpoint " << r;
    //deletes repeated patterns
    int numberDeleted = 0;
    for (int x = 0; x < r; x++)
    {
        
        for (int y = 0; y < r; y++)
        {
            if (strcmp(word1[x], word2[y]) == 0 && strcmp(word1[y], word2[x]) == 0 && (!(strcmp(word1[x], word2[x]) == 0)))
            {
                if (separation[x] < separation[y])
                {
                    r = deleteElement(word1, word2, separation, r, x);
                }
                else
                {
                    r = deleteElement(word1, word2, separation, r, y);
                }
                y--;
                numberDeleted++;
                
            }
        }
        x = x - numberDeleted;
        if (x < 0)
            x= 0;
        numberDeleted = 0;
        
        for (int y = x+1; y < r; y++)
        {
            if (strcmp(word1[x], word1[y]) == 0 && strcmp(word2[y], word2[x]) == 0 && (!(strcmp(word1[x], word2[x]) == 0)))
            {
                if (separation[x] < separation[y])
                {
                    r = deleteElement(word1, word2, separation, r, x);
                }
                else
                {
                    r = deleteElement(word1, word2, separation, r, y);
                }
                y--;
                numberDeleted++;
                
            }
        }
        x = x - numberDeleted;
        if (x < 0)
            x= 0;
        numberDeleted = 0;
    }
    return r;
}



//returns the score of a document
int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns)
{

    char documentCopy[251] = "";
    strcpy(documentCopy, document);
//    printCString(documentCopy);
    makeLowerCase(documentCopy);
//    printCString(documentCopy);
    for (int x = 0; documentCopy[x] != '\0'; x++) //remove anything thats not a space or a letter
    {
        if (!(isalpha(documentCopy[x])) && documentCopy[x] != ' ')
        {
            removeElement(documentCopy, x);
            x--;
        }
    }
    //printCString(documentCopy);
    
    int startingPositions[251]; //new array of the startng positions of every word in document
    int numberOfWords = 0;
    
    for (int x = 0; documentCopy[x] != '\0'; x++) //assigns the positions of the words to startingPositions
    {
        while (documentCopy[x] == ' ')
            x++;
        //cerr << "x = " << x;
        startingPositions[numberOfWords] = x;
        numberOfWords++;
        while (isalpha(documentCopy[x]))
            x++;
        
    }
    //printArray(startingPositions, numberOfWords);
    //cerr << "numberOfWords: " << numberOfWords << endl;
    char wordsInDocument[251][MAX_WORD_LENGTH + 1];
    
    //sets wordsInDocument to all the words in the Document
    for (int startingPosArrayPositions = 0; startingPosArrayPositions < numberOfWords; startingPosArrayPositions++) //x is the position in the array of the position of the words
    {
        char currentWord[21] = "";
        //x increments the startingpositions array
        //a increments the documentCopy characters or the wordsInDocument array
        //z increments the firstWord characters
        int a = startingPositions[startingPosArrayPositions];
        int z = 0;
        for (a; documentCopy[a] != ' ' && strlen(currentWord) < 21 && a < strlen(documentCopy); a++)
        {
            //cerr << z;
            
            currentWord[z] = documentCopy[a];
            z++;
        }
        //cerr<< "THE VALUE OF A IS " << a;
        //currentWord[a+1] = '\0';
        //cerr << " " << currentWord ;
        strcpy(wordsInDocument[startingPosArrayPositions], currentWord);
        //cerr << " " <<wordsInDocument[startingPosArrayPositions] << endl;
        
        //cerr << endl;
        
    }
//        printCString(documentCopy);
//        printCStringArray(wordsInDocument, numberOfWords);
//        printCStringArray(word1, nPatterns);
//        printCStringArray(word2, nPatterns);
//
    
    int score = 0;
    
       // printArray(separation, nPatterns);
    
    
    for (int x = 0; x < nPatterns; x++)
    {
        int wordOnePos = -1; //wordOnePos in wordsInDocument
        int wordTwoPos = -1;
        
        //find the positions of wordOne
        for (int y = 0; y < numberOfWords ; y++)
        {
            if (strcmp(word1[x], wordsInDocument[y]) == 0)
            {
                wordOnePos = y;
            }
        }
        
        //cerr << "wordOnePos = " << wordOnePos << endl;
        
        //finds the position of wordTwo
        for (int y = 0; y < numberOfWords ; y++)
        {
            if (strcmp(word2[x], wordsInDocument[y]) == 0)
            {
                wordTwoPos = y;
            }
        }
        
        //cerr << "wordTwoPos = " << wordTwoPos << endl;
        //calculates the score by subtracting the positions of the words
        if (wordOnePos != -1 && wordTwoPos != -1)   //CHANGED -2 to -1
        {
            //if ((wordTwoPos - wordOnePos)-1 <= separation[x] || ((wordOnePos - wordTwoPos)-1)<= separation[x])
            if (abs(wordTwoPos - wordOnePos)-1 <= separation[x])
            {
                //cerr << abs(wordTwoPos - wordOnePos - 1);
                score ++;
            }
        }
        
    }
    //cerr << score << endl;
    return score;
    
}




int main()
{
    
    
   // assert(makeProper(test2w1, test2w2, test2dist, 4) == 1); //checks to see if it removes improper words in w1
    
    const int RATE1_NRULES = 5;
    char rate1w1[RATE1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have" , "have"
    };
    char rate1w2[RATE1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad" ,  "have"
    };
    int rate1dist[RATE1_NRULES] = {
        1,           3,          0,           12     , 1
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                rate1w1, rate1w2, rate1dist, 0) == 0);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 0);
    assert(rate("have james have.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1);
    assert(rate("have mad have.",
                 rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 2);
//
    const int nPatterns = 9;

    char test1w1[9][MAX_WORD_LENGTH+1] =
    {
        "mad",      "deranged", "jam-es", "half-witted", "robot",  "plot",   "have", "have", "mad"
    };
    char test1w2[9][MAX_WORD_LENGTH+1] =
    {
        "scientist", "robot",    "PLOT",     "assistant", "deranged", "Nefarious", "mad",  "have", "scientist"
    };
    int test1dist[] =
    {
            1,           3,          0,           2,          1 ,         0  ,       12 ,     0,        3
    };
    printCStringArray(test1w1, nPatterns);
    printCStringArray(test1w2, nPatterns);
    printArray(test1dist, nPatterns);
    int r = makeProper(test1w1, test1w2, test1dist, nPatterns);
    printCStringArray(test1w1, r);
    printCStringArray(test1w2, r);
    printArray(test1dist, r);
    cerr << endl << endl ;

    assert(makeProper(test1w1, test1w2, test1dist, nPatterns)==5);
    char test2w1[9][MAX_WORD_LENGTH+1] =
    {
        "mad",      "deranged", "NEFARIOUS", "half-witted", "robot",    "plot",   "have", "mad"     , "NefARiOUs"
    };
    char test2w2[9][MAX_WORD_LENGTH+1] =
    {
        "scientist", "robot",    "PLOT",     "assistant", "deranged", "Nefarious", "mad", "scientist" , "pLoT"
    };
    int test2dist[] =
    {
        1,              3,          0,           2,          1 ,         -1  ,       12 ,         3   , 6
    };
    printCStringArray(test2w1, nPatterns);
    printCStringArray(test2w2, nPatterns);
    printArray(test2dist, nPatterns);
    r = makeProper(test2w1, test2w2, test2dist, nPatterns);
    printCStringArray(test2w1, r);
    printCStringArray(test2w2, r);
    printArray(test2dist, r);
    cerr << endl << endl ;

    assert(makeProper(test2w1, test2w2, test2dist, nPatterns)==4);



    char test3w1[5][MAX_WORD_LENGTH+1] =
    {
        "hello",      "heLLO", "hello", "HEllo", "heLLO"
    };
    char test3w2[5][MAX_WORD_LENGTH+1] =
    {
        "world", "WORLD",    "world",     "worLD", "WOrld"
    };
    int test3dist[5] =
    {
        1,              3,          0,           2,          4
    };
      assert(makeProper(test3w1, test3w2, test3dist, 5) == 1);

    printCStringArray(test3w1, 5);
    printCStringArray(test3w2, 5);
    printArray(test3dist, 5);
    r = makeProper(test3w1, test3w2, test3dist, 5);
    printCStringArray(test3w1, r);
    printCStringArray(test3w2, r);
    printArray(test3dist, r);
    cerr << endl << endl ;

    char test4w1[1][MAX_WORD_LENGTH+1] =
    {
        "hello"
    };
    char test4w2[1][MAX_WORD_LENGTH+1] =
    {
        "world"
    };
    int test4dist[1] =
    {
        1
    };
    assert(makeProper(test4w1, test4w2, test4dist, 1) == 1);

    printCStringArray(test4w1, 1);
    printCStringArray(test4w2, 1);
    printArray(test4dist, 1);
    r = makeProper(test4w1, test4w2, test4dist, 1);
    printCStringArray(test4w1, r);
    printCStringArray(test4w2, r);
    printArray(test4dist, r);
    cerr << endl << endl ;

    char test5w1[1][MAX_WORD_LENGTH+1] =
    {
        "hell-o"
    };
    char test5w2[1][MAX_WORD_LENGTH+1] =
    {
        "world"
    };
    int test5dist[1] =
    {
        1
    };
    assert(makeProper(test5w1, test5w2, test5dist, 1) == 0);

    printCStringArray(test5w1, 1);
    printCStringArray(test5w2, 1);
    printArray(test5dist, 1);
    r = makeProper(test5w1, test5w2, test5dist, 1);
    printCStringArray(test5w1, r);
    printCStringArray(test5w2, r);
    printArray(test5dist, r);
    cerr << endl << endl ;

    char test6w1[2][MAX_WORD_LENGTH+1] =
    {
        "hello", "he-llo"
    };
    char test6w2[2][MAX_WORD_LENGTH+1] =
    {
        "world", "hello"
    };
    int test6dist[2] =
    {
        1 , 7
    };
    assert(makeProper(test6w1, test6w2, test6dist, 2) == 1);

    printCStringArray(test6w1, 2);
    printCStringArray(test6w2, 2);
    printArray(test6dist, 2);
    r = makeProper(test6w1, test6w2, test6dist, 2);
    printCStringArray(test6w1, r);
    printCStringArray(test6w2, r);
    printArray(test6dist, r);
    cerr << endl << endl ;

    char test7w1[2][MAX_WORD_LENGTH+1] =
    {
        "hello(z", "he-llo"
    };
    char test7w2[2][MAX_WORD_LENGTH+1] =
    {
        "world", "hello"
    };
    int test7dist[2] =
    {
        1 , 7
    };
    assert(makeProper(test7w1, test7w2, test7dist, 2) == 0);

    printCStringArray(test7w1, 2);
    printCStringArray(test7w2, 2);
    printArray(test7dist, 2);
    r = makeProper(test7w1, test7w2, test7dist, 2);
    printCStringArray(test7w1, r);
    printCStringArray(test7w2, r);
    printArray(test6dist, r);
    cerr << endl << endl ;

      cerr << "All tests succeeded" << endl;
}

