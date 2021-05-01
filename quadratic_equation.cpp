#include <iostream>
#include "quadratic_equation.hpp"

double QuadraticEquation::Discriminant() {
	return (b * b - 4.0 * a * c);
}

void QuadraticEquation::ReadEqCoeffs(std::istream& readFile) {
	readFile >> a >> b >> c;
}

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

void QuadraticEquation::PrintEquation(std::ostream& printFile) {
	printFile << a << " " << b << " " << c << " ";
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

bool operator == (const QuadraticEquation& first, const QuadraticEquation& second) {
	return (abs(first.a - second.a) < pow(10, -ACCURACY) && abs(first.b - second.b) < pow(10, -ACCURACY) && abs(first.c - second.c) < pow(10, -ACCURACY));
}