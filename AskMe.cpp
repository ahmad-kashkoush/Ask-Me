//
// Created by ahmed-kashkoush on 2/14/23.
//

#include "AskMe.h"

Ask::Ask() {

}

void Ask::Menu(int i) {// i==1?MenuLogin:MenuOfQuestions
    cout<<"Menu : \n";
    if(i==1){
        cout<<"          1.Login\n"
            <<"          2.Sign Up\n\n";

    }else{
        cout<<"          1.Print Questions To Me\n"
            <<"          2.Print Questions From Me\n"
            <<"          3.Answer Questions\n"
            <<"          4.Delete Questions\n"
            <<"          5.Ask Questions\n"
            <<"          6.List System Users\n"
            <<"          7.Feed\n"
            <<"          8.Logout\n\n";

    }
}

void Ask::Run() {
           int choice=0;
           Menu(1);
           while(choice!=1 and choice !=2) {
               cout<<"Enter choice [1-2] : ";
               cin >> choice;
               if (choice == 1)Login();
               else if (choice == 2)SignUp();
               else {
                   cout << "Invalid Choice\n";
               }
           }
           Menu(2);
           choice=0;
           while(choice!=8){
                cout<<"Enter Choice [1-8] : ";
                cin>>choice;
                if(choice==1)PrintToMe();
                else if(choice==2)PrintFromMe();
                else if(choice==3)AnswerQuestion();
                else if(choice==4)DeleteQuestion();
                else if(choice==5)AskQuestion();
                else if(choice==6)ListUsers();
                else if(choice==7)Feed();
                else if(choice==8)
                    cout<<"Loging Out ...\n";
                else    cout<<"Invalid Choice ... Try Again\n";

           }



}

void Ask::AskQuestion() {
    cout<<"Enter User Id or -1 to cancel: ";
    int id;cin>>id;
    int UserIndex=SearchId(id, Users);
    if(UserIndex==-1){
        cout<<"Invalid User Id...Try Again\n";
        return;
    }
    if(Users[UserIndex].GetAnonymous())
        cout<<"Note :Anonymous Questions Are not allowed for this user\n";

    cout<<"For Thread Question Enter Question Id or -1 For New Question :";
        cin>>id;
        Question k;
        k.Enter(usr.GetId(), Users[UserIndex].GetId());
        if(id==-1) {
            Questions.emplace_back(k);
            Users[UserIndex].AddQuestionToMe(k);
        } else{
            int QuestionIndex=SearchId(id, Questions);
            if(QuestionIndex==-1){
                cout<<"Invalid Id\n";
                return;
            }
            Questions[QuestionIndex].AddThread(k);
        }

}

void Ask::Login() {
    cout<<"Enter User Name and Password ";
    string name, password;
    for(int i=0;i<Users.size();i++){
        if(Users[i].IsEqual(name, password)){
            usr=Users[i];
            return;
        }
    }
    cout<<"Invalid User name and password ... Please Try Again\n";
}

void Ask::PrintFromMe() {
    usr.PrintQuestionsFromMe();
}

void Ask::PrintToMe() {
    usr.PrintQuestionsToMe();
}

void Ask::SignUp() {
        usr.Enter();
        Users.emplace_back(usr);
}

void Ask::AnswerQuestion() {
        cout<<"Enter Question id or -1 to cancel: ";
        int id; cin>>id;
        int QuestionIndex= SearchId(id, Questions);
        if(QuestionIndex==-1)
            cout<<"Invalid Question Id\n";
        else
            Questions[QuestionIndex].SetAnswer();
}

void Ask::ListUsers() {
        for(auto USSR:Users)
            USSR.Print();
}

void Ask::Feed() {

}

void Ask::DeleteQuestion() {
    cout<<"Enter Question id or -1 to cancel : ";
    int id; cin>>id;
    int QuestionIndex= SearchId(id, Questions);
    // Todo     Update it by enabliing to Delete Threads        []
    if(id==-1){
        cout<<"Invalid Question Id... Try Again\n";
        return;
    }
    swap(Questions[QuestionIndex], Questions.back());
    Questions.pop_back();
}

template<typename t1>
int Ask::SearchId(int id, vector<t1> t) {
        for(int i=0;i<t.size();i++){
            if(id==t[i].GetId())
                return i;
        }
        return -1;
}









// Users
User::User():id(0), AllowAnonymous(true) {}

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

void Question::SetAnswer() {
    if(GetAnswer().size()!=0)
        cout<<"Warning : Alread Answered, answer will be updated\n";
    cout<<"Enter Answer Text :";
    getline(cin, Answer);

}

pair<int, int> Question::GetFromToId() {
    return make_pair(FromId, ToId);
}

void Question::Enter(int From, int To) {
        cout<<"Enter Question Text: ";
         getline(cin, text);
         FromId=From, ToId=To;


}

void Question::PrintQuestion() {
    int From=GetFromToId().first;
    string Ft;
    if(From==-1)Ft=")  !AQ";
    else        Ft=")  From User ("+ to_string(From)+")";

    cout<<"Question Id ("<<GetId()<<Ft<<
        " To User("<<GetFromToId().second<<") :    "
        <<GetText()<<el;
    cout<<" Answer: "<<GetAnswer()<<el;
}
void Question::Print(){
    PrintQuestion();
    for(auto i:Threads) {
        cout<<"Thread :      ";
        i.PrintQuestion();
    }
}

string Question::GetText() {
    return text;
}

int Question::GetId() {
    return id;
}

string Question::GetAnswer() {
    return Answer;
}

void Question::AddThread(Question &Q) {
    Threads.emplace_back(Q);
}

Question::Question()
    :id(0),FromId(-1),ToId(-1), Answer("Not Answered Yet") {}


