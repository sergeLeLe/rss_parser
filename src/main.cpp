#include "ConsoleMenu.h"
#include "iostream"
//#include "Windows.h"

using namespace std;

int main() {

    setlocale(LC_ALL,"");
    //	SetConsoleCP(1251);
    //	SetConsoleOutputCP(1251);

    ConsoleMenu console;
    console.start();

    return 0;
}
