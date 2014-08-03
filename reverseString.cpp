#include <string>
#include <iostream>

using namespace std;

int main(){
	string str = "hello world";

	string reverseStr(str.rbegin(),str.rend());

	cout<<reverseStr<<endl;

	return 0;
}