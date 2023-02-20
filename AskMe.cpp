//
// Created by ahmed-kashkoush on 2/14/23.
//
#include "AskMe.h"
Ask::Ask() {
    Questions=ReadFile("questions.txt");
    Users=ReadFile("users.txt");
}

const vector<string> &Ask::Menu()const {// i==1?MenuLogin:MenuOfQuestions
    vector<string> Men;
     Men.emplace_back("Print Questions To Me");
     Men.emplace_back("Print Questions From Me");
     Men.emplace_back("Answer Questions");
     Men.emplace_back("Delete Questions");
     Men.emplace_back("Ask Questions");
     Men.emplace_back("List System Users");
     Men.emplace_back("Feed");
     Men.emplace_back("Logout");
     return Men;
}

void Ask::Run() {
           int choice=0;
           Menu(1);
           int x=-1;
           while((choice!=1 and choice !=2)||x==-1) {
               cout<<"Enter choice [1-2] : ";
               cin >> choice;
                x=0;
               if (choice == 1)x=Login();
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


