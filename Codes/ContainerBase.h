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

struct ContainerBase12;
struct IteratorBase12;

struct ContainerProxy
{   // store head of iterator chain and back pointer
    ContainerProxy(): myContainer(0), myFistIter(0)
    {   // construct from pointers
    }

    const ContainerBase12 *myContainer;
    IteratorBase12 *myFistIter;
};

struct ContainerBase12
{   // store pointer to ContainerProxy
public:
    ContainerBase12(): myProxy(0)
    {   // construct childless container
    }

    ContainerBase12(const ContainerBase12&): myProxy(0)
    {   // copy a container
    }

    ContainerBase12& operator=(const ContainerBase12&)
    {   // assign a container
        return (*this);
    }

    ~ContainerBase12()
    {   // destroy the container
        OrphanAll();
    }

    IteratorBase12 **GetpFirstIter() const
    {   // get address of iterator chain
        return (myProxy == 0 ? 0 : &myProxy->myFistIter);
    }

    // orphan all iterators
    void OrphanAll()
    {}
    // swap all iterators
    void SwapAll(ContainerBase12&)
    {}

    ContainerProxy *myProxy;
};

struct IteratorBase12
{   // store links to container proxy, next iterator
public:
    IteratorBase12(): myProxy(0), myNextIter(0)
    {   // construct orphaned iterator
    }

    IteratorBase12(const IteratorBase12& right)
        : myProxy(0), myNextIter(0)
    {   // copy an iterator
        *this = right;
    }

    IteratorBase12& operator=(const IteratorBase12& right)
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

    ~IteratorBase12()
    {   // destroy the iterator
    }

    void Adopt(const ContainerBase12 *parent)
    {   // adopt this iterator by parent
        if (parent == 0)
        {   // no future parent, just disown current parent
            OrphanMe();
        }
        else
        {   // have a parent, do adoption
            ContainerProxy *_Parent_proxy = parent->myProxy;

            myProxy = _Parent_proxy;
        }
    }

    void ClearContainer()
    {   // disown owning container
        myProxy = 0;
    }

    const ContainerBase12 *GetContainer() const
    {   // get owning container
        return (myProxy == 0 ? 0 : myProxy->myContainer);
    }

    IteratorBase12 **GetNextIter()
    {   // get address of remaining iterator chain
        return (&myNextIter);
    }

    void OrphanMe()
    {   // cut ties with parent
    }

    ContainerProxy *myProxy;
    IteratorBase12 *myNextIter;
};

typedef ContainerBase12 ContainerBase;
typedef IteratorBase12 IteratorBase;



#endif /* _ContainerBase_h_ */
