#include "SystemInclude.h"
#include "SystemError.h" 

#if _MSC_VER >= 1700 || GCC_VERSION > 40600

using namespace std;
const char* system_category_impl::name() const noexcept
{
    return "Router error.";
}

string system_category_impl::message(int ev) const
{
    string ret;
    switch(ev)
    {
    case (int)system_error_t::file_not_exists:
        ret = "file not exists";
        break;
    case (int)system_error_t::bad_file_type:
        ret = "bad file type (supposed to be pcap format, 802.11 packet)";
        break;
    default:
        ret = "unknown error";
    }
    return ret;
}

error_condition system_category_impl::default_error_condition(int ev) const noexcept
{
    return error_condition(ev, *this);
}

const error_category& router_category()
{
    static system_category_impl instance;
    return instance;
}

error_code make_error_code(system_error_t e)
{
    return error_code(static_cast<int>(e), router_category());
}

error_condition make_error_condition(system_error_t e)
{
    return error_condition(static_cast<int>(e), router_category());
}

#endif
