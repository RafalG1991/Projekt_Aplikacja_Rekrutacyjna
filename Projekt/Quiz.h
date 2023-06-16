#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "Candidate.h";

using namespace std;

class Quiz {
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
	int wynik;
	sql::ResultSet* drawQuestionsForCandidate(AbstractCandidate* candidate, sql::ResultSet* res, sql::Statement* stmt);
	void displayQuestions(sql::ResultSet* res);
	void displayAndSaveResult(string firstName, string lastName, int level);
	AbstractCandidate* createCandidate(string firstName, string lastName, int level);
public:
	Quiz(string username, string password);
	void start();
	void displayHallOfFame();
	~Quiz();
};

