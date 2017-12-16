#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

void runTester();
void selectFiles();
void viewFiles();
void changeSettings();
void displayHelp();

std::string fileContents [10];

bool filters [10];
std::string nameOfFilters[10] = {"Uninitialized Variables", "Unused Procedures", "Division by 0", "Dead Code", "Numeric Overflow", "Range Constraint Violation", "Expression Always True", "Expression Always False", "Redundant Conditionals", "Infinite Loops"};

int numItemsInArray = 0;
std::string filePath = "/home";  //default to home root because linux and don't care

int main ()
{

  //Initialize filters array
  for (int i = 0; i < sizeof(filters); i++) {
    filters[i] = true; //Initialize to true so everything will be checked
  }
  
  printf("Software Integrity Tester\n");

  int input = 0;

  do {

    printf("\n1) Run Tester");
    printf("\n2) Choose Files To Run Tester On");
    printf("\n3) View Selected Files");
    printf("\n4) Change Settings");
    printf("\n5) Help");
    printf("\n6) Exit");

    printf("\nType number of desired option: ");
    cin >> input;
    printf("\n");

    switch (input)
    {

      case 1:
	runTester();
	break;
      case 2:
	selectFiles();
	break;
      case 3:
	viewFiles();
	break;
      case 4:
	changeSettings();
	break;
      case 5:
	displayHelp();
	break;
      case 6:
        break;
      default:
	printf("Invalid Input\n");
	input = 5;
	displayHelp();
    }
    
  } while (input != 6);

  return 0;
}

void runTester() {
  printf("\nrunTesterMethod");

  //TODO: Everything

  printf("\n");
  
}

/*
 * SelectFiles Method:
 *
 * This method prompts the user to enter the full file path. It then tries to
 * put the file name in the array if there is space.
 */
void selectFiles() {
  
  printf("\n");

  string fileName = "";
  printf("\tEnter name of file to be scanned (full file path): ");
  cin >> fileName;

  if (numItemsInArray < sizeof(fileContents)/32) {  //Array size is in bytes lol, therefore 10 strings = 320 bytes.
    fileContents[numItemsInArray] = fileName;
    numItemsInArray++;
  } else {
    cout << "Error: Max Number of Files in Queue" << endl;
  }
  
  printf("\n");
}

/*
 * ViewFiles Method:
 *
 * This method display the files with numeric labels. It then prompts the user
 * if they wish to remove a file. If so, they input a number (based on the labels)
 * and it is removed, and then the user is asked again (by recursively calling the method.
 */
void viewFiles() {
  printf("\n");

  cout << "\tFile Queue:" << endl;

  for (int i = 0; i < numItemsInArray; i++) {
    cout << "\t" << (i+1) << ") " << fileContents[i] << endl;
  }

  //Option to remove files
  if (numItemsInArray > 0) {
    string yesOrNo = "N";
    printf("Would you like to remove a file from this list? (Y/N): ");
    cin >> yesOrNo;

    if ((yesOrNo.compare("Y") == 0 || yesOrNo.compare("y") == 0)) {

      int fileNum = 0;
      printf("Please enter number of file to remove (from list above): ");
      cin >> fileNum;
      fileNum--;

      if (fileNum >= 0 && fileNum < numItemsInArray) {

	fileContents[fileNum] = "";
	numItemsInArray--;
      
	while (fileNum < numItemsInArray) {
	  fileContents[fileNum] = fileContents[fileNum+1];
	  fileNum++;
	}
      
      } else {
	printf("Invalid number");
      }

      printf("\n");
      viewFiles();
    
    }
  }

}

/*
 * ChangeSettings Method:
 *
 * 
 */
void changeSettings() {

  //Submenu
  int subMenuInput = 0;

  do {

     printf("\nCurrent Filters:\n");

     for (int i = 0; i < sizeof(filters); i++) {
       if (filters[i] == 1) {
	 cout << (i+1) << ") " << nameOfFilters[i] << ": " << "ON" << endl;
       } else {
	 cout << (i+1) << ") " << nameOfFilters[i] << ": " << "OFF" << endl;
       }
     }

     cout << "\nCurrent output file destination: " << filePath << endl;
    
    printf("\n1) Change Filters");
    printf("\n2) Change Output File Destination");
    printf("\n3) Exit");

    printf("\nType number of desired option: ");
    cin >> subMenuInput;
    printf("\n");

    int filterNumToToggle = 0;
    string newOutputPath = "";

    switch (subMenuInput)
    {


      //Change Filters
      case 1:
        printf("Enter number of filter to toggle: ");
        cin >> filterNumToToggle;
	filterNumToToggle--;

	if (filterNumToToggle >= 0 && filterNumToToggle < sizeof(filters)) {
	  filters[filterNumToToggle] = !filters[filterNumToToggle];
	} else {
	  printf("\nInvalid number!");
	}
	printf("\n");
	break;
      case 2:

	printf("Enter new filepath for output file: ");
	cin >> newOutputPath;
	filePath = newOutputPath;
	
	
	break;
      case 3:;
	break;
      default:
	printf("\nInvalid Input\n");
	subMenuInput = 3;
    }
    
  } while (subMenuInput != 3);
  
  printf("\n");
}


/*
 * DisplayHelp Method:
 *
 * This method displays how each menu option works.
 */
void displayHelp() {
  printf("Help:");

  //Display a lot of strings

  printf("\n\tHow to use:");
  printf("\n\t\tMenu Option 1 will run the tester on all the files given by the user, using the filters the user selected, and creating an output file where in a user specified location");
  printf("\n\t\tMenu Option 2 will prompt the user to enter the full file path of a file which they want to be scanned. This is saved by the program and used to determine which files the tester will run on when the 1st menu option is selected.");
  printf("\n\t\tMenu Option 3 will display the files currently stored by the program, and then ask the user if they would like to remove a file from the saved list. If they say yes, then the user can input which file they would like to remove.");
  printf("\n\t\tMenu Option 4 will show the user which filters are currently going to be used when the tester runs, and wherer the current output file destination is. The user has the option of choosing filters and also changing the output location.");
  printf("\n\t\tMenu Option 5 brings up this help menu.");

  printf("\n\n\tVersion 0.5.2.2");
  printf("\n");
}
