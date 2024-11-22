//2024 CAB301 Assignment 3 
//TransportationNetwok.cs
//Assignment3B-TransportationNetwork

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


class Node : IComparable<Node>
{
    public int Index { get; }
    public int Cost { get; set; }
    public double Heuristic { get; set; }
    public Node Parent { get; set; }

    public Node(int index, int cost = Int32.MaxValue, double heuristic = 0)
    {
        Index = index;
        Cost = cost;
        Heuristic = heuristic;
        Parent = null;
    }

    public double TotalCost => Cost + Heuristic;

    public int CompareTo(Node other)
    {
        return TotalCost.CompareTo(other.TotalCost);
    }
}


public partial class TransportationNetwork
{

    private string[]? intersections; //array storing the names of those intersections in this transportation network design
    private int[,]? distances; //adjecency matrix storing distances between each pair of intersections, if there is a road linking the two intersections

    public string[]? Intersections
    {
        get {return intersections;}
    }

    public int[,]? Distances
    {
        get { return distances; }
    }


    //Read information about a transportation network plan into the system
    //Preconditions: The given file exists at the given path and the file is not empty
    //Postconditions: Return true, if the information about the transportation network plan is read into the system, the intersections are stored in the class field, intersections, and the distances of the links between the intersections are stored in the class fields, distances;
    //                otherwise, return false and both intersections and distances are null.
    public bool ReadFromFile(string filePath)
    {
        if (!File.Exists(filePath)) return false;
        string[,] fileData = new string[File.ReadLines(filePath).Count(), 3];
        HashSet<string> UIntersections = new HashSet<string>();
        StreamReader sr = new StreamReader(filePath);
        String line = sr.ReadLine();
        int currentLineNum = 0;
        while (line != null)
        {
            List<String> linkD = line.Split(',').ToList();
            if(linkD.Count != 3) return false;
            string p1 = linkD[0].Trim();
            string p2 = linkD[1].Trim();
            string p3 = linkD[2].Trim();
            if (string.IsNullOrEmpty(p1) || string.IsNullOrEmpty(p2) || string.IsNullOrEmpty(p3)) return false;
            UIntersections.Add(p1);
            UIntersections.Add(p2); 
            fileData[currentLineNum, 0] = p1;
            fileData[currentLineNum, 1] = p2;
            fileData[currentLineNum, 2] = p3;
            line = sr.ReadLine();
            currentLineNum++;
        }
        sr.Close();
        intersections = new string[UIntersections.Count];
        distances = new int[UIntersections.Count,UIntersections.Count];
        for (int i = 0; i < UIntersections.Count; i++)
        {
            for (int j = 0; j < UIntersections.Count; j++) distances[i,j] = Int32.MaxValue;
        }
        UIntersections.CopyTo(intersections);
        for (int i = 0; i < fileData.GetLength(0); i++) 
        { 
            int start = Array.IndexOf(intersections, fileData[i, 0]);
            int end = Array.IndexOf(intersections, fileData[i, 1]);
            int weight = Int32.Parse(fileData[i, 2]);
            distances[start, end] = weight;
        }
        return true;
    }

    public int[,] Transpose(int[,] matrix)
    {
        int w = matrix.GetLength(0);
        int h = matrix.GetLength(1);
        int[,] result = new int[h, w];
        for (int i = 0; i < w; i++) for (int j = 0; j < h; j++) result[j, i] = matrix[i, j];
        return result;
    }

    public void DFS(int[,] matrix, int nodeIndex, bool[] visited) 
    {
        visited[nodeIndex] = true;
        for (int i = 0; i < matrix.GetLength(1); i++) 
            if (matrix[nodeIndex, i] != Int32.MaxValue && (!visited[i])) DFS(matrix, i, visited);
    }


    //Display the transportation network plan with intersections and distances between intersections
    //Preconditions: The given file exists at the given path and the file is not empty
    //Postconditions: The transportation netork is displayed in a matrix format
    public void DisplayTransportNetwork()
    {
        Console.Write("       ");
        for (int i = 0; i < intersections?.Length; i++)
        {
                    Console.Write(intersections[i].ToString().PadRight(5) + "  ");
        }
        Console.WriteLine();


        for (int i = 0; i < distances?.GetLength(0); i++)
        {
            Console.Write(intersections[i].ToString().PadRight(5) + "  ");
            for (int j = 0; j < distances?.GetLength(1); j++)
            {
                if (distances[i, j] == Int32.MaxValue)
                    Console.Write("INF  " + "  ");
                else
                    Console.Write(distances[i, j].ToString().PadRight(5)+"  ");
            }
            Console.WriteLine();
        }
    }


    //Check if this transportation network is strongly connected. A transportation network is strongly connected, if there is a path from any intersection to any other intersections in thihs transportation network. 
    //Precondition: Transportation network plan data have been read into the system.
    //Postconditions: return true, if this transpotation netork is strongly connected; otherwise, return false. This transportation network remains unchanged.
    public bool IsConnected()
    {
        bool[] visited = new bool[intersections.Length];
        DFS(distances, 0, visited);
        if (!visited.All(x => x)) return false;
        visited = new bool[intersections.Length];
        int[,] matrix = Transpose(distances);
        DFS(matrix, 0, visited);
        return visited.All(x => x);
    }

    
    
    //Find the shortest path between a pair of intersections
    //Precondition: transportation network plan data have been read into the system
    //Postcondition: return the shorest distance between two different intersections; return 0 if there is no path from startVerte to endVertex; returns -1 if startVertex or endVertex does not exists. This transportation network remains unchanged.
    public int FindShortestDistance(string startVertex, string endVertex)
    {
        int startNode = Array.IndexOf(intersections, startVertex);
        int goalNode = Array.IndexOf(intersections, endVertex);
        if (startNode < 0 || goalNode < 0) return -1;
        return AStar(distances, startNode, goalNode);
    }


    static int AStar(int[,] graph, int start, int goal)
    {
        int n = graph.GetLength(0);
        Node[] nodes = new Node[n];
        for (int i = 0; i < n; i++) nodes[i] = new Node(i);
        PriorityQueue<Node> openSet = new PriorityQueue<Node>();
        HashSet<int> closedSet = new HashSet<int>();
        nodes[start].Cost = 0;
        nodes[start].Heuristic = Heuristic(start, goal);
        openSet.Enqueue(nodes[start]);
        while (openSet.Count > 0)
        {
            Node current = openSet.Dequeue();
            if (current.Index == goal) return current.Cost;
            closedSet.Add(current.Index);
            for (int neighbor = 0; neighbor < n; neighbor++)
            {
                if (graph[current.Index, neighbor] == Int32.MaxValue || closedSet.Contains(neighbor)) continue;
                int tentativeCost = current.Cost + graph[current.Index, neighbor];
                if (tentativeCost < nodes[neighbor].Cost)
                {
                    nodes[neighbor].Parent = current;
                    nodes[neighbor].Cost = tentativeCost;
                    nodes[neighbor].Heuristic = Heuristic(neighbor, goal);
                    if (!openSet.Contains(nodes[neighbor])) openSet.Enqueue(nodes[neighbor]);
                }
            }
        }
        return 0;
    }

    static double Heuristic(int node, int goal)
    {
        return Math.Abs(node - goal);
    }


    public int[,] Floyds(int[,] adj) {
        int length = adj.GetLength(0);
        int[,] D = (int[,])adj.Clone();
        for (int k = 0; k < length; k++)
        {
            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < length; j++)
                {   
                    D[i,j] = new int[2] {D[i,j], D[i,k] == Int32.MaxValue || D[k,j] == Int32.MaxValue ? Int32.MaxValue : D[i,k] + D[k,j]}.Min();
                }
            }
        }

        return D;
    }

    //Find the shortest path between all pairs of intersections
    //Precondition: transportation network plan data have been read into the system
    //Postcondition: return the shorest distances between between all pairs of intersections through a two-dimensional int array and this transportation network remains unchanged
    public int[,] FindAllShortestDistances()
    {
        return Floyds(distances);
    }
}

public class PriorityQueue<T> where T : IComparable<T>
{
    private List<T> data;

    public PriorityQueue()
    {
        this.data = new List<T>();
    }

    public void Enqueue(T item)
    {
        data.Add(item);
        int ci = data.Count - 1;
        while (ci > 0)
        {
            int pi = (ci - 1) / 2;
            if (data[ci].CompareTo(data[pi]) >= 0)
                break;
            T tmp = data[ci];
            data[ci] = data[pi];
            data[pi] = tmp;
            ci = pi;
        }
    }

    public T Dequeue()
    {
        int li = data.Count - 1;
        T frontItem = data[0];
        data[0] = data[li];
        data.RemoveAt(li);

        --li;
        int pi = 0;
        while (true)
        {
            int ci = pi * 2 + 1;
            if (ci > li) break;
            int rc = ci + 1;
            if (rc <= li && data[rc].CompareTo(data[ci]) < 0)
                ci = rc;
            if (data[pi].CompareTo(data[ci]) <= 0) break;
            T tmp = data[pi];
            data[pi] = data[ci];
            data[ci] = tmp;
            pi = ci;
        }
        return frontItem;
    }

    public int Count => data.Count;

    public bool Contains(T item) => data.Contains(item);
}