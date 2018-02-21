#include "Header.h"
using namespace std;
std::mutex mut;
std::condition_variable data_cond;
std::queue<std::string>buf;
std::queue<std::string>buf2;

void write(){
	//ofstream result("C:\\Users\\nmaga\\Desktop\\auriga\\readFile\\file1.txt");
	ofstream result("file1.txt");
	while (!buf.empty())
	{
		
		std::string dataToFile;
		std::string str = "string";

 
		std::unique_lock<std::mutex>lkc(mut);
//
		while (buf2.empty())
		{
			data_cond.wait(lkc);
		}
	dataToFile = buf2.front();
	
	if (result.is_open()) {
		result << dataToFile;
		
	}
	//dataToFile.erase();

	buf2.pop();
	
		lkc.unlock(); //освобождает мьютекс
	//	if (buf2.empty()) { break; }
		
	
	}
	result.close();
}


void rever() {
	
	while (!buf.empty())
	{
		std::string data;
		
			std::unique_lock<std::mutex>lk(mut);

			while (buf.empty())
			{
				data_cond.wait(lk);
			}
		
		data = buf.front();

		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::reverse(data.begin(),data.end()-1);

		cout << data;

		buf.pop();

		buf2.push(data);
		data.erase();
		lk.unlock(); //освобождает мьютекс
		
		data_cond.notify_one();
	}
	

}

void readFile() {
	std::ifstream stream("C:\\Users\\nmaga\\Desktop\\auriga\\readFile\\ответы.txt");
	char ff = '\0';
	string file_buffer;

	if (!stream.is_open()) {
		cout << "error openning";
			}
	else {
		std::lock_guard<std::mutex>lk(mut);
		while (!stream.eof()) {
			ff = stream.get();
			file_buffer += ff;
			
			if (ff == '\n') {
				
				buf.push(file_buffer);
				data_cond.notify_one();
								
			file_buffer.clear();
			
			}
			
		}
		
	}

}


