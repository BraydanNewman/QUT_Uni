//CAB301 - Assignment 2 
//Tool ADT implementation


using System;
using System.Text;


//Invariants: Name=!null and Number >=1

partial class Tool : ITool
{
    private string name;
    private int number;
    private string[] borrowerList;


    //constructor 
    public Tool(string name, int number = 0)
    {
        if (name == null)
            throw new ArgumentNullException("Name is null");
        else
        { 
            this.name = name;
            this.number = number;
            borrowerList = new string[0];
        }
    }

    //get the name of this tool
    public string Name 
    {
        get { return name; }   // get method
    }

    //get the number of this tool currently available in the tool library
    public int Number 
    {
        get { return number; }   // get method
    }

    // Returns true/false if the name exists and the location as which it is or should be
    public Tuple<bool, int> BinarySearch(string name){
        int low = 0;
        int high = borrowerList.Length - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            int comp = String.Compare(name, borrowerList[mid]);
            if (comp == 0) return new Tuple<bool, int>(true, mid);
            else if (comp < 0) high = mid - 1;
            else if (comp > 0) low = mid + 1;
        }
        return new Tuple<bool, int>(false, low);

    }

    //check if a person is in the borrower list of this tool (is holding this tool)
    //Pre-condition: nil
    //Post-condition: return true if the person is in the borrower list; return false otherwise. The information about this tool remains unchanged.
    public bool IsInBorrowerList(string personName)
    {
        return Array.IndexOf(borrowerList, personName) != -1;
        // return BinarySearch(personName).Item1;
    }

    private void AddBorrowerAtIndex(string personName, int index)
    {   
        // Add extra space to array
        Array.Resize(ref borrowerList, borrowerList.Length + 1);
        // Move elements over
        for (int i = borrowerList.Length - 1; i-- > index;) borrowerList[i + 1] = borrowerList[i];
        borrowerList[index] = personName;
        number--;
    }

    private void RemoveBorrowerAtIndex(int index)
    {   
        // Move elements over
        for (int i = index; i < borrowerList.Length - 1; i++) borrowerList[i] = borrowerList[i + 1];
        // Remove extra space to array
        Array.Resize(ref borrowerList, borrowerList.Length - 1);
        number++;
    }


    //add a person to the borrower list
    //Pre-condition: the borrower is not in the borrower list and Number > 0
    //Post-condition: the borrower is added to the borrower list and new Number = old Number - 1
    public bool AddBorrower(string personName)
    {
        if (Number <= 0 || IsInBorrowerList(personName)) return false;
        if (number == 0)
        {
            AddBorrowerAtIndex(personName, 0);
            return true;
        }
        (bool exist, int index) = BinarySearch(personName);
        if (exist) return false;
        AddBorrowerAtIndex(personName, index);
        return true;
    }


    //remove a borrower from the borrower list
    //Pre-condition: the borrower is in the borrower list
    //Post-condition: the borrower is removed from the borrower list and new Number = old Number + 1
    public bool RemoveBorrower(string personName)
    {   
        if (borrowerList.Length == 0) return false;
        int index = Array.IndexOf(borrowerList, personName);
        if (index == -1) return false;
        RemoveBorrowerAtIndex(index);
        return true;
    }


    //Compare this tool's name to another tool's name 
    //Pre-condition: anotherTool =! null
    //Post-condition:  return -1, if this tool's name is less than another tool's name by alphabetical order
    //                 return 0, if this tool's name equals to another tool's name by alphabetical order
    //                 return +1, if this tool's name is greater than another tool's name by alphabetical order
    public int CompareTo(ITool? anotherTool)
    {
        if (anotherTool == null) return int.MaxValue; // TODO FIX THIS, IDK WHAT TO DO HERE
        return String.Compare(name, anotherTool.Name);
    }


    //Return a string containing the name and the number of this tool currently in the tool library 
    //Pre-condition: nil
    //Post-condition: A string containing the name and number of this tool is returned
    public override string ToString()
    {
        return name + number;
    }

    public void ChangeNumber() {
        number = 10;
    }
}
