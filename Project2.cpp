/*
CS 300
Project Two
Clayton Smith
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Defining structure for "Course"
struct Course
{
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

//Splits the string to a list of strings 
vector<string> tokenize(string s, string del = " ") {
    vector<string> stringArray;
    int start = 0;
    int end = s.find(del);

    //While not at end of file
    while (end != -1) {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    stringArray.push_back(s.substr(start, end - start));
    return stringArray;
}

//Loads file and stores file details into a list
vector<Course> LoadDataStructure() {

    //Using ifstream to open the file
    ifstream fin("abcu.txt", ios::in);
    vector<Course> courses;
    string line;

    //Loop
    while (1) {
        getline(fin, line);

        //If end of file reached, break loop
        if (line == "-1")
            break;

        Course course;

        //Separating info with commas from toenizedInformation
        vector<string> tokenizedInformation = tokenize(line, ",");

        //Storing information
        course.courseNumber = tokenizedInformation[0];
        course.name = tokenizedInformation[1];

        //If prerequisites found, store those too
        for (int i = 2; i < tokenizedInformation.size(); i++) {
            course.prerequisites.push_back(tokenizedInformation[i]);
        }

        //Append course into list of courses
        courses.push_back(course);
    }

    //Closes the file
    fin.close();

    //Return the list of courses
    return courses;
}

//Prints the course info in requested format
void printCourse(Course course) {
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;
    cout << "Course Number: " << courseNumber << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";

    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " ";
    }
    cout << "\n\n";
}

//Print method for printing course info for all courses in requested format
void printCourseList(vector<Course> courses) {
    int n = courses.size();

    /* Bubble sort used
    *  I used a refrence for this as someone recommended using it on stackoverflow
    *  Source:
    *  https://www.geeksforgeeks.org/bubble-sort/
    */
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j + 1], courses[j]);
            }
        }
    }

    //Traversing the list of courses to print
    for (int i = 0; i < n; i++) {
        printCourse(courses[i]);
    }
}

//Search method used for searching requested course from user input
void searchCourse(vector<Course> courses) {
    int n = courses.size();
    string courseNumber;
    int f = 0;
    cout << "Enter Course Number: ";
    cin >> courseNumber;

    /*
    * Forces user input to upper case
    * I refrenced this page for help:
    * https://stackoverflow.com/questions/23418390/how-to-convert-a-c-string-to-uppercase
    */
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    for (int i = 0; i < n; i++) {

        //If user requested course is found, print it
        if (courses[i].courseNumber == courseNumber) {
            f = 1;
            printCourse(courses[i]);
            break;
        }
    }

    //If course not found, print this error message
    if (f == 0) {
        cout << "Course with given course number not found\n";
    }
}

int main(int argc, char** argv) {
    vector<Course> courses;

    //Menu
    cout << "1.Load Data Structure\n";
    cout << "2.Print Course List\n";
    cout << "3.Print Course\n";
    cout << "9.Exit\n";

    //User input
    int uinput;

    //Menu loop (breaks when user enters '9')
    do {
        //Prompt for user input
        cout << "\nEnter your choice: ";
        cin >> uinput;
        switch (uinput) {

        case 1:
            courses = LoadDataStructure();
            cout << "File loaded Successfully\n";
            break;

        case 2:
            printCourseList(courses);
            break;

        case 3:
            searchCourse(courses);
            break;

        case 9:
            cout << "Exit\n";
            break;

        default:
            cout << "Invalid Choice\n";
            break;
        }

    } 
    while (uinput != 9);

    return 0;
}