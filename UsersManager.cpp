#include "AskMe.h"
User::User():id(-1), AllowAnonymous(true) {}


bool User::IsEqual(const string &Name, const string &Password) const {
    return Name==GetName() and Password==GetPassword();
}

void User::Enter() {
    cout<<"Enter Id (not negative) :";
    cin>>id;
    cout<<"Enter User Name (No Spaces) :";
    cin>>username;
    cout<<"Enter Password :";
    cin>>password;
    cout<<"Enter Name :";
    cin>>name;
    cout<<"Enter email :";
    cin>>email;
    cout<<"Allow Anonymous Questions [1 or 0] :";
    cin>>AllowAnonymous;
}

const string &User::GetName()const  {
    return name;
}

const string &User::GetPassword() const {
    return password;
}

const string & User::GetEmail()const {
    return email;
}

const string & User::GetUsername()const {
    return username;
}

int User::GetId()const {
    return id;
}

bool User::GetAnonymous()const {
    return AllowAnonymous;
}
const vector<int> &User::GetQuestionsIdFromMe() const {
    return QIdFrom;
}

const map<int, vector<int>> &User::GetIdToThread() const {
    return ToQuestionThreads;
}

void User::Print() const{
    cout<<"ID: "<<GetId()<<"         Name: "<<GetName()<<el;
}



User::User(const string &Line) {
        vector<string> v=Split(Line, string(","));
        id=stoi(v[0]);
        username=v[1];
        password=v[2];
        name=v[3];
        email=v[4];
        AllowAnonymous=stoi(v[5]);
}

const string &User::ToString() const{
    ostringstream oss;
    oss <<GetId()
        <<","<<GetUsername()<<","<<GetName()<<", "<<GetPassword()
        <<GetEmail()<<GetAnonymous();
    return oss.str();
}

void User::ResetQuestionsFromMe(const vector<int> &NewFrom) {
            QIdFrom.clear();
            for(auto idd:NewFrom)
                QIdFrom.emplace_back(idd);
}

void User::ResetQuestionsToMe(const vector<pair<int, int>> &NewTo) {
        // in pair we have<parentId, Thread>
        ToQuestionThreads.clear();
        for(auto &[ParentId, ThreadId]:NewTo)
            ToQuestionThreads[ParentId].emplace_back(ThreadId);
}

