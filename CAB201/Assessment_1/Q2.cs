using System;

namespace Q2
{
    public class Q2
    {
        static void Main ()
        {
            // Keep the following line intact 
            Console.WriteLine( "===========================" );

            Console.WriteLine("Enter the number of chickens:");
            int chickens = Int32.Parse(Console.ReadLine());
            int eggs = 0;
            for (int i = 0; i < chickens; i++)
            {
                Console.WriteLine("Eggs:");
                int amount = Int32.Parse(Console.ReadLine());
                if (amount > 0)
                {
                    eggs = eggs + amount;
                }
            }
            int remainder;
            int dozen = Math.DivRem(eggs, 12, out remainder);
            string remainderStr = $"{remainder} eggs left over.";
            if (remainder == 1)
            {
                remainderStr = $"{remainder} egg left over.";
            }
            if (eggs == 1)
            {
                Console.WriteLine($"You have {eggs} egg which equals {dozen} dozen and {remainderStr}");
            }
            else
            {
                Console.WriteLine($"You have {eggs} eggs which equals {dozen} dozen and {remainderStr}");
            }


            // Keep the following lines intact
            Console.WriteLine( "===========================" );
        }
    }
}

