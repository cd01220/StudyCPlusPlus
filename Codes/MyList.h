#ifndef _MyList_h_
#define _MyList_h_

#include "ContainerBase.h"

template<class _Category,
        class _ValueType,
        class _DifferenceType,
        class _Pointer,
        class _Reference,
        class _Base>
struct Iterator012: public Base
{   // base type for debugging iterator classes
    typedef _Category iterator_category;
    typedef _ValueType value_type;
    typedef _DifferenceType difference_type;
    typedef _DifferenceType distance_type;    // retained
    typedef _Pointer pointer;
    typedef _Reference reference;
};

/******** Template Class ListUncheckedConstIterator ********
    std::class _List_unchecked_const_iterator 
*/
template<class _MyList, class _Base = IteratorBase0>
class ListUncheckedConstIterator
    : public Iterator012<std::bidirectional_iterator_tag,
      typename _MyList::value_type,
      typename _MyList::difference_type,
      typename _MyList::const_pointer,
      typename _MyList::const_reference,
      _Base>
{   // unchecked iterator for non-mutable list
public:
    typedef ListUncheckedConstIterator<_MyList, _Base> MyIter;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename _MyList::NodePtr NodePtr;
    typedef typename _MyList::value_type value_type;
    typedef typename _MyList::difference_type difference_type;
    typedef typename _MyList::const_pointer pointer;
    typedef typename _MyList::const_reference reference;

    ListUncheckedConstIterator()
    : ptr(0)
    {   // construct with null node pointer
    }

    ListUncheckedConstIterator(NodePtr node, const _MyList *list)
    : ptr(node)
    {   // construct with node pointer _Pnode
        this->Adopt(list);
    }

    reference operator*() const
    {   // return designated value
        return (MyList::MyValue(ptr));
    }

    pointer operator->() const
    {   // return pointer to class object
        return (std::pointer_traits<pointer>::pointer_to(**this));
    }

    MyIter& operator++()
    {   // pre-increment
        ptr = MyList::GetNextNode(ptr);
        return (*this);
    }

    MyIter operator++(int)
    {   // post-increment
        MyIter _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    MyIter& operator--()
    {   // pre-decrement
        ptr = MyList::GetPrevNode(ptr);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }

    bool operator==(const MyIter& _Right) const
    {   // test for iterator equality
        return (ptr == _Right.ptr);
    }

    bool operator!=(const MyIter& _Right) const
    {   // test for iterator inequality
        return (!(*this == _Right));
    }

    NodePtr GetMyNode() const
    {   // return node pointer
        return (ptr);
    }

    NodePtr ptr;  // pointer to node
};

/******** Template Class ListUncheckedConstIterator ********
    std::_List_unchecked_iterator 
*/
template<class _MyList>
class ListUncheckedIterator
    : public ListUncheckedConstIterator<_MyList>
{   // unchecked iterator for mutable list
public:
    typedef ListUncheckedIterator<_MyList> MyIter;
    typedef ListUncheckedConstIterator<_MyList> MyBase;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename _MyList::NodePtr NodePtr;
    typedef typename _MyList::value_type value_type;
    typedef typename _MyList::difference_type difference_type;
    typedef typename _MyList::pointer pointer;
    typedef typename _MyList::reference reference;

    ListUncheckedIterator()
    {   // construct with null node
    }

    ListUncheckedIterator(NodePtr _Pnode, const _MyList *_Plist)
        : MyBase(_Pnode, _Plist)
    {   // construct with node pointer _Pnode
    }

    reference operator*() const
    {   // return designated value
        return ((reference) **(MyBase *) this);
    }

    pointer operator->() const
    {   // return pointer to class object
        return (std::pointer_traits<pointer>::pointer_to(**this));
    }

    MyIter& operator++()
    {   // pre-increment
        ++(*(MyBase *)this);
        return (*this);
    }

    MyIter operator++(int)
    {   // post-increment
        MyIter tmp = *this;
        ++*this;
        return (tmp);
    }

    MyIter& operator--()
    {   // pre-decrement
        --(*(MyBase *)this);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }
};

/******** Template Class ListConstIterator ********
    prototype: std::_List_const_iterator 
*/
template<class _MyList>
class ListConstIterator
    : public ListUncheckedConstIterator<_MyList, IteratorBase>
{   // iterator for non-mutable list
public:
    typedef ListConstIterator<_MyList> MyIter;
    typedef ListUncheckedConstIterator<_MyList, IteratorBase> MyBase;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename _MyList::NodePtr NodePtr;
    typedef typename _MyList::value_type value_type;
    typedef typename _MyList::difference_type difference_type;
    typedef typename _MyList::const_pointer pointer;
    typedef typename _MyList::const_reference reference;

    typedef ListUncheckedConstIterator<_MyList> UncheckedType;

    ListConstIterator()
        : MyBase()
    {   // construct with null node pointer
    }

    ListConstIterator(NodePtr _Pnode, const _MyList *_Plist)
        : MyBase(_Pnode, _Plist)
    {   // construct with node pointer _Pnode
    }    

    MyIter& Rechecked(UncheckedType _Right)
    {   // reset from unchecked iterator
        this->ptr = _Right.ptr;
        return (*this);
    }

    UncheckedType Unchecked() const
    {   // make an unchecked iterator
        return (UncheckedType(this->ptr, (_MyList *)this->_Getcont()));
    }

    reference operator*() const
    {   // return designated value
        return (MyList::MyValue(this->ptr));
    }

    MyIter& operator++()
    {   // pre-increment
        this->ptr = MyList::MyValue(this->ptr);
        return (*this);
    }

    MyIter operator++(int)
    {   // post-increment
        MyIter tmp = *this;
        ++*this;
        return (tmp);
    }

    MyIter& operator--()
    {   // pre-decrement
        this->ptr = MyList::GetPrevNode(this->ptr);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }

    bool operator==(const MyIter& _Right) const
    {   // test for iterator equality
        return (this->ptr == _Right.ptr);
    }

    bool operator!=(const MyIter& _Right) const
    {   // test for iterator inequality
        return (!(*this == _Right));
    }
};

template<class _MyList> inline
typename ListConstIterator<_MyList>::UncheckedType
Unchecked(ListConstIterator<_MyList> iter)
{   // convert to unchecked
    return (iter.Unchecked());
}

template<class _MyList>
inline ListConstIterator<_MyList>&
Rechecked(ListConstIterator<_MyList>& iter,    
          typename ListConstIterator<_MyList>::UncheckedType right)
{   // convert to checked
    return (iter.Rechecked(right));
}


/******** Template Class ListIterator ********
    prototype: std::_List_iterator 
*/
template<class MyList>
class ListIterator
    : public ListConstIterator<MyList>
{   // iterator for mutable list
public:
    typedef ListIterator<MyList> MyIter;
    typedef ListConstIterator<MyList> MyBase;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename MyList::NodePtr NodePtr;
    typedef typename MyList::value_type value_type;
    typedef typename MyList::difference_type difference_type;
    typedef typename MyList::pointer pointer;
    typedef typename MyList::reference reference;

    typedef ListUncheckedIterator<MyList> UncheckedType;

    ListIterator()
    {   // construct with null node
    }

    ListIterator(NodePtr node, const MyList *list)
        : MyBase(node, list)
    {   // construct with node pointer _Pnode
    }    

    MyIter& Rechecked(UncheckedType right)
    {   // reset from unchecked iterator
        this->ptr = right.ptr;
        return (*this);
    }

    UncheckedType Unchecked() const
    {   // make an unchecked iterator
        return (UncheckedType(this->ptr, (MyList *) this->GetContainer()));
    }

    reference operator*() const
    {   // return designated value
        return ((reference) **(MyBase *) this);
    }

    pointer operator->() const
    {   // return pointer to class object
        return (std::pointer_traits<pointer>::pointer_to(**this));
    }

    MyIter& operator++()
    {   // pre-increment
        ++(*(MyBase *) this);
        return (*this);
    }

    MyIter operator++(int)
    {   // post-increment
        MyIter _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    MyIter& operator--()
    {   // pre-decrement
        --(*(MyBase *) this);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }
};

template<class MyList>
inline typename ListIterator<MyList>::UncheckedType
Unchecked(ListIterator<MyList> iter)
{   // convert to unchecked
    return (iter.Unchecked());
}

template<class MyList> inline ListIterator<MyList>&
Rechecked(ListIterator<MyList>& iter,
    typename ListIterator<MyList>::UncheckedType right)
{   // convert to checked
    return (iter.Rechecked(right));
}

/******** Template Class ListIterTypes ********
    prototype: std::_List_iter_types 
*/
template<class ValueType,
    class SizeType,
    class DifferenceType,
    class Pointer,
    class ConstPointer,
    class Reference,
    class ConstReference,
    class NodePtrType>
struct ListIterTypes
{   // wraps types needed by iterators
    typedef ValueType value_type;
    typedef SizeType size_type;
    typedef DifferenceType difference_type;
    typedef Pointer pointer;
    typedef ConstPointer const_pointer;
    typedef Reference reference;
    typedef ConstReference const_reference;
    typedef NodePtrType NodePtr;
};

/******** Template Class ListNode ********
    prototype: std::_List_node 
*/
template<class ValueType,
    class VoidPtr>
struct ListNode
{   // list node
    VoidPtr next; // successor node, or first element if head
    VoidPtr prev; // predecessor node, or last element if head
    ValueType myValue; // the stored value, unused if head

private:
    ListNode& operator=(const ListNode&);
};

template<class ValueType>
struct ListNode<ValueType, void *>
{   // list node
    typedef ListNode<ValueType, void *> *NodePtr;
    NodePtr next; // successor node, or first element if head
    NodePtr prev; // predecessor node, or last element if head
    ValueType myValue; // the stored value, unused if head

private:
    ListNode& operator=(const ListNode&);
};

/******** Template Class ListSimpleTypes ********
    prototype: std::_List_simple_types 
*/
template<class Type>
struct ListSimpleTypes: public std::_Simple_types<Type>
{   // wraps types needed by iterators
    typedef ListNode<Type, void *> Node;
    typedef Node *NodePtr;
};

/******** Template Class ListBaseType ********
    prototype: std::_List_base_types 
*/
//template<class _Type = int, class _AllocatorType = std::allocator<Type>>
template<class _Type, class _AllocatorType>
struct ListBaseType
{   // types needed for a container base
    typedef _AllocatorType AllocatorType;
    typedef ListBaseType<_Type, AllocatorType> MyType;

    typedef typename _AllocatorType::template rebind<_Type>::other Allocator;

    typedef typename std::_Get_voidptr<Allocator, typename Allocator::pointer>::type VoidPtr;
    typedef ListNode<typename Allocator::value_type, VoidPtr> Node;

    typedef typename Allocator::template rebind<Node>::other NodeAllocator;
    typedef typename NodeAllocator::pointer NodePtr;
    typedef NodePtr& NodePtrRef;

    typedef typename std::_If<std::_Is_simple_alloc<Allocator>::value,
        ListSimpleTypes<typename Allocator::value_type>,
        ListIterTypes<typename Allocator::value_type,
            typename Allocator::size_type,
            typename Allocator::difference_type,
            typename Allocator::pointer,
            typename Allocator::const_pointer,
            typename Allocator::reference,
            typename Allocator::const_reference,
            NodePtr> >::type
    ValueType;
};

/******** Template Class ListValue ********
prototype: std::_List_val 
template para:  _ValueType, the list's emlement type, eg. ValueType is "ListSimpleTypes<int>" when list<int>.
*/
template<class _ValueType>
class ListValue: public ContainerBase
{   // base class for list to hold data
public:
    typedef ListValue<_ValueType> MyType;

    typedef typename _ValueType::NodePtr NodePtr;
    typedef NodePtr& NodePtrRef;

    typedef typename _ValueType::value_type value_type;
    typedef typename _ValueType::size_type size_type;
    typedef typename _ValueType::difference_type difference_type;
    typedef typename _ValueType::pointer pointer;
    typedef typename _ValueType::const_pointer const_pointer;
    typedef typename _ValueType::reference reference;
    typedef typename _ValueType::const_reference const_reference;

    typedef ListConstIterator<MyType> const_iterator;
    typedef ListIterator<MyType> iterator;

    typedef ListUncheckedConstIterator<MyType> UncheckedConstIterator;
    typedef ListUncheckedIterator<MyType> UncheckedIterator;

    ListValue()
    {   // initialize data
        this->myHead = 0;
        this->mySize = 0;
    }

    static NodePtrRef GetNextNode(NodePtr node)
    {   // return reference to successor pointer in node
        return ((NodePtrRef) node->next);
    }

    static NodePtrRef GetPrevNode(NodePtr node)
    {   // return reference to predecessor pointer in node
        return ((NodePtrRef) node->prev);
    }

    static reference GetValue(NodePtr node)
    {   // return reference to value in node
        return ((reference) node->myValue);
    }

    NodePtr myHead;   // pointer to head node
    size_type mySize;  // number of elements
};

/******** Template Class ListAlloc ********
    prototype: std::_List_alloc 
*/
template<bool AllocatorHasStorage, class _AllocatorType>
class ListAlloc: public ListValue<typename _AllocatorType::ValueType>
{   // base class for list to hold allocator with storage
public:
    typedef ListAlloc<AllocatorHasStorage, _AllocatorType> MyType;
    typedef ListValue<typename _AllocatorType::ValueType> MyBase;
    typedef typename _AllocatorType::Allocator Allocator;
    typedef typename _AllocatorType::NodeAllocator NodeAllocator;
    typedef typename _AllocatorType::Node Node;
    typedef typename _AllocatorType::NodePtr NodePtr;

    ListAlloc(const Allocator& allocator = Allocator())
        : nodeAllocator(allocator)
    {   // construct head node, allocator from Allocator
        this->myHead = BuyHeadNode();
    }

    ~ListAlloc()
    {   // destroy head node
        FreeHeadNode(this->myHead);
    }

    void ChangeAlloctor(const NodeAllocator& allocator)
    {   // replace old allocator
        nodeAllocator = allocator;
    }

    void SwapAlloctor(MyType& right)
    {   // swap allocators
        std::swap(nodeAllocator, right.nodeAllocator);
    }

    NodePtr BuyHeadNode()
    {   // get head node using current allocator
        return (BuyNode0(NodePtr(), NodePtr()));
    }

    void FreeHeadNode(NodePtr node)
    {   // free head node using current allocator
        nodeAllocator.destroy(std::addressof(this->GetNextNode(node)));
        nodeAllocator.destroy(std::addressof(this->GetPrevNode(node)));
        nodeAllocator.deallocate(node, 1);
    }

    NodePtr BuyNode0(NodePtr next, NodePtr prev)
    {   // allocate a node and set links
        NodePtr node = nodeAllocator.allocate(1);

        if (next == NodePtr())
        {   // point at self
            next = node;
            prev = node;
        }
        _TRY_BEGIN
            nodeAllocator.construct(std::addressof(this->GetNextNode(node)), next);
            nodeAllocator.construct(std::addressof(this->GetPrevNode(node)), prev);
        _CATCH_ALL
            nodeAllocator.deallocate(_Pnode, 1);
        _RERAISE;
        _CATCH_END

        return (node);
    }

    NodeAllocator& GetAllocator()
    {   // get reference to allocator
        return (nodeAllocator);
    }

    const NodeAllocator& GetAllocator() const
    {   // get reference to allocator
        return (nodeAllocator);
    }

    NodeAllocator nodeAllocator;   // allocator object for stored elements
};

//template<class AllocatorType = ListBaseType<int, std::allocator<Type>>>
template<class _AllocatorType>
class ListAlloc<false, _AllocatorType>
    : public ListValue<typename _AllocatorType::ValueType>
    {   // base class for list to hold allocator with no storage
public:
    typedef ListAlloc<false, _AllocatorType> MyType;
    typedef ListValue<typename _AllocatorType::ValueType> MyBase;
    typedef typename _AllocatorType::Allocator Allocator;
    typedef typename _AllocatorType::NodeAllocator NodeAllocator;
    typedef typename _AllocatorType::Node Node;
    typedef typename _AllocatorType::NodePtr NodePtr;

    ListAlloc(const Allocator& = Allocator())
    {   // construct head node, allocator from _Al
        this->myHead = BuyHeadNode();
    }

    ~ListAlloc()
    {   // destroy head node
        FreeHeadNode(this->myHead);
    }

    void ChangeAlloctor(const NodeAllocator&)
    {   // replace old allocator
    }

    void SwapAlloctor(MyType&)
    {   // swap allocators
    }

    NodePtr BuyHeadNode()
    {   // get head node using current allocator
        return (BuyNode0(NodePtr(), NodePtr()));
    }

    void FreeHeadNode(NodePtr node)
    {   // free head node using current allocator
        this->GetAllocator().destroy(std::addressof(this->GetNextNode(node)));
        this->GetAllocator().destroy(std::addressof(this->GetPrevNode(node)));
        this->GetAllocator().deallocate(node, 1);
    }

    NodePtr BuyNode0(NodePtr next, NodePtr prev)
    {   // allocate a node and set links
        NodePtr node = this->GetAllocator().allocate(1);

        if (next == NodePtr())
        {   // point at self
            next = node;
            prev = node;
        }
        _TRY_BEGIN
            this->GetAllocator().construct(std::addressof(this->GetNextNode(node)), next);
            this->GetAllocator().construct(std::addressof(this->GetPrevNode(node)), prev);
        _CATCH_ALL
            this->GetAllocator().deallocate(node, 1);
        _RERAISE;
        _CATCH_END

        return (node);
    }

    NodeAllocator GetAllocator() const
    {   // get reference to allocator
        return (NodeAllocator());
    }
};

/******** Template Class ListBuy ********
    prototype: std::_List_buy 
*/
//template<class Type = int, class AllocatorType = std::allocator<Type>> 
template<class _Type, class _AllocatorType>
class ListBuy
    : public ListAlloc<!std::is_empty<_AllocatorType>::value,
        ListBaseType<_Type, _AllocatorType> >
    {   // base class for list to hold buynode/freenode functions
public:
    typedef ListAlloc<!std::is_empty<_AllocatorType>::value,
        ListBaseType<_Type, _AllocatorType> > MyBase;
    typedef typename MyBase::NodeAllocator NodeAllocator;
    typedef typename MyBase::NodePtr NodePtr;

    ListBuy(const _AllocatorType& allocator = _AllocatorType())
        : MyBase(allocator)
    {   // construct from allocator
    }

    void FreeNode(NodePtr node)
    {   // give node back
        this->GetAllocator().destroy(addressof(this->GetNextNode(node)));
        this->GetAllocator().destroy(addressof(this->GetPrevNode(node)));
        this->GetAllocator().destroy(addressof(this->GetValue(node)));
        this->GetAllocator().deallocate(node, 1);
    }
};

/******** Template Class List ********
    prototype: std::list 
*/
template<class _Type, class _AllocatorType = allocator<_Type> >
class List : public ListBuy<_Type, _AllocatorType>
{   // bidirectional linked list
public:
    typedef List<_Type, _AllocatorType> MyType;
    typedef ListBuy<_Type, _AllocatorType> MyBase;
    typedef typename MyBase::Node Node;
    typedef typename MyBase::NodePtr NodePtr;
    typedef typename MyBase::NodeAllocator NodeAllocator;

    typedef _AllocatorType allocator_type;
    typedef typename MyBase::size_type size_type;
    typedef typename MyBase::difference_type difference_type;
    typedef typename MyBase::pointer pointer;
    typedef typename MyBase::const_pointer const_pointer;
    typedef typename MyBase::reference reference;
    typedef typename MyBase::const_reference const_reference;
    typedef typename MyBase::value_type value_type;

    typedef typename MyBase::const_iterator const_iterator;
    typedef typename MyBase::iterator iterator;
    typedef typename MyBase::UncheckedConstIterator UncheckedConstIterator;
    typedef typename MyBase::UncheckedIterator UncheckedIterator;
};

#endif /* _MyList_h_ */

