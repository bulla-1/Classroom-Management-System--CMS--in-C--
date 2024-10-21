#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2023) : day(d), month(m), year(y) {}

    bool operator==(const Date &other) const
    {
        return (day == other.day) && (month == other.month) && (year == other.year);
    }

    bool operator!=(const Date &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Date &other) const
    {
        if (year < other.year)
            return true;
        else if (year > other.year)
            return false;
        else
        {
            if (month < other.month)
                return true;
            else if (month > other.month)
                return false;
            else
            {
                return day < other.day;
            }
        }
    }

    bool operator>(const Date &other) const
    {
        return !(*this < other) && (*this != other);
    }

    bool operator<=(const Date &other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator>=(const Date &other) const
    {
        return (*this > other) || (*this == other);
    }

    string display() const
    {
        string strDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
        return strDate;
    }
};

struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    string toString()
    {
        string datetimeString = "";
        datetimeString += to_string(day) + "/";
        datetimeString += to_string(month) + "/";
        datetimeString += to_string(year) + " ";
        datetimeString += to_string(hour) + ":";
        datetimeString += to_string(minute) + ":";
        datetimeString += to_string(second) + " ";
        return datetimeString;
    }
};

DateTime getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&currentTime);

    DateTime datetime;
    datetime.year = localTime.tm_year + 1900;
    datetime.month = localTime.tm_mon + 1;
    datetime.day = localTime.tm_mday;
    datetime.hour = localTime.tm_hour;
    datetime.minute = localTime.tm_min;
    datetime.second = localTime.tm_sec;
    return datetime;
}

class User
{
public:
    string name;
    string roll;
    string email;
    string unique;
    string contact;
    string password;
    bool loggedIn;
    int encryptionKey = rand() % 50;

    User(string name = "", string roll = "", string email = "", string unique = "", string contact = "", string password = "")
        : name(name), roll(roll), email(email), unique(unique), contact(contact), password(password), loggedIn(false) {}

    string encrypt(string plaintext)
    {
        char *copiedtext = new char[plaintext.length() + 1];
        strcpy(copiedtext, plaintext.c_str());

        for (int i = 0; i < plaintext.length(); i++)
            copiedtext[i] += encryptionKey;

        string ciphertext(copiedtext);
        return ciphertext;
    }

    string decrypt(string ciphertext)
    {
        char *copiedtext = new char[ciphertext.length() + 1];
        strcpy(copiedtext, ciphertext.c_str());

        for (int i = 0; i < ciphertext.length(); i++)
            copiedtext[i] -= encryptionKey;

        string plaintext(copiedtext);
        return plaintext;
    }

    bool authenticateUser(string password)
    {
        return this->password == password;
    }

    void showDetails()
    {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << roll << endl;
        cout << "Email ID: " << email << endl;
        cout << "Unique ID: " << unique << endl;
        cout << "Contact Information: " << contact << endl;
        cout << "Encrypted Password: " << encrypt(password) << endl;
        cout << "Decrypted Password: " << decrypt(encrypt(password)) << endl;
        cout << endl;
    }
};

class Student : public User
{
public:
    string designation = "student";

    Student(string a = "", string b = "", string c = "", string d = "", string e = "", string f = "")
        : User(a, b, c, d, e, f) {}
};

class Teacher : public User
{
public:
    string designation = "teacher";

    Teacher(string a = "", string b = "", string c = "", string d = "", string e = "", string f = "")
        : User(a, b, c, d, e, f) {}
};

class Assignment
{
public:
    string title;
    string description;
    Date submissionDate;
    float weight;
    int marksTotal;

    Assignment(const string &assignmentTitle = "", const string &assignmentDescription = "", const Date &dueDate = Date(), const float weight = 0.0, const int marksTotal = 0)
        : title(assignmentTitle), description(assignmentDescription), submissionDate(dueDate), weight(weight), marksTotal(marksTotal) {}

    string display() const
    {
        string output;
        output += title + " ";
        output += to_string(weight) + " ";
        output += to_string(marksTotal) + " ";
        return output;
    }
};

class Submission
{
public:
    Student *student;
    Assignment *assignment;
    string timestamp;
    vector<string> files;
    bool evalStatus;
    string feedback;
    int marksAwarded;

    Submission(Student *student = nullptr, Assignment *assignment = nullptr)
        : student(student), assignment(assignment), timestamp(""), evalStatus(false), feedback(""), marksAwarded(-1) {}

    void addFile(string file)
    {
        files.push_back(file);
    }

    void evaluateSubmission(string comments, int marks)
    {
        evalStatus = true;
        feedback = comments;
        marksAwarded = marks;
    }

    string display()
    {
        string output = assignment->title + " by " + student->name + " ( ";
        for (string &file : files)
            output += file + " ";
        output += ") @ " + timestamp;
        output += (evalStatus ? "checked" : "unchecked");
        return output;
    }
};

class Classroom
{
public:
    string name;
    string subject;
    string description;
    Teacher *classTeacher;
    vector<Student *> studentRoster;
    vector<Assignment *> assignmentRoster;
    vector<Submission *> submissionRoster;

    Classroom(string name = "", string subject = "", string description = "", Teacher *classTeacher = nullptr)
        : name(name), subject(subject), description(description), classTeacher(classTeacher) {}

    void addStudent(Student *student)
    {
        studentRoster.push_back(student);
    }

    void delStudent(Student *student)
    {
        int index = -1;
        for (int i = 0; i < studentRoster.size(); i++)
            if (studentRoster[i] == student)
                index = i;

        if (index == -1)
            cout << "Student Not Found.\n";
        else
            studentRoster.erase(studentRoster.begin() + index);
    }

    void addAssignment(Assignment *assignment)
    {
        assignmentRoster.push_back(assignment);
    }

    void delAssignment(Assignment *assignment)
    {
        int index = -1;
        for (int i = 0; i < assignmentRoster.size(); i++)
            if (assignmentRoster[i] == assignment)
                index = i;

        if (index == -1)
            cout << "Assignment Not Found.\n";
        else
            assignmentRoster.erase(assignmentRoster.begin() + index);
    }

    void addSubmission(Submission *submission)
    {
        DateTime curTime = getCurrentDateTime();
        submission->timestamp = curTime.toString();
        submissionRoster.push_back(submission);
    }

    Student *selectStudent()
    {
        Student *current = nullptr;
        cout << "The following students are in this class:\n";
        for (int i = 0; i < studentRoster.size(); i++)
            cout << i << " -> " << studentRoster[i]->name << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the student you want to select: ";
            cin >> choice;
            if (choice >= studentRoster.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return studentRoster[choice];
        }
    }

    Assignment *selectAssignment()
    {
        Assignment *current = nullptr;
        cout << "The following assignments are assigned to this class:\n";
        for (int i = 0; i < assignmentRoster.size(); i++)
            cout << i << " -> " << assignmentRoster[i]->title << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the assignment you want to select: ";
            cin >> choice;
            if (choice >= assignmentRoster.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return assignmentRoster[choice];
        }
    }

    Submission *selectSubmission()
    {
        Submission *current = nullptr;
        cout << "The following submissions have been submitted to this class:\n";
        for (int i = 0; i < submissionRoster.size(); i++)
            cout << i << " -> " << submissionRoster[i]->display() << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the submission you want to select: ";
            cin >> choice;
            if (choice >= submissionRoster.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return submissionRoster[choice];
        }
    }

    void showDetails()
    {
        cout << "Class Name: " << name << endl;
        cout << "Subject: " << subject << endl;
        cout << "Description: " << description << endl;
        cout << "Class Teacher: " << classTeacher->name << endl;

        cout << "Student Roster:" << endl;
        for (int i = 0; i < studentRoster.size(); i++)
            cout << '\t' << studentRoster[i]->name << endl;

        cout << "Assignment Roster:" << endl;
        for (int i = 0; i < assignmentRoster.size(); i++)
            cout << '\t' << assignmentRoster[i]->display() << endl;

        cout << "Submission Roster:" << endl;
        for (int i = 0; i < submissionRoster.size(); i++)
            cout << '\t' << submissionRoster[i]->display() << endl;

        cout << endl;
    }
};

class GradeBook
{
public:
    Classroom *classroom;

    GradeBook(Classroom *classroom) : classroom(classroom) {}

    void percentageOfStudent(Student *student)
    {
        float scored = 0, total = 0;
        for (Submission *submit : classroom->submissionRoster)
        {
            if (submit->student == student)
            {
                scored += (submit->assignment->weight * submit->marksAwarded) / submit->assignment->marksTotal;
                total += submit->assignment->weight;
            }
        }

        cout << student->name << ": ";

        if (!total)
            cout << "No graded submissions for any assignment" << endl;
        else
            cout << "Scored " << (scored * 100) / total << "% across all graded assignments" << endl;
    }

    void averageOfAssignment(Assignment *assignment)
    {
        float scored = 0, total = 0;
        for (Submission *submit : classroom->submissionRoster)
        {
            if (submit->assignment == assignment)
            {
                scored += submit->marksAwarded;
                total++;
            }
        }

        cout << assignment->title << ": ";

        if (!total)
            cout << "No graded submissions for any student" << endl;
        else
            cout << "Average " << scored / total << " out of " << assignment->marksTotal << endl;
    }

    void AllStudentPercentage()
    {
        Student *prev = nullptr;
        for (int i = 0; i < classroom->studentRoster.size(); i++)
        {
            if (classroom->studentRoster[i] != prev)
            {
                prev = classroom->studentRoster[i];
                percentageOfStudent(prev);
            }
        }
        cout << endl;
    }

    void AllAssignmentAverage()
    {
        Assignment *prev = nullptr;
        for (int i = 0; i < classroom->assignmentRoster.size(); i++)
        {
            if (classroom->assignmentRoster[i] != prev)
            {
                prev = classroom->assignmentRoster[i];
                averageOfAssignment(prev);
            }
        }
        cout << endl;
    }
};

class Manager
{
public:
    vector<Classroom *> myclasses;
    vector<Student *> mystudents;
    vector<Teacher *> myteachers;
    Classroom *currentClass;

    void execute()
    {
        mainMenu();
    }

    void mainMenu()
    {
        cout << "You have " << myclasses.size() << " classes currently.\n";
        cout << "There are " << mystudents.size() << " students enrolled.\n";
        cout << "There are " << myteachers.size() << " teachers registered.\n\n";

        cout << "Would you like to:\n";
        cout << "0. Exit Program\n";
        cout << "1. Create a Class\n";
        cout << "2. Register a Student\n";
        cout << "3. Register a Teacher\n";
        cout << "4. Select Class\n";
        cout << "5. Show Students\n";
        cout << "6. Show Teachers\n";

        int choice;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 0:
            cout << "Goodbye\n";
            break;

        case 1:
            if (myteachers.size() == 0)
            {
                cout << "Register a teacher first before you try to make a class\n\n";
                mainMenu();
            }
            else
                createClass();
            break;

        case 2:
            registerStudent();
            break;

        case 3:
            registerTeacher();
            break;

        case 4:
            if (myclasses.size() == 0)
            {
                cout << "Currently no Classes to choose from\n\n";
                mainMenu();
            }
            else
            {
                currentClass = selectClass();
                classMenu();
            }
            break;

        case 5:
            if (mystudents.size() == 0)
            {
                cout << "Currently no Students to show\n\n";
                mainMenu();
            }
            else
                showStudents();
            break;

        case 6:
            if (myteachers.size() == 0)
            {
                cout << "Currently no Teachers to show\n\n";
                mainMenu();
            }
            else
                showTeachers();
            break;

        default:
            cout << "Invalid Choice\n\n";
            mainMenu();
            break;
        }
    }

    void createClass()
    {
        string a, b, c;
        cout << "Enter the Name of the Class: ";
        cin >> a;
        cout << "Enter the Subject of the Class: ";
        cin >> b;
        cout << "Enter the Description of the Class: ";
        cin >> c;

        Teacher *classTeacher = selectTeacher();
        Classroom *newClass = new Classroom(a, b, c, classTeacher);
        myclasses.push_back(newClass);
        mainMenu();
    }

    void registerStudent()
    {
        string a, b, c, d, e, f;
        cout << "Enter the Name of the Student: ";
        cin >> a;
        cout << "Enter the Roll Number of the Student: ";
        cin >> b;
        cout << "Enter the Email ID of the Student: ";
        cin >> c;
        cout << "Enter the Unique ID of the Student: ";
        cin >> d;
        cout << "Enter the Contact Number of the Student: ";
        cin >> e;
        cout << "Enter the Password of the Student: ";
        cin >> f;

        Student *newStudent = new Student(a, b, c, d, e, f);
        mystudents.push_back(newStudent);
        mainMenu();
    }

    void registerTeacher()
    {
        string a, b, c, d, e, f;
        cout << "Enter the Name of the Teacher: ";
        cin >> a;
        cout << "Enter the Roll Number of the Teacher: ";
        cin >> b;
        cout << "Enter the Email ID of the Teacher: ";
        cin >> c;
        cout << "Enter the Unique ID of the Teacher: ";
        cin >> d;
        cout << "Enter the Contact Number of the Teacher: ";
        cin >> e;
        cout << "Enter the Password of the Teacher: ";
        cin >> f;

        Teacher *newTeacher = new Teacher(a, b, c, d, e, f);
        myteachers.push_back(newTeacher);
        mainMenu();
    }

    void createAssignment()
    {
        string a, b;
        int d, m, y;
        float weight;
        int marksTotal;

        cout << "Enter the Assignment Title: ";
        cin >> a;

        cout << "Enter the Assignment Description: ";
        cin >> b;

        cout << "Enter the Due Date in the following format (DD MM YY): ";
        cin >> d >> m >> y;

        cout << "Enter the Weightage for the Assignment (floating point number between 0 and 1): ";
        cin >> weight;

        cout << "Enter the Total Marks for the Assignment: ";
        cin >> marksTotal;

        Assignment *newAssignment = new Assignment(a, b, Date(d, m, y), weight, marksTotal);
        currentClass->addAssignment(newAssignment);

        classMenu();
    }

    void createSubmission()
    {
        cout << "Which Student is making the submission?\n";
        Student *curStudent = currentClass->selectStudent();

        cout << "Which Assignment are they submitting?\n";
        Assignment *curAssignment = currentClass->selectAssignment();

        Submission *newSubmission = new Submission(curStudent, curAssignment);

        cout << "Do you want to attach a file to your submission? (y / n) ";
        char choice;
        cin >> choice;

        while (choice == 'y')
        {
            string filename;
            cout << "Enter the name of the file: ";
            cin >> filename;

            newSubmission->addFile(filename);

            cout << "Do you want to attach another file to your submission? (y / n) ";
            cin >> choice;
        }

        currentClass->addSubmission(newSubmission);
        cout << "Your submission has been created and submitted\n";

        classMenu();
    }

    void gradeSubmission()
    {
        cout << "Which Submission would you like to grade?";
        Submission *curSubmission = currentClass->selectSubmission();

        string comments;
        int marksAwarded;
        int marksTotal = curSubmission->assignment->marksTotal;

        cout << "What are your comments on this submission: ";
        cin >> comments;
        cout << "How many marks will you award out of " << marksTotal << ": ";
        cin >> marksAwarded;
        curSubmission->evaluateSubmission(comments, marksAwarded);

        classMenu();
    }

    void classMenu()
    {
        currentClass->showDetails();
        cout << "0. Go Back to Main Menu\n";
        cout << "1. Add Student to Class\n";
        cout << "2. Add Assignment to Class\n";
        cout << "3. Add Submission to Assignment\n";
        cout << "4. Grade an Assignment\n";
        cout << "5. View GradeBook\n";

        int choice;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 0:
            mainMenu();
            break;

        case 1:
            if (mystudents.size() == 0)
                cout << "First register some students\n";
            else
            {
                cout << "Which student would you like to add?\n";
                Student *studentToAdd = selectStudent();
                currentClass->addStudent(studentToAdd);
            }
            classMenu();
            break;

        case 2:
            createAssignment();
            break;

        case 3:
            if (currentClass->studentRoster.size() == 0)
            {
                cout << "First assign some students to this class\n";
                classMenu();
            }
            else if (currentClass->assignmentRoster.size() == 0)
            {
                cout << "First assign some work to this class\n";
                classMenu();
            }
            else
                createSubmission();
            break;

        case 4:
            if (currentClass->submissionRoster.size() == 0)
            {
                cout << "There are no submissions for you to grade\n";
                classMenu();
            }
            gradeSubmission();
            break;

        case 5:
            showGradeBook();
            break;

        default:
            cout << "Invalid Choice\n\n";
            classMenu();
            break;
        }
    }

    void showGradeBook()
    {
        GradeBook *mygradebook = new GradeBook(currentClass);
        Student *curStudent;
        Assignment *curAssignment;

        cout << "0. Return to Class Menu\n";
        cout << "1. Calculate a student's percentage\n";
        cout << "2. Calculate all students percentage\n";
        cout << "3. Calculate an assignment's average\n";
        cout << "4. Calculate all assignments average\n";

        int choice;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 0:
            classMenu();
            break;

        case 1:
            cout << "Choose the student who's percentage you would like to see.";
            curStudent = currentClass->selectStudent();
            mygradebook->percentageOfStudent(curStudent);
            showGradeBook();
            break;

        case 2:
            mygradebook->AllStudentPercentage();
            showGradeBook();
            break;

        case 3:
            cout << "Choose the assignment which's average you would like to see.";
            curAssignment = currentClass->selectAssignment();
            mygradebook->averageOfAssignment(curAssignment);
            showGradeBook();
            break;

        case 4:
            mygradebook->AllAssignmentAverage();
            showGradeBook();
            break;

        default:
            cout << "Invalid Choice\n\n";
            showGradeBook();
            break;
        }
    }

    Student *selectStudent()
    {
        Student *current = nullptr;
        cout << "The following students are registered:\n";
        for (int i = 0; i < mystudents.size(); i++)
            cout << i << " -> " << mystudents[i]->name << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the student you want to select: ";
            cin >> choice;
            if (choice >= mystudents.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return mystudents[choice];
        }
    }

    Teacher *selectTeacher()
    {
        Teacher *current = nullptr;
        cout << "The following teachers are registered:\n";
        for (int i = 0; i < myteachers.size(); i++)
            cout << i << " -> " << myteachers[i]->name << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the teacher you want to select: ";
            cin >> choice;
            if (choice >= myteachers.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return myteachers[choice];
        }
    }

    Classroom *selectClass()
    {
        Classroom *current = nullptr;
        cout << "The following classes are registered:\n";
        for (int i = 0; i < myclasses.size(); i++)
            cout << i << " -> " << myclasses[i]->name << endl;

        int choice;
        while (current == nullptr)
        {
            cout << "Please choose the number next to the class you want to select: ";
            cin >> choice;
            if (choice >= myclasses.size() || choice < 0)
                cout << "Invalid Choice\n\n";
            else
                return myclasses[choice];
        }
    }

    void showStudents()
    {
        cout << "Registered Students: ";
        for (int i = 0; i < mystudents.size(); i++)
            mystudents[i]->showDetails();
        cout << endl;
        mainMenu();
    }

    void showTeachers()
    {
        cout << "Registered Teachers: ";
        for (int i = 0; i < myteachers.size(); i++)
            myteachers[i]->showDetails();
        cout << endl;
        mainMenu();
    }
};
