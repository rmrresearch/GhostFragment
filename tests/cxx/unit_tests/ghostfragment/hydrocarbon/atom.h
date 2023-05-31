#ifndef ATOM_H_
#define ATOM_H_

#include<string>

class Atom{
	private:
		int id;
		std::string symbol;
		float xPos;
		float yPos;
		float zPos;

	public:
		//Constructors
		Atom(int n, std::string s);
		Atom(int n, std::string s, float x, float y, float z);

		//Getters
		int getId();
		std::string getSymbol();
		float getX();
		float getY();
		float getZ();

		//Setters
		void setSymbol(std::string s);
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		//Special Functions
		float *getPosition();
		std::string toString();
};
/*
class System{
	private:
		Atom *atoms;
		int num;
	public:
		System(Atom *a, int n);

		Atom *getAtoms();
		int getNum();
};
*/
#endif
