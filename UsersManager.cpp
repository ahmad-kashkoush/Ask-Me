#include "AskMe.h"
User::User():id(-1), AllowAnonymous(true) {}

void User::AddQuestionFromMe(Question q) {
    QFrom.emplace_back(q);
}
void User::AddQuestionToMe(Question q) {
    QTo.emplace_back(q);
}

bool User::IsEqual(string name, string Password) {
    return name==GetName() and Password==GetPassword();
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

string User::GetName() {
    return name;
}

string User::GetPassword() {
    return password;
}

string User::GetEmail() {
    return email;
}

string User::GetUsername() {
    return username;
}

int User::GetId() {
    return id;
}

bool User::GetAnonymous() {
    return AllowAnonymous;
}

void User::Print() {
    cout<<"ID: "<<GetId()<<"         Name: "<<GetName()<<el;
}

void User::PrintQuestionsFromMe() {
    for(auto i:QFrom)
        i.Print();

}

void User::PrintQuestionsToMe() {
    for(auto i:QTo)
        i.Print();
}

User::User(string Line) {
        vector<string> v=Split(Line, string(","));
        id=stoi(v[0]);
        username=v[1];
        password=v[2];
        name=v[3];
        email=v[4];
        AllowAnonymous=stoi(v[5]);
}

string User::ToString() {
    ostringstream oss;
    oss <<GetId()
        <<","<<GetUsername()<<","<<GetName()<<", "<<GetPassword()
        <<GetEmail()<<GetAnonymous();
    return oss.str();
}