#include "top.h"
using namespace std;



void assign(vs &temp, string &label, string &opcode, string &operand)
{
    label = temp[0];
    opcode = temp[1];
    operand = temp[2];
    // cout<<label<<" "<<opcode<<" "<<operand<<endl;
    return;
}

void addSpacesEnd(string &s, int n)
{
    while (s.size() < n)
    {
        s.push_back(' ');
    }
}
void addSpacesStart(string &s, int n)
{
    string temp = "";
    fori
    {
        temp.pb(' ');
    }
    temp += s;
    s = temp;
}


string intToHex(int n) {
    string ret = "";
    while(n){
        if(n%16 <10){
            ret += (n%16 +'0');
        }
        else{
            ret += (n%16 - 10 +'A');
        }
        n/=16;
    }
    reverse all(ret);
    return ret;
}

int hexToInt(string s) {
    int n= s.size(),power = 0;
    int result = 0;
    for(int i=n-1;i>=0;i--){
        if(s[i]-'0'<=9 ){
            int temp = pow(16,power);
            temp *= (s[i]-'0');
            result += temp;
        }
        else{
            int temp = pow(16,power);
            temp *= (s[i]-'A' + 10);
            result += temp;
        }
        power++;
    }
    return result;
}


int convertToInt(string& s) {
    return stoi(s);
}

void appendStart(string& s, int size, char waste) {
    reverse all(s);
    while(s.size() < size){
        s.pb(waste);
    }
    reverse all(s);
    return;
}

void appendEnd(string& s, int size, char waste) {
    while(s.size() < size) {
        s.pb(waste);
    }
    return;
}