//
// Created by ahmed-kashkoush on 2/14/23.
//

#ifndef ASK_ME_ASKME_H
#define ASK_ME_ASKME_H
#include "UserManager.h"
#include "QuestionManager.h"
#include "Macros.h"
vector<string> ReadFile(string);
vector<string> Split(string, string);
void WriteFileLines(const string &, const vector<string> &, bool append=true);
int MenuSides(int , int);
int ShowMenu(const vector<string> &);
int ToInt(const string &);

class Ask{
private:
    UsersManager    UU;
    QuestionsManager QQ;

public:
    Ask();
    void LoadDatabase(bool FillUser=true);
    void Run();
};
#endif //ASK_ME_ASKME_H
/*
 ?What I've Done
 1. [Adiminstrator-Question-User]
 2. implementation of simple features
 3. Run--> menu[choice[function]]
 4.Github
 5.parllel sesssion
 6. Reading from files
 ?What Are My Mistakes
 1. Questions Manager, Usersmanager
 !2. Abstraction [Graph Theory]
    2.2 vector<int id> Q
    2.3 map<int, vector<int>>
 3. Agile
    3.1 classes initial version-->





 *
 * */