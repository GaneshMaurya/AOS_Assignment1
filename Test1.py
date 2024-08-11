def is_reverse(file1_path, file2_path):
    try:
        with open(file1_path, 'r') as f1, open(file2_path, 'r') as f2:
            # Read all content from both files
            content1 = f1.read().strip()
            content2 = f2.read().strip()
            
            # Check if the content of one file is the reverse of the other
            if content1 == content2[::-1]:
                print("Success!!")
            else:
                print("Failed!!")
                
    except IOError as e:
        print("An error occurred while accessing the files")

# Example usage
file1_path = 'input.txt'
file2_path = 'Assignment1/output.txt'

is_reverse(file1_path, file2_path)
