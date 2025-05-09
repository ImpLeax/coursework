#ifndef PUZZLE_HPP
#define PUZZLE_HPP
#define ROWS 10
#define COLS 10
#include<set>
#include"cell.hpp"

using namespace std;

class puzzle {
    int problems;
    bool is_connected;
    set<pair<int, int>> problem_indexes;
    cell field[ROWS][COLS];

    bool checker(int row, int col);
    bool is_free(int row, int col);
    bool has_conflicts();
    bool check_connected();
    bool solve_backtrack(bool step_by_step);

    int free_counter(int row, int col);

    void problem_counter();

public:
    puzzle();
    puzzle(cell fld[][COLS]);
    ~puzzle();

    void set_field(cell fld[][COLS] = nullptr);
    void generate();
    void solve(bool step_by_step);
    void show();
};

#endif