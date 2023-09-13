//
// Created by ahmed-kashkoush on 3/1/23.
//

#ifndef ASK_ME_QUESTIONMANAGER_H
#define ASK_ME_QUESTIONMANAGER_H

class Question{
private:
    string text, Answer;
    int id;
    int FromId, ToId;
    int ParentId;
    bool Anynomous{};

public:
    //! Still Didn't Add Print From and print to functionalities
    Question(const string&);
    Question();
    void PrintTo() const;
    void PrintFrom() const;
    void PrintFeedQuestion();
    void Enter(int ,int);
    string ToString() const;
    //Getters
    const string &GetText()const;
    const string &GetAnswer()const;
    bool GetAnynomous()const;
    int GetId()const;
    int GetParentId()const;
    pair<int, int> GetFromToId()const;
    //Setters
    void SetText(const string&);
    void SetAnswer(const string &);
    void SetId(int);
    void SetParentId(int);
    void SetFromToId(int ,int);
    void SetAnynomous(int );


};

class QuestionsManager{
private:
    int last;
    map<int, vector<int>> QIdToThreads;
    map<int, Question> IdToQuestion;
public:
    QuestionsManager();
    void LoadDatabase();
    void FillUserQuestion( User&);
    void PrintToQuestions(const User &)const;
    void PrintFromQuestion(const User &)const;
    int ReadQuestionIdAny(const User &)const;
    int ReadQuestionIdThread(const User &)const;
    void UpdateDatabase();
    void AnswerQuestion(const User &);
    void DeleteQuestion(const User &);
    void AskQuestion(const User &, pair<int, int>);
    void ListFeeds();
    // Getters
    vector<int> GetToUserQuestion(const User &);
    vector<pair<int, int>> GetFromUserQuestion(const User &);//Get Question From this user

};



#endif //ASK_ME_QUESTIONMANAGER_H
