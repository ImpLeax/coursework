#ifndef CELL_HPP
#define CELL_HPP

/*  ---------------------------------------------------------------------[<]-
    Class: cell
    Synopsis: Describes the cell object in the field
 ---------------------------------------------------------------------[>]-*/
class cell {
    char value[4];
    bool marked;
    bool error;

public:
    cell(char character = '0');

    bool set_char(char c);
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

#endif