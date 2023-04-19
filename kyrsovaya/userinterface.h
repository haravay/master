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
				string param = "Исходящий звонок ";
				string toperson = calldatacheck2;
				string calltime = calldatacheck3 + calldatacheck4 + calldatacheck5;
				if (calltime != lasttime || toperson != last) {
					cout << param << "абоненту " << toperson << " в " << calldatacheck3 << ":" << calldatacheck4 << ":" << calldatacheck5 << endl;
					last = toperson;
					lasttime = calltime;
				}
			}
			if (calldatacheck2 == currentuser) {
				string param = "Входящий звонок ";
				string fromperson = calldatacheck1;
				string calltime = calldatacheck3 + calldatacheck4 + calldatacheck5;
				if (calltime != lasttime || fromperson != last) {
					cout << param << "от абонента " << fromperson << " в " << calldatacheck3 << ":" << calldatacheck4 << ":" << calldatacheck5 << endl;
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
		cout << "Не найдено ни одного звонка." << endl;
		Rankusermenu();
	}
}


void call(string abonent,double price) {
	system("cls");
	for (int i = 0; i < 3; i++) {
		cout << "Попытка соединения с абонентом " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "Попытка соединения с абонентом. " << abonent << endl;	
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "Попытка соединения с абонентом.. " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
		cout << "Попытка соединения с абонентом... " << abonent << endl;
		this_thread::sleep_for(chrono::seconds(1));
		system("cls");
	}
	cout << "Соеднинение установлено!" << endl;

	gettime = gettimenow(); 

	cout << "Для сброса нажмите клавишу '1'" << endl;
	bool is_calling = true;
	int sec = 0;
	double pricenow;
	while (is_calling) {
		pricenow = price * sec;
		cout << "Звонок длится " << sec << " сек. " <<"\t\tСтоимость звонка составляет: " << pricenow << "\t\t\t Ваш баланс: " << UserMas[UserID].balance << endl;
		UserMas[UserID].balance -= price;
		sec++;
		this_thread::sleep_for(chrono::seconds(1));
		if (_kbhit()) {
			int k = _getch();
			if (k == '1') {
				is_calling = false;
				cout << "Звонок завершен!" << endl;
				userdataupdate();
				phonecalladd();

				Rankusermenu();
			}
		}
		if ((UserMas[UserID].balance - pricenow + pricenow) < price ) {
			cout << "Недостаточно средств на балансе" << endl;
			userdataupdate();
			phonecalladd();
			Rankusermenu();
		}
	}
	Rankusermenu();
}


void callmanager(double price) {
	cout << "Телефонная книга: " << endl;
	int aht = 0;
	for (int i = 0; i < sizer; i++) {
		if (UserMas[i].username == currentuser) continue;
		else if (UserMas[i].rate != "NONE" && UserMas[i].rate != "") {
			cout <<  "Абонент: " << UserMas[i].username << endl;
			aht++;
		}
	}
	if (aht == 0) {
		system("cls");
		cout << "Помимо вас ни один абонет не подключил тариф." << endl;
		Rankusermenu();
	}
	cout << "Введите имя абонента, которому хотите набрать: " << endl;
	
	cin >> abonent;
	bool valid = false;
	for (int i = 0; i < sizer; i++) {
		if (UserMas[i].username == abonent) {
			valid = true;
			break;
		}
	}
	if (!valid) {
		cout << "Ошибка юзернейма." << endl;
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
	cout << "Имя Пользователя: " << UserMas[UserID].username << endl;
	cout << "Баланс: " << UserMas[UserID].balance << endl;
	if (UserMas[UserID].rate == "NONE") {
		cout << "Тариф не выбран" << endl;
	}
	else cout << "Тариф: " << UserMas[UserID].rate << endl;
	cout << "Промокод " << UserMas[UserID].promo << endl;
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
	cout << "1. Мой профиль" << endl;
	cout << "2. Промокоды" << endl;
	cout << "3. Тарифы" << endl;
	cout << "4. Звонки" << endl;
	cout << "5. Почта" << endl;
	cout << "6. Выйти из аккаунта" << endl;
	cout << "7. Выйти из приложения" << endl;
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
			cout << "Промокод не введён. Для получения промокода обратитесь к администрации. Если же у вас имеется промокод и вы желаете его ввести, введите 'promo'. Для выхода введите 'exit'" << endl;
			cin >> promocheck;
			if (promocheck == "promo") {
				string promokey;
				cout << "Введите промокод: " << endl;
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
					cout << "Ошибка промокода" << endl;
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
			cout << "Промокод уже введён. " << endl;
			Rankusermenu();
		}

	}
	if (oper == 3) {
		system("cls");
		if (UserMas[UserID].rate == "NONE") {
			cout << "Тариф еще не выбран." << endl << endl;
			cout << "Доступные тарифы: " << endl;
			cout << "1. Тариф 'На связи' (1руб./м) " << endl;
			cout << "2. Тариф 'Малый повзрослел' (5руб./м) " << endl;
			cout << "3. Тариф 'LUXE' (10руб./м) " << endl;
			int chrate;
			cin >> chrate;
			if (chrate == 1) {
				system("cls");
				cout << "Вы успешно подключились к тарифу " << endl;
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
				cout << "Вы успешно подключились к тарифу " << endl;
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
				cout << "Вы успешно подключились к тарифу " << endl;
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
			cout << "У вас уже подключен тариф. В случае, если вы хотите его изменить, наберите 'switch'. Для выхода наберите 'exit' " << endl;
			string swrate;
			cin >> swrate;
			if (swrate == "switch") {			
				cout << "Вы успешно отключились от тарифа " << endl;
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
			cout << "Приветствуем вас, " << UserMas[UserID].username << endl;
			double price;
			string nrate;
			double promobonus = 1;
			if (UserMas[UserID].promo == "active") {
				promobonus = 0.5;
				cout << "Действует промокод: Скидка 50%" << endl;
			}
			if (UserMas[UserID].rate == "svyas") {
				price = 1.0 / 60.0 * promobonus;
				nrate = "Тариф 'На связи'";
			}
			else if (UserMas[UserID].rate == "povz") {
				price = 5.0 / 60.0 * promobonus;
				nrate = "Тариф 'Малый повзрослел'";
			}
			else if (UserMas[UserID].rate == "luxe") {
				price = 10.0 / 60.0 * promobonus;
				nrate = "Тариф 'LUXE'";
			}
			cout << "Выбранный тариф:" << nrate << endl;
			cout << "Стоимость звонка в секунду: " << price << endl << endl;
			cout << "Меню вызовов: " << endl;
			cout << "1. Позвонить " << endl;
			cout << "2. История вызовов" << endl;
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
				cout << "Ошибка ввода." << endl;
				Rankusermenu();
			}

		}
		else {
			system("cls");
			cout << "Вы не можете совершать звонки, так как ваш тариф не выбран." << endl;
			Rankusermenu();
		}
	}
	if (oper == 5)
	{
		system("cls");
		cout << "1. Просмотреть сообщений" << endl;
		cout << "2. Связь с администрацией" << endl;
		cout << "3. Вернуться в меню" << endl;
		int nmail;
		cin >> nmail;
			if (nmail == 1) {
				system("cls");
				cout << "Cообщения: " << endl << endl;
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
						cout << "У вас нет сообщений." << std::endl;
					}
					cout << endl;
					cout << "Для выхода напишите exit" << endl;
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
				cout << "Введите сообщение, которое будет отправлено администрации: " << endl;
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
