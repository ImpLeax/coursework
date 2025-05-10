/*  ----------------------------------------------------------------<Header>-
    Name:       task29.cpp
    Title:      Letter grid puzzle solver

    Group:      TV-42
    Student:    Bondarchuk V. V.
    Written:    2025-05-10
    Revised:    2025-05-10

    Description: Write a program that shades some cells so that there are no repeating numbers in any row or column
                 there are no duplicate letters in any row or column. The shaded cells should not
                 be in contact with each other. All non-filled cells must
                 be connected to each other by sides horizontally or vertically
                 horizontally or vertically to form a single continuous space of
                 of unpainted cells.
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#ifdef _WIN32        //conditional construct for connecting a library that is supported for windows
#include <windows.h>
#endif
#include"cell.hpp"
#include"puzzle.hpp"
#include"handlers.hpp"

#define ROWS 10
#define COLS 10

using namespace std;

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);    //a function to change the output encoding in the Windows console to UTF-8 (required for the correct output of the field) 
    #endif
    srand(time(0));
    clear_console();

    puzzle game;

    //given field
    cell example[ROWS][COLS] = {
        {cell('K'), cell('O'), cell('P'), cell('R'), cell('I'), cell('V'), cell('N'), cell('I'), cell('C'), cell('A')},
        {cell('R'), cell('L'), cell('O'), cell('D'), cell('S'), cell('M'), cell('P'), cell('T'), cell('M'), cell('I')},
        {cell('Y'), cell('P'), cell('J'), cell('U'), cell('L'), cell('V'), cell('P'), cell('E'), cell('K'), cell('W')},
        {cell('D'), cell('M'), cell('I'), cell('A'), cell('B'), cell('B'), cell('J'), cell('Z'), cell('D'), cell('M')},
        {cell('G'), cell('O'), cell('D'), cell('R'), cell('X'), cell('G'), cell('L'), cell('M'), cell('B'), cell('S')},
        {cell('K'), cell('S'), cell('E'), cell('U'), cell('F'), cell('I'), cell('B'), cell('S'), cell('W'), cell('F')},
        {cell('M'), cell('Q'), cell('A'), cell('V'), cell('R'), cell('B'), cell('T'), cell('Z'), cell('Q'), cell('S')},
        {cell('N'), cell('I'), cell('V'), cell('H'), cell('B'), cell('A'), cell('I'), cell('K'), cell('N'), cell('H')},
        {cell('V'), cell('L'), cell('D'), cell('S'), cell('M'), cell('J'), cell('K'), cell('F'), cell('B'), cell('J')},
        {cell('W'), cell('P'), cell('C'), cell('C'), cell('R'), cell('O'), cell('A'), cell('T'), cell('I'), cell('A')}
    };
    //menu implementation
    while(true){
        int choice = -1;
        cout << setw(30) << " " << "====== MENU ======\n";
        cout << setw(30) << " " << "1. Solve programmatically\n";
        cout << setw(30) << " " << "2. Solve programmatically with step by step\n";
        cout << setw(30) << " " << "3. Enter manually and solve programmatically\n";
        cout << setw(30) << " " << "4. Enter manually and solve programmatically whith step by step\n";
        cout << setw(30) << " " << "5. Enter manually and solve manually\n";
        cout << setw(30) << " " << "6. Solve manually example\n";
        cout << setw(30) << " " << "7. Generate and solve the correct random field\n";
        cout << setw(30) << " " << "8. Rules\n";
        cout << setw(30) << " " << "9. Exit\n";
        cout << setw(30) << " " << "Enter your choice: ";

        if(!get_choice(choice, 9)){
            continue;
        }
        else{
            switch(choice){
                case 1:{
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field(example);
                    game.show();
                    game.solve(false);
                    cout << "\nSolved field: \n";
                    game.show();
                    continue;
                }
                case 2:{
                    clear_console();
                    cout << "Caution: The step-by-step process may take some time and may cause lags!\n";
                    cin.ignore(9999999, '\n');
                    pause();
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field(example);
                    game.show();
                    pause();
                    game.solve(true);
                    cout << "\nSolved field: \n";
                    game.show();
                    continue;
                }
                case 3:{
                    clear_console();
                    cout << "Good luck entering 100 cells :)\n";
                    cin.ignore(9999999, '\n');
                    pause();
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field();
                    game.show();
                    game.set_field(nullptr, true);
                    if(game.solve(false)){
                        clear_console();
                        game.show();
                    }else{
                        clear_console();
                        cout << "Your field cannot be solved!\n";
                        game.show();
                    }
                    continue;
                }
                case 4:{
                    clear_console();
                    cout << "Good luck entering 100 cells :)\n";
                    cin.ignore(9999999, '\n');
                    pause();
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field();
                    game.show();
                    game.set_field(nullptr, true);
                    if(game.solve(true)){
                        clear_console();
                        game.show();
                    }else{
                        clear_console();
                        cout << "Your field cannot be solved!\n";
                        game.show();
                    }
                    continue;
                }
                case 5:{
                    clear_console();
                    cout << "Good luck entering 100 cells :)\n";
                    cin.ignore(9999999, '\n');
                    pause();
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field();
                    game.show();
                    game.set_field(nullptr, true);
                    clear_console();
                    game.show();
                    game.solve(false, true);
                    clear_console();
                    game.show();
                    continue;
                }
                case 6:{
                    clear_console();
                    cout << "Initial field: \n";
                    game.set_field(example);
                    game.show();
                    cin.ignore(9999999, '\n');
                    game.solve(false, true);
                    clear_console();
                    game.show();
                    continue;
                }
                case 7:{
                    clear_console();
                    cout << "Solved random field:\n";
                    game.generate();
                    while(true){
                        if(game.solve())break;
                        game.generate();
                    }
                    game.show();
                    continue;
                }
                case 8:{
                    clear_console();
                    cin.ignore(9999999, '\n');
                    cout << "You need to fill in some cells so that there are no repeated letters in each row or column.\n" 
                         << "The filled cells must not touch each other. \n"
                         << "All the unfilled cells must be connected to each other by their sides horizontally or vertically\n"
                         << "so that a single continuous space of unfilled cells is formed.\n";
                    pause();
                    clear_console();
                    continue;
                }
                case 9:{
                    cout << "Exiting...\n";
                    break;
                }
            }
            break;
        }
    
    }

    return 0;
}