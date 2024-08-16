# Assignment1

Submitted by G V Ganesh Maurya - 2024201030

### Question-1

- Instructions were to reverse the content of an input file and store the result into another file.
- Two flags will be given as input 0 nad 1 (with start and end index).
- If the flag is 0, then reverse the entire content.
- If the flag is 1, reverse from starting till start index, leave the portion between start index and end index as it is, and then reverse the remaining portion of the file.

### Algorithm
- First handle all the wrong inputs(like flag values other than 0 or 1, wrong index values, etc.)
- If the flag is 0, create a dir using ```mkdir()``` and give the required permissions to the folder.
- Use ```open()``` system call and open the input text file. Read the input file using ```read()``` system call.
- Similarly open/create the output file.
- Reversing process is done chunk by chunk.
- We iterate the input file from the end using ```lseek()``` system call and read the last "chunk", reverse it and store the value in a dynamic array(buffer).
- Then this buffer is written onto the output file using ```write()``` system call.
- The loop goes on until the iterator reaches the beginning of the input file, which then terminates the loop.
- Similarly, for flag 1, iterate the portions separately.
- First portion (0 to start_index-1): In reverse order using ```lseek()``` and ```SEEK_SET``` flag.
- Second portion (start_index to end_index): Iterate in the normal order and write it onto the output file.
- Third portion (end_index+1 to last): Reverse in the reverse direction and write onto the file.


#### Code to run the code for Q1

To run the code please use the below commands

To compile the C++ program
```bash
  g++ 2024201030_A1_Q1.cpp -o Q1.out
```
In case of flag 0
```bash
  ./Q1.out input.txt 0
```

In case of flag 1
```bash
  ./Q1.out input.txt 1 5 10
```
Input file name, start and end indexes can be updated as required.

### Question-2

- Instructions were to test whether the output of first question (flag 0) is correct or not.
- In the second part of the code we have to check wht permissions of the input file, output file and directory.

### Algorithm
- Reverse checking is similar to the previous code.
- Read both the given files chunk by chunk. Read one of the file (input.txt) in forward direction and other (output.txt) file in reverse direction.
- Compare the two buffers using a while loop and if any of the characters do not match, then break out and output "No".
- For checking the permissions we can use ```stat()``` system call. 
- ```stat()``` returns a structure called stat. This stat stored the properties of the file like permissions, size in bytes, time of access, etc.
- For our case we only need st_mode (for permissions) and st_size (size of file).


#### Code to run the code for Q2

To run the code please use the below commands

To compile the C++ program
```bash
  g++ 2024201030_A1_Q2.cpp -o Q2.out
```
To run the C++ program and get the output
```bash
  ./Q1.out Assignment1/0_input.txt input.txt Assignment1/
```