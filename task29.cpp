#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <queue>

#define ROWS 10
#define COLS 10

using namespace std;

class cell {
    char value[4];
    bool marked;
    bool error;

public:
    cell(char character = '0');

    void set_char(char c);
    void set_random();

    void set_marked();    
    void unset_marked(); 

    void set_problem();    
    void unset_problem();  

    bool is_marked();
    bool is_error();

    const char *get_value();

    char get_char();

    void show();
};

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
    cout << " " << value << " ";
}

class puzzle {
    int problems;
    bool is_connected;
    set<pair<int, int>> problem_indexes;
    cell field[ROWS][COLS];

    bool checker(int row, int col);
    bool is_free(int row, int col);
    bool has_conflicts();
    bool check_connected();
    bool solve_backtrack();

    int free_counter(int row, int col);

    void problem_counter();

public:
    puzzle();
    puzzle(cell fld[][COLS]);
    ~puzzle();

    void generate();
    void solve();
    void show();
};

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

bool puzzle::solve_backtrack() {
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
                        if (check_connected()) {
                            if (solve_backtrack()) {
                                return true;
                            }
                        }
                        field[i][j].unset_marked();
                    }

                    if (!checker(i, k) && is_free(i, k)) {
                        field[i][k].set_marked();
                        if (check_connected()) {
                            if (solve_backtrack()) {
                                return true;
                            }
                        }
                        field[i][k].unset_marked();
                    }
                    return false; 
                }
            }

            for (int k = i + 1; k < ROWS; k++) {
                if (!field[k][j].is_marked() && field[k][j].get_char() == c) {
                    if (!checker(i, j) && is_free(i, j)) {
                        field[i][j].set_marked();
                        if (check_connected()) {
                            if (solve_backtrack()) {
                                return true;
                            }
                        }
                        field[i][j].unset_marked();
                    }

                    if (!checker(k, j) && is_free(k, j)) {
                        field[k][j].set_marked();
                        if (check_connected()) {
                            if (solve_backtrack()) {
                                return true;
                            }
                        }
                        field[k][j].unset_marked();
                    }
                    return false;
                }
            }
        }
    }
    return false;
}

bool puzzle::check_connected() {
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
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

void puzzle::solve() {
    solve_backtrack();
    problem_counter();
    is_connected = check_connected();
}

void puzzle::show() {
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j].show();
        }
        cout << endl;
    }
    cout << endl << "Total problems: " << problems << endl;
    cout << boolalpha << "Is connected: " << is_connected << endl;
    if (problems > 0) {
        cout << "Problem elements: ";
        for (const auto &p : problem_indexes) {
            cout << p.first << ',' << p.second << "; ";
        }
        cout << endl;
    }
}

int main() {
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
    game.solve();
    game.show();
}