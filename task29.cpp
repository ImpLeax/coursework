#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#ifdef _WIN32
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
        SetConsoleOutputCP(65001);     
    #endif
    srand(time(0));
    clear_console();

    puzzle game;

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
    while(true){
        int choice = -1;
        cout << setw(30) << " " << "====== MENU ======\n";
        cout << setw(30) << " " << "1. Solve programmatically\n";
        cout << setw(30) << " " << "2. Solve programmatically with step by step\n";
        cout << setw(30) << " " << "3. Enter manually and solve programmatically\n";
        cout << setw(30) << " " << "4. Enter manually and solve programmatically whith step by step\n";
        cout << setw(30) << " " << "5. Enter manually and solve manually\n";
        cout << setw(30) << " " << "6. Solve manually example\n";
        cout << setw(30) << " " << "7. Exit\n";
        cout << setw(30) << " " << "Enter your choice: ";

        if(!get_choice(choice, 7)){
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
                    cout << "\nExiting ... \n";
                    break;
                }
            }
            break;
        }
    
    }

    return 0;
}