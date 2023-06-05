#include "xyzWrite.h"

void printPositions(std::string filename, Atom* atoms, int num) {
    std::ofstream file(filename);

    file << num << std::endl << "Generated by personal code" << std::endl;

    for(int i = 0; i < num; i++) { file << atoms[i].toString(); }

    file.close();
}
