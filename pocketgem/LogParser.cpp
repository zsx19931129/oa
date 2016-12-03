#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

#define EPS 10e-6

bool doubleEqual(double a, double b){
    return fabs(a-b) < EPS;
}

time_t getUTC(string str){
    tm t;
    istringstream ss(str);
    ss.imbue(locale("en_US.utf-8"));
    ss>>get_time(&t, "%d/%m/%Y-%H:%M:%S");
    return timelocal(&t);
}

string getOnlinePercentage(vector<string> &lines){
    double total = 0, connected = 0;
    time_t start, end, connect, disconnect, curtime;
    bool gamestart = false, online = false;
    string status = "";
    
    for(int i=0;i<lines.size();++i){
        curtime = getUTC(lines[i].substr(1, 19));
        status = lines[i].substr(25);
        
        if(status == "START"){
            gamestart = true;
            start = curtime;
        }else if(status == "SHUTDOWN"){
            if(gamestart){
                gamestart = false;
                end = curtime;
                total = difftime(end, start);
            }
            break;
        }else if(status == "CONNECTED"){
            if(!gamestart || online){
                continue;
            }
            online = true;
            connect = curtime;
        }else if(status == "DISCONNECTED"){
            if(!gamestart || !online){
                continue;
            }
            online = false;
            disconnect = curtime;
            connected += difftime(disconnect, connect);
        }
    }
    if(online){
        online = false;
        connected += difftime(end, connect);
    }
    if(doubleEqual(total, 0)){
        return "0%";
    }else{
        int percentage = (connected*100)/total;
        char buffer[10];
        sprintf(buffer, "%d%%", percentage);
        return string(buffer);
    }
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
    vector<string> lines;
    lines.push_back("(02/03/2002-14:00:00) :: START");
    lines.push_back("(02/03/2002-14:00:00) :: CONNECTED");
    lines.push_back("(02/03/2002-14:08:00) :: DISCONNECTED");
    lines.push_back("(02/03/2002-14:10:00) :: CONNECTED");
    lines.push_back("(02/03/2002-14:12:00) :: DISCONNECTED");
    lines.push_back("(02/03/2002-14:15:00) :: SHUTDOWN");
//    vector<string> lines = readFile("input1.txt");
    string res = getOnlinePercentage(lines);
    cout<<res<<endl;
}