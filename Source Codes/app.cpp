#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;
List studentList;
List type1list, type2list;
char authors[50][10][20];


bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();
bool EmptyList(List);
bool EmptyFile(ifstream&);


int main() {
	bool loop = true;
	List* list, * type1, * type2; //Create pointers that will be passed into function.
	type1 = &type1list;
	type2 = &type2list;
	list = &studentList;
	LibStudent result;
	char studentID[10];
	char* id;
	int choice;

	//Loop the main menu forever
	do {
		choice = menu();

		switch (choice) {
		case 1: {
			// Read student information from file into the linked list
			cout << "Enter the filename to read student information from: ";
			string filename;
			cin >> filename;
			ReadFile(filename, &studentList);
			break;
		}
		case 2: {
			// Delete a student record based on their ID
			cout << "Enter the ID of the student to delete: ";
			//cin.ignore(); // Clear the newline character from previous input
			//cin.getline(studentID, sizeof(studentID));
			cin.get(studentID, 10);
			cout << "Deleting student with ID: " << studentID << endl; // Add this line
			if (DeleteRecord(&studentList, studentID)) {
				cout << "Record deleted successfully.\n";
			}
			else {
				cout << "Record not found or deletion failed.\n";
			}

			break;
		}
		case 3: {
			// Search for a student based on their ID and print their information
			char studentId[10];
			cout << "Enter the ID of the student to search: ";
			cin >> studentID;
			// Call SearchStudent function here
			SearchStudent(&studentList, studentID, result);
			break;

		}
		case 4: {
			//Check if the list is empty, if not, proceed
			if (!EmptyList(studentList)) {

				//if InsertBook return false, print error statement.
				if (!InsertBook("book.txt", list))
					cout << "Error! The operation is not successful!!\n\n" << endl;


			}
			break;
		}
		case 5: {
			int source, detail;

			//Check if the list is empty, if not, proceed
			if (!EmptyList(studentList)) {

				//Ask user how to display the file
				cout << "Where do you want to display the output? (1 for file, 2 for screen): ";
				cin >> source;
				cout << endl;

				cout << "Do you want to display every booklist for every student? (1 for YES, 2 for NO): ";
				cin >> detail;
				system("cls");

				//if Display return false, print error statement
				if (!(Display(list, source, detail)))
					cout << "Error! The operation is not successful!!\n\n" << endl;
			}
			break;

		}
		case 6: {
			//Check if the list is empty, if not, proceed
			if (!EmptyList(studentList)) {

				//if false is returned, print error statement.
				if (!computeAndDisplayStatistics(list)) {
					cout << "Error! The program run unsuccessfully!!\n\n" << endl;
				}
				break;
			}
		}

		case 7: {
			//Check if the list is empty, if not, proceed
			if (!EmptyList(studentList)) {
				char* PtrCallNum;
				char callNum[20];

				//Ask user to input call number
				cout << "\nPlease enter call number of the book:";
				cin >> callNum;
				PtrCallNum = callNum;

				//If function returns false, print error statement.
				if (!printStuWithSameBook(list, PtrCallNum))
					cout << "Incorrect call number! Please check again!!\n\n";

				cout << endl;
				break;
			}
		}
		case 8: {
			//Check if the list is empty, if not, proceed
			if (!EmptyList(studentList)) {

				//if function return false, print error statement
				if (!displayWarnedStudent(list, type1, type2)) {
					cout << "Error! This program run unsuccessfully!!!" << endl;
				}

				else {

					//if type1 list is not empty
					//if type1 is empty
					if (type1->empty()) {
						cout << "\nType1 List is empty." << endl;
						cout << "Do not have students who has more that 2 books that are overdue more than 10 days. " << endl;
					}
					else {
						cout << "\nType1 List:";
						for (int i = 1; i <= type1->count; i++) {
							type1->get(i, result);
							result.print(cout);
							for (int j = 0; j < result.totalbook; j++) {
								result.book[j].print(cout);
							}

						}
					}
				}
				if (type2->empty()) {
					cout << "\nType2 List is empty." << endl;
					cout << "Do not have students who have fine RM 50.00 and every book in booklist are overdue.\n" << endl;
				}
				else {
					cout << "\nType2 List:";
					for (int i = 1; i <= type2->count; i++) {
						type2->get(i, result);
						result.print(cout);
						cout << "Book(s) :";
						for (int j = 0; j < result.totalbook; j++) {
							result.book[j].print(cout);
						}
					}
				}
				break;
			}


		}
		case 9:
			cout << "Exiting the program...\n";
			break;

		default:
			cout << "Invalid choice! Please try again.\n";
			break;
		}
	} while (choice != 9);
	cout << "\n\n";
	system("pause");
	return 0;
}


bool ReadFile(string filename, List* list) {

	LibStudent Stu, repetitiveStu;
	string toSkip;
	char tempName[30], tempID[10], tempCourse[3], tempPhoneNo[10];
	bool dupli;

	//to read the student.txt file
	ifstream inFile;
	inFile.open(filename);

	// to check if the file exist or able to open or not
	if (!inFile.is_open())
	{
		cout << "Unable to get the information of student.\n";
		return false;
	}
	else
	{
		while (!inFile.eof())
		{
			dupli = false;

			inFile >> toSkip >> toSkip >> toSkip;
			inFile >> Stu.id;
			inFile >> toSkip >> toSkip;
			inFile.ignore();
			inFile.getline(Stu.name, 30);
			inFile >> toSkip >> toSkip;
			inFile >> Stu.course;
			inFile >> toSkip >> toSkip >> toSkip;
			inFile >> Stu.phone_no;

			for (int i = 1; i <= list->size(); i++)
			{
				list->get(i, repetitiveStu); //check if there is a duplicated student exist in the list
				if (strcmp(repetitiveStu.id, Stu.id) == 0)
				{
					dupli = true;
					break;
				}
			}

			//if (checkRepetitive(repetitiveStu, Stu, list))
			if (dupli) {
				cout << "Duplicate student found. ID: " << Stu.id << endl; // Debug print
			}
			else {
				list->insert(Stu);
				cout << "Student ID: " << Stu.id << endl; // Debug print
			}


		}

	}

	inFile.close();
	cout << list->size() << " records have been successfully read\n\n\n";
	return true;
}

bool DeleteRecord(List* list, char* id) {

	LibStudent StuToDelete;

	if (list->empty()) //check if there is any record in the list
	{
		cout << "No student is in the list. The list is empty.\n\n\n";
		return false;
	}
	else
	{
		for (int i = 1; i <= list->size(); i++)
		{
			list->get(i, StuToDelete);
			if (strcmp(StuToDelete.id, id) == 0) //search for the same id inserted as in the list
			{
				cout << "The student " << StuToDelete.name << " with id " << StuToDelete.id << " has been deleted.\n\n\n";
				list->remove(i); //delete record
				return true;
			}
		}

		cout << "The student inserted is not found.\n\n\n"; //if the inserted id is not found
		return false;
	}
}

bool SearchStudent(List* list, char* id, LibStudent& stu) {

	LibStudent StuToFind;

	if (list->empty()) //check if there is any record in the list
	{
		cout << "No student is in the list. The list is empty.\n\n\n";
		return false;
	}
	else
	{
		for (int i = 1; i <= list->size(); i++)
		{
			list->get(i, StuToFind);
			if (strcmp(StuToFind.id, id) == 0) //search for the same id inserted as in the list
			{
				StuToFind.print(cout); //print out the student information
				return true;
			}
		}

		cout << "The student inserted is not found.\n\n\n"; //if the inserted id is not found
		return false;

	}
}


bool InsertBook(string filename, List* list) {

	LibBook book;
	char studentID[10];
	string line;
	int num = 0, NumOfAuthor;
	int NumOfChar[10] = { 0 }, j, k;
	int PosChar[10] = { 0 };
	string author[10];
	char C_author[5][20];
	LibStudent student;
	Node* ptr;

	//Open the file
	ifstream infile;
	infile.open(filename);

	//If the file cannot be opened, print the error.
	if (infile.fail()) {
		cout << "The file" << filename << "cannot be opened." << endl;
		return false;
	}


	//If the list is not found, print the error.
	if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}


	else {
		while (!infile.eof()) {
			book.fine = 0;
			infile >> studentID;

			infile >> line;

			//To check how many authors, the first alphabet and how many characters for each author.
			NumOfAuthor = 1;
			j = 0; //index for NumOfChar
			PosChar[0] = 0; //the first pos character is always 0.
			k = 1; //index for PosChar
			int SumOfChar = 0;
			char slash[5]; //to store the position of '/' in a line.
			int count = 0;

			for (int i = 0; i < line.length(); i++) {
				//Check if there is any '/' in line
				if (line[i] == '/') {
					slash[count] = i;
					count++;

					//If the first '/' is found
					if (j == 0) {
						PosChar[k] = i + 1;
						k++;
						NumOfAuthor++;
						NumOfChar[j] = i;
						SumOfChar += NumOfChar[j];
						j++;
					}

					//If the '/' found is not the first one.
					else {
						PosChar[k] = i + 1;
						k++;
						NumOfChar[j] = i - NumOfChar[j - 1] - 1;
						j++;
						NumOfAuthor++;
					}
				}

				//If [i] is the last character of the line
				else if (i == (line.length() - 1)) {
					NumOfChar[j] = i - slash[num - 1];
				}
			}

			for (int i = 0; i < NumOfAuthor; i++) {
				// To substring the author name,
				author[i] = line.substr(PosChar[i], NumOfChar[i]);

				//Store author name in C_string
				for (int j = 0; j < author[i].length() + 1; j++) {
					C_author[i][j] = author[i][j];
				}
				strcpy_s(authors[num][i], C_author[i]);
			}


			//Insert the rest into LibBook object.
			infile >> book.title;

			infile >> book.publisher;

			infile >> book.ISBN;

			infile >> book.yearPublished;

			infile >> book.callNum;

			infile >> book.borrow.day;
			infile.ignore();
			infile >> book.borrow.month;
			infile.ignore();
			infile >> book.borrow.year;
			infile.ignore();

			infile >> book.due.day;
			infile.ignore();
			infile >> book.due.month;
			infile.ignore();
			infile >> book.due.year;
			infile.ignore();

			//Calculate fine
			int dueDay = (book.due.day + ((book.due.month - 1) * 30));
			int currentDay = 29 + (2 * 30);
			int Fineday = 0;

			//Check if the book is overdue
			if (dueDay < currentDay) {
				book.fine = (currentDay - dueDay) * 0.50;
			}


			//Check student ID
			for (int i = 1; i <= list->count; i++) {
				studentList.get(i, student);

				//if the matching student ID is found, insert the LibBook object into that particular student
				if (strcmp(student.id, studentID) == 0) {
					ptr = studentList.find(i);

					for (int j = 0; j < NumOfAuthor; j++) {
						ptr->item.book[ptr->item.totalbook].author[j] = authors[num][j];
					}

					strcpy_s(ptr->item.book[ptr->item.totalbook].title, book.title);
					strcpy_s(ptr->item.book[ptr->item.totalbook].publisher, book.publisher);
					strcpy_s(ptr->item.book[ptr->item.totalbook].ISBN, book.ISBN);
					ptr->item.book[ptr->item.totalbook].yearPublished = book.yearPublished;
					strcpy_s(ptr->item.book[ptr->item.totalbook].callNum, book.callNum);
					strcpy_s(ptr->item.book[ptr->item.totalbook].title, book.title);
					ptr->item.book[ptr->item.totalbook].borrow.day = book.borrow.day;
					ptr->item.book[ptr->item.totalbook].borrow.month = book.borrow.month;
					ptr->item.book[ptr->item.totalbook].borrow.year = book.borrow.year;
					ptr->item.book[ptr->item.totalbook].due.day = book.due.day;
					ptr->item.book[ptr->item.totalbook].due.month = book.due.month;
					ptr->item.book[ptr->item.totalbook].due.year = book.due.year;
					ptr->item.book[ptr->item.totalbook].fine = book.fine;

					ptr->item.totalbook += 1;

					//To calculate how many books have been inserted.
					num++;
				}
			}

		}


		//To update the total fine for each student
		for (int i = 1; i <= list->count; i++) {
			ptr = studentList.find(i);
			ptr->item.calculateTotalFine();
		}


		cout << num << " books have been inserted successfully to student list.\n\n" << endl;
		return true;
	}
}

bool Display(List* list, int source, int detail) {

	//If the list is not found, print error.
	if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}

	if (source == 1) {//print to file
		ofstream outfile;

		if (detail == 1) {
			outfile.open("student_booklist.txt");
			for (int i = 1; i <= list->count; i++) {// Print student info and book info in the file
				LibStudent result;
				list->get(i, result);
				outfile << "STUDENT " << i;
				result.print(outfile);//print student details
				outfile << "\n";
				if (result.totalbook != 0)
					outfile << "BOOK LIST:\n";

				for (int j = 0; j < result.totalbook; j++) {//print all the books
					outfile << "\nBOOK " << j + 1 << endl;
					result.book[j].print(outfile);
				}
				outfile << "\n*****************************************************************************\n" << endl;

			}
			cout << "Successfully display output to student_booklist.txt. Please check for it!!\n\n" << endl;
			system("pause");
		}

		else if (detail == 2) {
			outfile.open("student_info.txt");
			for (int i = 1; i <= list->count; i++) {// print student info into the file
				LibStudent result;
				list->get(i, result);
				outfile << "STUDENT " << i;
				result.print(outfile);
				outfile << "\n*****************************************************************************\n" << endl;
			}
			cout << "Successfully display output to student_info.txt. Please check for it!!\n\n" << endl;
			system("pause");
		}
		outfile.close();
	}

	else if (source == 2) {//cout to screen
		if (detail == 1) {
			for (int i = 1; i <= list->count; i++) {// Print student info and book info on the screen
				LibStudent result;
				list->get(i, result);
				cout << "STUDENT " << i;
				result.print(cout);//print student info
				if (result.totalbook != 0)
					cout << "BOOK LIST:\n";
				for (int j = 0; j < result.totalbook; j++) {//print all the books
					cout << "\nBOOK " << j + 1 << endl;
					result.book[j].print(cout);
				}
				cout << "\n*****************************************************************************\n" << endl;
			}
		}
		else if (detail == 2) {
			for (int i = 1; i <= list->count; i++) {// Print student info on the screen
				LibStudent result;
				list->get(i, result);
				cout << "STUDENT " << i;
				result.print(cout);
				cout << "\n*****************************************************************************\n" << endl;
			}
		}
		system("pause");
		return true;
	}
}

bool computeAndDisplayStatistics(List* list) {
	LibStudent result;

	int CS_count = 0, CS_Books = 0, CS_overdue = 0, CS_fine = 0;
	int IA_count = 0, IA_Books = 0, IA_overdue = 0, IA_fine = 0;
	int IB_count = 0, IB_Books = 0, IB_overdue = 0, IB_fine = 0;
	int CN_count = 0, CN_Books = 0, CN_overdue = 0, CN_fine = 0;
	int CT_count = 0, CT_Books = 0, CT_overdue = 0, CT_fine = 0;
	int dueDay, currentDay;


	Node* cur;

	//If the list is not found, print error.
	if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}

	//Trverse each node
	for (int i = 1; i <= list->count; i++) {
		list->get(i, result);

		//Check what is the course for each student

		if (strcmp(result.course, "CS") == 0) {
			CS_count++;
			CS_Books += result.totalbook;
			CS_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				dueDay = result.book[j].due.day + (result.book[j].due.month * 30);
				currentDay = 29 + (2 * 30); //
				if (dueDay < currentDay) {
					CS_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "IA") == 0) {
			IA_count++;
			IA_Books += result.totalbook;
			IA_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				dueDay = result.book[j].due.day + (result.book[j].due.month * 30);
				currentDay = 29 + (2 * 30);
				if (dueDay < currentDay) {
					IA_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "IB") == 0) {
			IB_count++;
			IB_Books += result.totalbook;
			IB_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				dueDay = result.book[j].due.day + (result.book[j].due.month * 30);
				currentDay = 29 + (2 * 30);
				if (dueDay < currentDay) {
					IB_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "CN") == 0) {
			CN_count++;
			CN_Books += result.totalbook;
			CN_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				dueDay = result.book[j].due.day + (result.book[j].due.month * 30);
				currentDay = 29 + (2 * 30);
				if (dueDay < currentDay) {
					CN_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "CT") == 0) {
			CT_count++;
			CT_Books += result.totalbook;
			CT_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				dueDay = result.book[j].due.day + (result.book[j].due.month * 30);
				currentDay = 29 + (2 * 30);
				if (dueDay < currentDay) {
					CT_overdue++;
				}
			}
		}
	}

	//Display all output.
	cout << "Course\t Number of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine (RM)\t" << endl;
	cout << "*****************************************************************************************************************" << endl;
	cout << "*  CS\t" << setw(10) << CS_count << "\t\t\t" << CS_Books << "\t\t\t" << CS_overdue << "\t\t\t" << CS_fine << "\t\t\t" << "*" << endl;
	cout << "*  IA\t" << setw(10) << IA_count << "\t\t\t" << IA_Books << "\t\t\t" << IA_overdue << "\t\t\t" << IA_fine << "\t\t\t" << "*" << endl;
	cout << "*  IB\t" << setw(10) << IB_count << "\t\t\t" << IB_Books << "\t\t\t" << IB_overdue << "\t\t\t" << IB_fine << "\t\t\t" << "*" << endl;
	cout << "*  CN\t" << setw(10) << CN_count << "\t\t\t" << CN_Books << "\t\t\t" << CN_overdue << "\t\t\t" << CN_fine << "\t\t\t" << "*" << endl;
	cout << "*  CT\t" << setw(10) << CT_count << "\t\t\t" << CT_Books << "\t\t\t" << CT_overdue << "\t\t\t" << CT_fine << "\t\t\t" << "*" << endl;
	cout << "*****************************************************************************************************************" << endl;
	cout << "\n\n" << endl;
	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {
	LibBook book;
	LibStudent student;
	int studarray[20], bookarray[20];
	int numOfStudent = 0;

	//If the list is not found, print error.
	if (!list) {
		cout << "The list is not found!" << endl;
		return false;
	}

	strcpy_s(book.callNum, callNum);//copy call Number to a struct callNum
	for (int i = 1; i <= list->count; i++) {//retrieve student details
		list->get(i, student);
		for (int j = 0; j < student.totalbook; j++) {//compare with all the book using callNumber
			if (student.book[j].compareCallNum(book)) {// if match the call Number of book
				studarray[numOfStudent] = i; //stored into student array
				bookarray[numOfStudent] = j;//stored into book array
				numOfStudent++;

			}
		}
	}
	if (numOfStudent == 0)//check if there is no student borrow book, if num=0, return false
		return false;
	if (numOfStudent > 0) {
		cout << "\nThere are " << numOfStudent << " students that borrow the book with call number " << callNum << " as shown below:\n";
		for (int a = 0; a < numOfStudent; a++) {// print out the result
			list->get(studarray[a], student);
			cout << "\nStudent Id = " << student.id << endl;
			cout << "Name = " << student.name << endl;
			cout << "Course = " << student.course << endl;
			cout << "Phone Number = " << student.phone_no << endl;
			cout << "Borrow Date: ";
			student.book[bookarray[a]].borrow.print(cout);
			cout << "\nDue Date: ";
			student.book[bookarray[a]].due.print(cout);
			cout << endl;


		}
		return true;
	}
	else
		return false;

}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	LibStudent student;
	int dueDay, currentDay;
	int case_count1, case_count2;

	//If the list is not found, the program will return false
	if (!list)
		return false;

	for (int i = 1; i < list->count; i++) {// retrieve list of student 
		case_count1 = 0;
		case_count2 = 0;
		list->get(i, student);

		for (int j = 0; j < student.totalbook; j++) { //check for each book

			dueDay = (student.book[j].due.day + ((student.book[j].due.month - 1) * 30));
			currentDay = 29 + (2 * 30);  //29/3/2023

			//overdue
			if (dueDay < currentDay) {//check for due books
				case_count2++;
				if (dueDay + 10 <= currentDay)//overdue more then 10 days
					case_count1++;
			}

		}


		if (case_count1 > 2) //final check for eligibilty of type1-> overdue more than 10 days
			type1->insert(student);

		if (student.total_fine > 50 and case_count2 == student.totalbook)//final check for eligibilty of type2-> fine rm 50 && overdue
			type2->insert(student);
	}
	return true;
}

bool EmptyList(List list) {
	//Check if the list is empty
	if (list.empty()) {
		cout << "Error! The list is empty." << endl;
		cout << "Cannot be empty! Please insert information into the list before proceed.\n\n" << endl;
		system("pause");
		return true;
	}

	else
		return false;
}

bool EmptyFile(ifstream& infile) {
	//Move the cursor at the end of file
	infile.seekg(0, infile.end);

	//Return true if the position < 1
	if (infile.tellg() < 1) { //if the positio cursor is less than 1, means it is an empty file
		return true;
	}

	//Clear and move the cursor back to the first position
	else {
		infile.clear(); //clear any error flags on the ifstream
		infile.seekg(0, infile.beg); //Move the cursor back to the beginning of the file
		return false;  // means file is not empty
	}
}

int menu() {

	int choice;
	cout << "Menu" << endl << endl;
	cout << "1. Read file" << endl;
	cout << "2. Delete record" << endl;
	cout << "3. Search student" << endl;
	cout << "4. Insert book" << endl;
	cout << "5. Display output" << endl;
	cout << "6. Compute and Display Statistics" << endl;
	cout << "7. Student with Same Book" << endl;
	cout << "8. Display Warned Student" << endl;
	cout << "9. Exit" << endl << endl;

	//Ask user to enter their choice
	cout << "Enter your choice: ";
	cin >> choice;
	cin.ignore();
	return choice;
}
