# Student Management System
This is a simple C program designed to manage a list of students using a doubly linked list. It allows you to perform operations such as adding, searching, updating, and deleting students from the list, as well as saving and loading student data from a file.

**NOTE:** This project is developed as part of a university assignment at Harokopio University of Athens.

## Table of Contents
- Features
- Compiling the Program
- Running the Program
- Program Structure
- Functionality
- Error Handling
- File Format

## Features
- **Add Student:** Add a new student to the list with a generated unique ID.

- **Search Student:** Search for a student by ID and display their details.

- **Delete Student:** Remove a student from the list by ID.

- **Update Student:** Update the details of a student by ID.

- **Display Student:** Print details of a specific student by ID.

- **Display All Students:** Print details of all students in the list.

- **Persistent Storage:** Save and load the list of students to and from a binary file.


## Prerequisites
C compiler  
Make sure the <u>students.h</u> header file is included and properly configured.   
Compiling the Program   
To compile the program, use the following command:

```bash
gcc -o student_manager main.c students.c
```
**Ensure** all necessary source and header files are included in the same directory or adjust the command to reflect the file paths.

## Running the Program
Run the compiled executable with a file name as an argument for storing student data:

```bash
./student_manager students.dat
```
If the file does not exist, it will be created automatically.

## Program Structure
**The program is organized into the following components:**

- Main Function: Controls the program flow and user interaction.
- Menu Functions: Provide user options and handle input.
- Linked List Operations: Functions to manipulate the doubly linked list (add, delete, find, update).
- File Operations: Save and load student data to and from a binary file.
- Utility Functions: Helper functions for error handling and ID generation.

## Functionality
Menu Options
Upon running the program, the user is presented with a menu of options:

- Add New Student: Prompts for the student's name and adds them to the list with a unique ID.
- Search by ID: Prompts for a student ID and searches for the student in the list.
- Delete by ID: Prompts for a student ID and deletes the student from the list if found.
- Change Details of a Student: Prompts for a student ID and updates the student's details.
- Print Details of a Student: Prompts for a student ID and displays the student's details.
- Print All Students: Displays the details of all students in the list.
- Exit: Saves the list to a file and exits the program.

**Data Structures**
- Student: A structure representing a student, containing an ID and a name.
- Node: A structure representing a node in the doubly linked list, containing a student data and pointers to the next and previous nodes.
- List: A structure representing the linked list, containing pointers to the head and tail nodes.

## Error Handling
The program uses a Result enumeration to handle various types of errors, such as memory allocation errors and file read/write errors. The isError function checks and displays appropriate error messages.

## File Format
Student data is stored in a binary file specified as a command-line argument. Each student's data is written in binary format, allowing for efficient storage and retrieval.