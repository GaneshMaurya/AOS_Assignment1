#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h> // To check the folder and file information
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);

    const char *NEW_FILE_PATH = argv[1];
    const char *OLD_FILE_PATH = argv[2];
    const char *DIR_FILE_PATH = argv[3];

    // Check if directory is created or not
    bool isDirCreated = false;

    // Check if the input file and output file has the same size
    bool checkSizeInputOutput = false;

    // Check permissions on the input file
    bool userReadInputFile = false;
    bool userWriteInputFile = false;
    bool userExecInputFile = false;
    bool groupReadInputFile = false;
    bool groupWriteInputFile = false;
    bool groupExecInputFile = false;
    bool othersReadInputFile = false;
    bool othersWriteInputFile = false;
    bool othersExecInputFile = false;

    // Check permissions on the output file
    bool userReadOutputFile = false;
    bool userWriteOutputFile = false;
    bool userExecOutputFile = false;
    bool groupReadOutputFile = false;
    bool groupWriteOutputFile = false;
    bool groupExecOutputFile = false;
    bool othersReadOutputFile = false;
    bool othersWriteOutputFile = false;
    bool othersExecOutputFile = false;

    // Check permissions on the directory file
    bool userReadDir = false;
    bool userWriteDir = false;
    bool userExecDir = false;
    bool groupReadDir = false;
    bool groupWriteDir = false;
    bool groupExecDir = false;
    bool othersReadDir = false;
    bool othersWriteDir = false;
    bool othersExecDir = false;

    struct stat dirInfo;
    if (lstat(DIR_FILE_PATH, &dirInfo) != 0)
    {
        cout << "Error in opening the file.\n";
    }
    else if (dirInfo.st_mode && S_IFDIR)
    {
        isDirCreated = true;
        cout << dirInfo.st_mode << "\n";
    }
    else
    {
        cout << "Specified path does not point to a folder.\n";
    }

    return 0;
}