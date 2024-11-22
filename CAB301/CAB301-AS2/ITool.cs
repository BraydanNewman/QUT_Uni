//CAB301 - Assignment 2
//Tool ADT specification

using System;
using System.Text;

//Invariants: Name=!null and Number >=1

public interface ITool
{
    
    // get the name of this tool

    string Name // get the name of this tool
    {
        get;
    }

    //get the number of this tool currently available in the tool library
    int Number 
    {
        get;
    }

    //check if a person is in the borrower list of this tool (is holding this tool)
    //Pre-condition: nil
    //Post-condition: return true if the person is in the borrower list; return false otherwise. The information about this tool remains unchanged.
    bool IsInBorrowerList(string personName);


    //add a person to the borrower list
    //Pre-condition: the borrower is not in the borrower list and Number > 0
    //Post-condition: the borrower is added to the borrower list and New Number = Old Number - 1
    bool AddBorrower(string personName);


    //remove a borrower from the borrower list
    //Pre-condition: the borrower is in the borrower list
    //Post-condition: the borrower is removed from the borrower list and and new Number = old Number + 1
    bool RemoveBorrower(string personName);


    //Compare this tool's name to another tool's name 
    //Pre-condition: anotherTool =! null
    //Post-condition:  return -1, if this tool's name is less than another tool's name by alphabetical order
    //                 return 0, if this tool's name equals to another tool's name by alphabetical order
    //                 return +1, if this tool's name is greater than another tool's name by alphabetical order
    int CompareTo(ITool? anotherTool);


    //Return a string containing the name and the number of this tool currently in the tool library 
    //Pre-condition: nil
    //Post-condition: A string containing the name and number of this tool is returned

    string ToString();

    void ChangeNumber();

}


