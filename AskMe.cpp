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
                else if(choice==3)AnswerQ();
                else if(choice==4)DeleteQ();
                else if(choice==5)AskQ();
                else if(choice==6)ListUsers();
                else if(choice==7)Feed();
                else if(choice==8)
                    cout<<"Loging Out ...\n";
                else    cout<<"Invalid Choice ... Try Again\n";

           }



}

void Ask::AskQ() {
        cout<<"Enter User id or -1 to cancel :";
        int id; cin>>id;
        int UserIndex=SearchId(id, Users);
        if(UserIndex==-1){
            cout<<"Invalid User Id\n";
            return;
        }
        if(Users[UserIndex].AllowAnonymous())
            cout<<"Note :Anonymous Questions Are not allowed for this user\n";

        cout<<"For Thread Question Enter Question Id or -1 For New Question :";
        cin>>id;
        Question k;
        k.Enter();
        if(id==-1) {
            Questions.emplace_back(k);
            Users[UserIndex].AddQuestion(k);
        } else{
            int QuestionIndex=SearchId(id, Questions);
            if(QuestionIndex==-1){
                cout<<"Invalid Id\n";
                return;
            }
            Users[UserIndex].AddQuestion(k);
            Thread[Questions[QuestionIndex]].emplace_back(k);
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

template<typename t1>
int Ask::SearchId(int id, vector<t1> t) {
        for(int i=0;i<t.size();i++){
            if(id==t[i].GetId())
                return i;
        }
        return -1;
}









// Users
User::User() {

}

void User::AddQuestionFromMe(Question q) {
    QFrom.emplace_back(q);
}
void User::AddQuestionToMe(Question q) {
    QTo.emplace_back(q);
}

bool User::IsEqual(string name, string Password) {
    return name==GetName() and Password==GetPassword();
}

