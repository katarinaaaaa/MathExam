#pragma once

#include <list>
#include <iostream>

class ScoreTable {
private:
	using StudientScore = struct {
		std::string name;
		int score;
	};
	std::list<StudientScore> studentsScoreList;
public:
	void ChangeScore(int points, std::string name);
	void PrintScoreTable(std::ostream& scoreFile);
};