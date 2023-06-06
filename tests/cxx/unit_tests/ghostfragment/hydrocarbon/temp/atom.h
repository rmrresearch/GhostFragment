#ifndef ATOM_H_
#define ATOM_H_

#include <string>

class Atom {
private:
    int id;
    std::string symbol;
    float x_pos;
    float y_pos;
    float z_pos;

public:
    // Constructors
    Atom(int n, std::string s);
    Atom(int n, std::string s, float x, float y, float z);

    // Getters
    int get_id();
    std::string get_symbol();
    float get_x();
    float get_y();
    float get_z();

    // Setters
    void set_symbol(std::string s);
    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

    // Special Functions
    float* get_position();
    std::string to_string();
};
#endif
