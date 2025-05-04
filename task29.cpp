#include<iostream>
#include<cstring>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define ROWS 10
#define COLS 10

class cell{
    char value[4];
    bool marked;
public:
    cell(char character='0');

    void set_char(char c);
    void set_random();

    void mark();

    void mark_problem();

    bool ismarked();

    char *get_value();

    char get_char();

    void show();
};

cell::cell(char character){
    if(character<65 || character>90)character = '0';
    strcpy(value, "   \0");
    value[1] = character;
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
void cell::mark_problem(){
    if(!marked){
        value[0] = '[';
        value[2] = ']';
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
    int problems;
    vector<int> problem_indexes;
    cell field[ROWS][COLS];
    bool checker(int row, int col);
    int freecounter(int row, int col);
    bool isfree(int row, int col);
    void problem_counter();
    bool backtrack(int index);
    bool hasDuplicate(int row, int col);

public:

    puzzle();
    puzzle(cell fld[][COLS]);
    ~puzzle();
    

    void generate();

    void solve();

    void show();

};

puzzle::puzzle(){
    problems = 0;
    cout << "Default constructor" << endl;  
}

puzzle::puzzle(cell fld[][COLS]){
    problems = 0;
    for(int i=0;i<ROWS;i++){   
        for(int j=0;j<COLS;j++){
            field[i][j] = fld[i][j];
        }
    }
}

puzzle::~puzzle(){
    cout << "Destructing puzzle" << endl;
}

void puzzle::problem_counter(){
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            if(!field[i][j].ismarked()){
                for(int k=i+1;k<ROWS;k++){
                    if(field[k][j].get_char() == field[i][j].get_char() && !field[k][j].ismarked()){
                        problems++;
                        problem_indexes.push_back(k);
                        problem_indexes.push_back(j);
                        field[k][j].mark_problem();
                    }
                }
                for(int n=j+1;n<COLS;n++){
                    if(field[i][n].get_char() == field[i][j].get_char() && !field[i][n].ismarked()){
                        problems++;
                        problem_indexes.push_back(i);
                        problem_indexes.push_back(n);
                        field[i][n].mark_problem();
                    }
                }
            }

        }
    }
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

bool puzzle::hasDuplicate(int row, int col) {
    char target = field[row][col].get_char();
    for(int i = 0; i < COLS; ++i) {
        if(i != col && !field[row][i].ismarked() && field[row][i].get_char() == target)
            return true;
    }
    for(int i = 0; i < ROWS; ++i) {
        if(i != row && !field[i][col].ismarked() && field[i][col].get_char() == target)
            return true;
    }
    return false;
}


bool puzzle::backtrack(int id){
    if(id >= ROWS * COLS)return true;

    int row = id / COLS;
    int col = id % COLS;

    if(!hasDuplicate(row, col))return backtrack(id + 1);

    if(!field[row][col].ismarked() && !checker(row, col) && isfree(row, col)){
        field[row][col].mark();
        if(backtrack(id + 1)) return true;
        field[row][col].mark();
    }

    return backtrack(id + 1);

}

void puzzle::generate(){
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            field[i][j].set_random();
        }
    }
}

void puzzle::solve(){
    problems = 0;
    backtrack(0);
    problem_counter();

}

void puzzle::show(){
    for(int i=0;i<ROWS;i++){   
        for(int j=0;j<COLS;j++){
            field[i][j].show();
        }
        cout << endl;
    }
    cout << endl << "Total problems: " << problems << endl;
    if(problems>0){
        cout << "Problem elements: ";
        for(int val : problem_indexes){
            cout << val << " ";
        }
        cout << endl;
    }
}

int main(){
    srand(time(0));

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

    

    puzzle game(example);
    game.show();
    //game.generate();
    game.show();
    game.solve();
    game.show();

}