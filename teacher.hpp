#pragma once

#include <list>
#include "quadratic_equation.hpp"
#include "eq_solution.hpp"
#include "score_table.hpp"


class Teacher {
private:
	std::list<Solution> correctAnswers;
	void GetCorrectEqAnswers(std::istream& taskFile);

public:
	void CheckStudentsAnswers(std::istream& taskFile, std::istream& answerFile, ScoreTable* table);
};
