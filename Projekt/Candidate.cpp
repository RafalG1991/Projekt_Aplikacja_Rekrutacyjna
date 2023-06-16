#include "Candidate.h"


sql::ResultSet* AbstractCandidate::drawQuestions(sql::ResultSet* res, sql::Statement* stmt) {
	return res;
};

JuniorCandidate::JuniorCandidate(string firstName, string lastName) : firstName(firstName), lastName(lastName) {};

sql::ResultSet* JuniorCandidate::drawQuestions(sql::ResultSet* res, sql::Statement* stmt) {
	try {
		res = stmt->executeQuery("SELECT id, question, a, b, c, answer FROM junior ORDER BY RAND() LIMIT 10");
	}
	catch (sql::SQLException e) {
		cout << "Cannot read from database! Error: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	return res;
}


MidCandidate::MidCandidate(string firstName, string lastName) : firstName(firstName), lastName(lastName) {};

sql::ResultSet* MidCandidate::drawQuestions(sql::ResultSet* res, sql::Statement* stmt) {
	try {
		res = stmt->executeQuery("SELECT id, question, a, b, c, answer FROM mid ORDER BY RAND() LIMIT 10");
	}
	catch (sql::SQLException e) {
		cout << "Cannot read from database! Error: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	return res;
}

SeniorCandidate::SeniorCandidate(string firstName, string lastName) : firstName(firstName), lastName(lastName) {};

sql::ResultSet* SeniorCandidate::drawQuestions(sql::ResultSet* res, sql::Statement* stmt) {
	try {
		res = stmt->executeQuery("SELECT id, question, a, b, c, answer FROM senior ORDER BY RAND() LIMIT 10");
	}
	catch (sql::SQLException e) {
		cout << "Cannot read from database! Error: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	return res;
}