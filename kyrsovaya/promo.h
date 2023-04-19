#include "includes.h"
ofstream prom;
fstream P;
using namespace std;
bool promochecking(string kod) {
	if ((kod[1] - kod[2]) < 4 && kod[5] - kod[9] < 75 && kod[0] + kod[11] + 1 == 2 * kod[16] && kod[18] % 2 == 0 && kod[17] % 2 == 1 && kod[4] == '-' && kod[9] == '-' && kod[14] == '-' && sqrt(kod[16]) + sqrt(kod[17]) >sqrt(kod[13]) + sqrt(kod[3])) {
		if (kod[15] + kod[0] - kod[11] + kod[8] - kod[14] > 25 && kod[15] + kod[0] - kod[11] + kod[8] - kod[14] < 140) {
			P.open("promo.txt");
			if (P) {

				ifstream prommsg("promo.txt");
				fstream SUP;
				string line;
				bool found = false;
				string name = kod; 
				while (getline(prommsg, line)) {
					if (line.find(name) == 0) {
						istringstream iss(line); 
						string word;
						iss >> word; 
						string restOfLine;
						getline(iss, restOfLine); 
						cout << "[ Данный код уже был введён: ] " << word << endl;
						found = true;
						P.close();
						return false;
						break;

						
						
					}
				}
				if (!found) {
					prom.open("promo.txt", ios::app);
					prom << kod << endl;
					prom.close();
					P.close();			
					return true;
				}
			}
			else {
				prom.open("promo.txt", ios::app);
				prom << kod << endl;
				prom.close();
				P.close();				
				return true;
			}
		}
	}
	else return false;
}