using System.Diagnostics;
using System.IO.Compression;
namespace CAB201
{
    public class Program
    {
        private static readonly UserManager Users = new UserManager();
        
        public static void Main(string[] args)
        {
            Console.WriteLine("+------------------------------+\n" +
                              "| Welcome to the Auction House |\n" +
                              "+------------------------------+");
            
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


        private static void SignIn()
        {
            Console.WriteLine("Sign In\n" +
                              "-------\n");
            
            Console.WriteLine("Please enter your email address");
            Console.Write("> ");
            var email = Console.ReadLine();
            
            Console.WriteLine("Please enter your password");
            Console.Write("> ");
            var password = Console.ReadLine();

            if (!Users.UserLogin(email, password))
            {
                Console.WriteLine("Incorrect email or password");
                return;
            }

            var output = $"Personal Details for {Users.CurrentUser?.Name}({Users.CurrentUser?.Email})";
            Console.WriteLine(output);
            Console.WriteLine(new string('-', output.Length));
            
            if (Users.CurrentUser!.Address != null) Users.CurrentUser.Address = GetAddress();

            ClientMenu();
        }

        private static void ClientMenu()
        {
            var exit = false;
            while (!exit)
            {
                Console.WriteLine("Client Menu\n" +
                                  "-----------\n" +
                                  "(1) Advertise Product\n" +
                                  "(2) View My Product List\n" +
                                  "(3) Search For Advertised Products\n" +
                                  "(4) View Bids On My Products\n" +
                                  "(5) View My Purchased Items\n" +
                                  "(6) Log off");
                Console.Write("> ");
                var userInput = Console.ReadLine();

                switch (userInput)
                {
                    case "1":
                        break;
                    case "2":
                        break;
                    case "3":
                        break;
                    case "4":
                        break;
                    case "5":
                        break;
                    case "6":
                        Logout();
                        exit = true;
                        break;
                    
                }
            }
        }

        private static void Logout()
        {
            Users.LogoutUser();
        }

        private static void Register()
        {
            Console.WriteLine("Registration");
            Console.WriteLine("------------\n");
            
            var name = GetName();
            var email = GetEmail();
            var password = GetPassword();

            Console.WriteLine($"\nClient Trader {name}({email}) has successfully registers at the Auction House.\n");
            Users.AddUser(name, email, password);
        }
        
        private static Address GetAddress()
        {
            Console.WriteLine("Please provide your home address.");

            var unitNumber = GetUnitNum();
            var streetNumber = GetStreetNum();
            var streetName = GetStreetName();
            var streetSuffix = GetStreetSuffix();
            var cityName = GetCityName();
            var state = GetState();
            var postcode = GetPostcode();
            
            return new Address(
                unitNumber, 
                streetNumber, 
                streetName, 
                streetSuffix, 
                cityName, 
                state, 
                postcode
                );
        }

        private static string GetState()
        {
            while (true)
            {
                Console.WriteLine("State (ACT, NSW, NT, QLD, SA, TAS, VIC, WA):");
                Console.Write("> ");
                var state = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(state) && DataValidation.StateValidation(state)) return state;
                Console.WriteLine("Invalid State or territory");

            }
        }

        private static int GetPostcode()
        {
            while (true)
            {
                Console.WriteLine("Postcode (1000 .. 9999):");
                Console.Write("> ");
                var postcode = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(postcode) &&
                    DataValidation.PositiveNonZeroIntegerValidation(postcode) &&
                    int.Parse(postcode) >= 1000 &&
                    int.Parse(postcode) <= 9999) return int.Parse(postcode);
                Console.WriteLine("Invalid postcode");
            }
        }

        private static string GetStreetSuffix()
        {
            while (true)
            {
                Console.WriteLine("Street suffix:");
                Console.Write("> ");
                var suffix = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(suffix) && DataValidation.StreetSuffixValidation(suffix)) return suffix;
                
                Console.WriteLine("Invalid street suffix");
            }
        }
        // TODO: Combined the get input functions into  a generic function maybe
        // Like GetCityName and GetStreetName 
        private static string GetCityName()
        {
            while (true)
            {
                Console.WriteLine("City:");
                Console.Write("> ");
                var name = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(name)) return name;
                Console.WriteLine("City name can't be empty");
            }
        }        
        
        private static string GetStreetName()
        {
            while (true)
            {
                Console.WriteLine("Street name:");
                Console.Write("> ");
                var name = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(name)) return name;
                Console.WriteLine("Street name can't be empty");
            }
        }

        private static int GetStreetNum()
        {
            while (true)
            {
                Console.WriteLine("Street number:");
                Console.Write("> ");
                var number = Console.ReadLine();
                if (!string.IsNullOrWhiteSpace(number) &&
                    DataValidation.PositiveNonZeroIntegerValidation(number)) return int.Parse(number);
                Console.WriteLine("Unit Number must be a Positive Non Zero Integer");
            }
        }

        private static int? GetUnitNum()
        {
            while (true)
            {
                Console.WriteLine("Unit number (0 = none):");
                Console.Write("> ");
                var number = Console.ReadLine();
                if (number == "0") return null;

                if (!string.IsNullOrWhiteSpace(number) &&
                    DataValidation.PositiveNonZeroIntegerValidation(number)) return int.Parse(number);
                Console.WriteLine("Unit Number must be a Positive Non Zero Integer");
            }
        }

        private static string GetName()
        {
            while (true)
            {
                Console.WriteLine("Please enter your name");
                Console.Write("> ");
                var name = Console.ReadLine();
                if (!string.IsNullOrWhiteSpace(name)) return name;
                Console.WriteLine("\tName can't be Empty");
            }
        }
        
        private static string GetEmail()
        {
            while (true)
            {
                Console.WriteLine("Please enter your email address");
                Console.Write("> ");
                var email = Console.ReadLine();
                if (string.IsNullOrWhiteSpace(email) || !DataValidation.EmailValidation(email))
                {
                    Console.WriteLine("\tThe supplied address is not a valid name.");
                    continue;
                }

                if (!Users.CheckEmailExists(email)) return email;
                Console.WriteLine("\tThe supplied address is already in use.");
            }
        }

        private static string GetPassword()
        {
            while (true)
            {
                Console.WriteLine("Please choose a password");
                Console.WriteLine("* At least 8 characters\n" +
                                  "* No white space characters\n" +
                                  "* At least one upper-case letter\n" +
                                  "* At least one lower-case letter\n" +
                                  "* At least one digit\n" +
                                  "* At least one special character\n");
                Console.Write("> ");
                var password = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(password) && DataValidation.PasswordValidation(password))
                    return password;
                Console.WriteLine("The supplied value is not a valid password");
            }
        }
    }
}