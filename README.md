CS 300 Data Structures and Algorithms
Project Overview

The main problem I worked on in this course was creating a course-planning system for ABC University. The program needed to read course information from a file, store the information in an appropriate data structure, display all courses in alphanumeric order, and allow a user to search for a specific course and view its prerequisites. During Project One, I compared vectors, hash tables, and binary search trees to determine which data structure would be the best choice. In Project Two, I used that analysis to develop the working course planner in C++.

How I Approached the Problem

I approached the problem by separating it into smaller tasks, including reading and validating the course file, storing course information, displaying the courses, and searching for individual courses. I then considered how vectors, hash tables, and binary search trees would perform for these operations.

Understanding data structures is important because the way information is stored affects how efficiently a program can access and process it. A vector is simple to use but may require searching through multiple elements. A hash table provides fast searching but does not automatically maintain sorted data. A binary search tree allows efficient searching and can display the courses in order using an in-order traversal. Based on these characteristics, I selected a binary search tree for the final program.

Overcoming Roadblocks

One of the challenges I encountered was making sure the course information from the input file was loaded correctly into the program. The program had to separate the course number, course title, and prerequisites before storing each course in the binary search tree. I also had to work through compilation and configuration issues while developing and testing the program in Eclipse.

I overcame these problems by testing smaller sections of the program separately. I checked the file-loading process first and then tested insertion, traversal, searching, and user input. Breaking the problem into smaller parts made it easier to identify errors and correct them.

Designing Software Differently

This project expanded my approach to software design because I now consider the data structure and algorithm before beginning the implementation. Before this course, I was more focused on whether a program produced the expected output. I now understand that programs that produce the same result can perform very differently depending on the algorithms and data structures being used.

Comparing vectors, hash tables, and binary search trees helped me understand the importance of considering efficiency during the design process. I now think about how much data a program may need to process and which operations will be performed most often before selecting a solution.

Maintainable, Readable, and Adaptable Programs

My work in this course also improved the way I organize my programs. In Project Two, I separated different responsibilities into classes and functions instead of placing all of the program logic inside main(). This makes the program easier to understand, test, and modify.

I also learned the importance of descriptive names, consistent formatting, comments, and functions with specific responsibilities. These practices make programs more readable and make it easier to change individual parts of a program without rewriting everything. I will continue using these techniques to create programs that are easier to maintain and adapt in future projects.
