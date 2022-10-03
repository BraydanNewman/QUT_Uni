using System.IO.Compression;
namespace CAB201
{
    public class Program
    {
        private static readonly UserManager Users = new UserManager();
        
        public static void Main(string[] args)
        {
            Users.LoadData();

            var exit = false;
            while (!(exit))
            {
                Console.WriteLine("Main Menu\n" +
                                  "---------\n"+
                                  "(1) Register\n" +
                                  "(2) Sign In\n" +
                                  "(3) Exit");
                Console.WriteLine("please select an option between 1 and 3");
                Console.Write("> ");
                
                var userInput = Console.ReadLine();

                switch (userInput)
                {
                    case "1":
                        Register();
                        break;
                    case "2":
                        SignIn();
                        break;
                    case "3":
                        exit = true;
                        break;
                }
            }
        }


        public static void SignIn()
        {
            
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
            Console.Write("> ");


        }

        private static void Register()
        {
            Console.WriteLine("Registration");
            Console.WriteLine("------------\n");


            // Name Validation
            var name = "";
            var validInput = false;
            while (!validInput)
            {
                Console.WriteLine("Please enter your name");
                Console.Write("> ");
                name = Console.ReadLine();
                if (!string.IsNullOrEmpty(name)) validInput = true;
            }

            // Email Validation
            var email = "";
            validInput = false;
            while (!validInput)
            {
                Console.WriteLine("Please enter your email address");
                Console.Write("> ");
                email = Console.ReadLine();

                if (!DataValidation.EmailValidation(email))
                {
                    Console.WriteLine("\tThe supplied address is not a valid name.");
                }
                else if (Users.CheckEmailExists(email))
                {
                    Console.WriteLine("\tThe supplied address is already in use.");
                }
                else validInput = true;
            }
            
            // Password Validation 
            var password = "";
            validInput = false;
            while (!validInput)
            {
                Console.WriteLine("Please choose a password");
                Console.WriteLine("* At least 8 characters\n" +
                                  "* No white space characters\n" +
                                  "* At least one upper-case letter\n" +
                                  "* At least one lower-case letter\n" +
                                  "* At least one digit\n" +
                                  "* At least one special character\n");
                Console.Write("> ");

                password = Console.ReadLine();

                if (!DataValidation.PasswordValidation(password))
                {
                    Console.WriteLine("The supplied value is not a valid password");
                }
                else
                {
                    validInput = true;
                }
            }
            
            Console.WriteLine($"\nClient Trader {name}({email}) has successfully registers at the Auction House.\n");
            Users.AddUser(name, email, password);
        }

    }
}