#include <iostream>
#include <fstream>
#include <list>
#include <iomanip>

#include "quadratic_equation.h"

class Student {
protected:
	std::string name;
	virtual void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {};

public:
	Student(std::string student_name) : name(student_name) {}
	void SolveAllEquations(std::istream& taskFile, std::ostream& answerFile) {
		while (!taskFile.eof())
			SolveOneEquation(taskFile, answerFile);
	};
};

class BadStudent : public Student {
public:
	BadStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
		QuadraticEquation currentEquation;
		currentEquation.ReadEqCoeffs(taskFile);
		currentEquation.PrintEquation(answerFile);
		answerFile << "ONE 0";
		answerFile << " " << name << std::endl;
	}
};

class GoodStudent : public Student {
public:
	GoodStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
		QuadraticEquation currentEquation;
		currentEquation.ReadEqCoeffs(taskFile);
		currentEquation.PrintEquation(answerFile);
		currentEquation.PrintSolution(answerFile);
		answerFile << " " << name << std::endl;
	}
};

class MediumStudent : public Student {
public:
	MediumStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {
		QuadraticEquation currentEquation;
		currentEquation.ReadEqCoeffs(taskFile);
		currentEquation.PrintEquation(answerFile);
		if(rand() % 3 == 0)
			answerFile << "ONE 0";
		else
			currentEquation.PrintSolution(answerFile);
		answerFile << " " << name << std::endl;
	}
};

class Teacher {
private:
	std::list<Solution> correctAnswers;

	using StudientScore = struct {
		std::string name;
		int score;
	};
	std::list<StudientScore> studentsScoreList;

	void GetCorrectEqAnswers(std::istream& taskFile) {
		while (!taskFile.eof()) {
			QuadraticEquation currentEquation;
			Solution answer;
			currentEquation.ReadEqCoeffs(taskFile);
			answer.CreateSolution(&currentEquation);
			correctAnswers.push_back(answer);
		}
	};

	void ChangeScore(int points, std::string name) {
		for (auto& curStudentScore : studentsScoreList) {
			if (curStudentScore.name == name) {
				curStudentScore.score += points;
				return;
			}
		}
		StudientScore newStudent;
		newStudent.name = name;
		newStudent.score = points;
		studentsScoreList.push_back(newStudent);
	}

public:
	void CheckStudentsAnswers(std::istream& taskFile, std::istream& answerFile) {
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
			ChangeScore(points, curStudentName);
		}
	}

	void PrintScoreTable(std::ostream& scoreFile) {
		scoreFile << "   student      score   " << std::endl;
		for (auto& curStudentScore : studentsScoreList)
			scoreFile << "    " << curStudentScore.name << "         " << curStudentScore.score << std::endl;
	}
};

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
	teacher->CheckStudentsAnswers(taskFile, answerFileRead);
	teacher->PrintScoreTable(scoreFile);

	taskFile.close();
	answerFileRead.close();
	scoreFile.close();
	delete teacher;
}