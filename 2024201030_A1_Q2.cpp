#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h> // To check the folder and file information
#include <fcntl.h>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 4000;

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

        cout << "---------------------------------------------------------------\n";

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

bool checkRev(char *inputChunk, char *outputChunk)
{
    int n = strlen(inputChunk);

    int i = 0;
    int j = strlen(outputChunk) - 1;

    while (i < n && j >= 0)
    {
        if (inputChunk[i] != outputChunk[j])
        {
            return false;
        }
        i++;
        j--;
    }

    return true;
}

void checkFileReversed(char *NEW_FILE_PATH, char *OLD_FILE_PATH)
{
    int inputFile = open(OLD_FILE_PATH, O_RDONLY);
    int outputFile = open(NEW_FILE_PATH, O_RDONLY);
    int inputFileSize = lseek(inputFile, 0, SEEK_END);
    int outputFileSize = lseek(outputFile, 0, SEEK_END);

    int inputChunk = inputFileSize >= BUFFER_SIZE ? BUFFER_SIZE : inputFileSize;
    int outputChunk = outputFileSize >= BUFFER_SIZE ? BUFFER_SIZE : outputFileSize;

    int inputPointer = 0;
    int outputPointer = outputFileSize - outputChunk;

    bool isRev = true;
    char *inputBuffer = (char *)malloc(inputChunk);
    char *outputBuffer = (char *)malloc(outputChunk);

    while (inputPointer < inputFileSize && outputPointer > 0)
    {
        // cout << inputPointer << " - " << outputPointer << endl;

        lseek(inputFile, inputPointer, SEEK_SET);
        read(inputFile, inputBuffer, inputChunk);
        lseek(outputFile, outputPointer, SEEK_SET);
        read(outputFile, outputBuffer, outputChunk);

        // cout << inputBuffer << " - " << outputBuffer << endl;

        if (!checkRev(inputBuffer, outputBuffer))
        {
            isRev = false;
            cout << "Whether file contents are reversed in newfile: No\n";
            break;
        }

        if (inputPointer + BUFFER_SIZE <= inputFileSize)
        {
            inputPointer += BUFFER_SIZE;
            inputChunk = BUFFER_SIZE;
        }
        else
        {
            inputChunk = inputFileSize - inputPointer;
            inputPointer = inputFileSize;
        }

        if (outputPointer - BUFFER_SIZE >= 0)
        {
            outputPointer -= BUFFER_SIZE;
            outputChunk = BUFFER_SIZE;
        }
        else
        {
            outputChunk = outputPointer;
            outputPointer = 0;
        }

        // cout << inputPointer << " - " << outputPointer << endl;
    }

    free(inputBuffer);
    free(outputBuffer);

    if (isRev == true)
    {
        cout << "Whether file contents are reversed in newfile: Yes\n";
    }

    close(inputFile);
    close(outputFile);
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);

    char *NEW_FILE_PATH = argv[1];
    char *OLD_FILE_PATH = argv[2];
    char *DIR_FILE_PATH = argv[3];

    string isDirCreated;
    struct stat dirInfo;
    int dirStat = stat(DIR_FILE_PATH, &dirInfo);
    if (dirStat != -1)
    {
        isDirCreated = "Yes";
    }
    else
    {
        isDirCreated = "No";
    }
    cout << "Directory is created: " << isDirCreated << "\n";

    struct stat newFileInfo;
    int newFileStat = stat(NEW_FILE_PATH, &newFileInfo);
    struct stat oldFileInfo;
    int oldFileStat = stat(OLD_FILE_PATH, &oldFileInfo);

    off_t inputFileSize = newFileInfo.st_size;
    off_t outputFileSize = newFileInfo.st_size;

    string isSizeSame;

    if (inputFileSize == outputFileSize)
    {
        isSizeSame = "Yes";
        cout << "Input File Size: " << inputFileSize << "B\n";
        cout << "Output File Size: " << outputFileSize << "B\n";
        cout << "Both Files Sizes are Same : " << isSizeSame << "\n";
        checkFileReversed(OLD_FILE_PATH, NEW_FILE_PATH);
    }
    else
    {
        isSizeSame = "No";
        cout << "Both Files Sizes are Same : " << isSizeSame << "\n";
        cout << "Whether file contents are reversed in newfile: No\n";
    }

    printPermissions(NEW_FILE_PATH, "newfile");
    printPermissions(OLD_FILE_PATH, "old file");
    printPermissions(DIR_FILE_PATH, "directory");

    return 0;
}