#ifndef _MyContainer_h_
#define _MyContainer_h_

class ContainerBase;
class IterBase: public std::iterator<std::forward_iterator_tag, int>
{
public:
    typedef const reference const_reference;

    IterBase(ContainerBase *container): myContainer(container)
    {}

    ContainerBase* GetContainer()
    { return myContainer; }

private:
    ContainerBase *myContainer;
};

class ContainerBase: public std::iterator<std::forward_iterator_tag, int>
{
public:
    typedef const reference const_reference;

    std::list<IterBase> *myIterList;
};

/////////////////////////////////////////////////////////////////////////////////
template<typename ContainerType>
class Iterator: public IterBase    
{
public:
    typedef ContainerType          MyContainer;
    typedef typename MyContainer::NodePtr NodePtr;

    typedef IterBase               MyBase;
    typedef Iterator<MyContainer>  MyIter;
    typedef const MyIter           MyConstIter;
    
    Iterator(): MyBase(nullptr), ptr(NodePtr())
    {}

    Iterator(MyContainer *container, NodePtr thePtr)
        : MyBase(container), ptr(thePtr)
    {}

    const_reference operator*() const
    {
        return (MyContainer::GetValue(this->ptr));
    }

    reference operator*()
    {
        return (MyContainer::GetValue(this->ptr));
    }

    MyConstIter& operator++() const
    {   // pre-increment
        ptr = MyContainer::GetNextNodePtr(this->ptr);
        return (*this);
    }

    MyConstIter operator++(int) const
    {   // post-increment
        MyIter tmp = *this;
        ++*this;
        return (tmp);
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

    bool operator==(const MyIter& right) const
    {   // test for iterator equality
        return (this->ptr == right.ptr);
    }

    bool operator!=(const MyIter& right) const
    {   // test for iterator inequality
        return (!(*this == right));
    }

private:
    NodePtr ptr;
};

/////////////////////////////////////////////////////////////////////////////////
class ContainerValue: public ContainerBase
{
public:
    typedef std::list<int>::iterator NodePtr;

    static reference GetValue(NodePtr ptr)
    {
        return *ptr;
    }

    static NodePtr GetNextNodePtr(NodePtr node)
    {   // return reference to successor pointer in node
        ++node;
        return node;
    }

protected:
    std::list<int> myList;
};

class Container: public ContainerValue
{
public:
    typedef Iterator<Container>::MyIter      iterator;
    typedef Iterator<Container>::MyConstIter const_iterator;

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