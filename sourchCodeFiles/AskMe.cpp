//
// Created by ahmed-kashkoush on 2/14/23.
//
#include "../HeaderFiles/AskMe.h"


void Ask::Run(){
    LoadDatabase(false);
    UU.AccessSystem();
    vector<string> Men;
    Men.emplace_back("Print Questions From Me");
    Men.emplace_back("Print Questions To Me");
    Men.emplace_back("Answer Questions");
    Men.emplace_back("Delete Questions");
    Men.emplace_back("Ask Questions");
    Men.emplace_back("List System Users");
    Men.emplace_back("Feed");
    Men.emplace_back("Logout");
    while(true){
        int choice=ShowMenu(Men);
        LoadDatabase(true);
        if(choice==1)QQ.PrintFromQuestion(UU.GetCurrentUser());
        else if(choice==2)QQ.PrintToQuestions(UU.GetCurrentUser());
        else if(choice==3){
            QQ.AnswerQuestion(UU.GetCurrentUser());
            QQ.UpdateDatabase();
        }
        else if(choice==4){
            const User &u=UU.GetCurrentUser();
            QQ.DeleteQuestion(u);
            UU.ResetQuestionsToMe(QQ.GetFromUserQuestion(u));
            UU.ResetQuestionsFromMe(QQ.GetToUserQuestion(u));
            QQ.UpdateDatabase();
        }
        else if(choice==5){
            // To Ask Question You need to know [id,status]
            auto [id, status]=UU.ReadUserId();
            if(id!=-1){
                QQ.AskQuestion(UU.GetCurrentUser(), make_pair(id, status));
                QQ.UpdateDatabase();
            }
        }
        else if(choice==6)UU.ListNamesIds();
        else if(choice==7)QQ.ListFeeds();
        else if(choice==8)break;

    }
    Run();

}

void Ask::LoadDatabase(bool FillUser) {
    UU.LoadDatabase();
    QQ.LoadDatabase();
    if(FillUser){
        const User &u=UU.GetCurrentUser();
        UU.ResetQuestionsToMe(QQ.GetFromUserQuestion(u));
        UU.ResetQuestionsFromMe(QQ.GetToUserQuestion(u));
    }

}

Ask::Ask() {}
