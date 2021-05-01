#include <iostream>
#include "student.hpp"

void Student::SolveAllEquations(std::istream& taskFile, std::ostream& answerFile) {
	while (!taskFile.eof())
		SolveOneEquation(taskFile, answerFile);
};

void BadStudent::SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
	QuadraticEquation currentEquation;
	currentEquation.ReadEqCoeffs(taskFile);
	currentEquation.PrintEquation(answerFile);
	answerFile << "ONE 0";
	answerFile << " " << name << std::endl;
}

void GoodStudent::SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
	QuadraticEquation currentEquation;
	currentEquation.ReadEqCoeffs(taskFile);
	currentEquation.PrintEquation(answerFile);
	currentEquation.PrintSolution(answerFile);
	answerFile << " " << name << std::endl;
}

void MediumStudent::SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
	QuadraticEquation currentEquation;
	currentEquation.ReadEqCoeffs(taskFile);
	currentEquation.PrintEquation(answerFile);
	if (rand() % 3 == 0)
		answerFile << "ONE 0";
	else
		currentEquation.PrintSolution(answerFile);
	answerFile << " " << name << std::endl;
}