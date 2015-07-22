#ifndef _MyList_h_
#define _MyList_h_

#include "ContainerBase.h"

template<class _Category,
        class _ValueType,
        class _DifferenceType,
        class _Pointer,
        class _Reference,
        class _Base>
struct Iterator012: public _Base
{   // base type for debugging iterator classes
    typedef _Base MyBase;
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
    {   // construct with node pointer
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
        ptr = _MyList::GetNextNodePtr(ptr);
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
        ptr = _MyList::GetPrevNodePtr(ptr);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }

    bool operator==(const MyIter& right) const
    {   // test for iterator equality
        return (ptr == right.ptr);
    }

    bool operator!=(const MyIter& right) const
    {   // test for iterator inequality
        return (!(*this == right));
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

    ListUncheckedIterator(NodePtr node, const _MyList *_Plist)
        : MyBase(node, _Plist)
    {   // construct with node pointer node
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

    ListConstIterator(NodePtr node, const _MyList *_Plist)
        : MyBase(node, _Plist)
    {   // construct with node pointer node
    }    

    MyIter& Rechecked(UncheckedType right)
    {   // reset from unchecked iterator
        this->ptr = right.ptr;
        return (*this);
    }

    UncheckedType Unchecked() const
    {   // make an unchecked iterator
        return (UncheckedType(this->ptr, (_MyList *)this->GetContainer()));
    }

    reference operator*() const
    {   // return designated value
        if (this->GetContainer() == 0
            || this->ptr == 0
            || this->ptr == ((_MyList *)this->GetContainer())->myHead)
        {	// report error
            std::_DEBUG_ERROR("list iterator not dereferencable");
            _SCL_SECURE_OUT_OF_RANGE;
        }

        return (_MyList::GetValue(this->ptr));
    }

    MyIter& operator++()
    {   // pre-increment
        this->ptr = _MyList::GetNextNodePtr(this->ptr);
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
        this->ptr = _MyList::GetPrevNodePtr(this->ptr);
        return (*this);
    }

    MyIter operator--(int)
    {   // post-decrement
        MyIter tmp = *this;
        --*this;
        return (tmp);
    }

    bool operator==(const MyIter& right) const
    {   // test for iterator equality
        return (this->ptr == right.ptr);
    }

    bool operator!=(const MyIter& right) const
    {   // test for iterator inequality
        return (!(*this == right));
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
    {   // construct with node pointer node
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
template<class ValueType, class VoidPtr>
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

/******** Template Class ListBaseType *********/
template<class _Type, class _AllocatorType> //int, std::allocator<Type>
struct ListBaseType
{   // types needed for a container base
    typedef _AllocatorType AllocatorType;
    typedef ListBaseType<_Type, AllocatorType> MyType;

    typedef typename _AllocatorType::template rebind<_Type>::other Allocator;

    typedef typename std::_Get_voidptr<Allocator, typename Allocator::pointer>::type VoidPtr;
    typedef ListNode<typename Allocator::value_type, VoidPtr> Node;  //ListNode<int,void *>

    typedef typename Allocator::template rebind<Node>::other NodeAllocator; //allocator<struct ListNode<int,void *>>
    typedef typename NodeAllocator::pointer NodePtr;
    typedef NodePtr& NodePtrRef;

    /* ValueType should be ListValue::_ValueType */
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
template para:  _ValueType, the list's emlement type, eg. _ValueType is "ListSimpleTypes<int>" when list<int>.
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
    //cout << typeid(IntList::ListValue::iterator).name() << endl;
    //class ListIterator<class ListValue<struct ListSimpleTypes<int> > >
    typedef ListIterator<MyType> iterator;

    typedef ListUncheckedConstIterator<MyType> UncheckedConstIterator;
    typedef ListUncheckedIterator<MyType> UncheckedIterator;

    ListValue()
    {   // initialize data
        this->myHead = 0;
        this->mySize = 0;
    }

    static NodePtrRef GetNextNodePtr(NodePtr node)
    {   // return reference to successor pointer in node
        return ((NodePtrRef) node->next);
    }

    static NodePtrRef GetPrevNodePtr(NodePtr node)
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
    typedef _AllocatorType MyTemplate1; 
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
        nodeAllocator.destroy(std::addressof(this->GetNextNodePtr(node)));
        nodeAllocator.destroy(std::addressof(this->GetPrevNodePtr(node)));
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
        try
        {
            nodeAllocator.construct(std::addressof(this->GetNextNodePtr(node)), next);
            nodeAllocator.construct(std::addressof(this->GetPrevNodePtr(node)), prev);
        } 
        catch (...) 
        {
            nodeAllocator.deallocate(node, 1);
            throw;
        }

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

template<class _AllocatorType>
class ListAlloc<false, _AllocatorType>
    : public ListValue<typename _AllocatorType::ValueType>
    {   // base class for list to hold allocator with no storage
public:
    typedef _AllocatorType MyTemplate1; //ListBaseType<int, std::allocator<Type>>
    typedef ListAlloc<false, _AllocatorType> MyType;
    typedef ListValue<typename _AllocatorType::ValueType> MyBase;
    typedef typename _AllocatorType::Allocator Allocator;
    typedef typename _AllocatorType::NodeAllocator NodeAllocator;
    typedef typename _AllocatorType::Node Node;
    typedef typename _AllocatorType::NodePtr NodePtr;

    ListAlloc(const Allocator& = Allocator())
    {   // construct head node, allocator from _AllocatorType
        this->myHead = BuyHeadNode();
        AllocProxy();
    }

    ~ListAlloc()
    {   // destroy head node
        FreeHeadNode(this->myHead);
        FreeProxy();
    }

    void ChangeAlloctor(const NodeAllocator& theNodeAllocator)
    {   // replace old allocator
        nodeAllocator = theNodeAllocator;
    }

    void SwapAlloctor(MyType& right)
    {   // swap allocators
        std::_Swap_adl(nodeAllocator, right.nodeAllocator);
    }

    void AllocProxy()
    {	// construct proxy from _Alnod
        typename Allocator::template rebind<ContainerProxy>::other proxyAllocator;
        this->myProxy = proxyAllocator.allocate(1);
        proxyAllocator.construct(this->myProxy, ContainerProxy());
        this->myProxy->myContainer = this;
    }

    void FreeProxy()
    {	// destroy proxy
        typename Allocator::template rebind<ContainerProxy>::other proxyAllocator;
        this->OrphanAll();
        proxyAllocator.destroy(this->myProxy);
        proxyAllocator.deallocate(this->myProxy, 1);
        this->myProxy = 0;
    }

    NodePtr BuyHeadNode()
    {   // get head node using current allocator
        return (BuyNode0(NodePtr(), NodePtr()));
    }

    void FreeHeadNode(NodePtr node)
    {   // free head node using current allocator
        this->GetAllocator().destroy(std::addressof(this->GetNextNodePtr(node)));
        this->GetAllocator().destroy(std::addressof(this->GetPrevNodePtr(node)));
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
        try
        {   
            this->GetAllocator().construct(std::addressof(this->GetNextNodePtr(node)), next);
            this->GetAllocator().construct(std::addressof(this->GetPrevNodePtr(node)), prev);            
        }
        catch (...)
        {
            this->GetAllocator().deallocate(node, 1);
            throw;
        }

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
template<class _Type, class _AllocatorType> //int, std::allocator<Type>
class ListBuy
    : public ListAlloc<!std::is_empty<_AllocatorType>::value,
        ListBaseType<_Type, _AllocatorType> >
    {   // base class for list to hold buynode/freenode functions
public:
    typedef _AllocatorType MyTemplate0;  //allocatoer<int>
    typedef ListAlloc<!std::is_empty<_AllocatorType>::value,
        ListBaseType<_Type, _AllocatorType> > MyBase;
    typedef typename MyBase::NodeAllocator NodeAllocator;
    typedef typename MyBase::NodePtr NodePtr;

    ListBuy(const _AllocatorType& allocator = _AllocatorType())
        : MyBase(allocator)
    {   // construct from allocator
    }
#define _LIST_BUYNODE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
    TEMPLATE_LIST(_CLASS_TYPE) \
    NodePtr BuyNode(NodePtr next, NodePtr prev COMMA LIST(_TYPE_REFREF_ARG)) \
    {	/* allocate a node and set links and value */ \
        NodePtr node = this->BuyNode0(next, prev); \
        _TRY_BEGIN \
            this->GetAllocator().construct(std::addressof(this->GetValue(node)) COMMA LIST(_FORWARD_ARG)); \
        _CATCH_ALL \
        this->GetAllocator().deallocate(node, 1); \
        _RERAISE; \
        _CATCH_END \
        return (node); \
    }
_VARIADIC_EXPAND_0X(_LIST_BUYNODE, , , , )
#undef _LIST_BUYNODE

    void FreeNode(NodePtr node)
    {   // give node back
        this->GetAllocator().destroy(addressof(this->GetNextNodePtr(node)));
        this->GetAllocator().destroy(addressof(this->GetPrevNodePtr(node)));
        this->GetAllocator().destroy(addressof(this->GetValue(node)));
        this->GetAllocator().deallocate(node, 1);
    }
};

/******** Template Class List ********
    prototype: std::list 
*/
template<class _Type, class _AllocatorType = std::allocator<_Type> >
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

    typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    List(): MyBase()
    {	// construct empty list
    }

    explicit List(const Allocator& allocator)
        : MyBase(allocator)
    {	// construct empty list, allocator
    }

    explicit List(size_type count)
        : MyBase()
    {	// construct list from count * _Type()
        Resize(count);
    }

    List(size_type count, const _Type& value)
        : MyBase()
    {	// construct list from count * value
        Construct(count, value);
    }

    List(size_type count, const _Type& value, const _AllocatorType& allocator)
        : MyBase(allocator)
    {	// construct list from count * value, allocator
        Construct(count, value);
    }

    List(const MyType& right)
        : MyBase(right.GetAllocator())
    {	// construct list by copying right
        try
        {
            Insert(Begin(), right.Begin(), right.End());
        }
        catch (...)
        {
            Tidy();
            throw;
        }
    }

    //line 943 at <list>
    List(const MyType& right, const _AllocatorType& allocator)
        : MyBase(allocator)
    {	// construct list by copying right, allocator
        try
        {
            Insert(Begin(), right.Begin(), right.End());
        }
        catch (...)
        {
            Tidy();
            throw;
        }
    }

    template<class _Iter>
    List(_Iter first, _Iter last, 
        typename std::enable_if<std::_Is_iterator<_Iter>::value, void>::type ** = 0)
        : MyBase()
    {	// construct list from [first, last)
        Construct(first, last);
    }

    template<class _Iter>
    List(_Iter first, _Iter last, const _AllocatorType& allocator,
        typename std::enable_if<std::_Is_iterator<_Iter>::value,  void>::type ** = 0)
        : Mybase(allocator)
    {	// construct list, allocator from [first, last)
        Construct(first, last);
    }

    template<class _Iter>
    void Construct(_Iter first, _Iter last)
    {	// construct list from [first, last), input iterators
        try
        {
            Insert(Begin(), first, last);
        }
        catch (...)
        {
            Tidy();
            throw;
        }
    }

    void ConstructNumOfValue(size_type count, const _Type& value)
    {	// construct from count * value
        try
        {
            InsertNumOfValue(UncheckedBegin(), count, value);
        }
        catch (...)
        {
            Tidy();
            throw;
        }
    }

    List(MyType&& right)
        : MyBase(right.GetAllocator())
    {	// construct list by moving right
        AssignRemove(std::forward<MyType>(right));
    }

    List(MyType&& right, const Allocator& allocator)
        : MyBase(allocator)
    {	// construct list by moving right, allocator
        AssignRemove(std::forward<MyType>(right));
    }

    MyType& operator=(MyType&& right)
    {	// assign by moving right
        if (this != &right)
        {	// different, assign it
            Clear();
            AssignRemove(std::forward<MyType>(right));
        }
        return (*this);
    }

    void AssignRemove(MyType&& right)
    {	// swap with empty *this, same allocator
        this->SwapAll(right);
        std::swap(this->myHead, right.myHead);
        std::swap(this->mySize, right.mySize);
    }

    void PushFront(_Type&& value)
    {	// insert element at beginning
        Insert(UncheckedBegin(), std::forward<_Type>(value));
    }

    void PushBack(_Type&& value)
    {	// insert element at end
        Insert(UncheckedEnd(), std::forward<_Type>(value));
    }
    
    //line 1040 of <list>
    iterator Insert(const_iterator whr, _Type&& value)
    {	// insert value at whr
        return (Emplace(whr, std::forward<_Type>(value)));
    }

#define _LIST_EMPLACE_INSERT( \
	TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
	TEMPLATE_LIST(_CLASS_TYPE) \
		void emplace_front(LIST(_TYPE_REFREF_ARG)) \
		{	/* insert element at beginning */ \
		Insert(_Unchecked_begin() COMMA LIST(_FORWARD_ARG)); \
		} \
	TEMPLATE_LIST(_CLASS_TYPE) \
		void emplace_back(LIST(_TYPE_REFREF_ARG)) \
		{	/* insert element at end */ \
		Insert(_Unchecked_end() COMMA LIST(_FORWARD_ARG)); \
		} \
	TEMPLATE_LIST(_CLASS_TYPE) \
		iterator emplace(const_iterator whr \
			COMMA LIST(_TYPE_REFREF_ARG)) \
		{	/* insert element at whr */ \
		_LIST_EMPLACE_CHECK \
		Insert(whr.Unchecked() COMMA LIST(_FORWARD_ARG)); \
		return (MakeIter(--whr)); \
		} \
    TEMPLATE_LIST(_CLASS_TYPE) \
    void Insert(UncheckedConstIterator whr COMMA LIST(_TYPE_REFREF_ARG)) \
    {	/* insert element at whr */ \
        NodePtr node = whr.GetMyNode(); \
        NodePtr newNode = this->BuyNode(node, \
	        this->GetPrevNodePtr(node) COMMA LIST(_FORWARD_ARG)); \
        IncSize(1); \
        this->GetPrevNodePtr(node) = newNode; \
        this->GetNextNodePtr(this->GetPrevNodePtr(newNode)) = newNode; \
    }

#define _LIST_EMPLACE_CHECK

_VARIADIC_EXPAND_0X(_LIST_EMPLACE_INSERT, , , , )
#undef _LIST_EMPLACE_CHECK
#undef _LIST_EMPLACE_INSERT

    ~List()
    {	// destroy the object
        Tidy();
    }

    MyType& operator=(const MyType& right)
    {	// assign right
        if (this != &right)
        {	// different, assign it
            Assign(right.Begin(), right.End());
        }
        return (*this);
    }

    iterator Begin()
    {	// return iterator for beginning of mutable sequence
        return (iterator(this->GetNextNodePtr(this->myHead), this));
    }

    const_iterator Begin() const
    {	// return iterator for beginning of nonmutable sequence
        return (const_iterator(this->GetNextNodePtr(this->myHead), this));
    }

    iterator End()
    {	// return iterator for End of mutable sequence
        return (iterator(this->myHead, this));
    }

    const_iterator End() const
    {	// return iterator for End of nonmutable sequence
        return (const_iterator(this->myHead, this));
    }

    UncheckedIterator UncheckedBegin()
    {	// return iterator for beginning of mutable sequence
        return (UncheckedIterator(this->GetNextNodePtr(this->myHead), this));
    }

    UncheckedConstIterator UncheckedBegin() const
    {	// return iterator for beginning of nonmutable sequence
        return (UncheckedConstIterator(this->GetNextNodePtr(this->myHead), this));
    }

    UncheckedIterator UncheckedEnd()
    {	// return unchecked iterator for end of mutable sequence
        return (UncheckedIterator(this->myHead, this));
    }

    UncheckedConstIterator UncheckedEnd() const
    {	// return unchecked iterator for end of nonmutable sequence
        return (UncheckedConstIterator(this->myHead, this));
    }

    iterator MakeIter(const_iterator whr) const
    {	// make iterator from const_iterator
        return (iterator(whr.ptr, this));
    }

    iterator MakeIter(UncheckedConstIterator whr) const
    {	// make iterator from UncheckedConstIterator
        return (iterator(whr.ptr, this));
    }

    reverse_iterator Rbegin()
    {	// return iterator for beginning of reversed mutable sequence
        return (reverse_iterator(End()));
    }

    const_reverse_iterator Rbegin() const
    {	// return iterator for beginning of reversed nonmutable sequence
        return (const_reverse_iterator(End()));
    }

    reverse_iterator Rend()
    {	// return iterator for End of reversed mutable sequence
        return (reverse_iterator(Begin()));
    }

    const_reverse_iterator Rend() const
    {	// return iterator for end of reversed nonmutable sequence
        return (const_reverse_iterator(Begin()));
    }

    //line 1207 of <list>
    void Resize(size_type newSize)
    {	// determine new length, padding with Type() elements as needed
        if (this->mySize < newSize)
        {	// pad to make larger
            size_type count = 0;
            try
            {
                for (; this->mySize < newSize; ++count)
                    Insert(UncheckedEnd());
            }
            catch (...)
            {
                for (; 0 < count; --count)
                    PopBack();	// undo inserts
                throw;
            }
        }
        else
            while (newSize < this->mySize) 
                PopBack();
    }

    void Resize(size_type newSize, const _Type& value)
    {	// determine new length, padding with value elements as needed
        if (this->mySize < newSize)
            InsertNumOfValue(UncheckedEnd(), newSize - this->mySize, value);
        else
            while (newSize < this->mySize)
                PopBack();
    }

    size_type Size() const
    {	// return length of sequence
        return (this->mySize);
    }

    size_type GetMaxSize() const 
    {	// return maximum possible length of sequence
        return (this->GetAllocator().max_size());
    }

    bool Empty() const 
    {	// test if sequence is empty
        return (this->mySize == 0);
    }

    allocator_type GetAllocator() const
    {	// return allocator object for values
        return (MyBase::GetAllocator());
    }

    reference Front()
    {	// return first element of mutable sequence
        return (*Begin());
    }

    const_reference Front() const
    {	// return first element of nonmutable sequence
        return (*Begin());
    }

    reference Back()
    {	// return last element of mutable sequence
        return (*(--End()));
    }

    const_reference Back() const
    {	// return last element of nonmutable sequence
        return (*(--End()));
    }

    void PushFront(const _Type& value)
    {	// insert element at beginning
        Insert(UncheckedBegin(), value);
    }

    void PopFront()
    {	// erase element at beginning
        Erase(Begin());
    }

    void PushBack(const _Type& value)
    {	// insert element at end
        Insert(UncheckedEnd(), value);
    }

    void PopBack()
    {	// erase element at end
        Erase(--End());
    }

    template<class _Iter>
    typename std::enable_if<std::_Is_iterator<_Iter>::value, void>::type
    Assign(_Iter first, _Iter last)
    {	// assign [first, last), input iterators
        iterator old = Begin();
        try
        {
            for (; first != last && old != End(); ++first, ++old)
                *old = *first;
            for (; first != last; ++first)
                Insert(UncheckedEnd(), *first);
        }
        catch (...)
        {
            Clear();
            throw;
        }
        Erase(old, End());
    }

    void Assign(size_type count, const _Type& value)
    {	// assign count * value
        AssignNumOfValue(count, value);
    }

    iterator Insert(const_iterator whr, const _Type& value)
    {	// insert value at whr
        Insert(whr.Unchecked(), value);
        return (MakeIter(--whr));
    }

    iterator Insert(const_iterator whr, size_type count, const _Type& value)
    {	// insert count * value at whr
        iterator prev = MakeIter(whr);
        if (prev == Begin())
        {	// insert sequence at beginning
            InsertNumOfValue(whr.Unchecked(), count, value);
            return (Begin());
        }
        else
        {	// insert sequence not at beginning
            --prev;
            InsertN(whr.Unchecked(), count, value);
            return (++prev);
        }
    }

    template<class _Iter>
    typename std::enable_if<std::_Is_iterator<_Iter>::value, iterator>::type
    Insert(const_iterator whr, _Iter first, _Iter last)
    {	// insert [first, last) at whr
        iterator prev = MakeIter(whr);
        if (prev == Begin())
        {	// insert sequence at beginning
            InsertRange(whr.Unchecked(), first, last, std::_Iter_cat(first));
            return (Begin());
        }
        else
        {	// insert sequence not at beginning
            --prev;
            InsertRange(whr.Unchecked(), first, last, std::_Iter_cat(first));
            return (++prev);
        }
    }

    template<class _Iter>
    void InsertRange(UncheckedConstIterator whr, _Iter first, _Iter last, std::input_iterator_tag)
    {	// insert [first, last) at whr, input iterators
        size_type num = 0;

        try
        {
            for (; first != last; ++first, ++num)
                Insert(whr, *first);
        }
        catch(...)
        {
            for (; 0 < num; --num)
            {	// undo inserts
                UncheckedConstIterator before = whr;
                UncheckedErase(--before);
            }
            throw;
        }
    }

    template<class _Iter>
    void InsertRange(UncheckedConstIterator whr, _Iter first, _Iter last, std::forward_iterator_tag)
    {	// insert [first, last) at whr, forward iterators
        _Iter next = first;

        try
        {
            for (; first != last; ++first)
                Insert(whr, *first);
        }
        catch(...)
        {
            for (; next != first; ++next)
            {	// undo inserts
                UncheckedConstIterator before = whr;
                UncheckedErase(--before);
            }
            throw;
        }
    }

    //line 1415 of list
    iterator Erase(const_iterator whr)
    {	// erase element at whr
        NodePtr node = (whr++).GetMyNode();

        if (node != this->myHead)
        {	// not list head, safe to erase
            this->GetNextNodePtr(this->GetPrevNodePtr(node)) = this->GetNextNodePtr(node);
            this->GetPrevNodePtr(this->GetNextNodePtr(node)) = this->GetPrevNodePtr(node);
            this->FreeNode(node);
            --this->mySize;
        }
        return (MakeIter(whr));
    }

    void UncheckedErase(UncheckedConstIterator whr)
    {	// erase element at whr
        NodePtr node = whr.GetMyNode();

        if (node != this->myHead)
        {	// not list head, safe to erase
            this->GetNextNodePtr(this->GetPrevNodePtr(node)) = this->GetNextNodePtr(node);
            this->GetPrevNodePtr(this->GetNextNodePtr(node)) = this->GetPrevNodePtr(node);
            this->FreeNode(node);
            --this->mySize;
        }
    }

    iterator Erase(const_iterator first, const_iterator last)
    {	// erase [first, last)
        if (first == Begin() && last == End())
        {	// erase all and return fresh iterator
            clear();
            return (End());
        }
        else
        {	// erase subrange
            while (first != last)
                first = Erase(first);
            return (MakeIter(last));
        }
    }

    void Clear()
    {	// erase all
        NodePtr node = this->GetNextNodePtr(this->myHead);
        this->GetNextNodePtr(this->myHead) = this->myHead;
        this->GetPrevNodePtr(this->myHead) = this->myHead;
        this->mySize = 0;

        for (NodePtr next; node != this->myHead; node = next)
        {	// delete an element
            next = this->GetNextNodePtr(node);
            this->FreeNode(node);
        }
    }

    void Swap(MyType& right)
    {	// exchange contents with right
        if (this == &right)
            ;	// same object, do nothing
        else if (this->GetAllocator() == right.GetAllocator())
        {	// same allocator, swap control information
            this->SwapAll(right);
            std::_Swap_adl(this->myHead, right.myHead);
            std::swap(this->mySize, right.mySize);
        }
        else
        {	// different allocator, do splices
            iterator whr = Begin();
            Splice(whr, right);
            right.splice(right.Begin(), *this, whr, End());
        }
    }

    void Splice(const_iterator whr, MyType& right)
    {	// splice all of right at whr
        if (this != &right && !right.Empty())
        {	// worth splicing, do it
            Splice(whr, right, right.Begin(), right.End(), right.mySize);
        }
    }

    void Splice(const_iterator whr, MyType&& right)
    {	// splice all of right at whr
        Splice(whr, (MyType&)right);
    }

    void Splice(const_iterator whr, MyType& right, const_iterator first)
    {	// splice right [first, first + 1) at whr
        if (first != right.End())
        {	// element exists, try splice
            const_iterator last = first;
            ++last;
            if (this != &right
                || (whr != first && whr != last))
                Splice(whr, right, first, last, 1);
        }
    }

    void Splice(const_iterator whr, MyType&& right, const_iterator first)
    {	// splice right [first, first + 1) at whr
        splice(whr, (MyType&)right, first);
    }

    void Splice(const_iterator whr, MyType& right, const_iterator first, const_iterator last)
    {	// splice right [first, last) at whr
        if (first != last && (this != &right || whr != last))
        {	// worth splicing, do it
            size_type count = 0;

            if (this == &right)
                ;	// just rearrange this list
            else if (first == right.Begin() && last == right.End())
                count = right.mySize;	// splice in whole list
            else
            {	// count nodes and check for knot
                const_iterator next = first;

                for (; next != last; ++next, ++count)
                    if (next == right.End())
                        _Xlength_error("list<T> bad splice");
            }
            Splice(whr, right, first, last, count);
        }
    }

    void Splice(const_iterator whr,
        MyType&& right, const_iterator first, const_iterator last)
    {	// splice right [first, last) at whr
        Splice(whr, (MyType&)right, first, last);
    }

    void Remove(const _Type& theValue)
    {	// erase each element matching theValue
        const _Type value = theValue;	// in case it's removed along the way
        const NodePtr head = this->myHead;
        NodePtr node = this->GetNextNodePtr(head);

        while (node != head)
        {
            if (node->myValue == value)
            {	// match, remove it
                const NodePtr prev = this->GetPrevNodePtr(node);
                const NodePtr tmp = node;
                node = this->GetNextNodePtr(node);

                this->GetNextNodePtr(prev) = node;
                this->GetPrevNodePtr(node) = prev;
                this->FreeNode(tmp);

                --this->mySize;
            }
            else
                node = this->GetNextNodePtr(node);
        }
    }

    template<class _Pr1>
    void RemoveIf(_Pr1 predicate)
    {	// erase each element satisfying predicate
        const NodePtr head = this->myHead;
        NodePtr node = this->GetNextNodePtr(head);

        while (node != head)
        {
            if (predicate(node->myValue))
            {	// match, remove it
                const NodePtr prev = this->GetPrevNodePtr(node);
                const NodePtr tmp = node;
                node = this->GetNextNodePtr(node);

                this->GetNextNodePtr(prev) = node;
                this->GetPrevNodePtr(node) = prev;
                this->FreeNode(tmp);

                --this->mySize;
            }
            else
                node = this->GetNextNodePtr(node);
        }
    }

    void Unique()
    {	// erase each element matching previous
        const NodePtr head = this->myHead;
        NodePtr prev = this->GetNextNodePtr(head);
        NodePtr node = this->GetNextNodePtr(prev);

        while (node != head)
        {
            if (prev->myValue == node->myValue)
            {	// match, remove it
                const NodePtr tmp = node;
                node = this->GetNextNodePtr(node);

                this->GetNextNodePtr(prev) = node;
                this->GetPrevNodePtr(node) = prev;
                this->FreeNode(tmp);

                --this->mySize;
            }
            else
            {	// no match, advance
                prev = node;
                node = this->GetNextNodePtr(node);
            }
        }
    }

    template<class _Pr2>
    void Unique(_Pr2 predicate)
    {	// erase each element satisfying predicate with previous
        const NodePtr head = this->myHead;
        NodePtr prev = this->GetNextNodePtr(head);
        NodePtr node = this->GetNextNodePtr(prev);

        while (node != head)
        {
            if (predicate(prev->myValue, node->myValue))
            {	// match, remove it
                const NodePtr _Perase = node;
                node = this->GetNextNodePtr(node);

                this->GetNextNodePtr(prev) = node;
                this->GetPrevNodePtr(node) = prev;
                this->FreeNode(_Perase);

                --this->mySize;
            }
            else
            {	// no match, advance
                prev = node;
                node = this->GetNextNodePtr(node);
            }
        }
    }

    void Merge(MyType& right)
    {	// merge in elements from right, both ordered by operator<
        if (&right != this)
        {	// safe to merge, do it
            iterator first1 = Begin(), last1 = End();
            iterator first2 = right.Begin(), last2 = right.End();

            while (first1 != last1 && first2 != last2)
                if (_DEBUG_LT(*first2, *first1))
                {	// splice in an element from right
                    iterator _Mid2 = first2;
                    Splice(first1, right, first2, ++_Mid2, 1);
                    first2 = _Mid2;
                }
                else
                    ++first1;

            if (first2 != last2)
            {   // splice remainder of right
                Splice(last1, right, first2, last2, right.mySize);	
            }
        }
    }

	void Merge(MyType&& right)
    {	// merge in elements from right, both ordered by operator<
        Merge((MyType&)right);
    }

    template<class _Pr2>
    void Merge(MyType& right, _Pr2 predicate)
    {	// merge in elements from right, both ordered by predicate
        if (&right != this)
        {	// safe to merge, do it
            iterator first1 = Begin(), last1 = End();
            iterator first2 = right.Begin(), last2 = right.End();

            while (first1 != last1 && first2 != last2)
                if (_DEBUG_LT_PRED(predicate, *first2, *first1))
                {	// splice in an element from right
                    iterator mid2 = first2;
                    Splice(first1, right, first2, ++mid2, 1);
                    first2 = mid2;
                }
                else
                    ++first1;

            if (first2 != last2)
                Splice(last1, right, first2, last2,
                right.mySize);	// splice remainder of right
        }
    }

    template<class _Pr2>
    void Merge(MyType&& right, _Pr2 predicate)
    {	// merge in elements from right, both ordered by predicate
        Merge((MyType&)right, predicate);
    }

    void Sort()
    {	// order sequence, using operator<
        if (2 <= this->mySize)
        {	// worth sorting, do it
            const size_t MaxBins = 25;
            MyType tempList(this->GetAllocator()), _Binlist[MaxBins + 1];
            size_t maxBin = 0;

            while (!empty())
            {	// sort another element, using bins
                tempList.SpliceSame(tempList.Begin(), *this, Begin(),
                    ++Begin(), 1);

                size_t bin;
                for (bin = 0; bin < maxBin && !_Binlist[bin].empty(); ++bin)
                {	// merge into ever larger bins
                    _Binlist[bin].Merge(tempList);
                    _Binlist[bin].swap(tempList);
                }

                if (bin == MaxBins)
                    _Binlist[bin - 1].Merge(tempList);
                else
                {	// spill to new bin, while they last
                    _Binlist[bin].swap(tempList);
                    if (bin == maxBin)
                        ++maxBin;
                }
            }

            for (size_t bin = 1; bin < maxBin; ++bin)
                _Binlist[bin].Merge(_Binlist[bin - 1]);	// merge up

            _Analysis_assume_(0 < maxBin);

            splice(Begin(), _Binlist[maxBin - 1]);	// result in last bin
        }
    }

    template<class _Pr2>
    void Sort(_Pr2 predicate)
    {	// order sequence, using predicate
        if (2 <= this->mySize)
        {	// worth sorting, do it
            const size_t MaxBins = 25;
            MyType tempList(this->GetAllocator()), _Binlist[MaxBins + 1];
            size_t maxBin = 0;

            while (!empty())
            {	// sort another element, using bins
                tempList.SpliceSame(tempList.Begin(), *this, Begin(),
                    ++Begin(), 1);

                size_t bin;
                for (bin = 0; bin < maxBin && !_Binlist[bin].empty();
                    ++bin)
                {	// merge into ever larger bins
                    _Binlist[bin].Merge(tempList, predicate);
                    _Binlist[bin].Swap(tempList);
                }

                if (bin == MaxBins)
                    _Binlist[bin - 1].Merge(tempList, predicate);
                else
                {	// spill to new bin, while they last
                    _Binlist[bin].Swap(tempList);
                    if (bin == maxBin)
                        ++maxBin;
                }
            }

            for (size_t bin = 1; bin < maxBin; ++bin)
                _Binlist[bin].Merge(_Binlist[bin - 1],
                predicate);	// merge up

            _Analysis_assume_(0 < maxBin);

            Splice(Begin(), _Binlist[maxBin - 1]);	// result in last bin
        }
    }

    void Reverse()
    {	// reverse sequence
        const NodePtr head = this->myHead;
        NodePtr node = head;

        for (; ; )
        {	// flip pointers in a node
            const NodePtr next = this->GetNextNodePtr(node);
            this->GetNextNodePtr(node) = this->GetPrevNodePtr(node);
            this->GetPrevNodePtr(node) = next;

            if (next == head)
                break;
            node = next;
        }
    }

    void Splice(const_iterator whr, MyType& right, 
        const_iterator first, const_iterator last,
        size_type count)
    {	// splice right [first, last) before whr
        if (this->GetAllocator() == right.GetAllocator())
            SpliceSame(whr, right, first, last, count);
        else
        {	// different allocator, copy nodes then erase source
            for (const_iterator next = first; next != last; ++next)
                insert(whr, (_Type&&)*next);
            right.erase(first, last);
        }
    }

    void SpliceSame(const_iterator whr, MyType& right, 
        const_iterator first, const_iterator last,
        size_type count)
    {	// splice right [first, last) before whr
        if (this != &right)
        {	// splicing from another list, adjust counts
            IncSize(count);
            right.mySize -= count;
        }
        this->GetNextNodePtr(this->GetPrevNodePtr(first.GetMyNode())) = last.GetMyNode();
        this->GetNextNodePtr(this->GetPrevNodePtr(last.GetMyNode())) = whr.GetMyNode();
        this->GetNextNodePtr(this->GetPrevNodePtr(whr.GetMyNode())) = first.GetMyNode();

        NodePtr node = this->GetPrevNodePtr(whr.GetMyNode());
        this->GetPrevNodePtr(whr.GetMyNode()) = this->GetPrevNodePtr(last.GetMyNode());
        this->GetPrevNodePtr(last.GetMyNode()) = this->GetPrevNodePtr(first.GetMyNode());
        this->GetPrevNodePtr(first.GetMyNode()) = node;
    }

    void UncheckedSplice(UncheckedConstIterator whr,
        UncheckedConstIterator first,
        UncheckedConstIterator last)
    {	// splice [first, last) before whr
        this->GetNextNodePtr(this->GetPrevNodePtr(first.GetMyNode())) = last.GetMyNode();
        this->GetNextNodePtr(this->GetPrevNodePtr(last.GetMyNode())) = whr.GetMyNode();
        this->GetNextNodePtr(this->GetPrevNodePtr(whr.GetMyNode())) = first.GetMyNode();

        NodePtr node = this->GetPrevNodePtr(whr.GetMyNode());
        this->GetPrevNodePtr(whr.GetMyNode()) = this->GetPrevNodePtr(last.GetMyNode());
        this->GetPrevNodePtr(last.GetMyNode()) = this->GetPrevNodePtr(first.GetMyNode());
        this->GetPrevNodePtr(first.GetMyNode()) = node;
    }

	void AssignNumOfValue(size_type count, const _Type& _Val)
		{	// assign count * _Val
		_Type _Tmp = _Val;	// in case _Val is in sequence
		clear();
		InsertNumOfValue(_Unchecked_begin(), count, _Tmp);
		}

    void Tidy()
    {	// free all storage
        Clear();
    }

    void InsertNumOfValue(UncheckedConstIterator whr,
        size_type count, const _Type& _Val)
    {	// insert count * _Val at whr
        size_type _Countsave = count;

        try
        {
            for (; 0 < count; --count)
                Insert(whr, _Val);
        }
        catch (...)
        {
            for (; count < _Countsave; ++count)
            {	// undo inserts
                UncheckedConstIterator _Before = whr;
                _Unchecked_erase(--_Before);
            }
            throw;
        }
    }

    void IncSize(size_type count)
    {	// alter element count, with checking
        if (GetMaxSize() - this->mySize - 1 < count)
        {
            _Xlength_error("list<T> too long");
        }
        this->mySize += count;
    }
};


template<class _Type, class _Alloc> 
inline void swap(List<_Type, _Alloc>& left, List<_Type, _Alloc>& right)
{	// swap _Left and right lists
    left.swap(right);
}

#endif /* _MyList_h_ */

