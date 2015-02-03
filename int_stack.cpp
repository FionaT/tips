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

#include <iostream>
#include <map>
#include <vector>
#include <stack>

#define SIZE1 4
#define SIZE2 6

using namespace std;

/*
it is a char stack that can contain char
 
 */

class Stack {
    int MaxStack;
    int EmptyStack;
    int index;
    int* items;
public:
    Stack(int size) {
        MaxStack = size;
        EmptyStack = -1;
        index = EmptyStack;
        items = new int[MaxStack];
    };
    
    ~Stack() {delete[] items;};
    
    void push(int c) {
        items[++index] = c;
    };
    
    int pop() {
        return items[index--];
    };
    
    int top(){
        return items[index];
    };
    
    int empty()  {
        return index == EmptyStack;
    };
    
    int full()  {
        return index + 1 == MaxStack;
    };
};


int main()
{
    Stack s(10); // the maximum size of the stack is 10 chars
    
    int ch;

    while ((cin>>ch) && ch != 0)
        if (!s.full())
            s.push(ch);
    
    //cout<<s.top()<<endl;
    
    
    while (!s.empty())
        cout<<s.pop()<<" ";
    
    cout<<endl;

    
    return 0;
}

