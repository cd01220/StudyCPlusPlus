#ifndef _TestList_h_
#define _TestList_h_
#include "SystemInclude.h"

#include "List.h"
#include "ContainerBase.h"

#ifdef ContainerModule
#ifdef _WIN32
inline List<int>::iterator GetIter()
{
    const int intArray[5] = {1, 2, 3, 4, 5};    
    List<int> intList(intArray, intArray+5);
    List<int>::iterator iter = intList.Begin();

    std::cout << iter.GetContainer() << std::endl;
    return iter;
}

inline void TestIllegalOperation()
{
    List<int>::iterator iter = GetIter();
    std::cout << iter.GetContainer() << std::endl;
    //runtime error, iterator is not dereferencable.  because of the container has been freed.
    std::cout << *iter << std::endl;  
}

#endif
#endif
#endif
