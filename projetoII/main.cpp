#include "secondary_indexing.h"
#include "control.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string a = "c", b = "abcdefghij";
    if (a > b)
        cout << "sim" << endl;
    else
        cout << "não" << endl;



    Control* control = new Control(argc, argv);
    delete control;





}
