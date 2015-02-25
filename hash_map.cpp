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
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

void printTri(int n){
    int level = n / 2 + n % 2;
    int num = n;
    int space = 0;
    
    for(int i = 0; i < level; i++){
        for(int j = 0; j < space; j++){
            cout<<" ";
        }
        
        for(int j = 0; j < num; j++){
            cout<<"*";
        }
        
        cout<<endl;
        space ++;
        num = num - 2;
    }
    
}

vector<int> findK(int arr[], int n, int k){
    vector<int> result;
    priority_queue<int> pq;
    
    if(n < k){
        for(int i = 0; i < n; i++)
            result.push_back(arr[i]);
        
        return result;
    }
    
    for(int i = 0; i < n; i++){
        pq.push(arr[i]);
    }
    
    for(int i = 0; i < k; i++){
        result.push_back(pq.top());
        pq.pop();
    }
    
    return result;
}


int main ( int argc, char *argv[] )
{
    int arr[10] = {1, 3, 2, 7, 55, 4, 9, 80, 9, 0};
    
    unordered_map<string, int> m;
    
    string a = "Jan", b = "Feb", c = "Mar", d = "Apri", e = "May", f = "Jun";
    
    m[a] = 1;
    m[b] = 2;
    m[c] = 3;
    m[d] = 4;
    m[e] = 5;
    m[f] = 6;
    
    cout<<"m[] "<<m[b]<<endl;
    
    //the insert function
    pair<string, int> p("Jul", 7);
    
    m.insert(p);
    cout<<"m.insert "<<m["Jul"]<<endl;
    
    
    //the element access way of at in unordered_map
    cout<<"m.at() "<<m.at("May")<<endl;
    
    //the count function that counts how many same keys exist in the hashmap
    //An unordered_map maintains a 1:1 mapping of key to value,
    //so count will always return zero or one.
    cout<<"m.count "<<m.count(e)<<endl;
    cout<<"m.count "<<m.count("mango")<<endl;
    
    //the find function
    cout<<"The find function ";
    
    a = "haha";
    
    if(m.find(a) != m.end()){
        cout<<m[a]<<endl;
    }else{
        cout<<"Not found"<<endl;
    }

    //the erase function
    m.erase ("Jan");
    cout<<"erase Jan already "<<m.count("Jan")<<endl;
    
    
    //the iterator in unordered_map
    // 2 elements 1.first->key  2.second->value
    cout<<(*m.begin()).first<<endl;
    cout<<(*m.begin()).second<<endl;
    cout<<(*++m.begin()).first<<endl;
    
    
    //the clear function
    m.clear();
    cout<<"after clear "<<m.count("May")<<endl;
    
    //the swap function
    unordered_map<std::string,std::string>
    temp1 = {{"Star Wars","G. Lucas"},
             {"Alien","R. Scott"},
             {"Terminator","J. Cameron"}},
    temp2  = {{"Inception","C. Nolan"},
               {"Donnie Darko","R. Kelly"}};
    
    for (auto& x: temp1)
        cout << x.first << " (" << x.second << "), ";
    
    cout<<endl;
    
    for (auto& x: temp2)
        cout << x.first << " (" << x.second << "), ";
    
    cout<<endl;
    
    temp1.swap(temp2);
    
    for (auto& x: temp1)
        cout << x.first << " (" << x.second << "), ";
    
    cout<<endl;
    
    for (auto& x: temp2)
        cout << x.first << " (" << x.second << "), ";
    
    cout<<endl;
    
    return 0;
}

