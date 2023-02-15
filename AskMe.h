//
// Created by ahmed-kashkoush on 2/14/23.
//

#ifndef ASK_ME_ASKME_H
#define ASK_ME_ASKME_H
#include<bits/stdc++.h>
typedef long long ll;
#define el "\n"
using namespace std;
class Question{
private:
    string Q, Answer;
public:
    Question();
    void Enter();

};
class User{
private:
    string name, password, email;
    int id;
    bool AllowAnonymous;
    vector<Question> QFrom;
    vector<Question> QTo;
public:
    User();
    void AddQuestionFromMe(Question);
    void AddQuestionToMe(Question);
    void PrintQuestionsFromMe();
    void PrintQuestionsToMe();
    bool IsEqual(string, string);

};
class Ask{
private:
    User usr;
    vector<User> Users;
    vector<Question> Questions;
    map<Question, vector<Question>> Thread;
    void Menu(int);
    void Login();
    void SignUp();
    void AskQ();//Done
    template<typename t1>
    int SearchId(int id, vector<t1>);
    void PrintFromMe();
    void PrintToMe();
public:
    Ask();
    void Run();

};

#endif //ASK_ME_ASKME_H
