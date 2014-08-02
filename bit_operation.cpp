//
//  main.cpp
//  test
//
//  Created by Fiona on 14-7-20.
//  Copyright (c) 2014年 Fiona. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;


int main(int argc, const char * argv[])
{
    //2 = 00000010 ; 1 = 00000001
    int b;
    
    b = 2 & 1;
    
    cout<<b<<endl;
    
    b = 2 | 1;
    
    cout<<b<<endl;
    
    b = 2 ^ 1;
    
    cout<<b<<endl;
    
    //1 = 00000001 ~1 = 11111110
    //计算机中表示用补码，更具先前的说明，所以补码110对应的即十进制中的2，
    //所以此时1取反后的数值对应的十进制数为-2
    b = ~1;
    
    cout<<b<<endl;
    
    return 0;
}

