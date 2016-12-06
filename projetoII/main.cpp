/*!
 *  \author Lukas Derner Grüdtner
 *  \author Luiz Felipe Ribeiro Baroncello
 *  \version 3.0
 *  \copyright General Public License version 2
 *
 */

#include <iostream>

#include "secondary_indexing.h"
#include "control.h"

using namespace std;

int main(int argc, char *argv[])
{
    Control* control = new Control(argc, argv);
    delete control;
}
