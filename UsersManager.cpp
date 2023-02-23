#include "AskMe.h"
User::User():id(-1), AllowAnonymous(true) {}


bool User::IsEqual(const string &Name, const string &Password) const {
    return Name==GetUsername() and Password==GetPassword();
}

void User::Enter(const string&usrName, int usrId) {
    SetId(usrId);
    SetUsername(usrName);
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
void User::SetName(const string &a){
    name=a;
}
void User::SetPassword(const string &a){
    password=a ;
}
void User::SetEmail(const string &a){
                email=a;
}
void User::SetUsername(const string &a){
    username=a;
}
void User:: SetId(int a ){
        id=a;
}
void User::SetAnonymous(bool a){
    AllowAnonymous=a;
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
        if(!Line.empty()) {
            id = stoi(v[0]);
            username = v[1];
            password = v[2];
            name = v[3];
            email = v[4];
            AllowAnonymous = stoi(v[5]);
        }
}

  string User::ToString() const {
    ostringstream oss;
    oss <<GetId()
        <<","<<GetUsername()<<","<<GetPassword()<<","<<GetName()<<","
        <<GetEmail()<<","<<GetAnonymous();
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

void User::ClearQuestions() {
    QIdFrom.clear();
    ToQuestionThreads.clear();
}

void User::AddToQuestionToMe(int qParentId, int qId) {
    ToQuestionThreads[qParentId].emplace_back(qId);
}

void User::AddToQuestionsFromMe(int qId) {
    QIdFrom.emplace_back(qId);
}


void UsersManager::AccessSystem(){
    int choice= ShowMenu({"Login", "SignUp"});
    if(choice==1)
        Login();
    else
        SignUp();
    QuestionsManager q;
    q.FillUserQuestion(cur);
}

void UsersManager::Login() {
    LoadDatabase();
    while(1) {
        cout << "Enter User Name and Password: ";
        string name, password;
        cin >> name >> password;
        if(!NameToUserObject.count(name))
            cout<<"Wrong Password or name...Try Again\n";
        else{
            cur=NameToUserObject[name];
            if(!cur.IsEqual(name, password))
                cout<<"Wrong Password or name...Try Again\n";
            else
                break;



        }

    }

}

void UsersManager::LoadDatabase() {
         NameToUserObject.clear();
         vector<string> Lines= ReadFile("../users.txt");
         for(auto &Line:Lines){
             if(Line.empty())continue;
             User tmp=User(Line);
             NameToUserObject[tmp.GetUsername()]=tmp;
             Last=max(Last, tmp.GetId());
         }
         
}

void UsersManager::SignUp() {
    string username;
   cout<<"Enter User Name (no spaces): ";
   cin>>username;
   if(NameToUserObject.count(username)){
       cout<<"username exist... try again\n";
       SignUp();
   }

   cur.Enter(username, ++Last);
   NameToUserObject[cur.GetUsername()]=cur;
   UpdateDatabase(cur);
}

void UsersManager::UpdateDatabase(const User &usr) const{
    string line= usr.ToString();
    vector<string> v;
    v.emplace_back(line);
    WriteFileLines("../users.txt", v);
}

void UsersManager::ListNamesIds() const{
        for(auto [UserName, Usr]:NameToUserObject)
            cout<<"ID: "<<Usr.GetId()<<"\tName: "<<Usr.GetName()<<el;

}

void UsersManager::ResetQuestionsFromMe(const vector<int> &FromMe) {
    cur.ResetQuestionsFromMe(FromMe);
}

void UsersManager::ResetQuestionsToMe(const vector<pair<int, int>> &ToMe) {
    cur.ResetQuestionsToMe(ToMe);
}

pair<int, int> UsersManager::ReadUserId()const {

    cout << "Enter User Id or -1 to cancel\n";
    int id;
    cin >> id;
    if (id == -1)
        return make_pair(-1, -1);
    for (auto &[UserName, usr]: NameToUserObject) {
        if (usr.GetId() == id)
            return make_pair(id, usr.GetAnonymous());
    }
    cout << "Invalid User Id ... Try Again\n";
    return ReadUserId();
}

User UsersManager::GetCurrentUser() {
    return cur;
}

