#pragma once

class Solution {
private:
	QuadraticEquation equation;
	EqRoots roots;

public:
	void ReadSolution(std::istream& readFile);
	void CreateSolution(QuadraticEquation* unsolvedEquation);
	friend bool operator == (const Solution& first, const Solution& second);
};