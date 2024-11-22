//CAB301 assessment 1
//The specification of Member ADT

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

//Invariants: Pin is a number which has a minimal of 4 and a maximal of 6 digits and ContactNumber has 10 digits and its first digit is 0; neither LastName nor FirstName is blank.

public interface IMember
    {

        // Get and set the first name of this member
        public string FirstName  
        {
            get;
            set;
        }
        // Get and set the last name of this member
        public string LastName 
        {
            get;
            set;
        }

        // Get and set the contact number of this member
        // A valid contact phone number has 10 digits and its first digit is 0
        public string ContactNumber 
            {
                get;
                set; //contact number must be valid 
            }

        // Get and set a pin for this member
        // A pin is valid if it is a number which has a minimal of 4 and a maximal of 6 digits
        public string Pin 
        {
            get;
            set; //pin must be valid 
        }

        // Define how to comapre two member objects
        // This member's full name is compared to another member's full name 
        // Pre-condition: nil
        // Post-condition: return -1 if this member's full name is before another memebr's full name in alphabetical order
        //                 return 0, if this member's full name is the same with another memeber's full name in alphabetical order
        //                 return +1, of this member's full name is after another member's full name in alphabetical order
        public int CompareTo(IMember member);


        // Check if a contact phone number is valid. A contact phone number is valid if it has 10 digits and the first digit is 0.
        // Pre-condition: nil
        // Post-condition: return true, if the phone number id valid; retuns false otherwise.
        public static bool IsValidContactNumber(string phonenumber)
        {
            return phonenumber[0] == '0' && int.TryParse(phonenumber, out _) && phonenumber.Length == 10;
        }

        // Check if a pin is valid. A pin is valid if it is a number which has a minimal of 4 and a maximal of 6 digits.
        // Pre-condition: nil
        // Post-condition: return true, if the pin valid; retuns false otherwise.
        public static bool IsValidPin(string pin)
        {
            return pin.Length >= 4 && pin.Length <= 6 && int.TryParse(pin, out _);
        }


        // Return a string containing the first name, last name and contact number of this memeber
        // Pre-condition: nil
        // Post-condition: a  string containing the first name, last name, and contact number of this member is returned
        public string ToString();  
}

