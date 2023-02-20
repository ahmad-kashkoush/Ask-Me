//
// Created by ahmed-kashkoush on 2/18/23.
//
#include"AskMe.h"

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
void WriteFileLines(const string &path, const vector<string> &lines, bool append = true){
    auto status = ios::in | ios::out | ios::app;

    if (!append)
        status = ios::in | ios::out | ios::trunc;	// overwrite

    fstream file_handler(path.c_str(), status);

    if (file_handler.fail()) {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }
    for (const auto &line : lines)
        file_handler << line << "\n";

    file_handler.close();
}

int MenuSides(int l, int r) {
    cout<<"Enter Choice in Range["<<l<<"-"<<r<<"]: ";
    int choice;cin>>choice;
    if(choice<l||choice>r){
        cout<<"Invalid Choice ... Try Again\n";
        return MenuSides(l, r);
    }
    return choice;

}

int ShowMenu(const vector<string> &v){
    cout<<"\nMenu\n";
    for(int choice=1;choice<=v.size();choice++)
        cout<<choice<<": "<<v[choice-1]<<el;
    return MenuSides(1, (int)v.size());
}