#ifndef _ContainerBase_h_
#define _ContainerBase_h_

struct ContainerBase0
{   // base of all containers
    void OrphanAll()
    {   // orphan all iterators
    }

    void SwapAll(ContainerBase0&)
    {   // swap all iterators
    }
};

struct IteratorBase0
{   // base of all iterators
    void Adopt(const void *)
    {   // adopt this iterator by parent
    }

    const ContainerBase0 *GetContainer() const
    {   // get owning container
        return (0);
    }
};

struct ContainerBase;
struct IteratorBase;

//stl: struct _Container_proxy
struct ContainerProxy
{   // store head of iterator chain and back pointer
    ContainerProxy(): myContainer(0), myFistIter(0)
    {   // construct from pointers
    }

    const ContainerBase *myContainer;
    IteratorBase *myFistIter;
};

//stl: struct _Container_base12;
struct ContainerBase
{   // store pointer to ContainerProxy
    ContainerBase(): myProxy(0)
    {   // construct childless container
    }

    ContainerBase(const ContainerBase&): myProxy(0)
    {   // copy a container
    }

    ContainerBase& operator=(const ContainerBase&)
    {   // assign a container
        return (*this);
    }

    ~ContainerBase()
    {   // destroy the container
        OrphanAll();
    }

    IteratorBase **GetpFirstIter() const
    {   // get address of iterator chain
        return (myProxy == nullptr ? nullptr : &myProxy->myFistIter);
    }

    // orphan all iterators
    void OrphanAll();

    // swap all iterators
    void SwapAll(ContainerBase&)
    {}

    ContainerProxy *myProxy;
};

//stl:  struct _Iterator_base12;
struct IteratorBase 
{   // store links to container proxy, next iterator
    IteratorBase(): myProxy(0), myNextIter(0)
    {   // construct orphaned iterator
    }

    IteratorBase(const IteratorBase& right)
        : myProxy(0), myNextIter(0)
    {   // copy an iterator
        *this = right;
    }

    IteratorBase& operator=(const IteratorBase& right)
    {   // assign an iterator
        if (myProxy == right.myProxy)
        {
            ;
        }
        else if (right.myProxy != 0)
            Adopt(right.myProxy->myContainer);
        else
        {   // becoming invalid, disown current parent
            OrphanMe();
        }
        return (*this);
    }

    ~IteratorBase()
    {   // destroy the iterator
        OrphanMe();
    }

    void Adopt(const ContainerBase *parent)
    {   // adopt this iterator by parent
        if (parent == 0)
        {   // no future parent, just disown current parent
            OrphanMe();
        }
        else
        {   // have a parent, do adoption
            ContainerProxy *parentProxy = parent->myProxy;

            if (myProxy != parentProxy)
            {	// change parentage
                OrphanMe();
                myNextIter = parentProxy->myFistIter;
                parentProxy->myFistIter = this;
                myProxy = parentProxy;
            }
        }
    }

    void ClearContainer()
    {   // disown owning container
        myProxy = 0;
    }

    const ContainerBase *GetContainer() const
    {   // get owning container
        return (myProxy == 0 ? 0 : myProxy->myContainer);
    }

    IteratorBase **GetNextIter()
    {   // get address of remaining iterator chain
        return (&myNextIter);
    }

    void OrphanMe()
    {   // cut ties with parent
        if (myProxy != 0)
        {	// adopted, remove self from list
            IteratorBase **next = &myProxy->myFistIter;
            while (*next != 0 && *next != this)
                next = &(*next)->myNextIter;

            assert(*next != 0); //Iterator list corrupted.
            *next = myNextIter;
            myProxy = 0;
        }
    }

    ContainerProxy *myProxy;
    IteratorBase *myNextIter;
};

inline void ContainerBase::OrphanAll()
{
    if (myProxy != 0)
    {	// proxy allocated, drain it
        for (IteratorBase **next = &myProxy->myFistIter;
            *next != 0; 
            *next = (*next)->myNextIter)
            (*next)->myProxy = 0;
        myProxy->myFistIter = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////
#endif /* _ContainerBase_h_ */
