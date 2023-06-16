#include "Quiz.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "Candidate.h";

using namespace std;

Quiz::Quiz(string username, string password) {
    try
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Cannot connect to database! Error: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    con->setSchema("pytania");
}

void Quiz::start() {
    stmt = con->createStatement();

    string firstName, lastName;
    int level = 0;

    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;

    while (level != 1 && level != 2 && level != 3) {
        cout << "\nChoose your level:\n1. Junior\n2. Mid\n3. Senior\n";
        cin >> level;
    }

    AbstractCandidate* candidate;
    candidate = createCandidate(firstName, lastName, level);
    res = drawQuestionsForCandidate(candidate, res, stmt);
    displayQuestions(res);
    displayAndSaveResult(firstName, lastName, level);
}

sql::ResultSet* Quiz::drawQuestionsForCandidate(AbstractCandidate* candidate, sql::ResultSet* res, sql::Statement* stmt) {
     return candidate->drawQuestions(res, stmt);
}

void Quiz::displayAndSaveResult(string firstName, string lastName, int level) {
    cout << "\n************************\nResult: " << wynik << "/10" << "\n************************" << endl;
    try {
        pstmt = con->prepareStatement("INSERT INTO results(firstname,lastname,result,level) VALUES (?,?,?,?)");
        pstmt->setString(1, firstName);
        pstmt->setString(2, lastName);
        pstmt->setInt(3, wynik);
        pstmt->setInt(4, level);
        pstmt->execute();
    }
    catch (sql::SQLException e)
    {
        cout << "Cannot write record to database! Error: " << e.what() << endl;
        system("pause");
        exit(1);
    }
}

void Quiz::displayQuestions(sql::ResultSet* res) {
    string answer;
    while (res->next()) {
        cout << res->getString("question") << endl;
        cout << "a) " << res->getString("a") << endl;
        cout << "b) " << res->getString("b") << endl;
        cout << "c) " << res->getString("c") << endl;
        cout << "Choose valid answer!" << endl;
        cin >> answer;
        while (answer != "a" && answer != "b" && answer != "c") {
            cout << "Choose the valid answer between: a, b or c" << endl;
            cin >> answer;
        }
        if (answer == res->getString("answer")) {
            cout << "\nCorrect!\n\n";
            wynik++;
        }
        else {
            cout << "\nWrong!\n";
            cout << "Correct answer: " << res->getString("answer") << ")\n" << endl;
        }
    }
}

AbstractCandidate* Quiz::createCandidate(string firstName, string lastName, int level) {
    if (level == 1) {
        JuniorCandidate j(firstName, lastName);
        return &j;
    }
    else if (level == 2) {
        MidCandidate j(firstName, lastName);
        return &j;
    }
    else if (level == 3) {
        SeniorCandidate j(firstName, lastName);
        return &j;
    }
}

void Quiz::displayHallOfFame() {
    int choice = 0;

    while (choice != 1 && choice != 2 && choice != 3) {
        cout << "\n\n -----------\t CHOOSE LEVEL \t-----------\n\n" << endl;
        cout << "\t1.Junior\n\t2.Mid\n\t3.Senior\n";
        cin >> choice;
    }
    stmt = con->createStatement();
    try {
       res = stmt->executeQuery("SELECT firstName, lastName, result, level FROM results WHERE level=" + to_string(choice) + " ORDER BY result DESC");
    }
    catch (sql::SQLException e)
    {
        cout << "Cannot read the hall of fame from database! Error: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    int i = 1;
    cout << "\n\n -----------\t HALL OF FAME \t-----------\n\n" << endl;
    while (res->next()) {
        cout << i << ") " << res->getString("firstName") << " ";
        cout << res->getString("lastName");
        cout << " -----------\t\t" << res->getInt("result") << endl;
        i++;
    }
}

Quiz::~Quiz() {
    delete stmt;
    delete pstmt;
    delete res;
    delete con;
}