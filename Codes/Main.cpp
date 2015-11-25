#include "SystemInclude.h"
#include "VariadicExpand.h"
#include "Main.h"

using namespace std;

static AutoRegisterSuite des1_1(1, new ConcreateCreator<1, std::tuple<int>>);
static AutoRegisterSuite des1_2_1(1, new ConcreateCreator<1, std::tuple<int, int>>);
static AutoRegisterSuite des1_2_2(1, new ConcreateCreator<1, std::tuple<int, char*>>);
static AutoRegisterSuite des2_1(2, new ConcreateCreator<2, std::tuple<int>>);

int main()
{
    CreateDescriptor(1, 1);
    CreateDescriptor(1, 1, 2);
    CreateDescriptor(1, 1, (char*)"abcd");
    CreateDescriptor(2, 1);
    
    return 0;
}
