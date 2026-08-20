#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure used to store one course and its prerequisites.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node used by the Binary Search Tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(const Course& aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree used to store, search, and print courses.
class BinarySearchTree {
private:
    Node* root;

    // Recursive helper function used to insert a course.
    void addNode(Node* node, const Course& course) {
        if (course.courseNumber < node->course.courseNumber) {

            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else if (course.courseNumber > node->course.courseNumber) {

            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
        else {
            // Replace the existing course if the same course number
            // is loaded more than once.
            node->course = course;
        }
    }

    // Performs an in-order traversal to print courses
    // alphabetically from lowest to highest.
    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        printInOrder(node->left);

        cout << node->course.courseNumber << ", "
             << node->course.courseTitle << endl;

        printInOrder(node->right);
    }

    // Deletes all nodes in the tree.
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

public:

    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }

    // Destructor
    ~BinarySearchTree() {
        clear();
    }

    // Inserts a course into the BST.
    void insert(const Course& course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    // Searches for a course by course number.
    Course* search(const string& courseNumber) {
        Node* current = root;

        while (current != nullptr) {

            if (courseNumber == current->course.courseNumber) {
                return &(current->course);
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }

    // Prints all courses in alphanumeric order.
    void printCourseList() const {
        printInOrder(root);
    }

    // Clears the BST.
    void clear() {
        deleteTree(root);
        root = nullptr;
    }
};

// Removes extra spaces from the beginning and end of a string.
string trim(const string& text) {

    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");

    return text.substr(start, end - start + 1);
}

// Converts course numbers to uppercase.
// Example: csci400 becomes CSCI400.
string toUpperCase(string text) {

    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char character) {
            return static_cast<char>(toupper(character));
        }
    );

    return text;
}

// Reads the CSV course file and loads each course into the BST.
bool loadCourses(const string& fileName, BinarySearchTree& courseTree) {

    ifstream inputFile(fileName);

    // Make sure the file can be opened.
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file "
             << fileName << "." << endl;

        return false;
    }

    // Clear previously loaded data before loading again.
    courseTree.clear();

    string line;
    int courseCount = 0;

    // Read the file one line at a time.
    while (getline(inputFile, line)) {

        if (trim(line).empty()) {
            continue;
        }

        stringstream lineStream(line);

        vector<string> fields;
        string field;

        // Separate each CSV field using commas.
        while (getline(lineStream, field, ',')) {
            fields.push_back(trim(field));
        }

        // Every valid course must contain at least
        // a course number and course title.
        if (fields.size() < 2 ||
            fields[0].empty() ||
            fields[1].empty()) {

            cout << "Warning: Skipping invalid course record: "
                 << line << endl;

            continue;
        }

        Course course;

        course.courseNumber = toUpperCase(fields[0]);
        course.courseTitle = fields[1];

        // Any fields after index 1 are prerequisites.
        for (size_t i = 2; i < fields.size(); ++i) {

            if (!fields[i].empty()) {
                course.prerequisites.push_back(
                    toUpperCase(fields[i])
                );
            }
        }

        // Insert the course into the BST.
        courseTree.insert(course);

        ++courseCount;
    }

    inputFile.close();

    // Make sure the file contained valid course records.
    if (courseCount == 0) {
        cout << "Error: No valid course records were found "
             << "in the file." << endl;

        return false;
    }

    cout << "Course data loaded successfully." << endl;

    return true;
}

// Displays the required Project Two menu.
void displayMenu() {

    cout << endl;

    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;

    cout << "What would you like to do? ";
}

int main() {

    BinarySearchTree courseTree;

    bool dataLoaded = false;

    int menuChoice = 0;

    cout << "Welcome to the course planner." << endl;

    // Continue displaying the menu until the user selects 9.
    while (menuChoice != 9) {

        displayMenu();

        // Validate menu input.
        if (!(cin >> menuChoice)) {

            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid input. "
                 << "Please enter 1, 2, 3, or 9."
                 << endl;

            continue;
        }

        cin.ignore(10000, '\n');

        switch (menuChoice) {

        // OPTION 1: LOAD COURSE DATA
        case 1:
        {
            string fileName;

            cout << "Enter the course data file name: ";

            getline(cin, fileName);

            dataLoaded =
                loadCourses(trim(fileName), courseTree);

            break;
        }

        // OPTION 2: PRINT COURSE LIST
        case 2:

            if (!dataLoaded) {

                cout << "Please load the course data first "
                     << "by selecting option 1."
                     << endl;
            }
            else {

                cout << "Here is a sample schedule:"
                     << endl;

                courseTree.printCourseList();
            }

            break;

        // OPTION 3: PRINT ONE COURSE
        case 3:

            if (!dataLoaded) {

                cout << "Please load the course data first "
                     << "by selecting option 1."
                     << endl;
            }
            else {

                string courseNumber;

                cout << "What course do you want to know about? ";

                getline(cin, courseNumber);

                courseNumber =
                    toUpperCase(trim(courseNumber));

                Course* course =
                    courseTree.search(courseNumber);

                if (course == nullptr) {

                    cout << "Course "
                         << courseNumber
                         << " was not found."
                         << endl;
                }
                else {

                    cout << course->courseNumber
                         << ", "
                         << course->courseTitle
                         << endl;

                    cout << "Prerequisites: ";

                    if (course->prerequisites.empty()) {

                        cout << "None";
                    }
                    else {

                        for (size_t i = 0;
                             i < course->prerequisites.size();
                             ++i) {

                            cout << course->prerequisites[i];

                            if (i <
                                course->prerequisites.size() - 1) {

                                cout << ", ";
                            }
                        }
                    }

                    cout << endl;
                }
            }

            break;

        // OPTION 9: EXIT
        case 9:

            cout << "Thank you for using the course planner!"
                 << endl;

            break;

        // INVALID MENU OPTION
        default:

            cout << menuChoice
                 << " is not a valid option."
                 << endl;

            break;
        }
    }

    return 0;
}
