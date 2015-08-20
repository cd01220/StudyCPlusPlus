#ifndef _ClassCreator_h_
#define _ClassCreator_h_

#ifdef _WIN32

#include "SystemInclude.h"

class Descriptor
{
public:
    virtual uchar_t GetTag() const = 0;
    virtual size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const = 0;
};

class NetworkNameDescriptor: public Descriptor
{
public:
    enum: uchar_t {Tag  = 0x40};
    /* Function 类型定义, 用于获取重载函数的指针 */
    typedef Descriptor*(*Constructor1)(int);
    typedef Descriptor*(*Constructor2)(uchar_t*, size_t);

    uchar_t GetTag() const 
    { return Tag; }

    size_t MakeCodes(uchar_t *buffer, size_t bufferSize) const
    { return 0; }

    static Descriptor* CreateInstance(int)
    {
        return new NetworkNameDescriptor;
    }

    static Descriptor* CreateInstance(uchar_t*, size_t)
    {
        return new NetworkNameDescriptor;
    }
};

/**********************class DescriptorFactory**********************/
#define DefineDescriptorFactory(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
    class DescriptorFactory ## X1 \
    { \
    public: \
        typedef std::function<Descriptor*(LIST(_TYPE))> DescriptorCreator;\
        void Register(uchar_t type, DescriptorCreator creator) \
        { \
            creators.insert(make_pair(type, creator)); \
        } \
        Descriptor* Create(uchar_t type COMMA LIST(_TYPE_ARG)) \
        { \
            auto iter = creators.find(type); \
            if (iter == creators.end()) \
                return nullptr; \
            return iter->second(LIST(_ARG)); \
        } \
        static DescriptorFactory ## X1& GetInstance() \
        { \
            static DescriptorFactory ## X1<LIST(_TYPE)> instance; \
            return instance; \
        } \
    private: \
        DescriptorFactory ## X1 () {} \
        std::map<uchar_t, DescriptorCreator> creators; \
    }; 

_VARIADIC_EXPAND_1(DefineDescriptorFactory, 1, , , )
_VARIADIC_EXPAND_2(DefineDescriptorFactory, 2, , , )
_VARIADIC_EXPAND_3(DefineDescriptorFactory, 3, , , )
_VARIADIC_EXPAND_4(DefineDescriptorFactory, 4, , , )
#undef DefineDescriptorFactory

/**********************class AutoRegisterSuite**********************/
#define DefineAutoRegisterSuite(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
    class AutoRegisterSuite ## X1 \
    { \
    public: \
        typedef std::function<Descriptor*(LIST(_TYPE))> DescriptorCreator;\
        AutoRegisterSuite ## X1 (uchar_t type, DescriptorCreator creator) \
        { \
            DescriptorFactory ## X1<LIST(_TYPE)>& factory = DescriptorFactory ## X1<LIST(_TYPE)>::GetInstance(); \
            factory.Register(type, creator); \
        } \
    };

_VARIADIC_EXPAND_1(DefineAutoRegisterSuite, 1, , , )
_VARIADIC_EXPAND_2(DefineAutoRegisterSuite, 2, , , )
_VARIADIC_EXPAND_3(DefineAutoRegisterSuite, 3, , , )
_VARIADIC_EXPAND_4(DefineAutoRegisterSuite, 4, , , )
#undef DefineAutoRegisterSuite

/*
 * From boost documentation:
 * The following piece of macro magic joins the two 
 * arguments together, even when one of the arguments is
 * itself a macro (see 16.3.1 in C++ standard).  The key
 * is that macro expansion of macro arguments does not
 * occur in JoinName2 but does in JoinName.
 */
#define JoinName(symbol1, symbol2)  JoinName1(symbol1, symbol2)
#define JoinName1(symbol1, symbol2) JoinName2(symbol1, symbol2)
#define JoinName2(symbol1, symbol2) symbol1##symbol2

#define DescriptorCreatorRgistration1(type, creator, template1)      \
    static AutoRegisterSuite1<template1>  JoinName(descriptorCreator, __LINE__)(type, creator)

#define DescriptorCreatorRgistration2(type, creator, template1, template2)      \
    static AutoRegisterSuite2<template1, template2>  JoinName(descriptorCreator, __LINE__)(type, creator)

/**********************Function CreateDescriptor**********************/
#define DefineCreate(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
    inline Descriptor* CreateDescriptor ## X1(uchar_t type COMMA LIST(_TYPE_REFREF_ARG)) \
    { \
        DescriptorFactory ## X1<LIST(_TYPE)>& instance =DescriptorFactory ## X1<LIST(_TYPE)>::GetInstance(); \
        return instance.Create(type COMMA LIST(_FORWARD_ARG)); \
    };

_VARIADIC_EXPAND_1(DefineCreate, 1, , , )
_VARIADIC_EXPAND_2(DefineCreate, 2, , , )
_VARIADIC_EXPAND_3(DefineCreate, 3, , , )
_VARIADIC_EXPAND_4(DefineCreate, 4, , , )
#undef DefineCreate

/* Example
DescriptorCreatorRgistration1(NetworkNameDescriptor::Tag, 
                              (NetworkNameDescriptor::Constructor1)NetworkNameDescriptor::CreateInstance, int);
DescriptorCreatorRgistration2(NetworkNameDescriptor::Tag, 
                              (NetworkNameDescriptor::Constructor2)NetworkNameDescriptor::CreateInstance, uchar_t*, size_t);

int main()
{
    Descriptor *ptr0 = CreateDescriptor1<int>(0x40, 1);
    Descriptor *ptr1 = CreateDescriptor2<uchar_t*, size_t>(0x40, (uchar_t*)"\x30\x31", 2);

    return 0;
}
*/

#endif //#ifdef _WIN32
#endif