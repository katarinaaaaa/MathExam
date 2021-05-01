#include "score_table.hpp"

void ScoreTable::PrintScoreTable(std::ostream& scoreFile) {
	scoreFile << "   student      score   " << std::endl;
	for (auto& curStudentScore : studentsScoreList)
		scoreFile << "    " << curStudentScore.name << "         " << curStudentScore.score << std::endl;
}

void ScoreTable::ChangeScore(int points, std::string name) {
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