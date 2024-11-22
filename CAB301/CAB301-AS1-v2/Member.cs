//CAB301 assessment 1 
//The implementation of Member ADT
using System;


//invariants: Pin is a number which has a minimal of 4 and a maximal of 6 digits and ContactNumber has 10 digits and its first digit is 0; neith LastName nor FirstName is blank.

class Member : IMember
{
    // Fields
    private string firstName;
    private string lastName;
    private string contactNumber;
    private string pin;


    // Properties
    public string FirstName { get { return firstName; } set { firstName = value; } }  // Get and set the first name of this member
    public string LastName { get { return lastName; } set { lastName = value; } }  // Get and set the last name of this member
    public string ContactNumber { get { return contactNumber; } set { contactNumber = value; } }  // Get and set the contact number of this member
    public string Pin { get { return pin; } set { pin = value; } }// Get and set a pin number



    // Constructor with member's first name and lastname
    public Member(string firstName, string lastName)
    {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    // Constructor with member's full details
    public Member(string firstName, string lastName, string contactNumber, string pin)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.contactNumber = contactNumber;
        this.pin = pin;
    }



    // Define how to comapre two member objects
    // This member's full name is compared to another member's full name 
    // Pre-condition: nil
    // Post-condition: return -1 if this member's full name is before another memebr's full name in alphabetical order
    //                 return 0, if this member's full name is the same with another memeber's full name in alphabetical order
    //                 return +1, of this member's full name is after another member's full name in alphabetical order
    public int CompareTo(IMember member)
    {
        return String.Compare(this.firstName + this.lastName, member.FirstName + member.LastName);
    }



    // Return a string containing the first name, last name and contact number of this memeber
    // Pre-condition: nil
    // Post-condition: a  string containing the first name, last name, and contact number of this member is returned
    public string ToString()
    {
        return lastName + "," + firstName + "," + contactNumber;
    }
}


