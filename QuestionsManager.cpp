#include "AskMe.h"
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



string Question::GetText() {
    return text;
}

int Question::GetId() {
    return id;
}

string Question::GetAnswer() {
    return Answer;
}



Question::Question()
        :id(-1),FromId(-1),ToId(-1),ParentId(-1) {}

int Question::GetParentId() {
    return ParentId;
}

Question::Question(string line){
        vector<string> v= Split(line, string(","));
        id=stoi(v[0]);
        ParentId=stoi(v[1]);
        FromId=stoi(v[2]);
        ToId=stoi(v[3]);
        Anynomous= v[4] == "1";
        text=v[5];
        Answer=v[6];
}

string Question::ToString() {
    ostringstream oss;
    oss <<GetId()
    <<","<<GetParentId()<<","<<GetFromToId().first<<","
    <<GetFromToId().second<<","<<GetText()<<", "<<GetAnswer();
    return oss.str();
}

QuestionsManager::QuestionsManager() {
    vector<string> Lines= ReadFile("questions.txt");
    Question tmp;
    for(auto i:Lines){
        tmp=Question(i);
        Questions[tmp.GetParentId()].emplace_back(tmp);
    }
}

