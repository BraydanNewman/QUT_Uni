using System;
using System.Collections.Generic;

namespace Q4
{
    public class Q4
    {
        static void Main ()
        {
            // Keep the following line intact 
            Console.WriteLine( "===========================" );

            Console.WriteLine("Enter the month:");
            int month = Int32.Parse(Console.ReadLine());
            
            Console.WriteLine("Enter the day:");
            int day = Int32.Parse(Console.ReadLine());

            string isValid = CheckValid(month, day);

            Console.WriteLine($"Combination ({month},{day}) is {isValid}.");
            // Keep the following line intact
            Console.WriteLine( "===========================" );
        }
        
       static string CheckValid(int month, int day)
        {
            Dictionary<int, int> monthDaysDict = new Dictionary<int, int>()
            {
                { 1, 31 },
                { 2, 28 },
                { 3, 31 },
                { 4, 30 },
                { 5, 31 },
                { 6, 30 },
                { 7, 31 },
                { 8, 31 },
                { 9, 30 },
                { 10, 31 },
                { 11, 30 },
                { 12, 31 },
            };
            if (day < 1) return "invalid";
            if (!(monthDaysDict.ContainsKey(month))) return "invalid";
            if (day > monthDaysDict[month]) return "invalid";
            return "valid";
        }

    }
}

