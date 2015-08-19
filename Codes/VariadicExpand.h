#ifndef _VariadicExpand_h_
#define _VariadicExpand_h_

#ifdef _WIN32
#include <memory>
#include <xstddef>

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
    

/* Example
int main()
{
    DescriptorFactory0 a;
    DescriptorFactory1<int> b;
    DescriptorFactory2<int, int> c;
    DescriptorFactory2<char*, char*> d;

    a.Create();
    b.Create(1);
    c.Create(1, 2);
    d.Create("aaaa", "bbb");
    return 0;
}
*/
class Descriptor
{
public:
    Descriptor() {}
    Descriptor(int) {}
    Descriptor(int, int) { std::cout << "int, int" << std::endl; }
    Descriptor(const char*, const char*) { std::cout << "char*, char*" << std::endl;}
};

#define DefineDescriptorFactory(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
    class DescriptorFactory ## X1 \
    { \
    public: \
        Descriptor* Create(LIST(_TYPE_ARG)) \
        { \
            return new Descriptor(LIST(_VAR_VAL)); \
        } \
    };

_VARIADIC_EXPAND_0(DefineDescriptorFactory, 0, , , )
_VARIADIC_EXPAND_1(DefineDescriptorFactory, 1, , , )
_VARIADIC_EXPAND_2(DefineDescriptorFactory, 2, , , )
_VARIADIC_EXPAND_3(DefineDescriptorFactory, 3, , , )
_VARIADIC_EXPAND_4(DefineDescriptorFactory, 4, , , )
#undef DefineDescriptorFactory

#endif //#ifdef _WIN32
#endif