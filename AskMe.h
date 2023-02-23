//
// Created by ahmed-kashkoush on 2/14/23.
//

#ifndef ASK_ME_ASKME_H
#define ASK_ME_ASKME_H
#include<bits/stdc++.h>
typedef long long ll;
#define el "\n"
#define stoi   ToInt
using namespace std;
vector<string> ReadFile(string);
vector<string> Split(string, string);
void WriteFileLines(const string &, const vector<string> &, bool append=true);
int MenuSides(int , int);
int ShowMenu(const vector<string> &);
int ToInt(const string &);


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
   string ToString() const;
    //Getters
    const string &GetText()const;
    const string &GetAnswer()const;
    bool GetAnynomous()const;
    int GetId()const;
    int GetParentId()const;
    pair<int, int> GetFromToId()const;
    //Setters
    void SetText(const string&);
    void SetAnswer(const string &);
    void SetId(int);
    void SetParentId(int);
    void SetFromToId(int ,int);
    void SetAnynomous(int );


};
class QuestionManager;
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
    string ToString() const;
    void Enter(const string &, int);
    void ResetQuestionsFromMe(const vector<int> &);
    void ResetQuestionsToMe(const vector<pair<int, int>> &);
    void ClearQuestions();
    void AddToQuestionsFromMe(int);
    void AddToQuestionToMe(int ,int);
    /*Getters*/
   const string& GetName()const;
   const string& GetPassword()const;
   const string& GetEmail()const;
   const string& GetUsername()const;
   bool GetAnonymous()const ;
   int  GetId()const;
   const vector<int> & GetQuestionsIdFromMe()const;
   const map<int, vector<int>> & GetIdToThread()const;
   void SetName(const string &);
   void SetPassword(const string &);
   void SetEmail(const string &);
   void SetUsername(const string &);
   void  SetId(int );
   void SetAnonymous(bool);
};
class UsersManager{
private:
    User cur;
    int Last;
    map<string, User> NameToUserObject;
    
public:
    UsersManager():Last(0){};
    void LoadDatabase();
    void Login();
    void SignUp();
    void AccessSystem();
    void UpdateDatabase(const User &)const;
    void ListNamesIds()const;
    void ResetQuestionsFromMe(const vector<int> &);
    void ResetQuestionsToMe(const vector<pair<int, int>> &);
    pair<int, int> ReadUserId()const;
    //Getters
     User GetCurrentUser();


};
class QuestionsManager{
private:
    int last;
    map<int, vector<int>> QIdToThreads;
    map<int, Question> IdToQuestion;
public:
    QuestionsManager();
    void LoadDatabase();
    void FillUserQuestion( User&);
    void PrintToQuestions(const User &)const;
    void PrintFromQuestion(const User &)const;
    int ReadQuestionIdAny(const User &)const;
    int ReadQuestionIdThread(const User &)const;
    void UpdateDatabase();
    void AnswerQuestion(const User &);
    void DeleteQuestion(const User &);
    void AskQuestion(const User &, pair<int, int>);
    void ListFeeds();
    // Getters
    vector<int> GetToUserQuestion(const User &);
    vector<pair<int, int>> GetFromUserQuestion(const User &);//Get Question From this user

};
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