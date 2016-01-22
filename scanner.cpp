/*
 * File: scanner.cpp
 * -----------------
 * Implementation for the simplified Scanner class.
 * Code taken from the CS106B/X Course Reader, page 332, Figure 9.6
 * Additional code by C. Schatz
 */

#include "scanner.h"
#include <cctype>
#include <iostream>

enum inputSymbolType { isaDigit = 0, isaPoint, isaPlusMinus, isanE, isOther };

/*
 * The details of the representation are inaccessible to the client,
 * but consist of the following fields:
 *
 * buffer -- String passed to setInput
 * len -- Length of buffer, saved for efficiency
 * cp -- Current character position in the buffer
 * spaceOption -- Setting of the space option extension
 */

Scanner::Scanner() {
    buffer = "";
    spaceOption = PreserveSpaces;
    numberOption = ScanNumbersAsLetters;
}

Scanner::~Scanner() {
    /* Empty */
}

void Scanner::setInput(string str) {
    buffer = str;
    len = (int) buffer.length();
    cp = 0;
}

void Scanner::setInput(istream & infile)
{
    string tempbuffer = "";
    char onechar;
    infile.clear();
    infile.seekg(0);
    while (1)
    {
        infile.read(&onechar, 1);
        if (!infile)
            break;
        tempbuffer += onechar;
    }
    setInput(tempbuffer);
}

/*
 * Implementation notes: nextToken
 * -------------------------------
 * The code for nextToken follows from the definition of a token.
 */

string Scanner::nextToken() {
    if (cp == -1) {
        Error("setInput has not been called");
    }
    if (! savedTokens.isEmpty())
    {
        return savedTokens.pop();
    }
    
    if (spaceOption == IgnoreSpaces) skipSpaces();
    int start = cp;
    if (start >= len) return "";
    if (stringOption == ScanQuotesAsStrings && buffer[cp] == '\"')
    {
        return (scanQuotedString());
    }
    else if (bracketOption == ScanBracketsAsTag && buffer[cp] == '<')
    {
        return (scanTag());
    }
    else if (isdigit(buffer[cp]) && numberOption != ScanNumbersAsLetters)
    {
        int finish;
        if (numberOption == ScanNumbersAsIntegers)
            finish = scanToEndOfInteger();
        else if (numberOption == ScanNumbersAsReals)
            finish = scanToEndOfReal();
        return buffer.substr(start, finish - start + 1);
    }
    else if (isalnum(buffer[cp]))
    {
        int finish = scanToEndOfIdentifier();
        return buffer.substr(start, finish - start + 1);
    }
    cp++;
    return buffer.substr(start, 1);
}

bool Scanner::hasMoreTokens() {
    if (cp == -1) {
        Error("setInput has not been called");
    }
    if (spaceOption == IgnoreSpaces) skipSpaces();
    return (cp < len);
}

void Scanner::setSpaceOption(spaceOptionT option) {
    spaceOption = option;
}

Scanner::spaceOptionT Scanner::getSpaceOption() {
    return spaceOption;
}


void Scanner::setStringOption(stringOptionT option) {
    stringOption = option;
}

Scanner::stringOptionT Scanner::getStringOption() {
    return stringOption;
}


void Scanner::setNumberOption(numberOptionT option)
{
    numberOption = option;
}

Scanner::numberOptionT Scanner::getNumberOption()
{
    return numberOption;
}


void Scanner::setBracketOption(bracketOptionT option)
{
    bracketOption = option;
}

Scanner::bracketOptionT Scanner::getBracketOption()
{
    return bracketOption;
}


/* Private functions */

/*
 * Private method: skipSpaces
 * Usage: skipSpaces();
 * -------------------
 * This function advances the position of the scanner until the
 * current character is not a whitespace character.
 */

void Scanner::skipSpaces() {
    while (cp < len && isspace(buffer[cp])) {
        cp++;
    }
}

/*
 * Private method: scanToEndOfIdentifier
 * Usage: finish = scanToEndOfIdentifier();
 * ----------------------------------------
 * This function advances the position of the scanner until it
 * reaches the end of a sequence of letters or digits that make
 * up an identifier. The return value is the index of the last
 * character in the identifier; the value of the stored index
 * cp is the first character after that.
 */

int Scanner::scanToEndOfIdentifier() {
    while (cp < len && isalnum(buffer[cp])) {
        cp++;
    }
    return cp - 1;
}

int Scanner::scanToEndOfInteger()
{
    while (cp < len && isdigit(buffer[cp])) {
        cp++;
    }
    return cp - 1;
}

string Scanner::scanQuotedString()
{
    string result = "";
    do
    {
        result += buffer[cp];
        cp++;
    }
    while (cp < len && buffer[cp] != '\"');
    if (buffer[cp] != '\"')
        Error("Unmatched \" in scanner input");
    cp++;
    return result + "\"";
}

static inputSymbolType CategorizeSymbol(char c)
{
    if (isdigit(c))
        return isaDigit;
    if (c == '.')
        return isaPoint;
    if (c == '+' || c == '-')
        return isaPlusMinus;
    if (c == 'e' || c == 'E')
        return isanE;
    
    return isOther;
}


int Scanner::scanToEndOfReal()
{
    // -- Finite State Machine represented as a table --
    // rows are states
    // columns are input symbol categories
    
    //  isaDigit = 0, isaPoint, isaPlusMinus, isanE
    
    int FSM[6][4] = {
        /* 0 InitialState */          {  1,  6,  6,  6 },
        /* 1 BeforeDecimalPoint */    {  1,  2,  6,  3 },
		/* 2 AfterDecimalPoint */     {  2,  6,  6,  3 },
		/* 3 StartingExponent */      {  5,  6,  4,  6 },
		/* 4 FoundExponentSign */     {  5,  6,  6,  6 },
		/* 5 ScanningExponent */      {  5,  6,  6,  6 },
    }; // (6 is final state)
    
    int state = InitialState;
    
    do
    {
        int category = CategorizeSymbol(buffer[cp]);
        if (category == isOther)
            state = FinalState;
        else
            state = FSM[state][category];
        if (state == FinalState)
            break;
        cp++;
    }
    while (cp < len);
    return (cp - 1);
}

string Scanner::scanTag()
{
    string result = "";
    do
    {
        result += buffer[cp];
        cp++;
    }
    while (cp < len && buffer[cp] != '>');
    if (buffer[cp] != '>')
        Error("Unmatched < in scanner input");
    cp++;
    return result + ">";
}


void Scanner::saveToken(string token)
{
    savedTokens.push(token);
}
