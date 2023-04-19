#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <ctime>
#include <sstream>
#include "promo.h"
#include "timenow.h"
int UserID;
string gettime;
using namespace std;

struct UserDB {
	string username;
	double balance;
	string rate;
	string registrationdata;
	string promo;

};
UserDB* UserMas = new UserDB[sizer];
string abonent;

void auth();
void phonecalladd();
void Rankusermenu();
void userdataupdate();
void UserDataCheck(string currentuser) {
	ofstream userdata;
	fstream FL;
	bool valid = false;
	FL.open("userdb.txt");
	if (FL) {
		for (int i = 0; i < sizer; i++) {
			
			FL >> UserMas[i].username;
			if (UserMas[i].username == currentuser) {
				valid = true;
				UserID = i;
			}
			FL >> UserMas[i].balance;
			FL >> UserMas[i].rate;
			FL >> UserMas[i].registrationdata;
			FL >> UserMas[i].promo;
		}
		FL.close(); 
		if (!valid) {
			userdata.open("userdb.txt", ios::app);
			double balance = 10;
			string username = currentuser;
			string rate = "NONE";
			string registrationdata = "time.";
			string promo = "standart";
			userdata << username << " " << balance << " " << rate << " " << registrationdata << " " << promo << endl;
			userdata.close();
			fstream FL2;
			FL2.open("userdb.txt");
			for (int i = 0; i < sizer; i++) {
				FL >> UserMas[i].username;
				FL >> UserMas[i].balance;
				FL >> UserMas[i].rate;
				FL >> UserMas[i].registrationdata;
				FL >> UserMas[i].promo;
			}
				FL2.close();
				UserDataCheck(currentuser);
		}
		Rankusermenu();
	}
	else {
		userdata.open("userdb.txt", ios::app);
		double balance = 10;
		string username = currentuser;
		string rate = "NONE";	
		string registrationdata = "time.";
		string promo = "standart";
		userdata << username << " " << balance << " " << rate << " " << registrationdata << " " << promo << endl;
		userdata.close();
		FL.open("userdb.txt");
		for (int i = 0; i < sizer; i++) {
			FL >> UserMas[i].username;
			FL >> UserMas[i].balance;
			FL >> UserMas[i].rate;
			FL >> UserMas[i].registrationdata;
			FL >> UserMas[i].promo;
		}
		FL.close();
		Rankusermenu();
	}
}

void callhistory() {
	system("cls");
	fstream H;
	ofstream callh;
	string calldatacheck1;
	string calldatacheck2;
	string calldatacheck3;
	string calldatacheck4;
	string calldatacheck5;
	
	H.open("calls.txt");
	if (H) {
		string last = "";
		string lasttime = "";
		int a = 0;
		while (a<100) {
			H >> calldatacheck1;
			if (calldatacheck1 == "") break;
			H >> calldatacheck2;
			H >> calldatacheck3;
			H >> calldatacheck4;
			H >> calldatacheck5;
			if (calldatacheck1 == currentuser) {
				string param = "��������� ������ ";
				string toperson = calldatacheck2;
				string calltime = calldatacheck3 + calldatacheck4 + calldatacheck5;
				if (calltime != lasttime || toperson != last) {
					cout << param << "�������� " << toperson << " � " << calldatacheck3 << ":" << calldatacheck4 << ":" << calldatacheck5 << endl;
					last = toperson;
					lasttime = calltime;
				}
			}
			if (calldatacheck2 == currentuser) {
				string param = "�������� ������ ";
				string fromperson = calldatacheck1;
				string calltime = calldatacheck3 + calldatacheck4 + calldatacheck5;
				if (calltime != lasttime || fromperson != last) {
					cout << param << "�� �������� " << fromperson << " � " << calldatacheck3 << ":" << calldatacheck4 << ":" << calldatacheck5 << endl;
					last = fromperson;
					lasttime = calltime;
				}
			}
			a++;
		}
		H.close();
		Rankusermenu();
	}
	else {
		system("cls");
		cout << "�� ������� �� ������ ������." << endl;
		Rankusermenu();
	}
}


void call(string abonent,double price) {
	system("cls");
	for (int i = 0; i < 3; i++) {
		cout << "������� ���������� � ��������� " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "������� ���������� � ���������. " << abonent << endl;	
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "������� ���������� � ���������.. " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "������� ���������� � ���������... " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
	}
	cout << "����������� �����������!" << endl;

	gettime = gettimenow(); 

	cout << "��� ������ ������� ������� '1'" << endl;
	bool is_calling = true;
	int sec = 0;
	double pricenow;
	while (is_calling) {
		pricenow = price * sec;
		cout << "������ ������ " << sec << " ���. " <<"\t\t��������� ������ ����������: " << pricenow << "\t\t\t ��� ������: " << UserMas[UserID].balance << endl;
		UserMas[UserID].balance -= price;
		sec++;
		this_thread::sleep_for(chrono::seconds(1));
		if (_kbhit()) {
			int k = _getch();
			if (k == '1') {
				is_calling = false;
				cout << "������ ��������!" << endl;
				userdataupdate();
				phonecalladd();

				Rankusermenu();
			}
		}
		if ((UserMas[UserID].balance - pricenow + pricenow) < price ) {
			cout << "������������ ������� �� �������" << endl;
			userdataupdate();
			phonecalladd();
			Rankusermenu();
		}
	}
	Rankusermenu();
}


void callmanager(double price) {
	cout << "���������� �����: " << endl;
	int aht = 0;
	for (int i = 0; i < sizer; i++) {
		if (UserMas[i].username == currentuser) continue;
		else if (UserMas[i].rate != "NONE" && UserMas[i].rate != "") {
			cout <<  "�������: " << UserMas[i].username << endl;
			aht++;
		}
	}
	if (aht == 0) {
		system("cls");
		cout << "������ ��� �� ���� ������ �� ��������� �����." << endl;
		Rankusermenu();
	}
	cout << "������� ��� ��������, �������� ������ �������: " << endl;
	
	cin >> abonent;
	bool valid = false;
	for (int i = 0; i < sizer; i++) {
		if (UserMas[i].username == abonent) {
			valid = true;
			break;
		}
	}
	if (!valid) {
		cout << "������ ���������." << endl;
		Rankusermenu();
	}
	else {
		call(abonent,price);
	}
}

void phonecalladd() {
	ofstream call;
	call.open("calls.txt", ios::app);
	call << currentuser << " " << abonent << " " << gettime << endl;
	call.close();

}

void UserProfile() {
	cout << "��� ������������: " << UserMas[UserID].username << endl;
	cout << "������: " << UserMas[UserID].balance << endl;
	if (UserMas[UserID].rate == "NONE") {
		cout << "����� �� ������" << endl;
	}
	else cout << "�����: " << UserMas[UserID].rate << endl;
	cout << "�������� " << UserMas[UserID].promo << endl;
	cout << endl;
	Rankusermenu();
}

void userdataupdate() {
	ofstream userdata;
	userdata.open("userdb.txt");
	for (int i = 0; i < sizer; i++) {
		if (UserMas[i].username == "") continue;
		userdata << UserMas[i].username << " ";
		userdata << UserMas[i].balance << " ";
		userdata << UserMas[i].rate << " ";
		userdata << UserMas[i].registrationdata << " ";
		userdata << UserMas[i].promo << " ";
		userdata << endl;
	}
	userdata.close();
}
void Rankusermenu() {
	ofstream userdata;
	cout << "1. ��� �������" << endl;
	cout << "2. ���������" << endl;
	cout << "3. ������" << endl;
	cout << "4. ������" << endl;
	cout << "5. �����" << endl;
	cout << "6. ����� �� ��������" << endl;
	cout << "7. ����� �� ����������" << endl;
	int oper;
	cin >> oper;
	if (oper ==1) {
		system("cls");
		UserProfile();
	}
	if (oper == 2) {
		system("cls");
		if (UserMas[UserID].promo == "standart") {
			string promocheck;
			cout << "�������� �� �����. ��� ��������� ��������� ���������� � �������������. ���� �� � ��� ������� �������� � �� ������� ��� ������, ������� 'promo'. ��� ������ ������� 'exit'" << endl;
			cin >> promocheck;
			if (promocheck == "promo") {
				string promokey;
				cout << "������� ��������: " << endl;
				cin >> promokey;
				if (promochecking(promokey)) {
					
					UserMas[UserID].promo = "active";
	
					userdata.open("userdb.txt");
					for (int i = 0; i < sizer; i++) {
						if (UserMas[i].username == "") continue;
						userdata << UserMas[i].username << " ";
						userdata << UserMas[i].balance << " ";
						userdata << UserMas[i].rate << " ";
						userdata << UserMas[i].registrationdata << " ";
						userdata << UserMas[i].promo << " ";
						userdata << endl;
					}
					userdata.close();
					Rankusermenu();


				}
				else {
					system("cls");
					cout << "������ ���������" << endl;
					Rankusermenu();
				}
			}
			else if (promocheck == "exit") {
				system("cls");
				Rankusermenu();
			}
			else {
				system("cls");
				Rankusermenu();
			}
		}
		else {
			system("cls");
			cout << "�������� ��� �����. " << endl;
			Rankusermenu();
		}

	}
	if (oper == 3) {
		system("cls");
		if (UserMas[UserID].rate == "NONE") {
			cout << "����� ��� �� ������." << endl << endl;
			cout << "��������� ������: " << endl;
			cout << "1. ����� '�� �����' (1���./�) " << endl;
			cout << "2. ����� '����� ����������' (5���./�) " << endl;
			cout << "3. ����� 'LUXE' (10���./�) " << endl;
			int chrate;
			cin >> chrate;
			if (chrate == 1) {
				system("cls");
				cout << "�� ������� ������������ � ������ " << endl;
				UserMas[UserID].rate = "svyas";
				userdata.open("userdb.txt");
				for (int i = 0; i < sizer; i++) {
					if (UserMas[i].username == "") continue;
					userdata << UserMas[i].username << " ";
					userdata << UserMas[i].balance << " ";
					userdata << UserMas[i].rate << " ";
					userdata << UserMas[i].registrationdata << " ";
					userdata << UserMas[i].promo << " ";
					userdata << endl;
				}
				userdata.close();
				Rankusermenu();
			}
			else if (chrate == 2) {
				system("cls");
				cout << "�� ������� ������������ � ������ " << endl;
				UserMas[UserID].rate = "povz";
				userdata.open("userdb.txt");
				for (int i = 0; i < sizer; i++) {
					if (UserMas[i].username == "") continue;
					userdata << UserMas[i].username << " ";
					userdata << UserMas[i].balance << " ";
					userdata << UserMas[i].rate << " ";
					userdata << UserMas[i].registrationdata << " ";
					userdata << UserMas[i].promo << " ";
					userdata << endl;
				}
				userdata.close();

				Rankusermenu();
			}
			else if (chrate == 3) {
				system("cls");
				cout << "�� ������� ������������ � ������ " << endl;
				UserMas[UserID].rate = "luxe";
				userdata.open("userdb.txt");
				for (int i = 0; i < sizer; i++) {
					if (UserMas[i].username == "") continue;
					userdata << UserMas[i].username << " ";
					userdata << UserMas[i].balance << " ";
					userdata << UserMas[i].rate << " ";
					userdata << UserMas[i].registrationdata << " ";
					userdata << UserMas[i].promo << " ";
					userdata << endl;
				}
				userdata.close();
				Rankusermenu();
			}
			else {
				system("cls");
				Rankusermenu();
			}
		}
		else {
			system("cls");
			cout << "� ��� ��� ��������� �����. � ������, ���� �� ������ ��� ��������, �������� 'switch'. ��� ������ �������� 'exit' " << endl;
			string swrate;
			cin >> swrate;
			if (swrate == "switch") {			
				cout << "�� ������� ����������� �� ������ " << endl;
				UserMas[UserID].rate = "NONE";
				userdata.open("userdb.txt");
				for (int i = 0; i < sizer; i++) {
					if (UserMas[i].username == "") continue;
					userdata << UserMas[i].username << " ";
					userdata << UserMas[i].balance << " ";
					userdata << UserMas[i].rate << " ";
					userdata << UserMas[i].registrationdata << " ";
					userdata << UserMas[i].promo << " ";
					userdata << endl;
				}
				userdata.close();
				Rankusermenu();
			}
			else {
				system("cls");
				Rankusermenu();
			}
		}
	
	}
	if (oper == 4) {
		system("cls");
		if (UserMas[UserID].rate != "NONE") {
			cout << "������������ ���, " << UserMas[UserID].username << endl;
			double price;
			string nrate;
			double promobonus = 1;
			if (UserMas[UserID].promo == "active") {
				promobonus = 0.5;
				cout << "��������� ��������: ������ 50%" << endl;
			}
			if (UserMas[UserID].rate == "svyas") {
				price = 1.0 / 60.0 * promobonus;
				nrate = "����� '�� �����'";
			}
			else if (UserMas[UserID].rate == "povz") {
				price = 5.0 / 60.0 * promobonus;
				nrate = "����� '����� ����������'";
			}
			else if (UserMas[UserID].rate == "luxe") {
				price = 10.0 / 60.0 * promobonus;
				nrate = "����� 'LUXE'";
			}
			cout << "��������� �����:" << nrate << endl;
			cout << "��������� ������ � �������: " << price << endl << endl;
			cout << "���� �������: " << endl;
			cout << "1. ��������� " << endl;
			cout << "2. ������� �������" << endl;
			string phonech;
			cin >> phonech;
			if (phonech == "1") {
				system("cls");
				callmanager(price);
			}
			else if (phonech == "2") {
				system("cls");
				callhistory();
			}
			else {
				system("cls");
				cout << "������ �����." << endl;
				Rankusermenu();
			}

		}
		else {
			system("cls");
			cout << "�� �� ������ ��������� ������, ��� ��� ��� ����� �� ������." << endl;
			Rankusermenu();
		}
	}
	if (oper == 5)
	{
		system("cls");
		cout << "1. ����������� ���������" << endl;
		cout << "2. ����� � ��������������" << endl;
		cout << "3. ��������� � ����" << endl;
		int nmail;
		cin >> nmail;
			if (nmail == 1) {
				system("cls");
				cout << "C��������: " << endl << endl;
				ifstream supportmsg("support.txt");
				fstream SUP;
				string line;
				bool found = false;
				string name = currentuser; 
				while (getline(supportmsg, line)) {
					if (line.find(name) == 0) {
						istringstream iss(line); 
						string word;
						iss >> word; 
						string restOfLine;
						getline(iss, restOfLine); 
						cout <<"[" << name << "] " << restOfLine << endl;
						found = true;
						continue;
					}
					else if (line.find("adminto" + name) == 0) {
						istringstream iss(line); 
						string word;
						iss >> word; 
						string restOfLine;
						getline(iss, restOfLine); 
						cout << "[ADMIN] " << restOfLine << endl;
						found = true;
						continue;
					}
				}
					if (!found) {
						cout << "� ��� ��� ���������." << std::endl;
					}
					cout << endl;
					cout << "��� ������ �������� exit" << endl;
					string varik;
					cin >> varik;
					if (varik == "exit") {
						system("cls");
						Rankusermenu();
					}
					else {
						system("cls");
						Rankusermenu();
					}

			}
			if (nmail == 2) {
				ofstream supportmsg;
				fstream SUP;
				system("cls");
				supportmsg.open("support.txt", ios::app);
				cout << "������� ���������, ������� ����� ���������� �������������: " << endl;
				string ms2g;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(cin, ms2g); 
				supportmsg << currentuser << ": " << ms2g << endl;
				supportmsg.close();
				Rankusermenu();
			}
			if (nmail == 3)
			{
				system("cls");
				Rankusermenu();
			}
		
	}
	if (oper == 6) {
		system("cls");
		auth();
	}
	if (oper == 7) {
		delete[] UserMas;
		for (int i = 0; i < sizer; i++) {
			delete[] info[i];
		}
		delete[] info;
		exit(0);
	}
	}
