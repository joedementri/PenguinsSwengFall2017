#include <iostream>
#include <fstream>
#include <string>
#include "AdaWeaknesses.h"

using namespace std;

AdaWeaknesses::AdaWeaknesses() {

}

void AdaWeaknesses::checkForWeakness1(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine1";
  
}

void AdaWeaknesses::checkForWeakness2(std::ofstream& mystream, string fileContents) {
  mystream << "\nProcedure Tracking:\n";

  //Keywords
  string procedureKW = "procedure";

  //initial position
  int procedurePos = fileContents.find(procedureKW);

  //In case of none:
  if (procedurePos == -1) {
    mystream << "\n\tNo procedures found.";
  }

  //Loop
  while (procedurePos != -1)
  {
    //Get all text after "procedure", then find the name of the procedure
    string textAfterProcedureKW = fileContents.substr(procedurePos+10);
    string procedureName = textAfterProcedureKW.substr(0, textAfterProcedureKW.find(" "));

    //Write Name of Procedure to Stream
    mystream << "\n\n\tProcedure: " << procedureName;

    int sameProcedureNextPosition = textAfterProcedureKW.substr(10+procedureName.length()).find(procedureName);

    if (sameProcedureNextPosition != -1) {
      mystream << "\n\t\tProcedure has use.";
    } else {
      mystream << "\n\t\tProcedure DOES NOT have use";
    }

    procedurePos = fileContents.find(procedureKW, procedurePos+1);
      
  }  
  mystream << "\n";
}

void AdaWeaknesses::checkForWeakness3(std::ofstream& mystream, string fileContents) {
  mystream << "\nDivision by Zero:\n";

  //Keywords
  string division = "/";
  string zero = "0";

  //initial position
  int divisionPos = fileContents.find(division);

  //In case of none:
  if (divisionPos == -1) {
    mystream << "\n\tNo division found";
  }

  while (divisionPos != -1) {

    int lineNum = 0;
    //Get Line Num
    int newLinePos = fileContents.find("\n");
    while (newLinePos < divisionPos) {
      lineNum++;
      newLinePos = fileContents.find("\n", newLinePos+1);
    }  

    mystream << "\n\tDivision occurs at Line " << lineNum;
    divisionPos = fileContents.find(division, divisionPos+1);
  }
  mystream << "\n";
}

void AdaWeaknesses::checkForWeakness4(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine4";
}

void AdaWeaknesses::checkForWeakness5(std::ofstream& mystream, string fileContents) {
  mystream << "\nNumeric Overflow\n";

  //Keywords
  string first = "'First";
  string last = "'Last";

  //initial position
  int foundPos = fileContents.find(first);

  //In case of none
  if (foundPos == -1) {
    mystream << "\n\tNo instances of 'First found";
  }

  while (foundPos != -1) {
    string assignmentOperator = ":=";
    string declarationOperator = ":";
    string newLineOperator = "\n";

    //Get Line Num
    int lineNum = 0;
    int newLinePos = fileContents.find("\n");
    while (newLinePos < foundPos) {
      lineNum++;
      newLinePos = fileContents.find("\n", newLinePos+1);
    }
    
    //find last assn op before passing
    int assnOpPos = fileContents.find(assignmentOperator);
    int lastAssnOpPos = assnOpPos;
    while (assnOpPos != -1 && assnOpPos < foundPos) {
      lastAssnOpPos = assnOpPos;
      assnOpPos = fileContents.find(assignmentOperator, assnOpPos+1);
    }

    //find last decl op before passing
    int declOpPos = fileContents.find(declarationOperator);
    int lastDeclOpPos = declOpPos;
    while (declOpPos != -1 && declOpPos < foundPos) {
      lastDeclOpPos = declOpPos;
      declOpPos = fileContents.find(declarationOperator, declOpPos+1);
    }

    //find last newline before passing
    int newlinePos = fileContents.find(newLineOperator);
    int lastNewlinePos = newlinePos;
    while (newlinePos != -1 && newlinePos < foundPos) {
      lastNewlinePos = newlinePos;
      newlinePos = fileContents.find(newLineOperator, newlinePos+1);
    }

    int lengthOfVarName  = lastDeclOpPos - lastNewlinePos;
    string varName = fileContents.substr(lastNewlinePos, lengthOfVarName);

    mystream << "\n\tVariable(s) assigned with 'First: " << varName;

    foundPos = fileContents.find(first, foundPos+1);
  }

  //---------------------------------------------------------------
  // EYE BREAk
  //---------------------------------------------------------------

  //initial position
  foundPos = fileContents.find(last);

  //If not found
  if (foundPos == -1) {
    mystream << "\n\tNo instances of 'Last found";
  }
  
  while (foundPos != -1) {
    string assignmentOperator = ":=";
    string declarationOperator = ":";
    string newLineOperator = "\n";

    //Get Line Num
    int lineNum = 0;
    int newLinePos = fileContents.find("\n");
    while (newLinePos < foundPos) {
      lineNum++;
      newLinePos = fileContents.find("\n", newLinePos+1);
    }
    
    //find last assn op before passing
    int assnOpPos = fileContents.find(assignmentOperator);
    int lastAssnOpPos = assnOpPos;
    while (assnOpPos != -1 && assnOpPos < foundPos) {
      lastAssnOpPos = assnOpPos;
      assnOpPos = fileContents.find(assignmentOperator, assnOpPos+1);
    }

    //find last decl op before passing
    int declOpPos = fileContents.find(declarationOperator);
    int lastDeclOpPos = declOpPos;
    while (declOpPos != -1 && declOpPos < foundPos) {
      lastDeclOpPos = declOpPos;
      declOpPos = fileContents.find(declarationOperator, declOpPos+1);
    }

    //find last newline before passing
    int newlinePos = fileContents.find(newLineOperator);
    int lastNewlinePos = newlinePos;
    while (newlinePos != -1 && newlinePos < foundPos) {
      lastNewlinePos = newlinePos;
      newlinePos = fileContents.find(newLineOperator, newlinePos+1);
    }

    int lengthOfVarName  = lastDeclOpPos - lastNewlinePos;
    string varName = fileContents.substr(lastNewlinePos, lengthOfVarName);

    mystream << "\n\tVariable(s) assigned with 'Last: " << varName;

    foundPos = fileContents.find(last, foundPos+1);
  }
  
  mystream << "\n";
}

void AdaWeaknesses::checkForWeakness6(std::ofstream& mystream, string fileContents) {
  mystream << "\nRange Constraints:\n";

  //Keywords
  string range = "..";

  //Initial Position
  int rangePos = fileContents.find(range);

  //if not found
  if (rangePos == -1) {
    mystream << "\n\tNo Range Constraints found.";
  }

  while (rangePos != -1) {
    
    //Get Line Num of RangePos
    int lineNum = 0;
    int newLinePos = fileContents.find("\n");
    while (newLinePos < rangePos) {
      lineNum++;
      newLinePos = fileContents.find("\n", newLinePos+1);
    }

    //if array kw found
    string arrayKW = "array";
    int arrayPos = fileContents.find(arrayKW);
    int lastArrayPos = arrayPos;
    while (arrayPos != -1 && arrayPos < rangePos) {
      lastArrayPos = arrayPos;
      arrayPos = fileContents.find(arrayKW, arrayPos+1);
    }

    //Get Line Num of Array KW
    int arrayLineNum = 0;
    int secondNewLinePos = fileContents.find("\n");
    while (secondNewLinePos < lastArrayPos) {
      arrayLineNum++;
      secondNewLinePos = fileContents.find("\n", secondNewLinePos+1);
    }

    //If array KW is on same line as ..
    if (lineNum == arrayLineNum) {

      
      //Get Left Parenthesis Pos
      string leftPar = "(";
      int leftParPos = fileContents.find(leftPar);
      int lastLeftParPos = leftParPos;
      while (leftParPos != -1 && leftParPos  < rangePos) {
	lastLeftParPos = leftParPos;
	leftParPos = fileContents.find(leftPar, leftParPos+1);
      }

      //Get Right Parenthesis
      string rightPar = ")";
      int rightParPos = fileContents.find(rightPar);
      while (rightParPos != -1 && rightParPos  < rangePos) {
	rightParPos = fileContents.find(rightPar, rightParPos+1);
      }

      string constraint = fileContents.substr(lastLeftParPos, (rightParPos-lastLeftParPos));
      mystream << "\n\tArray on Line " << lineNum << " has range constraints: " << constraint;

      
    } //end if

    rangePos = fileContents.find(range, rangePos+1);
  } //end while

  mystream << "\n";
}

void AdaWeaknesses::checkForWeakness7(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine7";
}

void AdaWeaknesses::checkForWeakness8(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine8";
}

void AdaWeaknesses::checkForWeakness9(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine9";
}

void AdaWeaknesses::checkForWeakness10(std::ofstream& mystream, string fileContents) {
  mystream << "\nTestLine10";
}
