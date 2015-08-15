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

#endif //#ifdef _WIN32
#endif