#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	int n=1;
	//little endian if true
	if(*(char *)&n == 1){
		cout<<"Little endian\n";
	}
	else cout<<"Big Endian\n";

	return 0;
}