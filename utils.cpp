#include<iostream>

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