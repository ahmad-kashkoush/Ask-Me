#include "AskMe.h"
void Question::SetAnswer(const string &answer) {
    Answer=answer;

}

pair<int, int> Question::GetFromToId()const {
    return make_pair(FromId, ToId);
}

void Question::Enter(int From, int To) {
    cout<<"Enter Question Text: ";
    getline(cin, text);
    FromId=From, ToId=To;


}




const string &Question::GetText()const {
    return text;
}

 int Question::GetId()const {
    return id;
}

const string &Question::GetAnswer()const {
    return Answer;
}



int Question::GetParentId() const{
    return ParentId;
}

 string Question::ToString()const {
    ostringstream oss;
    oss <<GetId()
    <<","<<GetParentId()<<","<<GetFromToId().first<<","
    <<GetFromToId().second<<","<<GetAnynomous()<<","<<GetText()<<","<<GetAnswer();
    return oss.str();
}
Question::Question()
        :id(-1),FromId(-1),ToId(-1),ParentId(-1) {}

Question::Question(const string &line){
        vector<string> v= Split(line, string(","));
        assert((int)v.size()==7);
        SetId(ToInt(v[0]));
        SetParentId(ToInt(v[1]));
        SetFromToId(ToInt(v[2]), ToInt(v[3]));
        SetAnynomous(ToInt(v[4]));
        SetText(v[5]);
        SetAnswer(v[6]);
}


void Question::PrintTo() const {
    if(GetParentId()!=-1)
        cout<<"\tThread :   ";
    if(!Anynomous)
        cout<<"From User Id ("<<GetFromToId().first<<")";
    cout<<"\t Question: ("<<GetId()<<"):"<<GetText()<<el;
    if(!GetAnswer().empty())cout<<"\t\t Answer: "<<GetAnswer()<<el;
}

void Question::PrintFrom() const {
        cout<<"Question Id ("<<GetId()<<") ";
        if(!Anynomous)cout<<"!AQ ";
        cout<<"To User Id ("<<GetFromToId().second;
        cout<<"\t Question ("<<GetId()<<"):"<<(GetText().empty()?"Fuck This":GetText())<<" \n";
        cout<<"\t\tAnswer:"<<(!GetAnswer().empty()?GetAnswer():"Not Answered Yet")<<el;
}
void Question::PrintFeedQuestion(){
    if (ParentId != -1)
        cout << "\tThread Parent Question ID (" << ParentId << ") ";

    cout << "Question Id (" <<id << ")";
    if (!Anynomous)
        cout << " from user id(" << FromId << ")";

    cout << " To user id(" << ToId<< ")";

    cout << "\t Question: " <<GetText() << "\n";
    if (!Answer.empty())
        cout << "\t\tAnswer: " << GetAnswer() <<"\n";
}

void Question::SetText(const string &txt){
    text=txt;
}

void Question::SetId(int a) {
    id=a;
}

void Question::SetParentId(int a) {
    ParentId=a;
}

void Question::SetFromToId(int from, int to) {
    FromId=from, ToId=to;
}

void Question::SetAnynomous(int st) {
    Anynomous=st;
}

bool Question::GetAnynomous() const {
    return Anynomous;
}


QuestionsManager::QuestionsManager():last(0) {}

void QuestionsManager::LoadDatabase() {
    last=0;
    IdToQuestion.clear();
    QIdToThreads.clear();
    vector<string> Questions= ReadFile("../questions.txt");
    for(auto in:Questions){
        Question q(in);
        IdToQuestion[q.GetId()]=q;
        last=max(last,q.GetId());
        if(q.GetParentId()==-1)// put it to himself
            QIdToThreads[q.GetId()].emplace_back(q.GetId());
        else
            QIdToThreads[q.GetParentId()].emplace_back(q.GetId());
    }
}

void QuestionsManager::FillUserQuestion( User &usr) {
    usr.ClearQuestions();
    // clean id to threads of this user
    // clean QIdFromme to this user

    for(auto  &[id,Q] : QIdToThreads){
         for(auto QuestionId:Q){
             Question &q=IdToQuestion[QuestionId];
             if(q.GetFromToId().first==usr.GetId())
                 usr.AddToQuestionsFromMe(QuestionId);
             if(q.GetFromToId().second==usr.GetId()){
                 if(q.GetParentId()==-1)
                     usr.AddToQuestionToMe(q.GetId(),q.GetId());
                 else
                     usr.AddToQuestionToMe(q.GetParentId(), q.GetId());
             }
         }


    }
}

void QuestionsManager::PrintToQuestions(const User &usr) const {
    if(usr.GetIdToThread().size()==0){
        cout<<"No Questions\n";
        return;
    }
    for(const auto &pair: usr.GetIdToThread()){
        //id--> ids
        for(auto &id:pair.second){
            const Question &q=IdToQuestion.find(id)->second;
            q.PrintTo();
        }

    }

}

void QuestionsManager::PrintFromQuestion(const User &usr) const {
            if(usr.GetQuestionsIdFromMe().size()==0){
                cout<<"NO Question\n";
                return;
            }
            for(auto &item :usr.GetQuestionsIdFromMe()){
                const Question &q=IdToQuestion.find(item)->second;
                q.PrintFrom();
            }
}

vector<pair<int, int>> QuestionsManager::GetFromUserQuestion(const User &usr) {
    /*
     * Return a vector of pair [parent of Question To this user,Question To this user]*/
        vector<pair<int, int>> qIds;
        for(auto &[la, Ids]:QIdToThreads)
            for (auto Id: Ids) {
                const Question &q = IdToQuestion.find(Id)->second;
                if (usr.GetId() == q.GetFromToId().second) {
                    int pr = (q.GetParentId() == -1 ? q.GetId() : q.GetParentId());
                    qIds.emplace_back(pr, q.GetId());
                }
            }
            return qIds;
}

vector<int> QuestionsManager::GetToUserQuestion(const User &usr) {
    // return vector of ids asked Fromthis user
    vector<int> QIds;
    for(auto &[Thread, Ids]: QIdToThreads)
        for(auto Id:Ids){
            const Question &q=IdToQuestion.find(Id)->second;
            if(q.GetFromToId().first==usr.GetId())
                QIds.emplace_back(q.GetId());
        }
    return QIds;
}

void QuestionsManager::UpdateDatabase() {
        vector<string> Lines;
        for(auto &[id, q]:IdToQuestion)
            Lines.emplace_back(q.ToString());
        WriteFileLines("../questions.txt", Lines, false);
}

void QuestionsManager::AnswerQuestion(const User &usr) {
        int id=ReadQuestionIdAny(usr);
        if(id==-1)
            return;
      Question &q=IdToQuestion[id];
      q.PrintTo();
      if(!q.GetAnswer().empty())
          cout<<"Already answered and will be updated\n";

      cout<<"Enter Answer :";
      string Answer;
      getline(cin,Answer);
      getline(cin,Answer);
      q.SetAnswer(Answer);
}

void QuestionsManager::DeleteQuestion(const User &usr) {
        /* ! To Delete a Question
         1. You need to delete it from Questions
         2. You need to Delete it from Users
         */
     cout<<"Enter Question Id or -1 to cancel: ";
     int id; cin>>id;
     if(id==-1)// cancel
         return;
     Question &q=IdToQuestion[id];
     // need to remove Question only if has no threads
     vector<int> ShouldBeRemoved;
    // if main Question Remove it with it's childs
    // else Remove it only
    // After that remove all Questions from IdToQuestion
     if(QIdToThreads.count(id)){

         ShouldBeRemoved=QIdToThreads[id];
         QIdToThreads.erase(id);
     }else{
         ShouldBeRemoved.emplace_back(id);
         for(auto &[idd,vec]:QIdToThreads){
             for(int i=0;i<vec.size();i++)
                 if(vec[i]==id) {
                     vec.erase(vec.begin() + i);
                     break;
                 }
         }

     }
     for(auto &i:ShouldBeRemoved)
         IdToQuestion.erase(id);
     ShouldBeRemoved.clear();
}

void QuestionsManager::AskQuestion(const User &usr, pair<int, int> AskedUserInformation) {
    int AskedUserId=AskedUserInformation.first;
    int AskedUserStatus=AskedUserInformation.second;
    Question q;
    if(AskedUserStatus){
        cout<<"Note: Anynomous Questions Aren't Allowed to this User\n";
        q.SetAnynomous(0);
    }else{
        cout<<"Anynomous Question? (0 or 1)";
        int st; cin>>st;
        q.SetAnynomous(st);
    }
    q.SetParentId(ReadQuestionIdThread(usr));
    cout<<"Enter Question Text: ";
    string text;
    getline(cin, text);
    getline(cin, text);
    q.SetText(text);
    q.SetId(++last);
    q.SetFromToId(usr.GetId(),AskedUserId);
    IdToQuestion[q.GetId()]=q;
    int pr=(q.GetParentId()!=-1?q.GetParentId():q.GetId());
    QIdToThreads[pr].emplace_back(q.GetId());


}

void QuestionsManager::ListFeeds() {
        for(auto &[id, q]:IdToQuestion){
//            if(q.GetAnswer().empty())continue;
            q.PrintFeedQuestion();
        }
}

int QuestionsManager::ReadQuestionIdAny(const User &usr) const {
    cout<<"Enter Question Id or -1 to cancel:\n";
    int id; cin>>id;
    if(id==-1)return id;
    if(!IdToQuestion.count(id)){
        cout<<"No Question with this id...Try Again\n";
        return ReadQuestionIdAny(usr);
    }
    const Question &q=IdToQuestion.find(id)->second;
    if(q.GetFromToId().second!=usr.GetId())   {
        cout<<"No Question with this id...Try Again\n";
        return ReadQuestionIdAny(usr);
    }
    return id;

}

int QuestionsManager::ReadQuestionIdThread(const User &usr) const {
    cout<<"Enter Question Id or -1 to For New Question: ";
    int id;cin>>id;
    if(id==-1)return id;
    if(!QIdToThreads.count(id)){
        cout<<"No Question with this id...Try Again\n";
        return ReadQuestionIdThread(usr);
    }
    return id;

}

