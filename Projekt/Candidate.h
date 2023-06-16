#pragma once
#include <string>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class AbstractCandidate {
public:
	virtual sql::ResultSet* drawQuestions(sql::ResultSet* res, sql::Statement* stmt) = 0;
};

class JuniorCandidate : public AbstractCandidate {
	string firstName;
	string lastName;
public:
	JuniorCandidate(string firstName, string lastName);
	sql::ResultSet* drawQuestions(sql::ResultSet* res, sql::Statement* stmt);
};

class MidCandidate : public AbstractCandidate {
	string firstName;
	string lastName;
public:
	MidCandidate(string firstName, string lastName);
	sql::ResultSet* drawQuestions(sql::ResultSet* res, sql::Statement* stmt);
};

class SeniorCandidate : public AbstractCandidate {
	string firstName;
	string lastName;
public:
	SeniorCandidate(string firstName, string lastName);
	sql::ResultSet* drawQuestions(sql::ResultSet* res, sql::Statement* stmt);
};

