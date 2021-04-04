#include <iostream>

#include "quadratic_equation.h"

enum RootsNum {
	NONE,
	ONE,
	TWO,
	ALL
} RootsNum;

EqRoots* QuadraticEquation::SolveEquation() {
	EqRoots* roots = new EqRoots;
	if (a == 0) {
		if (b == 0 && c == 0)
			roots->number = ALL;
		else if (b == 0 && c != 0)
			roots->number = NONE;
		else {
			roots->number = ONE;
			roots->x1 = -c / b;
		}
	}
	else {
		double d = Discriminant();
		if (d < 0)
			roots->number = NONE;
		else if (d == 0) {
			roots->number = ONE;
			roots->x1 = -b / (2.0 * a);
		}
		else {
			double firstRoot = (-b + sqrt(d)) / (2.0 * a);
			double secondRoot = (-b - sqrt(d)) / (2.0 * a);
			roots->number = TWO;
			if (firstRoot < secondRoot) {
				roots->x1 = firstRoot;
				roots->x2 = secondRoot;
			}
			else {
				roots->x2 = firstRoot;
				roots->x1 = secondRoot;
			}
		}
	}
	return roots;
}

void QuadraticEquation::PrintSolution(std::ostream& printFile) {
	EqRoots* roots = SolveEquation();
	switch (roots->number)
	{
	case NONE:
		printFile << "NONE";
		break;
	case ONE:
		printFile << "ONE "<< roots->x1;
		break;
	case TWO:
		printFile << "TWO " << roots->x1 << " " << roots->x2;
		break;
	case ALL:
		printFile << "ALL";
		break;
	default:
		break;
	}
}

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