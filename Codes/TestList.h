#ifndef _TestMyList_h_
#define _TestMyList_h_

#include "List.h"

typedef List<int> IntList;

inline IntList::iterator GetIter()
{
    const int intArray[5] = {1, 2, 3, 4, 5};    
    IntList intList(intArray, intArray+5);
    IntList::iterator iter = intList.Begin();

    std::cout << iter.GetContainer() << std::endl;
    return iter;
}

inline void TestIllegalOperation()
{
    IntList::iterator iter = GetIter();
    std::cout << iter.GetContainer() << std::endl;
    std::cout << *iter << std::endl;  //runtime error, iterator is not dereferencable
}

#endif
