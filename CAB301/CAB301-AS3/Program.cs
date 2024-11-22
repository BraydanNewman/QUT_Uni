//CAB301 - Assignment 3B - Main program
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace assignment3B
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Menu menu = new Menu();
            TransportationNetwork graph_expected = new TransportationNetwork();
            while (true)
            {
                menu.DisplayMenu();
                int choice = menu.GetUserChoice();
                
                menu.PerformUserAction(choice, ref graph_expected);
            }
            
        }
    }
}

