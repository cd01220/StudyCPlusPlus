#include "SystemInclude.h"

#include "ClassCreator.h"
#include "Main.h"

using namespace std;
DescriptorCreatorRgistration1(NetworkNameDescriptor::Tag, 
                              (NetworkNameDescriptor::Constructor1)NetworkNameDescriptor::CreateInstance, int);
DescriptorCreatorRgistration2(NetworkNameDescriptor::Tag, 
                              (NetworkNameDescriptor::Constructor2)NetworkNameDescriptor::CreateInstance, uchar_t*, size_t);

int main()
{
    Descriptor *ptr0 = CreateDescriptor1<int>(0x40, 1);
    Descriptor *ptr1 = CreateDescriptor2<uchar_t*, size_t>(0x40, (uchar_t*)"\x30\x31", 2);

    return 0;
}
