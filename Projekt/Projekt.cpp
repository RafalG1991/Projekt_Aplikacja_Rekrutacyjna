#include <stdlib.h>
#include <iostream>
#include <string>

#include "Quiz.h";
#include "Candidate.h";

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3) {
        cout << "Run app with two arguments: username and password to database!\n\n";
        system("pause");
        return 0;
    }

    Quiz q(argv[1], argv[2]);
    int choice=0;

    while (choice != 1 && choice != 2) {
        cout << "\t**************************\n\t********** MENU **********\n\t**************************" << endl;
        cout << "\t1.Start Quiz\n\t2.Display Hall of Fame\n\tChoose option:\n";
        cin >> choice;
    }
    switch (choice) {
    case 1:
        q.start();
        break;
    case 2:
        q.displayHallOfFame();
        break;
    }

    system("pause");
    return 0;
}

