#include "SystemInclude.h"
#include <regex>

#include "ClassCreator.h"
#include "Main.h"

using namespace std;

#define BufferSize 1024*16
char buffer[BufferSize];
char buffer2[BufferSize];

HANDLE hDir;
HANDLE hIoCompPort;
DWORD bytes;
std::thread myThread1;
std::thread myThread2;
std::thread myThread3;
std::thread myThread4;

ULONG somekey = 1;
ULONG_PTR CompletionKey;
    

    OVERLAPPED overlapped;


std::mutex  myMutext;

void ThreadMain(const char* value)
{ 
    BOOL resultl, resultr;
    LPOVERLAPPED lpoverlapped;
    DWORD filter = FILE_NOTIFY_CHANGE_FILE_NAME;
    char file[MAX_PATH];
    DWORD action;
    while (true)
    {
        memset(&overlapped, sizeof(OVERLAPPED), 0);
        resultl = ReadDirectoryChangesW(hDir, 
            (void*)buffer, BufferSize, FALSE,  
                filter,
            NULL, &overlapped, NULL );

        resultr = GetQueuedCompletionStatus(hIoCompPort, &bytes, 
            &CompletionKey, &lpoverlapped, INFINITE);

        FILE_NOTIFY_INFORMATION* ptr;
        
        size_t offset = 0;
        do
        {
            ptr = (FILE_NOTIFY_INFORMATION*)&buffer[offset];
            offset = offset + ptr->NextEntryOffset;
            
            int count = WideCharToMultiByte(CP_ACP, 0, ptr->FileName,
                ptr->FileNameLength / sizeof(WCHAR),
                file, MAX_PATH - 1, NULL, NULL);
            file[count] = '\0';

            action = ptr->Action;
 
            if (resultl && resultr)
            {            
                if (action == FILE_ACTION_ADDED)
                {
                    cout << file << endl;

                    string xmlPath = string("D:/Temp/XmlFiles/") + string(file);
                    fstream fs(xmlPath, ios::in | ios::binary);
                    fs.read(buffer2, BufferSize);
                    size_t size = (size_t)fs.gcount();                
                    //cout << buffer2 << endl;
                    buffer2[size] = 0;
                    assert(size != 0);
                    fs.close();
                    
                    remove(xmlPath.c_str());
                }
            }
            else
            {   cout << "error" << endl;}
        }while (ptr->NextEntryOffset != 0);
    } 
}

void WatchDir()
{
    hDir = CreateFile("D:\\Temp\\XmlFiles", 
        FILE_LIST_DIRECTORY, 
        FILE_SHARE_READ | FILE_SHARE_WRITE ,
        NULL, //security attributes
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, //OVERLAPPED!
        NULL);
    
    hIoCompPort = CreateIoCompletionPort(hDir, 
        NULL, 
        (ULONG_PTR)&somekey, 
        1);
    if( hIoCompPort == NULL )
    {
        DWORD dwError = GetLastError();
        cout << "CreateIoCompletionPort failed. dwError = " << dwError << endl;
        return;
    }

    myThread1 = thread(ThreadMain, ".*nit.*\\.xml");
}

int main()
{
    WatchDir();
    
    while(true) { SleepEx(5, true); }
    return 0;
}
