#include <iostream>
#include "teacher.hpp"

void Teacher::GetCorrectEqAnswers(std::istream& taskFile) {
	while (!taskFile.eof()) {
		QuadraticEquation currentEquation;
		Solution answer;
		currentEquation.ReadEqCoeffs(taskFile);
		answer.CreateSolution(&currentEquation);
		correctAnswers.push_back(answer);
	}
};

void Teacher::CheckStudentsAnswers(std::istream& taskFile, std::istream& answerFile, ScoreTable* table) {
	std::string curStudentName;
	Solution curStudentSolution;
	int points;
	GetCorrectEqAnswers(taskFile);
	while (!answerFile.eof()) {
		points = 0;
		curStudentSolution.ReadSolution(answerFile);
		answerFile >> curStudentName;
		for (auto& curCorrectSolution : correctAnswers)
			if (curCorrectSolution == curStudentSolution) {
				points++;
				break;
			}
		table->ChangeScore(points, curStudentName);
	}
}