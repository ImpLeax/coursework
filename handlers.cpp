#include <iostream>
#include <iomanip>
#include"handlers.hpp"

using namespace std;


/*  ---------------------------------------------------------------------[<]-
    Function: clear_console
    Synopsis: Cleans the console for both Windows and Linux.
 ---------------------------------------------------------------------[>]-*/
void clear_console() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear"); 
    #endif
}

/*  ---------------------------------------------------------------------[<]-
    Function: get_choice
    Synopsis: Menu helper function reads the selection and checks for correct input.
 ---------------------------------------------------------------------[>]-*/
bool get_choice(int &choice, int choices){
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(9999999, '\n');
        clear_console();
        cout << setw(30) << "\nInvalid input!\n";
        return false;
    }
    else if(choice < 1 || choice > choices){
        clear_console();
        cout << setw(30) << "\nInvalid number!\n";
        return false;
    }
    else{
        return true;
    }
}

/*  ---------------------------------------------------------------------[<]-
    Function: pause
    Synopsis: Suspends the program until you enter “Enter” or “q” to exit.
 ---------------------------------------------------------------------[>]-*/
void pause(){
    cout << "\nPress Enter to continue or 'q' to exit..." << endl;
    char ch;
    while (true) {
        ch = cin.get();
        if (ch == '\n') break;
        else if (ch == 'q'){
            cout << "\nExiting ... \n";
            exit(0);
        }   
    }
}