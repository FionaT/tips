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
    int top;
    char* items;
public:
    Stack(int size) {
        MaxStack = size;
        EmptyStack = -1;
        top = EmptyStack;
        items = new char[MaxStack];
    };
    
    ~Stack() {delete[] items;};
    
    void push(char c) {
        items[++top] = c;
    };
    
    char pop() {
        return items[top--];
    };
    
    int empty()  {
        return top == EmptyStack;
    };
    
    int full()  {
        return top + 1 == MaxStack;
    };
};


int main()
{
    Stack s(10); // the maximum size of the stack is 10 chars
    
    char ch;
    
    while ((ch = cin.get()) != '\n')
        if (!s.full()) s.push(ch);
    
    while (!s.empty())
        cout << s.pop();
    
    cout << endl;
    
    
    return 0;
}

