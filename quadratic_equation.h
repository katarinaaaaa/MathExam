#pragma once

#define ACCURACY 3

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

	double Discriminant() {
		return (b * b - 4.0 * a * c);
	}

public:
	void ReadEqCoeffs(std::istream& readFile) {
		readFile >> a >> b >> c;
	}
	EqRoots* SolveEquation();

	void PrintEquation(std::ostream& printFile) {
		printFile << a << " " << b << " " << c << " ";
	}

	void PrintSolution(std::ostream& printFile);

	friend bool operator == (const QuadraticEquation& first, const QuadraticEquation& second) {
		return (abs(first.a - second.a) < pow(10, - ACCURACY) && abs(first.b - second.b) < pow(10, -ACCURACY) && abs(first.c - second.c) < pow(10, -ACCURACY));
	}
};

class Solution {
private:
	QuadraticEquation equation;
	EqRoots roots;

public:
	void ReadSolution(std::istream& readFile);

	void CreateSolution(QuadraticEquation* unsolvedEquation) {
		equation = *unsolvedEquation;
		roots = *unsolvedEquation->SolveEquation();
	}

	friend bool operator == (const Solution& first, const Solution& second);
};