#include "secondary_indexing.h"
#include "control.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }
    Control* control = new Control(argc, argv);
    delete control;





}
