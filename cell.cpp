#include<iostream>
#include <iomanip>
#include"cell.hpp"

using namespace std;


/*  ---------------------------------------------------------------------[<]-
    Constructor: cell
    Synopsis: Initializes a cell according to the specified letter.
 ---------------------------------------------------------------------[>]-*/
cell::cell(char character) {
    if (character < 65 || character > 90) {
        character = '0';
    }
    value[0] = ' ';
    value[1] = character;
    value[2] = ' ';
    value[3] = '\0';

    marked = false;
    error = false;
}

/*  ---------------------------------------------------------------------[<]-
    Method: set_char
    Synopsis: Changes the letter of the cell.
 ---------------------------------------------------------------------[>]-*/
bool cell::set_char(char c) {
    if (c < 65 || c > 90) {
        return false;
    }
    value[1] = c;
    return true;
}

/*  ---------------------------------------------------------------------[<]-
    Method: set_random
    Synopsis: Sets a random letter.
 ---------------------------------------------------------------------[>]-*/
void cell::set_random() {
    unset_problem();
    unset_marked();
    value[1] = 'A' + rand() % 26;
}


/*  ---------------------------------------------------------------------[<]-
    Method: set_marked
    Synopsis: Marks (fills in) a cell.
 ---------------------------------------------------------------------[>]-*/
void cell::set_marked() {
    if (!marked && !error) {
        value[0] = '(';
        value[2] = ')';
        marked = true;
    }
}

/*  ---------------------------------------------------------------------[<]-
    Method: unset_marked
    Synopsis: Unmarks (erases) a cell.
 ---------------------------------------------------------------------[>]-*/
void cell::unset_marked() {
    if (marked && !error) {
        value[0] = ' ';
        value[2] = ' ';
        marked = false;
    }
}


/*  ---------------------------------------------------------------------[<]-
    Method: set_problem
    Synopsis: Selects (fills in) the problem cell.
 ---------------------------------------------------------------------[>]-*/
void cell::set_problem() {
    if (!marked && !error) {
        value[0] = '[';
        value[2] = ']';
        marked = true;
        error = true;
    }
}

/*  ---------------------------------------------------------------------[<]-
    Method: unset_problem
    Synopsis: Removes (erases) the problem cell.
 ---------------------------------------------------------------------[>]-*/
void cell::unset_problem() {
    if (error) {
        value[0] = ' ';
        value[2] = ' ';
        marked = false;
        error = false;
    }
}

/*  ---------------------------------------------------------------------[<]-
    Method: is_marked
    Synopsis: Lets you know if a cell is marked.
 ---------------------------------------------------------------------[>]-*/
bool cell::is_marked() {
    return marked;
}

/*  ---------------------------------------------------------------------[<]-
    Method: is_error
    Synopsis: Lets you know if a cell is problematic.
 ---------------------------------------------------------------------[>]-*/
bool cell::is_error() {
    return error;
}

/*  ---------------------------------------------------------------------[<]-
    Method: get_value
    Synopsis: Returns the whole cell.
 ---------------------------------------------------------------------[>]-*/
const char *cell::get_value(){
    return value;
}

/*  ---------------------------------------------------------------------[<]-
    Method: get_char
    Synopsis: Returns only a letter.
 ---------------------------------------------------------------------[>]-*/
char cell::get_char() {
    return value[1];
}

/*  ---------------------------------------------------------------------[<]-
    Method: show
    Synopsis: Prints a cell.
 ---------------------------------------------------------------------[>]-*/
void cell::show() {
    cout << setw(1) << " " << value << setw(1) << " ";
}