#include<iostream>
#include<set>
#include <iomanip>
#include <queue>
#include <sstream>
#include <string>
#include"cell.hpp"
#include"puzzle.hpp"
#include"handlers.hpp"

#define ROWS 10
#define COLS 10

using namespace std;

puzzle::puzzle() {
    problems = 0;
    is_connected = false;
}

puzzle::puzzle(cell fld[][COLS]) {
    problems = 0;
    is_connected = false;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j] = fld[i][j];
        }
    }
}

puzzle::~puzzle() {
}

void puzzle::set_field(cell fld[][COLS], bool manualy){
    problems = 0;
    is_connected = false;
    if(fld == nullptr){
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                field[i][j] = cell();
            }
        }
    }
    else{
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                field[i][j] = fld[i][j];
            }
        }
    }

    if(manualy){
        int a, b;
        char ch;
        string input;

        while (true) {
            cout << "Enter a cell row and column and a letter (example: 0 0 A), or 'q' to finish: ";
            getline(cin, input);

            if (input == "q") {
                break;
            }

            stringstream ss(input);
            if (ss >> a >> b >> ch && (ch >= 'A' && ch <= 'Z')) {
                if (a >= 0 && a < 10 && b >= 0 && b < 10) {
                    field[a][b].set_char(ch);
                    clear_console();
                    show();
                } else {
                    cout << "Cell position out of bounds!\n";
                }
            } else {
                cout << "Invalid input! Try again.\n";
            }
        }
    }
}



bool puzzle::solve_backtrack(bool step_by_step) {
    if (!has_conflicts()) {
        return true;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (field[i][j].is_marked()) {
                continue;
            }

            char c = field[i][j].get_char();

            for (int k = j + 1; k < COLS; k++) {
                if (!field[i][k].is_marked() && field[i][k].get_char() == c) {
                    if (!checker(i, j) && is_free(i, j)) {
                        field[i][j].set_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                        if (check_connected()) {
                            if (solve_backtrack(step_by_step)) {
                                return true;
                            }
                        }
                        field[i][j].unset_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                    }

                    if (!checker(i, k) && is_free(i, k)) {
                        field[i][k].set_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                        if (check_connected()) {
                            if (solve_backtrack(step_by_step)) {
                                return true;
                            }
                        }
                        field[i][k].unset_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                    }
                    return false; 
                }
            }

            for (int k = i + 1; k < ROWS; k++) {
                if (!field[k][j].is_marked() && field[k][j].get_char() == c) {
                    if (!checker(i, j) && is_free(i, j)) {
                        field[i][j].set_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                        if (check_connected()) {
                            if (solve_backtrack(step_by_step)) {
                                return true;
                            }
                        }
                        field[i][j].unset_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                    }

                    if (!checker(k, j) && is_free(k, j)) {
                        field[k][j].set_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                        if (check_connected()) {
                            if (solve_backtrack(step_by_step)) {
                                return true;
                            }
                        }
                        field[k][j].unset_marked();
                        if(step_by_step){
                            clear_console();
                            show();
                            pause();
                        }
                    }
                    return false;
                }
            }
        }
    }
    return false;
}

bool puzzle::check_connected() {
    bool visited[ROWS][COLS] = {false};
    queue<pair<int, int>> q;

    bool found = false;
    for (int i = 0; i < ROWS && !found; ++i) {
        for (int j = 0; j < COLS && !found; ++j) {
            if (!field[i][j].is_marked()) {
                q.push({i, j});
                visited[i][j] = true;
                found = true;
            }
        }
    }

    if (!found) {
        return false; 
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> p = q.front(); 
        q.pop();
        int x = p.first;
        int y = p.second;

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS &&
                !field[nx][ny].is_marked() && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (!field[i][j].is_marked() && !visited[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void puzzle::problem_counter() {
    problems = 0;
    problem_indexes.clear();

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (field[i][j].is_marked()) {
                continue;
            }

            char current = field[i][j].get_char();

            for (int k = i + 1; k < ROWS; ++k) {
                if (!field[k][j].is_marked() && field[k][j].get_char() == current) {
                    field[i][j].set_problem();
                    field[k][j].set_problem();
                    problem_indexes.insert({i, j});
                    problem_indexes.insert({k, j});
                }
            }

            for (int n = j + 1; n < COLS; ++n) {
                if (!field[i][n].is_marked() && field[i][n].get_char() == current) {
                    field[i][j].set_problem();
                    field[i][n].set_problem();
                    problem_indexes.insert({i, j});
                    problem_indexes.insert({i, n});
                }
            }
        }
    }
    problems = problem_indexes.size();
}

bool puzzle::has_conflicts() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (field[i][j].is_marked()) {
                continue;
            }
            char c = field[i][j].get_char();
            for (int k = j + 1; k < COLS; k++) {
                if (!field[i][k].is_marked() && field[i][k].get_char() == c) {
                    return true;
                }
            }
            for (int k = i + 1; k < ROWS; k++) {
                if (!field[k][j].is_marked() && field[k][j].get_char() == c) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool puzzle::is_free(int row, int col) {
    if (row > 0 && free_counter(row - 1, col) < 2) {
        return false;
    }
    if (row < ROWS - 1 && free_counter(row + 1, col) < 2) {
        return false;
    }
    if (col > 0 && free_counter(row, col - 1) < 2) {
        return false;
    }
    if (col < COLS - 1 && free_counter(row, col + 1) < 2) {
        return false;
    }
    return true;
}

int puzzle::free_counter(int row, int col) {
    int counter = 0;
    if (row > 0 && !field[row - 1][col].is_marked()) {
        counter++;
    }
    if (row < ROWS - 1 && !field[row + 1][col].is_marked()) {
        counter++;
    }
    if (col > 0 && !field[row][col - 1].is_marked()) {
        counter++;
    }
    if (col < COLS - 1 && !field[row][col + 1].is_marked()) {
        counter++;
    }
    return counter;
}

bool puzzle::checker(int row, int col) {
    if (row > 0 && field[row - 1][col].is_marked()) {
        return true;
    }
    if (row < ROWS - 1 && field[row + 1][col].is_marked()) {
        return true;
    }
    if (col > 0 && field[row][col - 1].is_marked()) {
        return true;
    }
    if (col < COLS - 1 && field[row][col + 1].is_marked()) {
        return true;
    }
    return false;
}

void puzzle::generate() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j].set_random();
        }
    }
}

bool puzzle::solve(bool step_by_step, bool solve_manualy) {
    if(solve_manualy){
        int a, b;
        string input;

        while (true) {
            cout << "Enter a cell row and column to mark or unmark (example: 0 0), or 'q' to finish: ";
            getline(cin, input);

            if (input == "q") {
                break;
            }

            stringstream ss(input);
            if (ss >> a >> b) {
                if (a >= 0 && a < 10 && b >= 0 && b < 10) {
                    if(!field[a][b].is_marked()){
                        field[a][b].set_marked();
                        clear_console();
                        show();
                    }else{
                        field[a][b].unset_marked();
                        clear_console();
                        show();
                    }
                } else {
                    cout << "Cell position out of bounds!\n";
                }
            } else {
                cout << "Invalid input! Try again.\n";
            }
        }
        problem_counter();
        is_connected = check_connected();
    }else{
        bool is_solved = solve_backtrack(step_by_step);
        problem_counter();
        is_connected = check_connected();
        return is_solved;
    }
    return false;
}

void puzzle::show() {
    cout << " ";
    for (int i = 0; i < COLS; i++) cout << setw(6) << i;
    cout << endl;
    cout << "   ┌";
    for (int j = 0; j < COLS - 1; j++) cout << "───" << "──┬"; 
    cout << "───" << "──┐" << endl; 

    for (int i = 0; i < ROWS; i++) {
        cout << " " << i << " │"; 
        for (int j = 0; j < COLS; j++) {
            field[i][j].show(); 
            cout << "│"; 
        }
        cout << endl;

        if (i != ROWS - 1) {
            cout << "   ├"; 
            for (int j = 0; j < COLS - 1; j++) cout << "───" << "──┼"; 
            cout << "───" << "──┤" << endl; 
        }
    }

    cout << "   └"; 
    for (int j = 0; j < COLS - 1; j++) cout << "───" << "──┴"; 
    cout << "───" << "──┘" << endl; 

    cout << "\nTotal problems: " << problems << endl;
    cout << boolalpha << "Is connected: " << is_connected << endl;
    if (problems > 0) {
        cout << "Problem elements: ";
        for (const auto &p : problem_indexes) {
            cout << p.first << ',' << p.second << "; ";
        }
        cout << endl;
    }
}