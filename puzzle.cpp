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


/*  ---------------------------------------------------------------------[<]-
    Constructor: puzzle
    Synopsis: Initializes the variables for errors and connectivity and 
    the field with empty cells.
 ---------------------------------------------------------------------[>]-*/
puzzle::puzzle() {
    problems = 0;
    is_connected = false;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j] = cell();
    }
  }
}

/*  ---------------------------------------------------------------------[<]-
    Constructor: puzzle
    Synopsis: Initializes the variables for errors and connectivity and 
    initializes the field with the passed completed field.
 ---------------------------------------------------------------------[>]-*/
puzzle::puzzle(cell fld[][COLS]) {
    problems = 0;
    is_connected = false;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j] = fld[i][j];
        }
    }
}

/*  ---------------------------------------------------------------------[<]-
    Destructor: puzzle
 ---------------------------------------------------------------------[>]-*/
puzzle::~puzzle() {
}

/*  ---------------------------------------------------------------------[<]-
    Method: set_field
    Synopsis: Fills the field in different modes:
              1)fills the field with zeros
              2) fills the field with a ready-made field
              3) fills the field manually
 ---------------------------------------------------------------------[>]-*/
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


/*  ---------------------------------------------------------------------[<]-
    Method: solve_backtrack
    Synopsis: Recursive backtracking algorithm 
              that attempts to solve the puzzle by finding unmarked pairs 
              of identical characters in rows and columns. 
              For each valid pair, it marks one cell, checks connectivity 
              and constraints, and recursively proceeds. 
              If the constraints fail or no solution is found deeper in 
              recursion, it unmarks the cell and tries the other cell of 
              the pair. 
              If no valid pair leads to a solution, the function 
              backtracks. 
              Also supports a step-by-step mode that shows the current 
              state at each decision point, which may require many steps.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: check_connected
    Synopsis: Looks for the first unmarked cell to start the traversal 
              from there.
              Then it checks whether all other unmarked cells are 
              reachable by the width 
              traversal (i.e., the cellularity check).
              If at least one unmarked cell is not reachable,
              it returns false.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: problem_counter
    Synopsis: Goes through the field and marks problem cells, that is, 
              if there are cells that are repeated in a row or column 
              and one of them is not marked, 
              that is, does not meet the condition, then marks it as 
              problematic.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: has_conflicts
    Synopsis: Returns true if there are no problem cells, i.e. 
              no duplicates in a row or column and one of them is labeled, 
              and false if there are problems.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: is_free
    Synopsis: Checks if there is space in neighboring cells to avoid 
              blocking them with a marked cell and thus violating the 
              conditions.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: free_counter
    Synopsis: Determines the number of unlabeled neighbors, 
              i.e. free spaces.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: checker
    Synopsis: Checks if adjacent cells are labeled 
              (method for labeled cells to avoid violating the condition).
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: generate
    Synopsis: Generates a random field.
 ---------------------------------------------------------------------[>]-*/
void puzzle::generate() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j].set_random();
        }
    }
}

/*  ---------------------------------------------------------------------[<]-
    Method: solve
    Synopsis: A generalized method that solves the field, counts errors, 
              and determines connectivity. 
              Also supports manual input mode.
 ---------------------------------------------------------------------[>]-*/
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

/*  ---------------------------------------------------------------------[<]-
    Method: show
    Synopsis: Method for printing a field.
 ---------------------------------------------------------------------[>]-*/
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