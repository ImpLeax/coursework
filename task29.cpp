#include<iostream>
#include<cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ROWS 10
#define COLS 10

class cell{
    char value[4];
    bool marked;
public:
    cell();

    void set_char(char c);
    void set_random();

    void mark();

    bool ismarked();

    char *get_value();

    char get_char();

    void show();
};

cell::cell(){
    strcpy(value, " 0 \0");
    marked = false;
}

void cell::set_char(char c){
    if(c<65 || c>90)return;
    value[1] = c;
}
void cell::set_random(){
    value[1] = 'A' + rand() % 26;
}

void cell::mark(){
    if(!marked){
        value[0] = '(';
        value[2] = ')';
        marked = true;
    }
    else{
        value[0] = ' ';
        value[2] = ' ';
        marked = false;
    }
}

bool cell::ismarked(){
    return marked;
}

char* cell::get_value(){
    char *tmp = new char[4];
    strcpy(tmp, value);
    return tmp;
}

char cell::get_char(){
    return value[1];
}

void cell::show(){
    cout << " " << value << " ";
}

class puzzle{
    cell field[ROWS][COLS];
    void search_for_element(int row, int col);
    bool checker(int row, int col);
    int freecounter(int row, int col);
    bool isfree(int row, int col);

public:

    puzzle();
    ~puzzle();

    void generate();

    void solve();

    void show();

};

puzzle::puzzle(){
    cout << "Construct empty puzzle" << endl;  
}

puzzle::~puzzle(){
    cout << "Destructing puzzle" << endl;
}

bool puzzle::isfree(int row, int col){
    if(row>0 && freecounter(row-1, col)<2)return false;
    if(row<ROWS-1 && freecounter(row+1, col)<2)return false;
    if(col>0 && freecounter(row, col-1)<2)return false;
    if(col<COLS-1 && freecounter(row, col+1)<2)return false;
    return true;
}

int puzzle::freecounter(int row, int col){
    int counter=0;
    if(row>0 && !field[row-1][col].ismarked())counter++;
    if(row<ROWS-1 && !field[row+1][col].ismarked())counter++;
    if(col>0 && !field[row][col-1].ismarked())counter++;
    if(col<COLS-1 && !field[row][col+1].ismarked())counter++;
    return counter;
}

bool puzzle::checker(int row, int col){
    if(row>0 && field[row-1][col].ismarked())return true;
    if(row<ROWS-1 && field[row+1][col].ismarked())return true;
    if(col>0 && field[row][col-1].ismarked())return true;
    if(col<COLS-1 && field[row][col+1].ismarked())return true;
    return false;
}

void puzzle::search_for_element(int row, int col){
    char target = field[row][col].get_char();
    for(int i = 0; i < COLS; i++){
        if(field[row][i].get_char() == target && !field[row][col].ismarked() && !field[row][i].ismarked() && i != col){
            if(!checker(row, col) && isfree(row, col))field[row][col].mark();
            else{
                if(!checker(row, i) && isfree(row, i))field[row][i].mark();
            }
        }    
    }
    for(int i = 0; i < ROWS; i++){
        if(field[i][col].get_char() == target && !field[row][col].ismarked() && !field[i][col].ismarked() && i != row){
            if(!checker(row, col) && isfree(row, col))field[row][col].mark();
            else{
                if(!checker(i, col) && isfree(i, col))field[i][col].mark();
            }
        }
    }
}

void puzzle::generate(){
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            field[i][j].set_random();
        }
    }
}

void puzzle::solve(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            search_for_element(i, j);
        }
    }
}

void puzzle::show(){
    for(int i=0;i<ROWS;i++){   
        for(int j=0;j<COLS;j++){
            field[i][j].show();
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    srand(time(0));

    puzzle game;
    game.show();
    game.generate();
    game.show();
    game.solve();
    game.show();
}