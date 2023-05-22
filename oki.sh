#!/bin/bash

# Test suite for your shell

# Function to check the output and error handling of a command
check_command() {
  local command="$1"
  local expected_output="$2"
  local expected_error="$3"

  echo "Command: $command"
  echo "Expected output: $expected_output"
  echo "Expected error: $expected_error"

  # Run the command in your shell and capture the output and error
  output=$(echo "$command" | PATH="/bin" ./your_shell 2>/dev/null)
  error=$(echo "$command" | PATH="/bin" ./your_shell 2>&1 >/dev/null)

  # Run the command in /bin/sh shell and capture the output and error
  expected_output=$(echo "$command" | /bin/sh 2>/dev/null)
  expected_error=$(echo "$command" | /bin/sh 2>&1 >/dev/null)

  # Compare the output and error with the expected values
  if [[ "$output" == "$expected_output" && "$error" == "$expected_error" ]]; then
    echo "Test passed."
  else
    echo "Test failed."
    echo "Actual output: $output"
    echo "Actual error: $error"
  fi

  echo
}

# Test case 1: Run a simple command
echo "Test Case 1: Run a simple command"
echo "--------------------------------"
check_command "ls" "" ""
echo

# Test case 2: Run an unknown command
echo "Test Case 2: Run an unknown command"
echo "----------------------------------"
check_command "foobar" "" "your_shell: command not found: foobar"
echo

# Test case 3: Handle end of file (Ctrl+D)
echo "Test Case 3: Handle end of file (Ctrl+D)"
echo "----------------------------------------"
check_command "" "" "your_shell: end of file"
echo

# Test case 4: Run a command with arguments
echo "Test Case 4: Run a command with arguments"
echo "----------------------------------------"
check_command "echo Hello, World!" "Hello, World!" ""
echo

# Test case 5: Run a command with multiple arguments
echo "Test Case 5: Run a command with multiple arguments"
echo "------------------------------------------------"
check_command "echo This is a test." "This is a test." ""
echo

# Test case 6: Run a command in your shell that fails
echo "Test Case 6: Run a failing command"
echo "---------------------------------"
check_command "non_existing_command" "" "your_shell: command not found: non_existing_command"
echo

# Add more test cases as needed

echo "Test suite complete."

