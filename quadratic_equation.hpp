#pragma once

#define ACCURACY 3

enum RootsNum {
	NONE,
	ONE,
	TWO,
	ALL
};

using EqRoots = struct {
	enum RootsNum number;
	double x1;
	double x2;
};

class QuadraticEquation {
private:
	double a;
	double b;
	double c;

	double Discriminant();

public:
	void ReadEqCoeffs(std::istream& readFile);
	EqRoots* SolveEquation();
	void PrintEquation(std::ostream& printFile);
	void PrintSolution(std::ostream& printFile);
	friend bool operator == (const QuadraticEquation& first, const QuadraticEquation& second);
};