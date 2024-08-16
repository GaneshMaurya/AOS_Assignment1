def process_file(input_filename, output_filename, start_index, end_index):
    # Read the input file
    with open(input_filename, 'r') as infile:
        input_text = infile.read()

    # Split the input text into three parts
    part1 = input_text[:start_index][::-1]  # Reverse from 0 to start_index - 1
    part2 = input_text[start_index:end_index + 1]  # Keep from start_index to end_index as is
    part3 = input_text[end_index + 1:][::-1]  # Reverse from end_index + 1 to the end
    
    # Combine the parts to form the output
    output_text = part1 + part2 + part3

    # Write the output text to the output file
    with open(output_filename, 'w') as outfile:
        outfile.write(output_text)

    return output_text

def verify_output(output_filename, expected_output):
    with open(output_filename, 'r') as outfile:
        actual_output = outfile.read()
    
    if actual_output == expected_output:
        print("Success: The output file matches the expected output.")
    else:
        print("Error: The output file does not match the expected output.")
        print(f"Expected Output: {expected_output}")
        print(f"Actual Output: {actual_output}")

# Example usage
input_filename = 'input.txt'
output_filename = 'Assignment1/1_input.txt'
start_index = 10  # Example start index
end_index = 999999990 # Example end index

# Process the input file and generate the output
expected_output = process_file(input_filename, output_filename, start_index, end_index)

# Verify if the output is correct
verify_output(output_filename, expected_output)
