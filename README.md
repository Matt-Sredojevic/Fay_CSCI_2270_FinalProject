# Fay_CSCI_2270_FinalProject
Final Project for CSCI 2270

========================Project Description==========================

For my final project, I wanted to make something that I could actually use. After some consideration, I decided to make a program that would help keep track of students' progress on the computer science minor here at CU Boulder. The program uses a mix between a graph and a hash table to store data that it reads from a handful of text files I created. The actual nodes that store the data are kept in a vector, while different lists and structures of classes are all pointers back to contents of that initial vector. The program allows the user to input the classes they have completed, display completed classes, display all classes recognized by the program, display all computer science electives, check remaining requirements to complete the minor, and list the requisites for any recognized class.

=======================How to Run====================================

To get the program, download and extract all files from MinorAudit.zip to the desired location on your computer. The program can be run through any IDE, or it can be run in a terminal by running the MinorAuditMk2 executable file. When it starts, the user will be prompetd with a title and menu like this:


===================================================

      COMPUTER SCIENCE MINOR PROGRESS CHECKER

                      made for

           University of Colorado, Boulder

___________________________________________________



            A final project for CSCI 2270

                    By Justin Fay

===================================================



============MENU============

1: List all classes

2: List completed classes

3: List electives

4: Show requisites

5: Add a completed class

6: Remaining requirements

7: End audit

============================

At this point all the user has to do is make a decision from the menu by typing the number of their desired function and pressing enter. For the first three choices, the program will list the requested classes without need for any additional input.
If the user chooses options 4 or 5, they will be prompted with:


Enter class prefix and number (Ex: "CSCI 2270"):

Here they will have to enter the desired class in the format above. If the class is not entered in this format, it will display:


please enter a valid class

If the program does not recognize the class, it will display:


Class not recognized

If the user chooses option 6, the program will display requirements still need to be completed for the computer science minor.

============================Dependencies=============================

The program relies on a handful of text files to import the data as well as the c++ header "AuditGraph.h". All of these are in the folder with the executable, and should be recognized by program automatically.

=======================System Requirements==========================|

The only system requirements are that the system have basic libraries for c++, nothing special. It will run on all common operating systems.

===========================Group Members============================|

Justin Fay

========================Open Issues/Bugs============================|

If more classes are added to the program, the vector that stores the actual nodes may resize which will change the addresses of the data stored there. This will cause a segmentation fault if the user tries to access the data. Currently if this happens, the program will write the new number of classes to a text file and read from it to reserve space for that vector the next time it runs. If you encounter this problem, restarting the program should fix th problem.