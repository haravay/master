#include "includes.h"
#include "authfunctions.h"
#include <Windows.h>
using namespace std;

int main()
{
    for (int i = 0; i < sizer; i++) {
        info[i] = new string[cols];
    }
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    auth();
}

