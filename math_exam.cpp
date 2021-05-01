#include <iostream>
#include <fstream>
#include <iomanip>

#include "student.hpp"
#include "teacher.hpp"
#include "score_table.hpp"

int main() {
	std::ifstream studentsFile("students.txt");
	std::ofstream answerFileWrite("answers.txt");
	answerFileWrite << std::setprecision(ACCURACY) << std::fixed;

	while (!studentsFile.eof()) {
		std::ifstream taskFile("task.txt");
		std::string studentName;
		std::string studentType;
		studentsFile >> studentName >> studentType;
		Student* curStudent;
		if (studentType == "Bad")
			curStudent = new BadStudent(studentName);
		else if (studentType == "Good")
			curStudent = new GoodStudent(studentName);
		else if (studentType == "Medium")
			curStudent = new MediumStudent(studentName);
		else
			break;
		curStudent->SolveAllEquations(taskFile, answerFileWrite);
		delete curStudent;
		taskFile.close();
	}

	studentsFile.close();
	answerFileWrite.close();
	std::ifstream taskFile("task.txt");
	std::ifstream answerFileRead("answers.txt");
	std::ofstream scoreFile("score.txt");

	Teacher* teacher = new Teacher();
	ScoreTable* table = new ScoreTable();

	teacher->CheckStudentsAnswers(taskFile, answerFileRead, table);
	table->PrintScoreTable(scoreFile);

	taskFile.close();
	answerFileRead.close();
	scoreFile.close();
	delete teacher;
	delete table;
}