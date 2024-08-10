#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h> // To check the folder and file information
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void printPermissions(const char *PATH, string fileType)
{
    struct stat info;
    int stats = stat(PATH, &info);

    if (stats != 0)
    {
        cout << "Error in opening the file.\n";
    }
    else if (S_ISDIR(info.st_mode) != -1)
    {
        mode_t mode = info.st_mode;

        string userRead = (mode & 0400) ? "Yes" : "No";
        string userWrite = (mode & 0200) ? "Yes" : "No";
        string userExec = (mode & 0100) ? "Yes" : "No";

        string groupRead = (mode & 0040) ? "Yes" : "No";
        string groupWrite = (mode & 0020) ? "Yes" : "No";
        string groupExec = (mode & 0010) ? "Yes" : "No";

        string othersRead = (mode & 0004) ? "Yes" : "No";
        string othersWrite = (mode & 0002) ? "Yes" : "No";
        string othersExec = (mode & 0001) ? "Yes" : "No";

        cout << "User has read permissions on " << fileType << ": " << userRead << "\n";
        cout << "User has write permission on " << fileType << ": " << userWrite << "\n";
        cout << "User has execute permission on " << fileType << ": " << userExec << "\n";
        cout << "Group has read permissions on " << fileType << ": " << groupRead << "\n";
        cout << "Group has write permission on " << fileType << ": " << groupWrite << "\n";
        cout << "Group has execute permission on " << fileType << ": " << groupExec << "\n";
        cout << "Others has read permissions on " << fileType << ": " << othersRead << "\n";
        cout << "Others has write permissions on " << fileType << ": " << othersWrite << "\n";
        cout << "Others has execute permissions on " << fileType << ": " << othersExec << "\n";

        cout << "---------------------------------------------------------------\n";
    }
    else
    {
        cout << "Specified path does not point to a folder.\n";
    }
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);

    const char *NEW_FILE_PATH = argv[1];
    const char *OLD_FILE_PATH = argv[2];
    const char *DIR_FILE_PATH = argv[3];

    printPermissions(NEW_FILE_PATH, "newfile");
    printPermissions(OLD_FILE_PATH, "old file");
    printPermissions(DIR_FILE_PATH, "directory");

    return 0;
}