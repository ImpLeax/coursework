#include<iostream>
#include <iomanip>
#include"cell.hpp"

using namespace std;

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

void cell::set_char(char c) {
    if (c < 65 || c > 90) {
        return;
    }
    value[1] = c;
}

void cell::set_random() {
    value[1] = 'A' + rand() % 26;
}

void cell::set_marked() {
    if (!marked && !error) {
        value[0] = '(';
        value[2] = ')';
        marked = true;
    }
}

void cell::unset_marked() {
    if (marked && !error) {
        value[0] = ' ';
        value[2] = ' ';
        marked = false;
    }
}

void cell::set_problem() {
    if (!marked && !error) {
        value[0] = '[';
        value[2] = ']';
        marked = true;
        error = true;
    }
}

void cell::unset_problem() {
    if (error) {
        value[0] = ' ';
        value[2] = ' ';
        marked = false;
        error = false;
    }
}

bool cell::is_marked() {
    return marked;
}

bool cell::is_error() {
    return error;
}

const char *cell::get_value(){
    return value;
}

char cell::get_char() {
    return value[1];
}

void cell::show() {
    cout << setw(1) << " " << value << setw(1) << " ";
}