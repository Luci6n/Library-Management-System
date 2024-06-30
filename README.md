# Library-Management-System
## **Project Overview**
Library Management System is a C++ program designed to manage student information and their borrowed library books for the Faculty of Information and Communication Technology (FICT). This system uses linked lists to store and handle data efficiently, offering functionalities for both students and administrators. The project includes three main classes: LibStudent, LibBook, and Date to manage student records, library books, and date information respectively.

## **Features**
1. LibStudent Class:
- Attributes:

  - id: A 7-digit number where the first two digits represent the enrollment year (e.g., 1300345).
   - name: A string to store student names, up to 30 characters.
   - course: A 2-character code representing the student's course (e.g., CS for Computer Science).
   - phone_no: A 7-digit phone number in the format: 123-4567.
   - total_fine: The total overdue fine for a student.
   - totalbook: The number of books borrowed, ranging from 0 to 15.
   - book: An array storing borrowed book information.

- Member Functions:
    - LibStudent(): Initializes name, course, and phone_no to empty strings, sets id to 0, and total_fine to 0.
    - bool compareName1(LibStudent p2): Compares the names of two students using the >= operator.
    - bool compareName2(LibStudent p2): Compares the names of two students using the == operator.
    - void print(ostream &out): Prints LibStudent data to the specified output stream.
    - bool calculateTotalFine(): Calculates the total overdue fine for all books in the book array.

2. LibBook Class:
  - Attributes:
    - title: Title of the book, up to 250 characters.
    - author[]: An array of pointers to store up to 10 authors for a book.
    - publisher: Publisher of the book.
    - ISBN: A 10-digit ISBN number.
    - yearPublished: The year the book was published.
    - callNum: The call number for the book.
    - fine: The overdue fine for the book.
    - borrow: A Date object representing the borrow date.
    - due: A Date object representing the due date.

  - Member Functions:
    - LibBook(): Initializes yearPublished and fine to 0, and sets string attributes to empty strings. Initializes all elements in author to NULL.
    - bool compareTitle(LibBook b2): Compares the titles of two books using the >= operator.
    - bool compareCallNum(LibBook b2): Compares the call numbers of two books using the == operator.
    - void print(ostream &out): Prints LibBook data to the specified output stream.

3. Date Struct:
  - Attributes:
    - day: The day of the month (1-30).
    - month: The month of the year (1-12).
    - year: The year, represented by a 4-digit number.

  - Member Functions:
    - Date(): Initializes day, month, and year to 0.
    - void print(ostream &out): Prints the date in day/month/year format.

## **Main Functionalities**
1. Reading from File:
  - Function: bool ReadFile(string filename, List *list)
  - Description: Reads student information from a file and stores it in a linked list, ensuring no duplicate records.
  - Returns: true if successful, false otherwise.
2. Deleting Records:
  - Function: bool DeleteRecord(List *list, char *id)
  - Description: Deletes a student record from the linked list based on the student ID.
  - Returns: true if successful, false otherwise.
3. Searching for a Student:
  - Function: bool SearchStudent(List *list, char *id, LibStudent &stu)
  - Description: Searches for a student in the linked list based on ID and prints their information if found.
  - Returns: true if found, false otherwise.
4. Inserting Book Records:
  - Function: bool InsertBook(string filename, List *list)
  - Description: Inserts book information for a student by reading from a file, calculates fines, and updates the student’s record.
  - Returns: true if successful, false otherwise.
5. Displaying Records:
  - Function: bool Display(List *list, int source, int detail)
  - Description: Displays student and book information based on the specified source and detail level.
  - Returns: true if successful, false otherwise.
6. Computing and Displaying Statistics:
  - Function: bool computeAndDisplayStatistics(List *list)
  - Description: Computes and displays statistics on students, books borrowed, overdue books, and total fines by course.
  - Returns: true if successful, false otherwise.
7. Displaying Students with Same Book:
  - Function: bool printStuWithSameBook(List *list, char *callNum)
  - Description: Finds and displays students who borrowed the same book based on its call number.
  - Returns: true if successful, false otherwise.
8. Displaying Warned Students:
  - Function: bool displayWarnedStudent(List *list, List *type1, List *type2)
  - Description: Identifies and displays students to be warned based on overdue books and fines.
  - Returns: true if successful, false otherwise.
9. Menu:
  - Function: int menu()
  - Description: Displays a menu with options to perform various tasks, and allows the user to select a choice until exit.
  - Returns: The chosen menu option

## **Usage Instructions**
- Select a Menu Option: Choose a task from the menu to perform various operations like reading files, deleting records, searching students, and more.
- Manage Records: Follow the on-screen instructions to manage student and book records effectively.
- Compute Statistics: Use the option to compute and display detailed statistics about the library usage.
