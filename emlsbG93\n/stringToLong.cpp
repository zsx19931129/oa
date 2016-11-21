//Question 1) Given a string, write a routine that converts the string to a long, without using the
//built in functions that would do this. Describe what (if any) limitations the code has.
//example:
//long stringToLong(String s)
//{
//    /* code goes here to convert a string to a long */
//}
//void test()
//{
//    long i = stringToLong("123");
//    if (i == 123)
//        // success.
//    else
//        // failure.
//}

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <climits>
#include <regex>

using namespace std;

void getMaxMinLongValueString(string &smax, string &smin){
    char buffer[25];
    sprintf(buffer, "%ld", LONG_MAX);
    smax = string(buffer);
    sprintf(buffer, "%ld", LONG_MIN);
    smin = string(buffer+1);
}

signed long long parseLong(string str) throw(exception) {
    regex pattern("(\\s*)([+-]?)(0|([1-9][0-9]*))(\\s*)");
    smatch smGroups;
    if(!regex_match(str, smGroups, pattern)){
//        throw invalid_argument("Invalid Number. str:"+str);
        throw exception();
    }
    
    string sign = smGroups[2];
    string digits = smGroups[3];
    size_t dlen = digits.length();
    
    bool negative = false;
    if(sign.length() > 0 && sign[0] == '-'){
        negative = true;
    }
    string strLongMax, strLongMin;
    getMaxMinLongValueString(strLongMax, strLongMin);
    if(dlen>strLongMax.length() || (!negative && digits>strLongMax) || (negative && digits>strLongMin)){
//        throw invalid_argument("overflow. str:"+sign+digits);
        throw exception();
    }
    
    if(digits == strLongMin){
        return LONG_MIN;
    }
    
    signed long long res = 0;
    for(int i=0;i<dlen;++i){
        res = res*10 + (digits[i]-'0');
    }
    if(negative){
        res = -res;
    }
    return res;
}

int main(){
//        cout<<parseLong("  + 1")<<endl;
    cout<<parseLong(" 1")<<endl;
    cout<<parseLong("-1")<<endl;
    cout<<parseLong("  +0")<<endl;
    //    cout<<parseLong("-01")<<endl;
    cout<<parseLong("12312412314")<<endl;
    cout<<parseLong("-1242313772")<<endl;
    cout<<parseLong("9223372036854775807")<<endl;
    cout<<parseLong("-9223372036854775808")<<endl;
    //    cout<<parseLong("9223372036854775808")<<endl;
    //    cout<<parseLong("92233720368547758081")<<endl;
    //    cout<<parseLong("-19223372036854775808")<<endl;
    //    cout<<parseLong("  -9223372036854775809  ")<<endl;
    
    return 0;
}