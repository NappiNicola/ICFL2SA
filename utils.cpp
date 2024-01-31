#include<iostream>
#include<string.h>

#include "utils.h"

using namespace std;

void print(string word){
    cout<<word<<endl;
}

void printVector(vector<int> vec, string msg){
    print(msg);
    for(int i=0; i<vec.size(); i++)
        cout<<vec.at(i)<<" ";
    cout<<endl;
}

char* append(const char *s, char c) {
    int len = strlen(s);
    char buf[len+2];
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = 0;
    return strdup(buf);
}