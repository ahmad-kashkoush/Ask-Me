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
    bool Anynomous{};

public:
    //! Still Didn't Add Print From and print to functionalities
    Question(const string&);
    Question();
    void PrintTo() const;
    void PrintFrom() const;
    void PrintFeedQuestion();
    void Enter(int ,int);
   const string &ToString()const;
    //Getters
    const string &GetText()const;
    const string &GetAnswer()const;
    const int &GetId()const;
    int GetParentId()const;
    pair<int, int> &GetFromToId()const;
    //Setters
    void SetText(const string&);
    void SetAnswer();
    void SetId(int);
    void SetParentId(int);
    void SetFromToId(int ,int);


};
class User{
private:
    string name, password, email, username;
    int id;
    bool AllowAnonymous;// 0 or 1 and initialized with -1
    vector<int> QIdFrom;
    map<int, vector<int>> ToQuestionThreads;

public:
    User(const string&);
    User();
    bool IsEqual(const string&, const string&) const;
    void Print()const;
    const string &ToString()const;
    void Enter();
    void ResetQuestionsFromMe(const vector<int> &);
    void ResetQuestionsToMe(const vector<pair<int, int>> &);
    /*Getters*/
   const string& GetName()const;
   const string& GetPassword()const;
   const string& GetEmail()const;
   const string& GetUsername()const;
    int  GetId()const;
    bool GetAnonymous()const;
    const vector<int> & GetQuestionsIdFromMe()const;
    const map<int, vector<int>> & GetIdToThread()const;
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