#pragma once

#include "quadratic_equation.hpp"

class Student {
protected:
	std::string name;
	virtual void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile) {};

public:
	Student(std::string student_name) : name(student_name) {}
	void SolveAllEquations(std::istream& taskFile, std::ostream& answerFile);
};

class BadStudent : public Student {
public:
	BadStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile);
};

class GoodStudent : public Student {
public:
	GoodStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile);
};

class MediumStudent : public Student {
public:
	MediumStudent(std::string student_name) : Student(student_name) {}

private:
	void SolveOneEquation(std::istream& taskFile, std::ostream& answerFile);
};