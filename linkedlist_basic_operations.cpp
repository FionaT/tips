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
#define SIZE1 4
#define SIZE2 6

using namespace std;

class ListNode {
public:
    int val;
    ListNode *next = NULL;
    
    ListNode(int x) : val(x), next(NULL) {}
    
    void appendToTail(int d){
        ListNode *end = new ListNode(d);
        ListNode *n = this;
        
        while(n->next != NULL){
            n = n->next;
        }
        
        n->next = end;
    }
    

};

ListNode* deleteNode(int d, ListNode *head){
    ListNode *n = head;
    
    if(n->val == d)
        return n->next;
    
    while(n->next != NULL){
        if(n->next->val == d){
            n->next = n->next->next;
            //cout<<"!"<<endl;
            return head;
        }
        n = n->next;
    }
    
    return head;
}



int main()
{
    ListNode *head = new ListNode(1);

    for(int i = 2; i < 10; i++){
        head->appendToTail(i);
    }
    
    ListNode *h = head;
    
    while(h != NULL){
        cout<<h->val<<" ";
        
        h = h->next;
    }
    
    cout<<endl;
    
    head = deleteNode(2, head);
    
    h = head;
    
    while(h != NULL){
        cout<<h->val<<" ";
        
        h = h->next;
    }
    
	return 0;
}

