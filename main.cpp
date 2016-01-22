#include "lpclib.h"
#include "hgraphics.h"
#include "vector.h"
#include "scanner.h"
#include "lexicon.h"
using namespace std;

// NOTE: This main() is set up to demonstrate a few different
// parts of the code provided for you. It is NOT meant
// as a suggestion for what your actual main program should look like.

struct pos
{
    int x;
    int y;
    pos(int xx=0, int yy=0): x(xx), y(yy) { }
};

Lexicon lexi("Lexicon.dat");
bool DoesFileOpen(string fileName, Vector <string> & diceVector);
void ProcessFile(ifstream & tube, Vector<string> & diceVector);
void RandomizeDiceList(Vector <string> & diceVector);
void SetBoard(Vector<string> & diceVector);
Vector<string> HumanPlayGame();
void ComputerPlayGame(Vector <string> wordsPlayed);
bool isFormable(int currentRow, int currentCol, string soFar, string word, Vector<pos> & HighLightPositions);
bool isInBounds(int Row, int Col);
bool hasBeenPlayed(int Row, int Col, Vector <pos> HighLightPositions);
bool wordHasBeenPlayed(Vector<string> wordVector, string word);
void highLightVector(Vector<pos>HighlightPositions);
bool canCreateWord(int currentRow, int currentCol, string &wordReturn, string soFar, Vector<string> wordVector, Vector<pos> & PositionsVisted);

void playGame(Vector<string> dice);
///void ComputerPlayGame();

bool DoesFileOpen(string fileName, Vector <string> & diceVector)
{

    ifstream mytube;
    mytube.open(fileName.c_str());

    if (mytube.fail())
    {
        cout << "FAILED - could not open " << fileName << endl;
        return false;
    }

    ProcessFile(mytube, diceVector);
    return true;
}


void ProcessFile(ifstream & tube, Vector <string> & diceVector)
{
string currentLine = "start";
  while (currentLine != "")
  {
      currentLine = GetLine(tube);
      if (currentLine == "")
      {
        break;
      }
      diceVector.add(currentLine);
  }
}

void RandomizeDiceList(Vector <string> &diceVector)
{
  int numberOfDice = diceVector.size()-1;
  int RandomDice;
  for (int i = 0; i < numberOfDice; i++)
  {
    RandomDice = RandomInt(0, numberOfDice);
    string currentSpot = diceVector.getAt(i);
    diceVector.setAt(i, diceVector.getAt(RandomDice));
    diceVector.setAt(RandomDice, currentSpot);
  }
}

void SetBoard(Vector<string> & diceVector)
{
int currentSpot =0;
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < DiceInRow(r); c++)
        {
            string randWord =  diceVector.getAt(currentSpot);
            char insertChar = randWord[RandomInt(0,randWord.size()-1)];
            LabelHex(r, c, insertChar);
            currentSpot++;
        }
    }
}

Vector<string> HumanPlayGame()
{
PrintMessage("Welcome to Hoggle\n");
string word = "start";
Vector<string> temp;
    while(word != "")
    {
        bool hasBeenFormed = true;
        PrintMessage ("Please enter a word ");
        word = BoardGetLine();
        if (word.length() <3 && word != "")
        {
            PrintMessage("The word must be at least 3 letters long!\n");
        }
        else if (wordHasBeenPlayed(temp,word))
        {
            PrintMessage("That word has already been played!\n");
        }
        else
        {
            for (int r = 0; r < 5; r++)
            {
                hasBeenFormed = false;
                for (int c = 0; c < DiceInRow(r); c++)
                {

                    if (LetterAt(r,c) == word[0])
                    {
                        Vector<pos> highLightPos;
                        highLightPos.add(pos(r,c));
                        bool wordFormed = isFormable(r,c,word.substr(0,1),word, highLightPos);
                        if (wordFormed && lexi.containsWord(word))
                        {
                                ///found the word got options 1) we've already played the word
                                ///2) it must be at least 3 length. probably check before looking
                                ///3)must be a real word
                            temp.add(word);
                            hasBeenFormed =true;
                            RecordNewWord(word, Human);
                            PrintMessage("Found a real word on the board.\n");
                            highLightVector(highLightPos);
                            break;
                        }
                        else if(wordFormed && !lexi.containsWord(word))
                        {
                            hasBeenFormed = true;
                            PrintMessage("Word on board but is not real.\n");
                            highLightVector(highLightPos);
                            break;
                        }
                    highLightPos.clear();
                    }
                    if (hasBeenFormed)
                        break;
                }
                 if (hasBeenFormed)
                        break;
            }
        if(!hasBeenFormed)
        {
            PrintMessage("Could not find the word on the board.\n");
        }
        }
    }
return temp;
}


bool isFormable(int currentRow, int currentCol,  string soFar, string word, Vector<pos> & HighLightPositions)
{
    static int TOP_CHANGE_X[6] = {-1,-1,0,1,1,0};
    static int TOP_CHANGE_Y[6] = {-1,0,1,1,0,-1};

    static int MIDDLE_CHANGE_X[6] = {-1,-1,0,1,1,0};
    static int MIDDLE_CHANGE_Y[6] = {-1,0,1,0,-1,-1}; ///check this one

    static int BOTTOM_CHANGE_X[6] ={-1,-1,0,1,1,0};
    static int BOTTOM_CHANGE_Y[6] = {0,1,1,0,-1,-1};
    int nextRow;
    int nextCol;

    if (soFar == word)
    {
        return true;
    }

    else
    {

        for (int direction =0; direction < 6; direction++)
        {
            if (currentRow == 0 || currentRow == 1)
            {
            nextRow = currentRow + TOP_CHANGE_X[direction];
            nextCol = currentCol + TOP_CHANGE_Y[direction];
            }
            else if (currentRow ==2)
            {
                nextRow = currentRow +MIDDLE_CHANGE_X[direction];
                nextCol = currentCol +MIDDLE_CHANGE_Y[direction];
            }
            else
            {
                nextRow = currentRow + BOTTOM_CHANGE_X[direction];
                nextCol = currentCol + BOTTOM_CHANGE_Y[direction];
            }

            if (isInBounds(nextRow,nextCol) && !hasBeenPlayed(nextRow,nextCol,HighLightPositions))
            {
                if (LetterAt(nextRow,nextCol) == word[soFar.size()])
                {
                    HighLightPositions.add(pos(nextRow,nextCol));
                      if (isFormable(nextRow,nextCol, soFar + LetterAt(nextRow,nextCol), word,HighLightPositions))
                      {
                          return true;
                      }
                      else
                      {
                          HighLightPositions.removeAt(HighLightPositions.size()-1);
                      }
                }
            }
        }
    }

    return false;
}


bool isInBounds(int Row, int Col)
{
    if (Row < 0 || Row >4)
    {
        return false;
    }
    else if ((Row ==0 || Row == 4) && (Col < 0 || Col >2))
    {
        return false;
    }
    else if ((Row ==1 || Row == 3) && (Col < 0 || Col >3))
    {
        return false;
    }
    else if ((Row ==2) && (Col < 0 || Col >4))
    {
        return false;
    }

    else
        return true;
}


bool hasBeenPlayed(int Row, int Col, Vector <pos> HighLightPositions)
{
   for (int i =0; i < HighLightPositions.size(); i++)
   {
      if (Row == HighLightPositions.getAt(i).x && Col ==  HighLightPositions.getAt(i).y)
      {
          return true;
      }
   }
   return false;
}




void highLightVector(Vector<pos>HighlightPositions)
{
   for (int i =0; i < HighlightPositions.size(); i++)
   {
      HighlightHex(HighlightPositions.getAt(i).x  , HighlightPositions.getAt(i).y, true);
      Pause(.1);
      HighlightHex(HighlightPositions.getAt(i).x  , HighlightPositions.getAt(i).y, false);
   }
}


void ComputerPlayGame(Vector <string> wordsPlayed)
{
    string word;
    bool wordFound;
    Vector<pos> computerHighLightPositions;
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < DiceInRow(r); c++)
        {
             //cout << "At position " << r << "***" << c << endl;
            word = string(1, LetterAt(r,c));
            computerHighLightPositions.add(pos(r,c));
            string wordReturn = "";
            wordFound = canCreateWord(r,c,wordReturn, word, wordsPlayed,computerHighLightPositions);

            while (wordFound)
            {

                wordsPlayed.add(wordReturn);
                PrintMessage("Computer found word: " + wordReturn + "\n");
                highLightVector(computerHighLightPositions);
                RecordNewWord(wordReturn,Computer);
                computerHighLightPositions.clear();
                computerHighLightPositions.add(pos(r,c));
                wordReturn = "";
                wordFound = canCreateWord(r,c, wordReturn, word, wordsPlayed,computerHighLightPositions);
            }
                computerHighLightPositions.clear();


        }
    }
}


bool canCreateWord(int currentRow, int currentCol, string &wordReturn,string soFar, Vector<string> wordVector, Vector<pos> & PositionsVisted)
{
   static int TOP_CHANGE_X[6] = {-1,-1,0,1,1,0};
    static int TOP_CHANGE_Y[6] = {-1,0,1,1,0,-1};

    static int MIDDLE_CHANGE_X[6] = {-1,-1,0,1,1,0};
    static int MIDDLE_CHANGE_Y[6] = {-1,0,1,0,-1,-1}; ///check this one

    static int BOTTOM_CHANGE_X[6] ={-1,-1,0,1,1,0};
    static int BOTTOM_CHANGE_Y[6] = {0,1,1,0,-1,-1};
    int nextRow;
    int nextCol;

    if (lexi.containsWord(soFar) && soFar.length() >3 && !wordHasBeenPlayed(wordVector,soFar))
    {
        //cout << "FOUND THE WORD " << soFar << endl;
        wordReturn=soFar;
        return true;
    }

    else if (!lexi.containsPrefix(soFar))
    {
        return false;
    }
    else
    {
        for (int direction =0; direction < 6; direction++)
        {
            if (currentRow == 0 || currentRow == 1)
            {
            nextRow = currentRow + TOP_CHANGE_X[direction];
            nextCol = currentCol + TOP_CHANGE_Y[direction];
            }
            else if (currentRow ==2)
            {
                nextRow = currentRow +MIDDLE_CHANGE_X[direction];
                nextCol = currentCol +MIDDLE_CHANGE_Y[direction];
            }
            else
            {
                nextRow = currentRow + BOTTOM_CHANGE_X[direction];
                nextCol = currentCol + BOTTOM_CHANGE_Y[direction];
            }

            if (isInBounds(nextRow,nextCol) && !hasBeenPlayed(nextRow,nextCol,PositionsVisted))
            {
                    PositionsVisted.add(pos(nextRow,nextCol));
                      if (canCreateWord(nextRow,nextCol,wordReturn,soFar+LetterAt(nextRow,nextCol),wordVector,PositionsVisted))
                      {
                          return true;
                      }
                      else
                      {
                          PositionsVisted.removeAt(PositionsVisted.size()-1);
                      }

            }
        }
    }

    return false;
}



bool wordHasBeenPlayed(Vector<string> wordVector, string word)
{
    for (int i =0; i < wordVector.size(); i++)
    {
        if (word == wordVector.getAt(i))
        {
            return true;
        }
    }
return false;
}



void playGame(Vector<string> dice)
{
    RandomizeDiceList(dice);
    // Use DrawBoard() to open the graphics window
    // instead of GraphicsWindow()
    DrawBoard();

    // Here is a double for loop that iterates through all dice
    // on the board
    SetBoard(dice);
    UpdateDisplay();

    // Scoring is done with the RecordNewWord function

    // Printing onscreen with PrintMessage

    // Getting input onscreen
    Vector<string> humanWords = HumanPlayGame();
    ComputerPlayGame(humanWords);


    string response = "asdf";
    while(response !="n")
    {
        PrintMessage("Play again Y/N ");
        response = BoardGetLine();
        if (response == "Y" || response == "y")
        {
            playGame(dice);
        }
        else if (response == "N" || response == "n")
        {
            break;
        }

    }


}
















































int main()
{

    Vector<string> diceList;
    if(!DoesFileOpen("dice.txt", diceList))
    {
        cout << "\nSorry that file does not exist.";
    }
    playGame(diceList);

    // Highlighting hexes on the board

    return 0;

}
