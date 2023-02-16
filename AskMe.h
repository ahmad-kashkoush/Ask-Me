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
    string text, Answer;
    int id;
    int FromId, ToId;
    vector<Question> Threads;
    void PrintQuestion();
public:
    Question();
    string GetText();
    string GetAnswer();
    int GetId();
    void SetAnswer();
    pair<int, int> GetFromToId();
    void Print();
    void Enter(int ,int);
    void AddThread(Question &);




};
class User{
private:
    string name, password, email, username;
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
    void Enter();
    string GetName();
    string GetPassword();
    string GetEmail();
    string GetUsername();
    int  GetId();
    bool GetAnonymous();
    void Print();

};
class Ask{
private:
    User usr;
    vector<User> Users;
    vector<Question> Questions;

    void Menu(int);
    void Login();
    void SignUp();
    void AskQuestion();//Done
    template<typename t1>
    int SearchId(int id, vector<t1>);
    void PrintFromMe();
    void PrintToMe();
    void AnswerQuestion();
    void DeleteQuestion();
    void  ListUsers();
    void Feed();
public:
    Ask();
    void Run();

};

#endif //ASK_ME_ASKME_H
