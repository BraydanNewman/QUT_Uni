//CAB301 Assignment 2 
//ToolCollection ADT specification


using System;

// Invariants: no duplicate tools in this tool collection (all the tools in this tool collection have different names) and the number of tools in this tool collection is greater than equals to 0

interface IToolCollection
{
    // get the number of tools in this tool collection
    int Number
    {
        get;
    }

    // Check if this tool collection is empty
    // Pre-condition: nil
    // Post-condition: return true if this tool collection is empty; otherwise, return false. This tool collection remains unchanged and new Number = old Number
    bool IsEmpty();


    // Insert a new tool into this tool collection
    // Pre-condition: the new tool is not in this tool collection
    // Post-condition: the new tool is added into this tool collection, new Number = old Number + 1 and return true; otherwise, the new tool is not added into this tool collection, new Number = old Number and return false.
    bool Insert(ITool tool);



    // Delete a tool from this tool collection
    // Pre-condition: nil
    // Post-condition: the tool is removed out of this tool collection, new Number = old Number - 1 and return true, if the tool is present in this tool collection; 
    // otherwise, this tool collection remains unchanged, and new Number = old Number, and return false, if the tool is not present in this tool collection.
    bool Delete(ITool tool);



    // Search for a tool by its name in this tool collection  
    // pre: nil
    // post: return the reference of the tool object if the tool is in this tool collection;
    //	     otherwise, return null. New Number = old Number.
    ITool? Search(string toolName);




    // Return an array that contains all the tools in this tool collection and the tools in the array are sorted in the dictionary order by their names
    // Pre-condition: nil
    // Post-condition: return an array that contains all the tools in this tool collection and the tools in the array are sorted in alphabetical order by their names and new Number = old Number.
    ITool[] ToArray();

    // Clear this tool collection
    // Pre-condition: nil
    // Post-condition: all the tools in this tool collection are removed from this tool collection and Number = 0. 
    void Clear();

}



