#include<iostream>
#include<cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ROWS 10
#define COLS 10

class Cell{
    char value[4];
    bool marked;
public:
    Cell(){
        strcpy(value, " 0 \0");
        marked = false;
    }

    void set_char(char c){
        if(c<65 || c>90)return;
        value[1] = c;
    }
    void set_random(){
        value[1] = 'A' + rand() % 26;
    }

    void mark(){
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

    bool ismarked(){
        return marked;
    }

    char *get_value(){
        char *tmp = new char[4];
        strcpy(tmp, value);
        return tmp;
    }

    char get_char(){
        return value[1];
    }

    void show(){
        cout << " " << value << " ";
    }
};

class Puzzle{
    Cell field[ROWS][COLS];
    bool search_for_element(int row, int col){
        for(int i=col;i>0;i--){
        }
    }
public:
    Puzzle(){
        cout << "Construct empty puzzle" << endl;  
    }
    ~Puzzle(){
        cout << "Destructing puzzle" << endl;
    }
    void generate(){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                field[i][j].set_random();
            }
        }
    }
    void solve(){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                field[i][j].mark();
            }
        }
    }
    void show(){
        for(int i=0;i<ROWS;i++){   
            for(int j=0;j<COLS;j++){
                field[i][j].show();
            }
            cout << endl;
        }
        cout << endl;
    }

};

int main(){
    srand(time(0));

    Puzzle game;
    game.show();
    game.generate();
    game.show();
    game.solve();
    game.show();
}