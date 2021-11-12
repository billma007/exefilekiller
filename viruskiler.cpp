#include <iostream>
#include <cstring>
#include <windows.h>

void listFiles(const char * dir);

int main()
{
    using namespace std;
    char dir[100];
    cout << "Enter a directory (ends with \'\\\'): ";
    cin.getline(dir, 100);
    strcat(dir, "*.*");    // ��Ҫ��Ŀ¼�������*.*��ʾ�����ļ�/Ŀ¼
    listFiles(dir);
    return 0;
}

void listFiles(const char * dir)
{
    using namespace std;
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    hFind = FindFirstFile(dir, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Failed to find first file!\n";
        return;
    }
    do
    {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  
        {
            cout << findData.cFileName << "\t<dir>\n";
             string str="attrib \"";
//             string k(1,dir[0]);
//             str.append(k) ;
//             str.append("\\");
			str.append(findData.cFileName);
			str.append("\" -s -h");
            system(str.c_str());
            
        }
        else
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
        }
    } while (FindNextFile(hFind, &findData));
    cout << "Done!\n";
    system("Pause");
}
