#include "includes.h"
#include "values.h"
#include "userinterface.h"
using namespace std;
void checking();
void newacc();
void acc();
void usermenu();
void adminmenu();
void deleteacc();
void auth();
bool newnamecheck(string login);
void newuser();
void regconfirm();
void userdell();
void nadminlist();
void addadm();
bool isNumeric(string const& str);
string promogeneration();

bool isNumeric(string const& str)
{
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

void checking() {
    string login, pass;
    cout << "���������� ����� � �������!" << endl;
    cout << "������� �����: " << endl;
    cin >> login;
    cout << "������� ������: " << endl;
    cin >> pass;
}

void newacc() {
    ofstream file;
    string login, pass, token, access;
    file.open("data.txt", ios::app);
    cout << "������� ����� ������ ��������: " << endl;
    cin >> login;
    if (newnamecheck(login) == true) {
        cout << "������� ������ ������ ��������: " << endl;
        char password[256];
        char c;
        int i = 0;
        while ((c = _getch()) != '\r')
        {
            password[i++] = c;
            _putch('*');
        }
        password[i] = '\0';
        string str(password, i);


        cout << "����� �� ��������� user." << endl;
        token = "user";
        access = "1";
        file << login << " " << str << " " << token << " " << access << endl;
        file.close();
    }
    else {
        cout << "��� ������� ��� �����. ���������� ������" << endl;
        file.close();
        newacc();
    }
    fstream F;
    F.open("data.txt");
    if (F)
    {
        while (!F.eof())
        {
            for (int i = 0; i < sizer; i++) {
                for (int j = 0; j < 4; j++) {
                    F >> info[i][j];
                }
            }
        }
    }
    system("cls");
    adminmenu();
}

void nadminlist() {
    for (int i = 0; i < sizer; i++) {
        if (info[i][0] == "") addadm();
        else if (info[i][0] == info[i + 1][0]) continue;
        cout << (i + 1) << ". ";
        for (int j = 0; j < 4; j++) {
            cout << info[i][j] << " ";
        }
        cout << endl;
    }
}

void addadm() {
    cout << "�������� ����� ������������, �������� ������ ������ ������ ��������������:(��� ������ �� ������� ���� ������� 1212)" << endl;
    string s;
    cin >> s;
    if (isNumeric(s)) {
        int c = stoi(s);

        if (c == 1212) {
            system("cls");
            adminmenu();
        }
        if (info[c - 1][2] != "admin") {
            cout << "�� �������, ��� ������ ��������� ������������ " << info[c - 1][0] << " ���������������? (yes/no)" << endl;
            string arg;
            cin >> arg;
            if (arg == "yes") {
                info[c - 1][2] = "admin";
                ofstream file;
                file.open("data.txt");
                for (int i = 0; i < sizer; i++) {
                    if (info[i][0] == "") {
                        file.close();
                        system("cls");
                        cout << "����� �������������� ������� ������" << endl;
                        acc();
                    }
                    for (int j = 0; j < 4; j++) {
                        file << info[i][j] << " ";
                    }
                    file << endl;
                }

            }
            else if (arg == "no") {
                acc();
            }
            else {
                system("cls");
                cout << "������ �����." << endl;
                nadminlist();
            }
        }
        else {
            system("cls");
            cout << "������ ������������ ��� �������� ���������������." << endl;
            acc();
        }
    }
    else {
        system("cls");
        cout << "������������ ����." << endl;
        nadminlist();
    }
}

void acc() {
    cout << "�������� �����: " << endl;
    cout << "1. ���������� ������ ��������������" << endl;
    cout << "2. �������� �������� ������������" << endl;
    cout << "3. ��������� � ����� ������" << endl;
    int a;
    cin >> a;
    system("cls");
    if (a == 1) {
        nadminlist();
    }
    if (a == 2) {
        userdell();
    }
    if (a == 3) {
        adminmenu();
    }
}

void newuser() {
    fstream F;
    ofstream file;
    string login, pass, token, access = "0";
    file.open("data.txt", ios::app);
    cout << "������� ����� ������ ��������: " << endl;
    cin >> login;
    F.open("data.txt");
    for (int i = 0; i < sizer; i++) {
        for (int j = 0; j < 4; j++) {
            F >> info[i][j];
        }
    }
    if (newnamecheck(login) == true) {
        cout << "������� ������ ������ ��������: " << endl;
        char password[256];
        char c;
        int i = 0;
        while ((c = _getch()) != '\r')
        {
            password[i++] = c;
            _putch('*');
        }
        password[i] = '\0';
        string str(password, i);
        cout << "����� �� ��������� user." << endl;
        token = "user";
        file << login << " " << str << " " << token << " " << access << endl;
        file.close();
    }
    else {
        cout << "��� ������� ��� �����. ���������� ������" << endl;
        file.close();
        F.close();
        newuser();
    }
    if (F)
    {
        while (!F.eof())
        {
            for (int i = 0; i < sizer; i++) {
                for (int j = 0; j < 4; j++) {
                    F >> info[i][j];
                }
            }
        }
    }
    F.close();
    system("cls");
    cout << "������ �� ����������� ������� ������! ��������." << endl;
    auth();
}


void usermenu() {
    system("cls");
    UserDataCheck(currentuser);
}

void adminmenu() {
    cout << "�������� ����� ����: " << endl;
    cout << "1. �������� ������ ��������" << endl;
    cout << "2. ���������� ������ �������������" << endl;
    cout << "3. ����� �������" << endl;
    cout << "4. ������� �� �����������" << endl;
    cout << "5. ����� �� ��������" << endl;
    cout << "6. �����" << endl;
    cout << "7. ���������" << endl;
    cout << "8. ����� �� ����������" << endl;

    int a;
    cin >> a;
    system("cls");
    if (a == 1)
        newacc();
    bool end = false;
    if (a == 2) {

        cout << "\t�����\t\t" << "\t\t������\t\t " << "\t\t����" << endl;
        for (int i = 0; i < sizer * 4 + 9; i++) {          
                cout << "-";
        }
        cout << endl;
        for (int i = 0; i < sizer; i++) {
            if (info[i][3] == "0" || info[i][0] == info[i + 1][0]) continue;
            for (int j = 0; j < 3; j++) {

                if (j != 0)

                    cout << "\t" << info[i][j] << "\t\t-\t ";
                else cout << "-\t" << info[i][j] << "\t\t-\t ";
            }


            if (info[i + 1][0] == "") {
                cout << endl;

                for (int i = 0; i < sizer * 4 + 9; i++) {
                        cout << "-";
                }
                cout << endl;

                adminmenu();
            }
            cout << endl;
            for (int i = 0; i < sizer * 4 + 9; i++) {
                    cout << "-";
            }

            cout << endl;
        }
        cout << endl;

    }
    if (a == 3) {
        acc();
    }
    if (a == 4)
        regconfirm();


    if (a == 5)
        auth();
    if (a == 6) {

        ofstream userdata;
        fstream FL;
        bool valid = false;
        FL.open("userdb.txt");
        if (FL) {
            for (int i = 0; i < sizer; i++) {

                FL >> UserMas[i].username;
                if (UserMas[i].username == currentuser ) {
                    valid = true;
                    UserID = i;
                }
                FL >> UserMas[i].balance;
                FL >> UserMas[i].rate;
                FL >> UserMas[i].registrationdata;
                FL >> UserMas[i].promo;

            }
        }






        ofstream supportmsg;
        fstream SUP;
        system("cls");

        int k = 1;
        ifstream file("userdb.txt"); 
        cout << "������ �������������, ������� ����� ���������: " << endl;
        if (file.is_open()) {
            string line;
            while (std::getline(file, line)) {
                istringstream iss(line); 
                string word;
                iss >> word;
                cout << k << ". " << word << endl; 
                k++;
            }
        }


        supportmsg.open("support.txt", ios::app);

        cout << "���� ������ ���������?" << endl;
        string ans;
        cin >> ans;
        ans = "adminto" + ans;
        cout << "������� ���������, ������� ����� ���������� ������������: " << endl;
        string ms2g;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, ms2g); 

        supportmsg << ans << ": " << ms2g << endl;
        supportmsg.close();



    }
    if (a == 7) {

        system("cls");
        cout << "1. ������� ����� �������� � ��������� ��� �� ����� ������������" << endl;
        cout << "2. ����� � ������� ����" << endl;
        string promoch;
        cin >> promoch;
        if (promoch == "1") {
            int k = 1;
            ifstream file("userdb.txt"); 
            cout << "������ �������������, ������� ����� ��������� ��������: " << endl;
            if (file.is_open()) {
                string line;
                while (std::getline(file, line)) {
                    istringstream iss(line); 
                    string word;
                    iss >> word; 
                    cout << k << ". " << word << endl; 
                    k++;
                }
                ofstream supportmsg;
                supportmsg.open("support.txt", ios::app);

                cout << "���� ������ ���������?" << endl;
                string ans;
                cin >> ans;
                bool acc = false;
                ifstream file2("userdb.txt");
                while (std::getline(file2, line)) {
                    istringstream iss(line); 
                    string word;
                    iss >> word;
                    
                    if (word == ans) {
                        acc = true;
                        break;
                    }
             
                }
                if (!acc) {
                    system("cls");
                    cout << "������ ���������." << endl;
                    adminmenu();
                }               
                ans = "adminto" + ans;                
                bool error = true;
                string ms2g;
                while (error) {
                    string keycheck = promogeneration();
                    char kod[19];
                    for (int i = 0; i < 19; i++) {
                        kod[i] = (int)keycheck[i];
                    }
                    if ((kod[1] - kod[2]) < 4 && kod[5] - kod[9] < 75 && kod[0] + kod[11] + 1 == 2 * kod[16] && kod[18] % 2 == 0 && kod[17] % 2 == 1 && kod[4] == '-' && kod[9] == '-' && kod[14] == '-' && sqrt(kod[16]) + sqrt(kod[17]) >sqrt(kod[13]) + sqrt(kod[3])) {
                        if (kod[15] + kod[0] - kod[11] + kod[8] - kod[14] > 25 && kod[15] + kod[0] - kod[11] + kod[8] - kod[14] < 140) {
                            cout << keycheck << endl;
                            ms2g = keycheck;
                            error = false;
                        }
                    }
                }

                
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');               
                supportmsg << ans << ": ��� �������� - " << ms2g << endl;               
                supportmsg.close();
                system("cls");
                cout << "������� ����������." << endl;
                adminmenu();
            }
            else {
                cout << "error" << endl;
                adminmenu();
            }
        }
        else adminmenu();

    }
    if (a == 8) {
        delete[] UserMas;
        for (int i = 0; i < sizer; i++) {
            delete[] info[i];
        }
        delete[] info;
        exit(0);
    }
    else adminmenu();

}

string promogeneration() {
    string key;
    int doings = 0;
    int count = 0;
    int numeration = 0;
    string product[19];

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution <> distr('a', 'z');

    for (int i = 0; i < 19; i++) {
        product[i] = distr(gen);
    }

    int tester = 0;
    for (int i = 0; i < 19; i++) {

        if (tester == 4) {
            product[i] = "-";
            tester = -1;
        }
        tester += 1;
    }
    for (int i = 0; i < 19; i++) {
        key += product[i];
    }

    return key;
}


void userdell() {
    for (int i = 0; i < sizer; i++) {

        if (info[i][0] == "") deleteacc();
        else if (info[i][0] == info[i + 1][0]) continue;
        cout << (i + 1) << ". ";
        for (int j = 0; j < 4; j++) {
            cout << info[i][j] << " ";
        }
        cout << endl;
    }
}

void deleteacc() {
    cout << "�������� ����� ������������, �������� ������ �������:(��� ������ �� ������� ���� ������� 1212)" << endl;
    string s;
    cin >> s;

    if (isNumeric(s)) {
        int c = stoi(s);

        if (c != 1) {

            if (c == 1212) {
                system("cls");
                adminmenu();
            }

            if (info[c - 1][0] != "") {
                cout << "�� �������, ��� ������ ������� ������� ������������ " << info[c - 1][0] << "? (yes/no)" << endl;
                string arg;
                cin >> arg;
                if (arg == "yes") {
                    info[c - 1][0] = "";
                    info[c - 1][1] = "";
                    info[c - 1][2] = "";

                    ofstream file;
                    file.open("data.txt");

                    for (int i = 0; i < sizer; i++) {


                        if (info[i][1] == "" && info[i + 1][1] == "") break;
                        if (info[i][2] == "") i += 1;

                        for (int j = 0; j < 4; j++) {
                            if (info[i][0] != "")
                                file << info[i][j] << " ";

                        }
                        if (info[i][0] != "") file << endl;
                    }
                    file.close();

                    for (int i = 0; i < sizer; i++) {
                        delete[] info[i];
                    }
                    for (int i = 0; i < sizer; i++) {
                        info[i] = new string[cols];
                    }

                    fstream F;
                    F.open("data.txt");
                    for (int i = 0; i < sizer; i++) {
                        for (int j = 0; j < 4; j++) {
                            F >> info[i][j];
                        }
                    }
                    F.close();
                    acc();
                }
                else if (arg == "no") {
                    acc();
                }
                else {
                    system("cls");
                    cout << "������������ ����." << endl;
                    acc();
                }
            }
            else {
                system("cls");
                cout << "����� ������ ��� � ������!" << endl;
                userdell();
            }
        }
        else {
            cout << "������ ������� �������������� �������." << endl;
            acc();
        }

    }
    else {
        system("cls");
        cout << "������������ ������." << endl;
        userdell();
    }

}

bool newnamecheck(string login) {
    bool valid = true;
    for (int i = 0; i < sizer; i++) {
        if (info[i][0] == login) {
            valid = false;
        }
    }
    if (valid) return true;
    else return false;
}

void regconfirm() {
    bool valid = false;
    for (int i = 0; i < sizer; i++) {
        if (info[i][3] == "0" && info[i][2] != "")
            valid = true;
    }
    if (valid) {
        cout << "\t�����\t\t" << "\t\t������\t\t " << "\t\t����" << endl;
        for (int i = 0; i < sizer * 4 + 9; i++) {
            cout << "-";
        }
        cout << endl;
        for (int i = 0; i < sizer; i++) {
            if (info[i][3] != "0") continue;
            for (int j = 0; j < 3; j++) {
                if (j != 0)
                    cout << "\t" << info[i][j] << "\t\t-\t ";
                else cout << "-\t" << info[i][j] << "\t\t-\t ";
            }
            cout << endl;
            if (info[i + 1][0] == "") {
                cout << endl;
                for (int i = 0; i < sizer * 4 + 9; i++) {
                    cout << "-";
                }
                cout << endl;
            }
        }
        cout << "������� ����� ������������, ������� �������� ������ �����������: " << endl;
        string c;
        cin >> c;
        bool valid = false;
        for (int i = 0; i < sizer; i++) {
            if (info[i][0] == c) {
                if (info[i][3] == "0") {
                    valid = true;
                    cout << "�� �������, ��� ������ ����������� ����������� ��������  " << c << " (yes/no)" << endl;
                    string arg;
                    cin >> arg;
                    if (arg == "yes") {
                        info[i][3] = "1";
                        ofstream file;
                        file.open("data.txt");
                        for (int i = 0; i < sizer; i++) {
                            if (info[i][0] == "") {
                                file.close();
                                system("cls");
                                cout << "������� ������� ��������!" << endl << endl;
                                adminmenu();
                            }
                            for (int j = 0; j < 4; j++) {
                                file << info[i][j] << " ";
                            }
                            file << endl;
                        }
                    }
                    else {
                        system("cls");
                        adminmenu();
                    }
                }
            }
        }
        if (!valid) {
            system("cls");
            cout << "������ ���������." << endl;
            adminmenu();
        }
    }
    else {
        system("cls");
        cout << "��� ������ �� �����������." << endl;
        adminmenu();
    }
}


void auth() {
    ofstream file;
    string login, pass, token, access;
    string loginc, passc;
    fstream F;
    F.open("data.txt");
    if (F) {
        string s;
        cout << "�������� �����: " << endl;
        cout << "1. �����������" << endl;
        cout << "2. �����������" << endl;
        cout << "3. ����� �� ����������" << endl;
        cin >> s;
        if (isNumeric(s)) {
            int cn = stoi(s);

            if (cn == 1) {
                while (!F.eof())
                {
                    for (int i = 0; i < sizer; i++) {
                        for (int j = 0; j < 4; j++) {
                            F >> info[i][j];
                        }
                    }
                }
                cout << "���������� ����� � �������!" << endl;
                cout << "������� �����: " << endl;
                cin >> loginc;
                cout << "������� ������: " << endl;
                char password[256];
                char c;
                int i = 0;
                while ((c = _getch()) != '\r')
                {
                    password[i++] = c;
                    _putch('*');
                }
                password[i] = '\0';
                string str(password, i);
                bool valid = false;
                for (int i = 0; i < sizer; i++) {
                    if (info[i][0] == loginc && info[i][1] == str && info[i][2] == "admin") {
                        if (info[i][3] == "1") {
                            valid = true;
                            system("cls");
                            cout << "���� ������� (admin)" << endl;
                            currentuser = info[i][0];
                            adminmenu();
                        }
                        else {
                            cout << "��� ������� ��� �� ����������� ��������������." << endl << endl;
                            system("pause");
                        }
                    }
                    if (info[i][0] == loginc && info[i][1] == str && info[i][2] == "user") {
                        if (info[i][3] == "1") {
                            valid = true;
                            cout << "���� ������� (user)" << endl;
                            currentuser = info[i][0];
                            usermenu();
                        }
                        else {
                            cout << "��� ������� ��� �� ����������� ��������������." << endl << endl;
                            system("pause");
                        }
                    }
                    cout << endl;
                }
                if (!valid) {
                    system("cls");
                    cout << "������ �����" << endl;
                    auth();
                }
                F.close();
            }
            else if (cn == 2) {
                newuser();
            }
            else if (cn == 3) {
                delete[] UserMas;

                for (int i = 0; i < sizer; i++) {
                    delete[] info[i];
                }
                delete[] info;
                exit(0);
            }
            else if (cn > 3) {
                system("cls");
                cout << "������������ ����." << endl;
                auth();
            }
        }
        else {
            system("cls");
            cout << "������������ ������." << endl;
            auth();
        }
    }
    else {
        file.open("data.txt", ios::app);
        cout << "�� ������� �� ������ ��������. ��������� � �����������!" << endl;
        cout << "������� �����: " << endl;
        cin >> login;
        cout << "������� ������: " << endl;

        char password[256];
        char c;
        int i = 0;
        int y = 1;
        while ((c = _getch()) != '\r')
        {
            password[i++] = c;
            _putch('*');
        }
        password[i] = '\0';
        string str(password, i);

        system("cls");
        cout << "��� ������������� ����� ������, �.�. ������ ������� �������� ��������� ��������������." << endl;
        token = "admin";
        access = "1";
        file << login << " " << str << " " << token << " " << access << endl;
        for (int i = 0; i < sizer; i++) {
            for (int j = 0; j < 4; j++) {
                F >> info[i][j];
            }
        }
        F.close();
        file.close();
        currentuser = info[i][0];
        adminmenu();
    }

}