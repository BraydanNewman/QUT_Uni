// CAB301 - Assignment 2
// ToolCollection ADT implementation


using System;
//A class that models a node of Binary Tree
public class BTreeNode
{
    public ITool tool; 
    public BTreeNode? lchild; // reference to its left child 
    public BTreeNode? rchild; // reference to its right child

    public BTreeNode(ITool tool)
    {
        this.tool = tool;
        this.lchild = null;
        this.rchild = null;
    }
}

// Invariants: no duplicate tools in this tool collection (all the tools in this tool collection have different names) and the number of tools in this tool collection is greater than equals to 0


partial class ToolCollection : IToolCollection
{
	private BTreeNode? root; // tools are stored in a binary search tree and the root of the binary search tree is 'root' 
	private int count; // the number of different tools currently stored in this tools collection 


    // constructor - create an object of ToolCollection object
    public ToolCollection()
    {
        root = null;
        count = 0;
    }

    // get the number of tools in this movie colllection 
    public int Number { get { return count; } }



    // Check if this tool collection is empty
    // Pre-condition: nil
    // Post-condition: return true if this tool collection is empty; otherwise, return false. This tool collection remains unchanged and new Number = old Number
    public bool IsEmpty()
	{
        return count == 0;
    }

    // Insert a new tool into this tool collection
    // Pre-condition: the new tool is not in this tool collection
    // Post-condition: the new tool is added into this tool collection, new Number = old Number + 1 and return true; otherwise, the new tool is not added into this tool collection, new Number = old Number and return false.
    public bool Insert(ITool tool)
	{
        if (root != null) return InsertTool(tool, root);
        count++;
        root = new BTreeNode(tool);
        return true;
    }

    private bool InsertTool(ITool tool, BTreeNode node)
    {
        switch (tool.CompareTo(node.tool)) {
            case -1:
                
                return nodeInsertCheck(ref node.lchild, tool);
            case 1:
                return nodeInsertCheck(ref node.rchild, tool);
            default:
                return false;
        }
    }

    private bool nodeInsertCheck(ref BTreeNode? node, ITool tool) 
    {
        if (node == null) 
        {
            node = new BTreeNode(tool);   
            count++; 
            return true;
        }                                              
        else return InsertTool(tool, node);

    }



    // Delete a tool from this tool collection
    // Pre-condition: nil
    // Post-condition: the tool is removed out of this tool collection, new Number = old Number - 1 and return true, if the tool is present in this tool collection; 
    // otherwise, this tool collection remains unchanged, and new Number = old Number, and return false, if the tool is not present in this tool collection.

    public bool Delete(ITool tool)
    {
        // search for item and its parent
        BTreeNode ptr = root; // search reference
        BTreeNode parent = null; // parent of ptr
        while((ptr!=null)&&(tool.CompareTo(ptr.tool)!=0))
        {
            parent = ptr;
            if(tool.CompareTo(ptr.tool) < 0) ptr = ptr.lchild; // move to the left child of ptr
            else ptr = ptr.rchild;
                
        }

        if(ptr == null) return false;

        // case 3: item has two children
        if((ptr.lchild != null)&&(ptr.rchild != null))
        {
            // find the right-most node in left subtree of ptr
            if(ptr.lchild.rchild == null) // a special case: the right subtree of ptr.LChild is empty
            {
                ptr.tool = ptr.lchild.tool;
                ptr.lchild = ptr.lchild.lchild;
            }
            else 
            {
                BTreeNode p = ptr.lchild;
                BTreeNode pp = ptr; // parent of p
                while(p.rchild != null)
                {
                    pp = p;
                    p = p.rchild;
                }
                // copy the item at p to ptr
                ptr.tool = p.tool;
                pp.rchild = p.lchild;
            }
        }
        else // cases 1 & 2: item has no or only one child
        {
            BTreeNode c;
            if(ptr.lchild != null) c = ptr.lchild;
            else c = ptr.rchild;

            // remove node ptr
            if(ptr == root) root = c; //need to change root
            else
            {
                if(ptr == parent.lchild) parent.lchild = c;
                else parent.rchild = c;
            }
        }

        count--;
        return true;
    }



    // Search for a tool by its name in this tool collection  
    // pre: nil
    // post: return the reference of the tool object if the tool is in this tool collection;
    //	     otherwise, return null. New Number = old Number.
    public ITool? Search(string toolName)
	{   
        if (root == null) return null;
        return SearchForTool(new Tool(toolName, 0), root);
    }
 
    private ITool? SearchForTool(ITool tool, BTreeNode node)
	{
        if (node == null) return null;
        switch (tool.CompareTo(node.tool)) {
            case 0:
                return node.tool;
            case -1:
                if (node.lchild != null) return SearchForTool(tool, node.lchild);
                return null;
            case 1:
                if (node.rchild != null) return SearchForTool(tool, node.rchild);
                return null;
            default:
                return null;
        }
    }




    // Return an array that contains all the tools in this tool collection and the tools in the array are sorted in the dictionary order by their names
    // Pre-condition: nil
    // Post-condition: return an array that contains all the tools in this tool collection and the tools in the array are sorted in alphabetical order by their names and new Number = old Number.
    public ITool[] ToArray()
	{
        ITool[] tools = new ITool[count]; 
        int index = 0; 
        if (root != null) InOrderTraversal(root, ref tools, ref index);
        return tools;
    }

    private void InOrderTraversal(BTreeNode node, ref ITool[] tools, ref int index)
    {
        if (node.lchild != null) InOrderTraversal(node.lchild, ref tools, ref index);
        tools[index++] = node.tool;
        if (node.rchild != null) InOrderTraversal(node.rchild, ref tools, ref index);
    }

    public (ITool[], int) ToArrayCount()
	{
        ITool[] tools = new ITool[count]; 
        int index = 0; 
        int basicCount = 0;
        if (root != null) InOrderTraversalCount(root, ref tools, ref index, ref basicCount);
        return (tools, basicCount);
    }

    private void InOrderTraversalCount(BTreeNode node, ref ITool[] tools, ref int index, ref int basicCount)
    {
        basicCount++;
        if (node.lchild != null) InOrderTraversalCount(node.lchild, ref tools, ref index, ref basicCount);
        tools[index++] = node.tool;
        basicCount++;
        if (node.rchild != null) InOrderTraversalCount(node.rchild, ref tools, ref index, ref basicCount);
    }


    // Clear this tool collection
    // Pre-condition: nil
    // Post-condition: all the tools in this tool collection are removed from this tool collection and Number = 0. 
    public void Clear()
	{
        root = null;
		count = 0;
	}

}