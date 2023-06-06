#include "atom.h"

Atom::Atom(int n, std::string s) {
    symbol = s;
    id     = n;
    x_pos  = 0;
    y_pos  = 0;
    z_pos  = 0;
}

Atom::Atom(int n, std::string s, float x, float y, float z) {
    id     = n;
    symbol = s;
    x_pos  = x;
    y_pos  = y;
    z_pos  = z;
}

int Atom::get_id() { return id; }

std::string Atom::get_symbol() { return symbol; }

float Atom::get_x() { return x_pos; }

float Atom::get_y() { return y_pos; }

float Atom::get_z() { return z_pos; }

void Atom::set_symbol(std::string s) { symbol = s; }

void Atom::set_x(float x) { x_pos = x; }

void Atom::set_y(float y) { y_pos = y; }

void Atom::set_z(float z) { z_pos = z; }

float* Atom::get_position() {
    float* position = (float*)calloc(3, sizeof(float));
    position[0]     = x_pos;
    position[1]     = y_pos;
    position[2]     = z_pos;

    return position;
}

std::string Atom::to_string() {
    std::string msg = "   ";
    msg.append(symbol);
    msg.append("   ");
    msg.append(std::to_string(x_pos));
    msg.append(" ");
    msg.append(std::to_string(y_pos));
    msg.append(" ");
    msg.append(std::to_string(z_pos));
    msg.append("\n");

    return msg;
}
