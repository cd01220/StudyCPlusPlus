#ifndef _Common_h_
#define _Common_h_

#if _MSC_VER >= 1700 || GCC_VERSION > 40600

template<class T>
class MemStream
{
public:
    MemStream(const T* const theMem, size_t theLen):mem(theMem), len(theLen){}

    void Put(std::ostream& os) const
    {
        size_t i;
        std::ios::fmtflags flags = os.setf(std::ios::hex, std::ios::basefield);
        for (i = 0; i < len; ++i)
        {
            if (i != 0)
            {
                if (i % 16 == 0)
                {
                    os << std::endl;
                }
                else if (i % 8 == 0)
                {
                    os << "  ";
                }
            }
            os << std::setw(2) << std::setfill('0') << (uint_t)(uchar_t)mem[i];
        }
        os.setf(flags, std::ios::basefield);
    }
private:
    const T* const mem;
    size_t   len;
};

inline std::ostream& operator << (std::ostream& os, MemStream<uint_t> const& mem)
{
    mem.Put(os);
    return os;
}

inline std::ostream& operator << (std::ostream& os, MemStream<uchar_t> const& mem)
{
    mem.Put(os);
    return os;
}

#define MacBroadcast (uchar_t*)"\xFF\xFF\xFF\xFF\xFF\xFF"
#define MacZero      (uchar_t*)"\x00\x00\x00\x00\x00\x00"
 
class Mac
{
public:    
    Mac(const uchar_t*);
    Mac(Mac const&);
    Mac const& operator =(Mac const&);
    bool IsBroadcast() const;
    bool IsZero() const;

    int Compare(Mac const&) const;
    void Put(std::ostream&) const;

private:
    Mac();
    std::shared_ptr<uchar_t> mac;
};
std::ostream& operator << (std::ostream& os, Mac const& mac);
inline bool operator == (Mac const& left, Mac const& right)
{
    return (left.Compare(right) == 0);
}

inline bool operator != (Mac const& left, Mac const& right)
{
    return !(left == right);
}

inline bool operator < (Mac const& left, Mac const& right)
{
    return (left.Compare(right) < 0);
}

inline bool operator > (Mac const& left, Mac const& right)
{
    return (left.Compare(right) > 0);
}

#endif

/******************Read from / Write to packet buffer******************/
size_t Read16(uchar_t* buf, uint16_t&);
size_t Read32(uchar_t* buf, uint32_t&);

size_t Write16(uchar_t* buf, uint16_t);
size_t Write32(uchar_t* buf, uint32_t);

/******************shared_ptr<...> deleter******************/
/*
CharDeleter, auxiliary class used by shared_ptr<char>.  
Example:
{
    shared_ptr<char> buffer(new char[128], CharDeleter());
}
*/
class CharDeleter
{
public:
    CharDeleter()
    {}

    void operator()(char *ptr) const
    {
        delete[] ptr;
    }
};

class UcharDeleter
{
public:
    UcharDeleter()
    {}

    void operator()(uchar_t *ptr) const
    {
        delete[] ptr;
    }
};

#endif
