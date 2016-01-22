/**
  File: hgraphics.h
  ---------------
  Functions are provided here to:

    1. Draw the boggle board
    2. Manage the word lists
    3. Update the scoreboard
    4. Give information about how many dice are in each row

  A NOTE ABOUT GRID POSITIONS:
  The normal size grid is organized into 5 rows, with different numbers
  of "columns" in each.  The row and column numbers are as follows:

  Row 0:    0 1 2
  Row 1:   0 1 2 3
  Row 2:  0 1 2 3 4
  Row 3:   0 1 2 3
  Row 4:    0 1 2

*/

#ifndef _HGRAPHICS_H
#define _HGRAPHICS_H

#include <string>
using namespace std;


/*
 * Type: playerT
 * -------------
 * This enumeration distinguishes the human and computer players.
 */

enum playerT {Human, Computer};


/*
 * Type: boardCoordT
 * -----------------
 * This struct specifies a single hex position on the board
 */

struct boardCoordT
{
    int row;
    int col;
};

/*
 * Function: LetterAt
 * Sample Usage: char letter = LetterAt(2, 2);
 * -------------------------------------------
 * Returns the label on the die at the given row and column
 */

char LetterAt(int row, int col);

/*
 * Function: DiceInRow
 * Sample Usage: int numDice = DiceInRow(1);
 * -----------------------------------------
 * Returns the number of dice in a given row.
 * For instance, asking for the number of dice in row 2, the
 * center row of the default board setup, would return 5.
 */

int DiceInRow(int row);

/*
 * Function: DrawBoard
 * Usage: DrawBoard();
 * -------------------
 * This function draws the empty layout of the board.  It should
 * be called once at the beginning of each game, after calling
 * InitGraphics() to erase the graphics window.  It will redraw
 * the boggle cubes, board, and scores.  It resets the scores
 * and word lists to zero for each player.  The boggle cubes are
 * drawn with blank faces, ready for letters to be set using the
 * LabelCube function.
 */

void DrawBoard();

/*
 * Function: LabelHex
 * Usage: LabelHex(row, col, letter);
 * -----------------------------------
 * This function draws the specified letter on the face of the
 * hex at position (row, col). See above for the layout
 * of the hexes.
 * Example: the call:
 *
 *      LabelHex(0, 2, 'D');
 *
 * would put a D on the rightmost hex in the top row
 */

void LabelHex(int row, int col, char letter);

/*
 * Function: HighlightHex
 * Usage: HighlightHex(row, col, flag);
 * -------------------------------------
 * This function highlights or unhighlights the specified cube
 * according to the setting of flag: if flag is TRUE, the cube
 * is highlighted; if flag is FALSE, the highlight is removed.
 * The highlight flag makes it possible for you to show which
 * letters are in a word.
 */

void HighlightHex(int row, int col, bool flag);


bool PointIsInHex(int x, int y, int row, int col);

/*
 * Function: RecordNewWord
 * Usage: RecordNewWord(word, player);
 * -----------------------------------
 * This function records the specified word by adding it to
 * the screen display for the specified player and updating
 * the scoreboard accordingly.  Scoring is calculated as
 * follows:  a 4-letter word is worth 1 point, a 5-letter
 * is worth 2 points, and so on.
 */

void RecordNewWord(string word, playerT player);

/*
 * Function: PrintMessage
 * Usage: PrintMessage(message);
 * ------------------------------
 * This function prints to the message area of the graphics window.
 */

void PrintMessage(string msg);

/*
 * Function: BoardGetLine()
 * Usage: string userinput = BoardGetLine();
 * -----------------------------------------
 * This function works like the normal GetLine() function,
 * put works on the graphics window.
 */

string BoardGetLine();

#endif
