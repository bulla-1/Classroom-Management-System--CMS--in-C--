# Classroom Management System (CMS)

The Classroom Management System (CMS) is a project designed to simulate the management of a classroom environment. It allows teachers to manage students, assignments, and submissions, while providing a structured interface for organizing and tracking class activities.

## Features

- **Student Management**: Add, remove, and view details of students in a class.
- **Assignment Management**: Create, delete, and manage assignments for students.
- **Submission Tracking**: Handle student submissions, evaluate them, and provide feedback.
- **Teacher and Classroom Management**: Manage classroom details, including assigning teachers to classes.

## Classes and Key Functionalities

1. **Submission Class**
   - Handles student submissions, including file attachments, feedback, and marks.
   - Methods:
     - `addFile()`: Adds a file to the submission.
     - `evaluateSubmission()`: Evaluates a submission by assigning feedback and marks.
     - `display()`: Displays the submission details along with its evaluation status.

2. **Classroom Class**
   - Manages the classroom details, including students, assignments, and submissions.
   - Methods:
     - `addStudent()`, `delStudent()`: Add or remove a student from the classroom.
     - `addAssignment()`, `delAssignment()`: Add or remove assignments from the classroom.
     - `showStudents()`, `showTeachers()`: Display the registered students and teachers.

## Requirements

- C++ compiler

## How to Run

1. Clone this repository:
    ```bash
    git clone https://github.com/yourusername/Classroom-Management-System.git
    ```
2. Navigate to the project directory:
    ```bash
    cd Classroom-Management-System
    ```
3. Compile the project:
    ```bash
    g++ main.cpp -o classroom_management_system
    ```
4. Run the executable:
    ```bash
    ./classroom_management_system
    ```

## Future Enhancements

- Add GUI support for better user interaction.
- Implement user authentication for students and teachers.
- Add a grading analytics feature for performance tracking.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
