#include<iostream>
#include<thread>
#include "Header.h"
using namespace std;





int main() {
	
	thread func_read(readFile);
	thread func_rev(rever);
	thread func_write(write);

	func_read.join();
	func_rev.join();
	func_write.join();
	





	cout <<"Ooen the file"<< endl;
	system("pause");

	
	return 0;

}