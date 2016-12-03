#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

vector<string> split(string str, string delim){
    vector<string> ret;
    size_t pos = 0;
    string token;
    while((pos = str.find(delim)) != string::npos){
        token = str.substr(0, pos);
        if(token.length() > 0){
            ret.push_back(token);
        }
        str.erase(0, pos + delim.length());
    }
    ret.push_back(str);
    return ret;
}

string combine(vector<string> strArr){
    string ret = "";
    for(int i=0;i<strArr.size();++i){
        ret += strArr[i];
    }
    return ret;
}

class Graph{
public:
    Graph();
    void addEdge(string u, string v);
    vector<string> getAllPaths(string src, string dst);
    void backtracking(string src, string dst, unordered_map<string, bool> &visited, vector<string> &solution, vector<string> &ret);
    //private:
    unordered_map<string, vector<string>>::iterator it;
    unordered_map<string, vector<string>> adj;
};

Graph::Graph(){
    this->adj.clear();
}

void Graph::addEdge(string u, string v){
    if(adj.find(u) != adj.end()){
        adj[u].push_back(v);
    }else{
        vector<string> tmp;
        tmp.push_back(v);
        adj[u] = tmp;
    }
}

void Graph::backtracking(string src, string dst, unordered_map<string, bool> &visited, vector<string> &solution, vector<string> &ret){
    visited[src] = true;
    solution.push_back(src);
    
    if(src == dst){
        ret.push_back(combine(solution));
    }else{
        for(int i=0;i<adj[src].size();++i){
            if(!visited[adj[src][i]]){
                backtracking(adj[src][i], dst, visited, solution, ret);
            }
        }
    }
    
    solution.pop_back();
    visited[src] = false;
}

vector<string> Graph::getAllPaths(string src, string dst){
    unordered_map<string, bool> visited;
    for(it = adj.begin();it != adj.end();++it){
        visited[it->first] = false;
    }
    vector<string> solution;
    vector<string> ret;
    backtracking(src, dst, visited, solution, ret);
    return ret;
}

// print all paths from a source to destination
vector<string> getAllPaths(vector<string> lines){
    Graph g = Graph();
    vector<string> strArr = split(lines[0], " ");
    string src = strArr[0];
    string dst = strArr[1];
    for(int i=1;i<lines.size();++i){
        strArr = split(lines[i], " ");
        string cur = strArr[0];
        for(int j=2;j<strArr.size();++j){
            g.addEdge(cur, strArr[j]);
        }
    }
    return g.getAllPaths(src, dst);
}

vector<string> readFile(string &fname){
    ifstream in(fname.c_str(), ios::in);
    if(!in){
        throw "file is not exist";
    }
    vector<string> lines;
    string line;
    while(getline(in, line)){
        lines.push_back(line);
    }
    return lines;
}


int main(){
//    vector<string> inputGraph;
//    inputGraph.push_back("A J");
//    inputGraph.push_back("A : B C");
//    inputGraph.push_back("B : C E G");
//    inputGraph.push_back("C : A F");
//    inputGraph.push_back("D : C J");
//    inputGraph.push_back("F : B H");
//    inputGraph.push_back("G : C D");
//    inputGraph.push_back("H : A B F I");
//    inputGraph.push_back("I : B");
    string fname = "input_1.txt";
    vector<string> inputGraph = readFile(fname);
    
    vector<string> allPaths = getAllPaths(inputGraph);
    for(int i=0;i<allPaths.size();++i){
        cout<<allPaths[i]<<endl;
    }
    return 0;
}