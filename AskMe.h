//
// Created by ahmed-kashkoush on 2/14/23.
//

#ifndef ASK_ME_ASKME_H
#define ASK_ME_ASKME_H
#include<bits/stdc++.h>
typedef long long ll;
#define el "\n"
using namespace std;
vector<string> ReadFile(string);
vector<string> Split(string, string);
/*
 * Question->[id, text, Answer, From, to, parent_id]
 * */
class Question{
private:
    string text, Answer;
    int id;
    int FromId, ToId;
    int ParentId;
    bool Anynomous;

public:
    //! Still Didn't Add Print From and print to functionalities
    Question(string);
    Question();
    void PrintFeedQuestion();
    void Enter(int ,int);
    string ToString();
    //Getters
    string GetText();
    string GetAnswer();
    int GetId();
    void SetAnswer();
    int GetParentId();
    pair<int, int> GetFromToId();


};
class QuestionsManager{
    /*Job
     * 1. Upload Questions From Questions.txt
     * 2. Write New Questions On Questions.txt
     * 3. Print Questions*/
private:
    map<int, vector<Question>> Questions;
public:
    QuestionsManager();
    void Print();

};
class User{
private:
    string name, password, email, username;
    int id;
    bool AllowAnonymous;// 0 or 1 and initialized with -1
    vector<int> QIdFrom;

public:
    User(string);
    User();
    void AddQuestionFromMe(Question);
    void AddQuestionToMe(Question);
    void PrintQuestionsFromMe();
    void PrintQuestionsToMe();
    bool IsEqual(string, string);
    void Print();
    string ToString();
    void Enter();
    /*Getters*/
    string GetName();
    string GetPassword();
    string GetEmail();
    string GetUsername();
    int  GetId();
    bool GetAnonymous();
};
class Ask{
private:
    User usr;
    vector<User> Users;
    vector<Question> Questions;
    void Menu(int);
    int Login();
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
