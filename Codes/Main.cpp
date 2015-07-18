#include "SystemInclude.h"
#include "Common.h"
#include "Debug.h"
#include "SystemError.h" 
#include "Iterator.h"
#include "Main.h"

using namespace std;

int main()
{
    //Container container;
    //Container::Iterator iter;
    //for (iter = container.Begin(); iter != container.End(); ++iter)
    //{
    //    cout << " " << *iter;
    //}

    int intArray[5] = {0,1,2,3,4};
    list<int> intList(intArray, intArray + 5);
    list<int>::iterator iter = intList.begin();
    ++iter;

	return 0;
}
