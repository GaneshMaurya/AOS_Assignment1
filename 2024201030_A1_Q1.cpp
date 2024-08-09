#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/stat.h>  // For creating a new directory (mkdir)
#include <sys/types.h> // For creating a new directory (mkdir)
#include <fcntl.h>     // For opening a file
#include <unistd.h>    // For reading data from file
#include <time.h>      // Used for calculating the time
using namespace std;

// Define the buffer size beforehand.
const int BUFFER_SIZE = 100000;

void reverseString(string &str, int start, int end)
{
    while (start < end)
    {
        swap(str[start], str[end]);
        start++;
        end--;
    }
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio();
    cin.tie(NULL);
    cout.tie(NULL);

    const char *INPUT_FILE_PATH = argv[1];
    int flag = stoi(argv[2]);
    const char *FOLDER_PATH = "Assignment1/";

    if (flag == 0)
    {
        // Reverse the file
        // Make a directory and five RWX access group and user
        // Check if folder is already created
        if (mkdir(FOLDER_PATH, 0770) < 0 && errno == EEXIST)
        {
            if (rmdir(FOLDER_PATH) == 0)
            {
                cout << "Folder does not exist. Proceeding to create.\n";
            }
            else
            {
                cout << "Folder already exists. Hence deleting all its contents.\n";
            }
            mkdir(FOLDER_PATH, 0770);
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
            char inputDataBuffer[BUFFER_SIZE];

            // lseek(inputFile, BUFFER_SIZE, SEEK_SET);
            ssize_t inputSize = read(inputFile, inputDataBuffer, BUFFER_SIZE);

            if (inputSize == 0)
            {
                cout << "Error in reading the file.\n";
                return 0;
            }
            else
            {
                string str = inputDataBuffer;
                double time1 = (double)clock() / CLOCKS_PER_SEC;
                reverseString(str, 0, str.size() - 1);

                char outputDataBuffer[str.size()];
                for (int i = 0; i < str.size(); i++)
                {
                    outputDataBuffer[i] = str[i];
                }

                string OUTPUT_FILE_NAME = "output.txt";
                string OUTPUT_FILE_PATH = FOLDER_PATH + OUTPUT_FILE_NAME;

                int outputFile = open(OUTPUT_FILE_PATH.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0770);
                if (outputFile < 0)
                {
                    // Errors - Handle this
                    cout << " Error in opening the output file.\n";
                    return 0;
                }

                ssize_t outputSize = write(outputFile, outputDataBuffer, str.size());
                if (outputSize < 0)
                {
                    cout << "Error in writing content onto the file.\n";
                    return 0;
                }

                double time2 = (double)clock() / CLOCKS_PER_SEC;
                printf("File took %lfs to reverse and write onto new text file.\n", time2 - time1);
            }
        }
    }
    else if (flag == 1)
    {
        // Reverse first part and last part of file
        int start_index = stoi(argv[4]);
        int end_index = stoi(argv[5]);
    }
    else
    {
        cout << "Error. Enter correct flag value. Correct values are 0 and 1\n";
    }

    return 0;
}