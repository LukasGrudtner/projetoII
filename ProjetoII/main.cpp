#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    LinkedList* list = new LinkedList();
    list->push_back("lukas");
    cout << list->contains("lukas");
}
