#include <iostream>
#include "linked_list.h"
#include "secondary_indexing.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    SecondaryIndexing* secondIndex = new SecondaryIndexing();
    secondIndex->addIndexKey("lukas");
    cout << secondIndex->findIndexKey("lukas") << endl;

    secondIndex->addRegister("1", "lukas");
    secondIndex->addRegister("1", "lukas");
    secondIndex->addRegister("1", "lukas");
    secondIndex->addRegister("1", "lukas");

    secondIndex->addRegister("2", "lukas");
    secondIndex->addRegister("2", "lukas");

    cout << secondIndex->findIndexKey("lukas")->getQuantidadeNode("1") << endl;
    cout << secondIndex->findIndexKey("lukas")->getQuantidadeNode("2") << endl;
    cout << secondIndex->findIndexKey("lukas")->size() << endl;





}
