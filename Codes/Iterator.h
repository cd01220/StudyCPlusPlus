#ifndef _Iterator_h_
#define _Iterator_h_

#if 0
class MyIterator;
class Container
{    
public:
    typedef MyIterator Iterator;
    Container()
    {
        for (int i = 0; i < 10; ++i)
        { valueList[i] = i; }
    }
    MyIterator Begin() throw ()
    {
        return MyIterator(this, 0); 
    }
    Iterator End() throw ()
    {
        return MyIterator(this, 10); 
    }

    friend class Iterator;
private:
    int valueList[10];
};

class MyIterator : public std::iterator<std::forward_iterator_tag, int>
{
public:
    MyIterator(): container(nullptr), index(0) {}
    MyIterator(Container *container, int index): container(container), index(index) {}
    int& operator*() const {return container->valueList[index];}
    int* operator->() const{return &container->valueList[index];}

    MyIterator& operator++() 
    { 
        ++index; 
        return *this; 
    }
    MyIterator operator++ ( int )
    {
        MyIterator clone(*this);
        ++index;
        return clone;
    }

    bool operator==(const MyIterator& right) const
    {
        return (index == right.index);
    }

    bool operator!=(const MyIterator& right) const
    {
        return (!(*this == right));
    }

private:
    Container *container;
    int index;
};

#endif
#endif