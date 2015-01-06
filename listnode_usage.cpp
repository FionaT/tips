//
//  main.cpp
//  test
//
//  Created by Fiona on 14-10-27.
//  Copyright (c) 2014年 Fiona. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    };


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
    ListNode *p1 = headA;
    ListNode *p2 = headB;
    
    while(p1 != NULL){
        //cout<<p1->val<<endl;
        
        while(p2 != NULL){
            if(p1 == p2)
                return p1;
            p2 = p2->next;
        }
        p2 = headB;
        p1 = p1->next;
    }
    
    return NULL;
}

int main(int argc, const char * argv[]){
    ListNode l1 = ListNode(1);
    ListNode l2 = ListNode(2);
    ListNode l3 = ListNode(3);
    ListNode l4 = ListNode(4);
    ListNode l5 = ListNode(5);
    ListNode l6 = ListNode(6);
    ListNode l7 = ListNode(7);
    
    
    ListNode *p1 = &l1;
    ListNode *p2 = &l2;
    ListNode *p3 = &l3;
    ListNode *p4 = &l4;
    ListNode *p5 = &l5;
    ListNode *p6 = &l6;
    ListNode *p7 = &l7;

    
    l1.next = p3;
    l3.next = p6;
    l6.next = p7;
    
    l2.next = p4;
    l4.next = p5;
    //l5.next = p7;
    
    ListNode *pointer;
    
    pointer = p1;
    
    /*
    while(pointer != NULL){
        cout<<pointer->val<<endl;
        pointer = pointer->next;
    }*/
    
    ListNode *ans = getIntersectionNode(p1, p2);
    
    cout<<ans->val<<endl;
    
    return 0;
}



