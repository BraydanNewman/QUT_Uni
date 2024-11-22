using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace assignment3B
{
    internal class Menu
    {
       
        //Display menu
        public void DisplayMenu()
        {
     
            Console.WriteLine("\nTransportation Network Planning");
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine("1. Read Transportation Network Plan Data from File");
            Console.WriteLine("2. Display Transportation Network Plan in Matrix Format");
            Console.WriteLine("3. Check Connectivity of Transportation Network");
            Console.WriteLine("4. Find Shortest Path between Two Intersections");
            Console.WriteLine("5. Find Shortest Path between All Pairs of Intersections");
            Console.WriteLine("0. Exit");
            Console.WriteLine("--------------------------------------------------");
            Console.Write("Enter your choice (1-5) or press 0 to exit: ");
        }

        //Get the user's choice
        public int GetUserChoice()
        {
            int choice;
            while (true)
            {
                try
                {
                    if (int.TryParse(Console.ReadLine(), out choice))
                    {
                        if (choice == 0)
                        {
                            Console.WriteLine("Thanks for using this system!");
                            Environment.Exit(0);
                        }
                        else if (choice >= 1 || choice <= 4)
                        {
                            return choice;
                        }
                        else
                        {
                            Console.WriteLine();
                            Console.WriteLine("Invalid input. Please enter a valid choice (0-5).");
                        }
                    }
                    else
                    {
                        Console.WriteLine();
                        Console.WriteLine("Invalid input. Please enter a valid choice (0-5).");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Invalid input: {ex.Message}");
                    Console.WriteLine();
                }
            }
        }

        //Perform an action selected by the user
        public void PerformUserAction(int choice, ref TransportationNetwork g)
        {
            try
            {
                switch (choice)
                {
                    case 1:
                        string currentDirectory = Environment.CurrentDirectory;
                        //Console.WriteLine("Current Directory: " + currentDirectory);
                        Console.WriteLine("Please input file name, from which the system read a transpportation network plan.");
                        Console.WriteLine("Make sure the transportation network plan files are in a sub-directory, namely Tests, under the current directory");
                        string? fileName = Console.ReadLine();
                        
                        fileName = "Test_12.txt";

                        //string? filePath = currentDirectory + "\\" + "Tests" + "\\"+fileName;
                        string filePath = Path.Combine(currentDirectory, "Tests", fileName);
                        Console.WriteLine(filePath);
                        if (g.ReadFromFile(filePath))
                        {
                            Console.WriteLine("\nFile read succesfully.");
                        }
                        else 
                        {
                            Console.WriteLine("\nFile did not read succesfully.");
                        }
                        break;

                    case 2:
                        if (g.Intersections == null)
                        {
                            Console.WriteLine("Transportation network plan data have not been read into the system!");
                            Console.WriteLine("Please read transportation plan data into the system first.");
                        }
                        else
                        {
                            g.DisplayTransportNetwork();
   
                        }
                        break;

                    case 3:
                        if (g.Intersections == null)
                        {
                            Console.WriteLine("Transportation network plan data have not been read into the system!");
                            Console.WriteLine("Please read transportation plan data into the system first.");
                        }
                        else
                        {
                            if (g.IsConnected())
                                Console.WriteLine("The transportation network is strongly connected.");
                            else
                                Console.WriteLine("The transportation network is not strongly connected.");
                        }
                        break;

                    case 4:
                        if (g.Intersections == null)
                        {
                            Console.WriteLine("Transportation network plan data have not been read into the system!");
                            Console.WriteLine("Please read transportation plan data into the system first.");
                        }
                        else
                        {
                            bool found1, found2;
                            string? intersection1, intersection2;
                            while (true)
                            {
                                Console.Write("Select a start intersection (" + string.Join(", ", g.Intersections) + "): ");
                                intersection1 = Console.ReadLine();

                                found1 = false;

                                // Iterate through the array to check if the string is present
                                foreach (string str1 in g.Intersections)
                                {
                                    if (str1 == intersection1)
                                    {
                                        found1 = true;
                                        break;
                                    }
                                }
                                if (!found1)
                                    Console.WriteLine("The start intersection you selected is not valid");
                                else
                                    break;
                            }

                            while (true)
                            {
                                Console.Write("Select end intersection (" + string.Join(", ", g.Intersections) + "): ");
                                intersection2 = Console.ReadLine();

                                found2 = false;

                                // Iterate through the array to check if the string is present
                                foreach (string str2 in g.Intersections)
                                {
                                    if (str2 == intersection2)
                                    {
                                        found2 = true;
                                        break;
                                    }
                                }
                                if (!found2)
                                    Console.WriteLine("The end intersection you selected is not valid");
                                else
                                    break;
                            }

                            if (intersection1 == intersection2)
                            {
                                Console.WriteLine("The two intersections that you selected are the same.");
                            }
                            else
                            {

                                double dist = g.FindShortestDistance(intersection1!, intersection2!);
                                if (dist == 0)
                                    Console.WriteLine("No path from {0} to {1}", intersection1, intersection2);
                                else
                                    Console.WriteLine("The shortest distance from {0} to {1} is {2}", intersection1, intersection2, dist);
                            }
                        }
                        break;

                    case 5:
                        if (g.Intersections == null)
                        {
                            Console.WriteLine("Transportation network plan data have not been read into the system!");
                            Console.WriteLine("Please read transportation plan data into the system first.");
                        }
                        else
                        {
                            int[,] shortestdistances = g.FindAllShortestDistances();
                            //Diaplay the shortest distance between all pairs of intersections
                            int n = shortestdistances.GetLength(0);
                            string[,] temp = new string[n + 1, n + 1];
                            temp[0, 0] = "".PadLeft(5);
                            for (int k = 0; k < n; k++)
                            {
                                temp[0, k + 1] = g.Intersections[k].PadLeft(5);
                                temp[k + 1, 0] = g.Intersections[k].PadLeft(5);
                            }

                            for (int i = 0; i < n; i++)
                            {
                                for (int j = 0; j < n; j++)
                                {
                                    if (shortestdistances[i, j] == Int32.MaxValue)
                                        temp[i + 1, j + 1] = "*".PadLeft(5);
                                    else
                                        temp[i + 1, j + 1] = shortestdistances[i, j].ToString().PadLeft(5);
                                }
                            }

                            for (int i = 0; i < (n + 1); i++)
                            {
                                for (int j = 0; j < (n + 1); j++)
                                {

                                    Console.Write(temp[i, j]);
                                }
                                Console.WriteLine();
                            }
                        }
                        break;


                    default:
                        Console.WriteLine("Invalid selection");
                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An exception occurred: {ex.Message}");
            }

        }
    }
}
