#include "atom.h"

Atom::Atom(int n, std::string s) {
    symbol = s;
    id     = n;
    xPos   = 0;
    yPos   = 0;
    zPos   = 0;
}

Atom::Atom(int n, std::string s, float x, float y, float z) {
    id     = n;
    symbol = s;
    xPos   = x;
    yPos   = y;
    zPos   = z;
}

int Atom::getId() { return id; }

std::string Atom::getSymbol() { return symbol; }

float Atom::getX() { return xPos; }

float Atom::getY() { return yPos; }

float Atom::getZ() { return zPos; }

void Atom::setSymbol(std::string s) { symbol = s; }

void Atom::setX(float x) { xPos = x; }

void Atom::setY(float y) { yPos = y; }

void Atom::setZ(float z) { zPos = z; }

float* Atom::getPosition() {
    float* position = (float*)calloc(3, sizeof(float));
    position[0]     = xPos;
    position[1]     = yPos;
    position[2]     = zPos;

    return position;
}

std::string Atom::toString() {
    std::string msg = "   ";
    msg.append(symbol);
    msg.append("   ");
    msg.append(std::to_string(xPos));
    msg.append(" ");
    msg.append(std::to_string(yPos));
    msg.append(" ");
    msg.append(std::to_string(zPos));
    msg.append("\n");

    return msg;
}
