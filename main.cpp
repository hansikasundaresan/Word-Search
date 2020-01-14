#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include<cmath>
using namespace std;

enum direction {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, LEFT_DOWN, RIGHT_DOWN, LEFT_UP, RIGHT_UP};
string arrayDirection[8] = { "right", "left", "down", "up", "left/down", "right/down", "left/up", "right/up" };
//arrayDirection parrallels to enum direction which allows code to print the direction rather than enum number

const int MAX = 50;

ifstream myFile; //Input file stream for the puzzle I searching through
ifstream otherFile; //Input file stream for words I need to find
string puzzleFileName;//the name of the puzzle file that will be accessed with myFile
string wordFileName;//the name of the word file that will be accessed with otherFile

struct wordGame
{
    char puzzle[MAX][MAX]; //puzzle array
    int numberRows;
    int numberColumns;
    int version=2;//version 2 for extra credit
};

//wordFind struct used for storing results
struct wordFind
{
    string word;
    bool found = false;
    int row;
    int column;
    direction where;
    int foundCount = 0;
};

//reads the puzzle file inorder to fill in the char array through which we are searching for words
bool readPuzzle(wordGame& game, string inputFileName)
{
    char letterAdded = ' ';
    myFile.open(inputFileName);
    if (!myFile)
    {
        return false;
    }
    
    myFile >> game.numberRows;
    myFile >> game.numberColumns;
    if(!(game.numberRows>0) && !(game.numberRows<51))
    {
        return false;
    }
    
    //fills in the array
    for (int x = 0; x < game.numberRows; ++x)
    {
        for (int y = 0; y < game.numberColumns; ++y)
        {
            if(!(myFile >> letterAdded))
            {
                return false;
            }
            game.puzzle[x][y] = toupper(letterAdded);
            
        }
        
    }
    return true;
}

//displays puzzle with no return type
void displayPuzzle(wordGame& game)
{
    for (int x = 0; x < game.numberRows; x++)
    {
        for (int y = 0; y < game.numberColumns; y++)
        {
            cout << game.puzzle[x][y];
        }
        cout << endl;
    }
}

//reads word file and returns bool whether it opens or not
bool readWord(string inputFileName)
{
    otherFile.open(inputFileName);
    if (!otherFile.is_open())
    {
        return false;
    }
    otherFile.close();
    return true;
}

//searches for words from left to right
//temp is the string in which the comparison word is stored
//returns bool which returns back to read word which returns to main as parameters in functions were passed with &
bool leftToRight(wordGame& game, wordFind& theFind)
{
    for (int i = 0; i < game.numberRows; i++)
    {
        for (int j = 0; j < game.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 < game.numberColumns)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i][j + int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_RIGHT;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words from right to left
bool rightToLeft(wordGame& game, wordFind& theFind)
{
    
    for (int i = game.numberRows - 1; i > -1; i--)
    {
        for (int j = game.numberColumns - 1; j > -1; j--)
        {
            if (j - int(theFind.word.length()) + 1 > -1)
            {
                
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i][j - int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_LEFT;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words from up to down
bool upToDown(wordGame& game, wordFind& theFind)
{
    
    for (int i = 0; i < game.numberRows; i++)
    {
        for (int j = 0; j < game.numberColumns; j++)
        {
            if (i + int(theFind.word.length()) - 1 < game.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i + int(k)][j];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = DOWN;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words from down to up
bool downToUp(wordGame& game, wordFind& theFind)
{
    for (int j = game.numberRows-1; j > -1; j--)
    {
        for (int i = game.numberColumns-1; i > -1; i--)
        {
            if (j - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[j - int(k)][i];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = j + 1;
                    theFind.column = i + 1;
                    theFind.foundCount++;
                    theFind.where = UP;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally right and down
bool rightAndDown(wordGame& game, wordFind& theFind)
{
    for (int i = 0; i < game.numberRows; i++)
    {
        for (int j = 0; j < game.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 <game.numberColumns && i + int(theFind.word.length()) - 1 < game.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i + int(k)][j + int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_DOWN;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally left and down
bool leftAndDown(wordGame& game, wordFind& theFind)
{
    for (int i = 0; i < game.numberRows; i++)
    {
        for (int j = game.numberColumns; j > -1; j--)
        {
            if (j - int(theFind.word.length()) +1 > -1 && i + int(theFind.word.length()) - 1 < game.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i + int(k)][j - int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_DOWN;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally left to up
bool leftToUp(wordGame& game, wordFind& theFind)
{
    for (int i = game.numberRows; i > -1; i--)
    {
        for (int j = 0; j < game.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 <game.numberColumns && i - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i - int(k)][j + int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_UP;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally from right to up
bool rightToUp(wordGame& game, wordFind& theFind)
{
    
    for (int i = game.numberRows; i > -1; i--)
    {
        for (int j = game.numberColumns; j > -1; j--)
        {
            if (j - int(theFind.word.length()) + 1 >-1 && i - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += game.puzzle[i - int(k)][j - int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_UP;
                }
            }
        }
    }
    return theFind.found;
}

//calls the othe methods to find one word
//then loops for the methods to be called again for the next word
//does nout cout anything
void findWord(wordGame& game, wordFind& theFind)
{
    leftToRight(game, theFind);
    rightToLeft(game, theFind);
    upToDown(game, theFind);
    downToUp(game, theFind);
    leftAndDown(game, theFind);
    rightAndDown(game, theFind);
    leftToUp(game, theFind);
    rightToUp(game, theFind);
}

//calls all the other methods
//couts for reading the puzzles
int main()
{
    wordGame game1;
    wordFind word1;
    cout<< "Enter puzzle file name: ";
    cin >> puzzleFileName;
    if (!readPuzzle(game1, puzzleFileName))
    {
        cout << "The puzzle file " << "\"" << puzzleFileName << "\"" << " could not be opened or is invalid" << endl;
        return 0;
    }
    else
    {
        cout << "The puzzle from file " << "\"" << puzzleFileName << "\"" << endl;
        displayPuzzle(game1);
        cout<<"Enter file name containing words to search for: ";
        cin >> wordFileName;
        if (!readWord(wordFileName))
        {
            cout << "The puzzle file " << "\"" << wordFileName << "\"" << " could not be opened or is invalid" << endl;
        }
        
        else
        {
            otherFile.open(wordFileName);
            
            while(otherFile>>word1.word)
            {
                for(unsigned int i=0; i<word1.word.length(); i++)
                {
                    word1.word.at(i)=toupper(word1.word.at(i));
                }
                findWord(game1, word1);
                if(word1.found)
                {
                    
                    if (word1.foundCount > 1)
                    {
                        cout << "The word " << word1.word << " was found " << word1.foundCount << " times" << endl;
                    }
                    
                    else if (word1.foundCount == 1)
                    {
                        cout << "The word " << word1.word << " was found at (" << word1.row << ", " << word1.column << ") - " << arrayDirection[word1.where] << endl;
                    }
                }
                
                else
                {
                    cout << "The word " << word1.word << " was not found" << endl;
                }
                word1.found=false;
                word1.foundCount=0;
            }
        }
        
        
    }
    
    myFile.close();
    otherFile.close();
    return 0;
}
