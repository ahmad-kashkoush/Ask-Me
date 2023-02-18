#include "AskMe.h"
void Question::SetAnswer() {
    if(GetAnswer().size()!=0)
        cout<<"Warning : Alread Answered, answer will be updated\n";
    cout<<"Enter Answer Text :";
    getline(cin, Answer);

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

const int Question::GetId()const {
    return id;
}

const string &Question::GetAnswer()const {
    return Answer;
}



int Question::GetParentId() const{
    return ParentId;
}

const string &Question::ToString()const {
    ostringstream oss;
    oss <<GetId()
    <<","<<GetParentId()<<","<<GetFromToId().first<<","
    <<GetFromToId().second<<","<<GetText()<<", "<<GetAnswer();
    return oss.str();
}
Question::Question()
        :id(-1),FromId(-1),ToId(-1),ParentId(-1) {}

Question::Question(const string &line){
        vector<string> v= Split(line, string(","));
        id=stoi(v[0]);
        ParentId=stoi(v[1]);
        FromId=stoi(v[2]);
        ToId=stoi(v[3]);
        Anynomous= v[4] == "1";
        text=v[5];
        Answer=v[6];
}


void Question::PrintTo() const {
    if(GetParentId()!=-1)
        cout<<"\tThread :   ";
    if(!Anynomous)
        cout<<"From User Id ("<<GetFromToId().first<<")";
    cout<<"\t Question: "<<GetText()<<el;
    if(!GetAnswer().empty())cout<<"\t Answer: "<<GetAnswer()<<el;
}

void Question::PrintFrom() const {
        cout<<"Question Id ("<<GetId()<<") ";
        if(!Anynomous)cout<<"!AQ ";
        cout<<"To User Id ("<<GetFromToId().second;
        cout<<"\t Question: "<<GetText()<<" ";
        cout<<"-->"<<(!GetAnswer().empty()?GetAnswer():"Not Answered Yet")<<el;
}
void Question::PrintFeedQuestion(){
    if (ParentId != -1)
        cout << "Thread Parent Question ID (" << ParentId << ") ";

    cout << "Question Id (" <<id << ")";
    if (!Anynomous)
        cout << " from user id(" << FromId << ")";

    cout << " To user id(" << ToId<< ")";

    cout << "\t Question: " << text << "\n";
    if (!Answer.empty())
        cout << "\tAnswer: " << Answer <<"\n";
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


QuestionsManager::QuestionsManager() {
    vector<string> Lines= ReadFile("questions.txt");
    Question tmp;
    for(auto i:Lines){
        tmp=Question(i);
        Questions[tmp.GetParentId()].emplace_back(tmp);
    }
}

