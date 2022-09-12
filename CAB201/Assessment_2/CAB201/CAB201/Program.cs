using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;  
using Microsoft.VisualBasic;

namespace CAB201
{
    public class Program
    {
        public static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("Main Menu:\n" +
                                  "1) Register\n" +
                                  "2) Sign In\n" +
                                  "3) Exit");
                Console.Write(">>> ");
                string? userInput = Console.ReadLine();
                Console.Clear();

                switch (userInput)
                {
                    case "1":
                        Register();
                        break;
                    case "2":
                        break;
                    case "3":
                        return;
                }
            }
        }

        public static void ClientMenu()
        {
            Console.Clear();
            Console.WriteLine("ClientMenu:\n" +
                              "1) Advertisements\n" +
                              "2) Product List\n" +
                              "3) Bid on Product List\n" +
                              "4) Search\n" +
                              "5) Purchased Products");
            Console.Write(">>>");


        }

        static void Register()
        {

        }

    }
}