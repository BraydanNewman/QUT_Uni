using System;

namespace Q3
{
    public class Program
    {
        public static void Main( string[] args )
        {
            // Keep the following line intact 
            Console.WriteLine( "===========================" );

            Calculations();

            // Keep the following lines intact
            Console.WriteLine( "===========================" );
        }
        
       private static void Calculations()
        {
            Console.WriteLine("Enter the simulation period (whole years):");
            int years = Int32.Parse(Console.ReadLine());
            if (years < 1)
            {
                Console.WriteLine("Simulation cancelled: no years.");
                return;
            }
            
            Console.WriteLine("Enter the number of towns:");
            int towns = Int32.Parse(Console.ReadLine());
            if (towns < 1)
            {
                Console.WriteLine("Simulation cancelled: no towns.");
                return;
            }

            for (int i = 0; i < towns; i++)
            {
                Console.WriteLine("Enter the name of the town:");
                string name = Console.ReadLine();
                
                Console.WriteLine("Enter the initial population of the town:");
                int initial = Int32.Parse(Console.ReadLine());
                
                Console.WriteLine("Enter the growth rate of the town:");
                double growthRate = Double.Parse(Console.ReadLine());

                double current = initial;

                for (int j = 0; j < years; j++)
                {
                    current = Math.Round(current * growthRate);
                    if (current < 0)
                    {
                        current = 0;
                    }
                    // Might Need rounding here
                }
                Console.WriteLine($"The population of {name} goes from {initial} to {Math.Round(current)} with growth factor {growthRate} after {years} years.");

            }
        }
    }
}

