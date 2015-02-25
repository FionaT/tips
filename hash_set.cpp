//
//  main.cpp
//  leet
//
//  Created by Fiona on 14-7-28.
//  Copyright (c) 2014年 Fiona. All rights reserved.
//

//
//  main.cpp
//  test
//
//  Created by Fiona on 14-7-20.
//  Copyright (c) 2014年 Fiona. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;



int main ( int argc, char *argv[] )
{
    unordered_map<std::string,double> mypantry = {{"milk",2.0},{"flour",1.5}};
    
    cout<<mypantry["milk"]<<endl;
    
    
    unordered_set<string> s;
    array<string,3> myarray = {"black","white","red"};
    
    //the insert function
    s.insert (myarray.begin(), myarray.end());

    for(const string& x: s)
        cout<<x<<" ";
    
    cout<<endl;
    
    //the find function
    string key = "black";
    
    if(s.find(key) == s.end())
        cout<<"not found"<<endl;
    else
        cout<<*s.find(key)<<" found "<<endl;
    
    
    return 0;
}

