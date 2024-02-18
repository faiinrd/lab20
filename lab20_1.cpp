#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream f("name_score.txt");
    string s;
    char name[100];
    char format[] = "%[^:]: %d %d %d";
    int a,b,c;
    while(getline(f,s)){
        sscanf(s.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){
    string ans,x;
    cout << "Please input your command: ";
    cin >> ans;
    command = ans;
    if(toUpperStr(ans) == "EXIT"){
        command = ans;
    }else if(toUpperStr(ans) == "GRADE"){
        command = ans;
        cin >> x;
        key = x;
    }else if(toUpperStr(ans) == "NAME"){
        command = ans;
        cin.ignore();
        getline(cin,x);
        key = x;
    }
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(key) == toUpperStr(names[i])){
        printf("%s's score = %d\n%s's grade = %c\n",names[i].c_str(),scores[i],names[i].c_str(),grades[i]);
        found = true;
        break;
        }
    }
    if(!found){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < grades.size(); i++){
        if(*key.c_str() == grades[i]){
        printf("%s (%d)\n",names[i].c_str(),scores[i]);
        found = true;
        }
    }
    if(!found){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}