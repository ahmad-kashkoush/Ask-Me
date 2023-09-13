//
// Created by ahmed-kashkoush on 3/1/23.
//

#ifndef ASK_ME_USERMANAGER_H
#define ASK_ME_USERMANAGER_H
#include "Macros.h"
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


#endif //ASK_ME_USERMANAGER_H
