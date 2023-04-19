#include <ctime>
#include <iostream>
#include <string>
using namespace std;

string gettimenow() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	cout << "Time: " <<  ltm->tm_hour << ":";
	cout <<  ltm->tm_min << ":";
	cout <<  ltm->tm_sec << endl;
	string datanow = to_string(ltm->tm_hour) +" " + to_string(ltm->tm_min) +" "+ to_string(ltm->tm_sec);
	return datanow;
}
