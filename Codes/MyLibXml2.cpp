#include "SystemInclude.h"
#include "MyLibXml2.h"

using namespace std;

void PrintXpathNode(xmlNodeSetPtr nodes)
{
    size_t i, size;
    size = (nodes) ? nodes->nodeNr : 0;     

    string del(10, '-');
    del = del + "  ";
    cout.setf(ios::left);
    cout << setw(12) << "ID" << setw(12) << "Name" << setw(20) << "Email" << setw(12) << "Company" << endl;
    cout << del << del << setw(20) << del << del << endl;

    for (i = 0; i < size; ++i)
    {        
        if(nodes->nodeTab[i]->type != XML_ELEMENT_NODE)
            continue;

        xmlNodePtr cur = nodes->nodeTab[i];           
        for (cur = xmlFirstElementChild(cur); cur != nullptr; cur = xmlNextElementSibling(cur))
        {
            if (xmlStrcmp(cur->name, (xmlChar*)"ID") == 0)
                cout << setw(12) << (char*)xmlNodeGetContent(cur);

            if (xmlStrcmp(cur->name, (xmlChar*)"Name") == 0)
                cout << setw(12) << (char*)xmlNodeGetContent(cur);

            if (xmlStrcmp(cur->name, (xmlChar*)"Email") == 0)
                cout << setw(20) << (char*)xmlNodeGetContent(cur);

            if (xmlStrcmp(cur->name, (xmlChar*)"Company") == 0)
                cout << setw(12) << (char*)xmlNodeGetContent(cur);
        }
        cout << endl;
    }    
}

void TraverseXmlXpathNode()
{
    const char* xmlFile = "../XmlFiles/AddressListXml.xml";

    xmlInitParser();

    shared_ptr<xmlDoc> doc(xmlParseFile(xmlFile), XmlDocDeleter());
    shared_ptr<xmlXPathContext> xpathCtx(xmlXPathNewContext(doc.get()), xmlXPathContextDeleter());
    
    xmlChar *xpathExpr = (xmlChar*)"/AddressList/Contact[*]";
    shared_ptr<xmlXPathObject> xpathObj(xmlXPathEvalExpression(xpathExpr, xpathCtx.get()), xmlXPathObjectDeleter()); 

    PrintXpathNode(xpathObj->nodesetval);
}