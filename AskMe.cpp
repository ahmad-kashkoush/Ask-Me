//
// Created by ahmed-kashkoush on 2/14/23.
//

#include "AskMe.h"
Ask::Ask() {
    Questions=ReadFile("questions.txt");
    Users=ReadFile("users.txt");
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

int Ask::Login() {
    cout<<"Enter User Name and Password ";
    string name, password;
    cin>>name>>password;
    for(int i=0;i<Users.size();i++){
        if(Users[i].IsEqual(name, password)){
            usr=Users[i];
            return 0;
        }
    }
    cout<<"Invalid User name and password ... Please Try Again\n";
    return -1;
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

vector<string> ReadFile(string file){
    ifstream fin(file);
    fstream Details(file.c_str());
    vector<string> Lines;
    if(Details.fail()){
        cout<<"\nError : Can't Open File\n";
        return Lines;
    }
    string line;
    while(getline(Details, line)){
        while(line.size()==0)
            continue;
        Lines.emplace_back(line);
    }
    Details.close();
    return Lines;

}

vector<string> Split(string line, string Delimeter) {
    vector<string> Details;
    int pos=0;
    line+=Delimeter;
    while((pos=line.find(Delimeter))!=-1){
        string tmp=line.substr(0, pos);
        line.erase(0, pos+(int)Delimeter.size());
        Details.emplace_back(tmp);
    }
    return Details;
}


