#ifndef _MyContainer_h_
#define _MyContainer_h_

class ContainerBase;
class IterBase 
{
public:
    IterBase(ContainerBase *container): myContainer(container)
    {}

    ContainerBase* GetContainer()
    { return myContainer; }

private:
    ContainerBase *myContainer;
};

class ContainerBase
{
public:
    std::list<IterBase> *myIterList;
};

/////////////////////////////////////////////////////////////////////////////////
template<typename ContainerType>
class ConstIterator: public IterBase    
{
public:
    typedef ContainerType                 MyContainer;
    
    typedef IterBase                     MyBase;
    typedef ConstIterator<ContainerType> MyIter;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename MyContainer::NodePtr NodePtr;
    typedef typename MyContainer::value_type value_type;
    typedef typename MyContainer::size_type size_type;
    typedef typename MyContainer::difference_type difference_type;
    typedef typename MyContainer::const_pointer pointer;
    typedef typename MyContainer::const_reference reference;

    ConstIterator(): MyBase(nullptr), ptr(NodePtr())
    {}

    ConstIterator(MyContainer *container, NodePtr thePtr)
        : MyBase(container), ptr(thePtr)
    {}

    reference operator*() const
    {
        return (MyContainer::GetValue(this->ptr));
    }

    MyIter& operator++() const
    {   // pre-increment
        ptr = MyContainer::GetNextNodePtr(this->ptr);
        return (*this);
    }

    MyIter operator++(int) const
    {   // post-increment
        MyIter tmp = *this;
        ++*this;
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

protected:
    NodePtr ptr;
};

template<typename ContainerType>
class Iterator: public ConstIterator<ContainerType> 
{
public:
    typedef ConstIterator<ContainerType> MyBase;
    typedef Iterator<ContainerType>      MyIter;

    typedef std::bidirectional_iterator_tag iterator_category;

    typedef typename MyContainer::NodePtr NodePtr;
    typedef typename MyContainer::value_type value_type;
    typedef typename MyContainer::size_type size_type;
    typedef typename MyContainer::difference_type difference_type;
    typedef typename MyContainer::pointer pointer;
    typedef typename MyContainer::reference reference;
    
    Iterator()
    {}

    Iterator(MyContainer *container, NodePtr ptr)
        : MyBase(container, ptr)
    {}

    reference operator*()
    {
        return (MyContainer::GetValue(this->ptr));
    }

    MyIter& operator++()
    {   // pre-increment
        ptr = MyContainer::GetNextNodePtr(this->ptr);
        return (*this);
    }

    MyIter operator++(int)
    {   // post-increment
        MyIter tmp = *this;
        ++*this;
        return (tmp);
    }
};

/////////////////////////////////////////////////////////////////////////////////
class ContainerValue: public ContainerBase
{
public:
    typedef std::list<int> ValueType;
    typedef ValueType::iterator NodePtr;

    typedef ValueType::value_type value_type;
    typedef ValueType::size_type size_type;
    typedef ValueType::difference_type difference_type;
    typedef ValueType::pointer pointer;
    typedef ValueType::const_pointer const_pointer;
    typedef ValueType::reference reference;
    typedef ValueType::const_reference const_reference;

    static NodePtr GetNextNodePtr(NodePtr node)
    {   // return reference to successor pointer in node
        ++node;
        return node;
    }

    static reference GetValue(NodePtr ptr)
    {
        return *ptr;
    }

protected:
    std::list<int> myList;
};

class ContainerAlloc: public ContainerValue
{
public:
    typedef ContainerAlloc MyType;
    typedef ContainerValue MyBase;
    typedef MyBase::NodePtr NodePtr;

    ContainerAlloc()
    {
        AllocProxy();
    }

    ~ContainerAlloc()
    {   // destroy head node
        FreeProxy();
    }

    void AllocProxy()
    {	// construct proxy from _Alnod

    }

    void FreeProxy()
    {	// destroy proxy
    }
};

class Container: public ContainerValue
{
public:
    typedef ContainerValue MyBase;
    typedef Iterator<Container>::MyIter      iterator;
    typedef ConstIterator<Container>::MyIter const_iterator;

    typedef MyBase::value_type value_type;
    typedef MyBase::size_type size_type;
    typedef MyBase::difference_type difference_type;
    typedef MyBase::pointer pointer;
    typedef MyBase::const_pointer const_pointer;
    typedef MyBase::reference reference;
    typedef MyBase::const_reference const_reference;

    iterator Begin()
    {
        return iterator(this, myList.begin());
    }

    iterator End()
    {
        return iterator(this, myList.end());
    }

    void Add(int value)
    {
        myList.push_back(value);
    }
};



#endif