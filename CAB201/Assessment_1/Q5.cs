using System;
using System.Collections.Generic;
using System.Linq;

namespace Q5
{
    public class Program
    {
        public static void Main( string[] args )
        {
            // Keep the following line intact 
            Console.WriteLine( "===========================" );
            Console.WriteLine("Please provide a list of integers in a single line, separated by ',':");
            string[] inputSplit = Console.ReadLine().Split(",").Where(x => !string.IsNullOrEmpty(x)).ToArray();
            int[] inputsInts = Array.ConvertAll(inputSplit, s => int.Parse(s));
            Array.Sort(inputsInts);
            int distinct = 0;
            while (inputsInts.Length > 0)
            {
                if (inputsInts.Length > 1)
                {
                    if (inputsInts[0] == inputsInts[1])
                    {
                        distinct++;
                    }
                }
                int currentInt = inputsInts[0];
                inputsInts = inputsInts.Where(x => x != currentInt).ToArray();
            }
            Console.WriteLine($"The total number of values with repeats is {distinct}.");
            // Keep the following lines intact
            Console.WriteLine( "===========================" );
        }
    }
}

