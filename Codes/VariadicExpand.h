#ifndef _VariadicExpand_h_
#define _VariadicExpand_h_

#include "SystemInclude.h"

#ifdef VariadicExpandModule
#ifdef _WIN32
#include <memory>
#include <xstddef>

/******************* Variadic Function *******************/
/* descript how to use _VARIADIC_EXPAND_0X,  just like std::list to define class _List_buy.
   Example:
int main()
{
    Nodeptr ptr1 = AllocatNode(1);
    Nodeptr ptr2 = AllocatNode(1, 2);
    return 0;
}
*/

struct Node
{
    Node(): x(0), y(0) {}
    Node(int x): x(x), y(0) {}
    Node(int x, int y): x(x), y(y) {}
    int x, y;
};

typedef Node* Nodeptr;

#define AllocatNodeMacro(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
	inline Nodeptr AllocatNode(LIST(_TYPE_REFREF_ARG)) \
	{	/* allocate a node and set links and value */ \
        std::allocator<Node> myAllocator; \
	    Nodeptr node = myAllocator.allocate(1); \
        myAllocator.construct(node COMMA LIST(_FORWARD_ARG)); \
	    return (node); \
	}

_VARIADIC_EXPAND_0X(AllocatNodeMacro, , , , )
#undef AllocatNodeMacro


/******************* Variadic Class *******************/
/* CreateDescriptor() function can create class instance according to:  
    1 value of tag.
    2 variadic parameter,  both parameter number and parameter's type.

example:
    static AutoRegisterSuite des1_1(1, new ConcreateCreator<1, std::tuple<int>>);
    static AutoRegisterSuite des1_2_1(1, new ConcreateCreator<1, std::tuple<int, int>>);
    static AutoRegisterSuite des1_2_2(1, new ConcreateCreator<1, std::tuple<int, char*>>);
    static AutoRegisterSuite des2_1(2, new ConcreateCreator<2, std::tuple<int>>);
    
    int main()
    {
        CreateDescriptor(1, 1);
        CreateDescriptor(1, 1, 2);
        CreateDescriptor(1, 1, (char*)"abcd");
        CreateDescriptor(2, 1);
    
        return 0;
    }
*/
template<class Tuple>
struct DescriptorCreator
{	
    public: virtual void Create(Tuple) { std::cout << "DescriptorCreator" << std::endl; }
};

template<uchar_t tag, class Tuple>
class ConcreateCreator
{};

/**********************class NetworkNameDescriptor and Creator**********************/
class NetworkNameDescriptor
{
public:
    NetworkNameDescriptor(int v1) { std::cout << "tag1, " << v1 << std::endl; }
    NetworkNameDescriptor(int v1, int v2) { std::cout << "tag1, " << v1 << ", " << v2 << std::endl; }
    NetworkNameDescriptor(int v1, char* v2) { std::cout << "tag1, " << v1 << ", " << v2 << std::endl; }
};

template<class T1>
class ConcreateCreator<1, std::tuple<T1>>: public DescriptorCreator<std::tuple<T1>>
{
public:
    ConcreateCreator() { }

    void Create(std::tuple<T1> tp)
    {
        NetworkNameDescriptor *ptr = new NetworkNameDescriptor(std::get<0>(tp));
    }
};

template<class T1, class T2>
class ConcreateCreator<1, std::tuple<T1, T2>>: public DescriptorCreator<std::tuple<T1, T2>>
{
public:
    ConcreateCreator() {}

    void Create(std::tuple<T1, T2> tp)
    {
        NetworkNameDescriptor *ptr = new NetworkNameDescriptor(std::get<0>(tp), std::get<1>(tp));
    }
};

/**********************class ServiceListDescriptor and Creator**********************/
class ServiceListDescriptor
{
public:
    ServiceListDescriptor(int v1) { std::cout << "tag2, " << v1 << std::endl; }
    ServiceListDescriptor(int v1, int v2) { std::cout << "tag2, " << v1 << ", " << v2 << std::endl; }
    ServiceListDescriptor(int v1, char* v2) { std::cout << "tag2, " << v1 << ", " << v2 << std::endl; }
};

template<class T1>
class ConcreateCreator<2, std::tuple<T1>>: public DescriptorCreator<std::tuple<T1>>
{
public:
    ConcreateCreator() { }

    void Create(std::tuple<T1> tp)
    {
        ServiceListDescriptor *ptr = new ServiceListDescriptor(std::get<0>(tp));
    }
};

/**********************class Factory**********************/
template<class T>
class Factory
{
public:
    static Factory* GetInstance()
    {
        static Factory<T> instance;
        return &instance;
    }

    void Register(uchar_t tag, DescriptorCreator<T> *creator)
    {
        factory.insert(make_pair(tag, creator));
    }

    void Create(uchar_t tag, T value)
    {
        auto iter = factory.find(tag);
        if (iter == factory.end())
        {
            std::cout << "no creator" << std::endl;
            return;
        }

        DescriptorCreator<T> *creator = iter->second;
        creator->Create(value);
    }

private:    
    std::map<uchar_t, DescriptorCreator<T>*> factory;
};

#define CreateDescriptorMacro(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
	inline void CreateDescriptor(uchar_t tag COMMA LIST(_TYPE_ARG)) \
	{	\
        Factory<std::tuple<LIST(_VAR_TYPE)>> *instance = Factory<std::tuple<LIST(_VAR_TYPE)>>::GetInstance(); \
        instance->Create(tag, std::tuple<LIST(_VAR_TYPE)>(LIST(_VAR_VAL)) );\
	    return; \
	}

_VARIADIC_EXPAND_0X(CreateDescriptorMacro, , , , )
#undef CreateDescriptorMacro

class AutoRegisterSuite
{
public:
    template <typename T>
    AutoRegisterSuite(uchar_t tag, DescriptorCreator<T> *creator)
    {
        Factory<T> *instance1 = Factory<T>::GetInstance();
        instance1->Register(tag, creator);
    }
};


#endif //#ifdef _WIN32
#endif
#endif