#include "SystemInclude.h"
#include "Common.h"
#include "Debug.h"
#include "SystemError.h" 
#include "MyList.h"
#include "Main.h"

using namespace std;

int main()
{
    //class ListValue<struct ListSimpleTypes<int> >
    cout << typeid(List<int>::ListValue::MyType).name() << endl;
  
	return 0;
}
