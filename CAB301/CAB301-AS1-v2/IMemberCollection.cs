//CAB301 assessment 1 
//The specifications of MemberCollection ADT
using System;
using System.Collections.Generic;
using System.Text;

//Invariants: Capacity >= Count; Count >=0; and members in this member collection are sorted in alphabetical ascending order by their full name (if there are two members who have the same last name, they are sorted by their first name in ascending order).


public interface IMemberCollection
{
    // get the capacity of this member collection 
    // pre-condition: nil
    // post-condition: return the capacity of this member collection and this member collection remains unchanged
    public int Capacity // get the capacity of this member collection 
    {
        get;
    }

    // get the number of members in this member collection 
    // pre-condition: nil
    // post-condition: return the number of members in this member collection and this member collection remains unchanged
    public int Number // get the number of members in this collection
    {
        get;
    }

    // Check if this member collection is full
    // Pre-condition: nil
    // Post-condition: return true if this member collection is full; otherwise return false. This member collection remains unchanged.
    public bool IsFull();


    // check if this member collection is empty
    // Pre-condition: nil
    // Post-condition: return true if this member collection is empty; otherwise return false. This member collection remains unchanged.
    public bool IsEmpty();


    // Add a new member to this member collection
    // Pre-condition: this member collection is not full
    // Post-condition: The given member is added to this member collection and the members remains sorted in alphabetical order by their full names, if the given member does not appear in this member collection; otherwise, the given member is not added to this member collection. 
    // No duplicate has been added into this the member collection
    public void Add(IMember member);


    // Remove a given member out of this member collection
    // Pre-condition: nil
    // Post-condition: the given member is removed from this member collection, if the given member is in this member collection and the members in this member collection remains sorted in alphabetical order by their full names; otherwise, no member is removed from this member collection and this member collection remains unchanged. 
    public void Delete(string lastname, string firstname);

    // Search a given member by last name and first name in this member collection 
    // Pre-condition: nil
    // Post-condition: return true if the given member is in this member collection; return false otherwise. This member collection remains unchanged.
    public bool Search(string lastname,  string firstname);

    // Remove all the members in this member collection
    // Pre-condition: nil
    // Post-condition: Capacity remins unchanged; Number = 0; this member collection is empty.
    public void Clear();


    // Return a string containing the information about all the members in this member collection.
    // The information includes last name, first name and contact number in this order
    // Pre-condition: nil
    // Post-condition: a string containing the information about all the members in this member collection is returned, the order of the members in the returned string is the same with that in this member collection and this collection remains unchanged. 
    //                  The information about a member includes the last name, first name and contact phone number of the member, which are separated by a comma (no whitespace before or after the comma). The members are separated by a semicolon (no white space before or after the semicolon).
    public string ToString();

}


