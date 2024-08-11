#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/stat.h>  // For creating a new directory (mkdir)
#include <sys/types.h> // For creating a new directory (mkdir)
#include <fcntl.h>     // For opening a file
#include <unistd.h>    // For reading data from file
#include <time.h>      // Used for calculating the time
using namespace std;

// Define the buffer size beforehand.
const int BUFFER_SIZE = 4000;

string getOutputName(string str)
{
    string res = "";
    int i = str.size() - 1;
    while (i >= 0 && str[i] != '/')
    {
        res += str[i];
        i--;
    }

    reverse(res.begin(), res.end());
    res = "O_" + res;

    return res;
}

void reverseString(string &str, int start, int end)
{
    int i = start;
    int j = end;
    while (i <= j)
    {
        swap(str[i], str[j]);
        i++;
        j--;
    }
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);
    // To check the folder and file information
    const char *INPUT_FILE_PATH = argv[1];
    int flag = stoi(argv[2]);
    const char *FOLDER_PATH = "Assignment1/";

    if (flag == 0)
    {
        // Reverse the file
        // Make a directory and file RWX access group and user
        // Check if folder is already created
        int createDir = mkdir(FOLDER_PATH, 0700);
        chmod(FOLDER_PATH, 0700);
        if (createDir < 0 && errno == EEXIST)
        {
            // Folder already exists. Hence deleting all its contents.
            rmdir(FOLDER_PATH);
            mkdir(FOLDER_PATH, 0700);
            chmod(FOLDER_PATH, 0700);
        }

        // Open file in Read only mode
        int inputFile = open(INPUT_FILE_PATH, O_RDWR);
        if (inputFile < 0)
        {
            // Errors - Handle this
            cout << "Error in opening the input file.\n";
            return 0;
        }
        else
        {
            // Function to read a file. Reads n Bytes of the input.txt file and stores it in the below char array
            char *inputDataBuffer = (char *)malloc(BUFFER_SIZE * (sizeof(char)));
            ssize_t inputSize = read(inputFile, inputDataBuffer, BUFFER_SIZE);

            if (inputSize == 0)
            {
                cout << "Error in reading the file.\n";
                return 0;
            }
            else
            {
                string OUTPUT_FILE_NAME = getOutputName(INPUT_FILE_PATH);
                string OUTPUT_FILE_PATH = FOLDER_PATH + OUTPUT_FILE_NAME;

                int outputFile = open(OUTPUT_FILE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600);
                chmod(OUTPUT_FILE_PATH.c_str(), 0600);
                if (outputFile < 0)
                {
                    // Errors - Handle this
                    cout << " Error in opening the output file.\n";
                    return 0;
                }
                double time1 = (double)clock() / CLOCKS_PER_SEC;

                off_t totalSize = lseek(inputFile, 0, SEEK_END);
                size_t currBufferSize = 0;
                size_t currAllocSpace = 0;
                while (currBufferSize < totalSize)
                {
                    if (currBufferSize + BUFFER_SIZE <= totalSize)
                    {
                        currAllocSpace = BUFFER_SIZE;
                        currBufferSize += BUFFER_SIZE;
                    }
                    else
                    {
                        currAllocSpace = totalSize - currBufferSize;
                        currBufferSize = totalSize;
                    }

                    inputDataBuffer = (char *)malloc(currAllocSpace);

                    lseek(inputFile, -currBufferSize, SEEK_END);
                    read(inputFile, inputDataBuffer, currAllocSpace);

                    string str = inputDataBuffer;
                    reverseString(str, 0, currAllocSpace - 1);

                    char outputDataBuffer[currAllocSpace];
                    for (int i = 0; i < currAllocSpace; i++)
                    {
                        outputDataBuffer[i] = str[i];
                    }

                    ssize_t outputSize = write(outputFile, outputDataBuffer, currAllocSpace);
                    if (outputSize < 0)
                    {
                        cout << "Error in writing content onto the file.\n";
                        return 0;
                    }
                    double percentage = ((double)currBufferSize * 100.0 / (double)totalSize);
                    cout << "\r" << "Progress = " << percentage << " %" << flush;

                    free(inputDataBuffer);
                }
                cout << "\n";

                double time2 = (double)clock() / CLOCKS_PER_SEC;
                printf("File took %lfs to reverse and write onto new text file.\n", time2 - time1);
                close(inputFile);
                close(outputFile);
            }
        }
    }
    else if (flag == 1)
    {
        // Reverse first part and last part of file
        int start_index = stoi(argv[3]);
        int end_index = stoi(argv[4]);

        if (start_index > end_index)
        {
            cout << "Error. Start index is greater than End index.\n";
        }

        int createDir = mkdir(FOLDER_PATH, 0700);
        chmod(FOLDER_PATH, 0700);
        if (createDir < 0 && errno == EEXIST)
        {
            // Folder already exists. Hence deleting all its contents.
            rmdir(FOLDER_PATH);
            mkdir(FOLDER_PATH, 0700);
            chmod(FOLDER_PATH, 0700);
        }

        // Open file in Read only mode
        int inputFile = open(INPUT_FILE_PATH, O_RDWR);
        if (inputFile < 0)
        {
            // Errors - Handle this
            cout << "Error in opening the input file.\n";
            return 0;
        }
        else
        {
            char *inputDataBuffer = (char *)malloc(BUFFER_SIZE * (sizeof(char)));
            ssize_t inputSize = read(inputFile, inputDataBuffer, BUFFER_SIZE);

            if (inputSize == 0)
            {
                cout << "Error in reading the file.\n";
                return 0;
            }
            else
            {
                string OUTPUT_FILE_NAME = getOutputName(INPUT_FILE_PATH);
                string OUTPUT_FILE_PATH = FOLDER_PATH + OUTPUT_FILE_NAME;

                int outputFile = open(OUTPUT_FILE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0600);
                chmod(OUTPUT_FILE_PATH.c_str(), 0600);
                if (outputFile < 0)
                {
                    // Errors - Handle this
                    cout << " Error in opening the output file.\n";
                    return 0;
                }

                double time1 = (double)clock() / CLOCKS_PER_SEC;

                // Reverse first part (from 0 to start_index - 1)
                size_t fileSize = lseek(inputFile, 0, SEEK_END);
                int currPointer = start_index;
                size_t chunk = 0;

                size_t totalSizeTillNow = 0;

                // Reverse first portion
                while (currPointer > 0)
                {
                    if (currPointer >= BUFFER_SIZE)
                    {
                        currPointer -= BUFFER_SIZE;
                        chunk = BUFFER_SIZE;
                    }
                    else
                    {
                        chunk = currPointer;
                        currPointer = 0;
                    }

                    inputDataBuffer = (char *)malloc(chunk);

                    lseek(inputFile, currPointer, SEEK_SET);
                    read(inputFile, inputDataBuffer, chunk);

                    string str = inputDataBuffer;
                    reverseString(str, 0, chunk - 1);

                    char *outputDataBuffer = (char *)malloc(chunk);
                    for (int i = 0; i < chunk; i++)
                    {
                        outputDataBuffer[i] = str[i];
                    }

                    ssize_t outputSize = write(outputFile, outputDataBuffer, chunk);
                    if (outputSize < 0)
                    {
                        cout << "Error in writing content onto the file first step.\n";
                        return 0;
                    }

                    free(inputDataBuffer);
                    free(outputDataBuffer);

                    totalSizeTillNow += chunk;
                    double percentage = ((double)totalSizeTillNow * 100.0 / (double)fileSize);
                    cout << "\r" << "Progress = " << percentage << " %" << flush;
                }

                // Write the second protion as it is
                lseek(inputFile, start_index, SEEK_SET);
                currPointer = start_index;
                while (currPointer < end_index + 1)
                {
                    int flag = false;
                    if (currPointer + BUFFER_SIZE <= end_index)
                    {
                        currPointer += BUFFER_SIZE;
                        chunk = BUFFER_SIZE;
                    }
                    else
                    {
                        chunk = end_index - currPointer + 1;
                        currPointer = end_index + 1;
                        flag = true;
                    }

                    inputDataBuffer = (char *)malloc(chunk);
                    read(inputFile, inputDataBuffer, chunk);
                    lseek(inputFile, currPointer, SEEK_SET);

                    ssize_t outputSize = write(outputFile, inputDataBuffer, chunk);
                    if (outputSize < 0)
                    {
                        cout << "Error in writing content onto the file second step.\n";
                        return 0;
                    }

                    free(inputDataBuffer);
                    totalSizeTillNow += chunk;
                    double percentage = ((double)totalSizeTillNow * 100.0 / (double)fileSize);
                    cout << "\r" << "Progress = " << percentage << " %" << flush;
                }

                // Reverse the last protion
                currPointer = fileSize;
                while (currPointer > end_index)
                {
                    bool flag = false;
                    if (currPointer - BUFFER_SIZE > end_index)
                    {
                        currPointer -= BUFFER_SIZE;
                        chunk = BUFFER_SIZE;
                    }
                    else
                    {
                        flag = true;
                        chunk = currPointer - (end_index + 1);
                        currPointer = end_index + 1;
                    }

                    inputDataBuffer = (char *)malloc(chunk);
                    lseek(inputFile, currPointer, SEEK_SET);
                    read(inputFile, inputDataBuffer, chunk);

                    string str = inputDataBuffer;
                    reverseString(str, 0, chunk - 1);

                    char *outputDataBuffer = (char *)malloc(chunk);
                    for (int i = 0; i < chunk; i++)
                    {
                        outputDataBuffer[i] = str[i];
                    }

                    ssize_t outputSize = write(outputFile, outputDataBuffer, chunk);
                    if (outputSize < 0)
                    {
                        cout << "Error in writing content onto the file last step.\n";
                        return 0;
                    }

                    free(inputDataBuffer);
                    free(outputDataBuffer);

                    totalSizeTillNow += chunk;
                    double percentage = ((double)totalSizeTillNow * 100.0 / (double)fileSize);
                    cout << "\r" << "Progress = " << percentage << " %" << flush;

                    if (flag == true)
                    {
                        break;
                    }
                }

                double time2 = (double)clock() / CLOCKS_PER_SEC;
                cout << "\n";
                printf("File took %lfs to do the operations and write onto new text file.\n", time2 - time1);
                close(inputFile);
                close(outputFile);
            }
        }
    }
    else
    {
        cout << "Error. Enter correct flag value. Correct values are 0 and 1\n";
    }

    return 0;
}