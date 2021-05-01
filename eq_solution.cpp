#include <iostream>

#include "quadratic_equation.hpp"
#include "eq_solution.hpp"

void Solution::ReadSolution(std::istream& readFile) {
	std::string rootsNumber;
	equation.ReadEqCoeffs(readFile);

	readFile >> rootsNumber;
	if (rootsNumber == "NONE")
		roots.number = NONE;
	else if (rootsNumber == "ALL")
		roots.number = ALL;
	else if (rootsNumber == "ONE") {
		roots.number = ONE;
		readFile >> roots.x1;
	}
	else if (rootsNumber == "TWO") {
		roots.number = TWO;
		readFile >> roots.x1 >> roots.x2;
	}
}

void Solution::CreateSolution(QuadraticEquation* unsolvedEquation) {
	equation = *unsolvedEquation;
	roots = *unsolvedEquation->SolveEquation();
}

bool operator == (const Solution& first, const Solution& second) {
	if (first.equation == second.equation) {
		if (first.roots.number == NONE && second.roots.number == NONE)
			return true;
		else if (first.roots.number == ALL && second.roots.number == ALL)
			return true;
		else if (first.roots.number == ONE && second.roots.number == ONE && abs(first.roots.x1 - second.roots.x1) < pow(10, -ACCURACY))
			return true;
		else if (first.roots.number == TWO && second.roots.number == TWO && abs(first.roots.x1 - second.roots.x1) < pow(10, -ACCURACY) && abs(first.roots.x2 - second.roots.x2) < pow(10, -ACCURACY))
			return true;
		else
			return false;
	}
	else
		return false;
}