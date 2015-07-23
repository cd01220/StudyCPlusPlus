#ifndef _TestList_h_
#define _TestList_h_

#include "List.h"
#include "MyContainer.h"

inline MyStlList::List<int>::iterator GetIter()
{
    const int intArray[5] = {1, 2, 3, 4, 5};    
    MyStlList::List<int> intList(intArray, intArray+5);
    MyStlList::List<int>::iterator iter = intList.Begin();

    std::cout << iter.GetContainer() << std::endl;
    return iter;
}

inline void TestIllegalOperation()
{
    MyStlList::List<int>::iterator iter = GetIter();
    std::cout << iter.GetContainer() << std::endl;
    std::cout << *iter << std::endl;  //runtime error, iterator is not dereferencable
}


inline void TestMyContainer()
{
    Container container;
    container.Add(1);
    container.Add(2);

    Container::iterator iter;
    for (iter = container.Begin(); iter != container.End(); ++iter)
    {
        std::cout << *iter << ", ";
    }
}

#endif
