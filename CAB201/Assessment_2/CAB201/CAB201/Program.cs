namespace CAB201;

public class Program
{
    private static readonly UserManager Users = new();
    private static readonly ProductManager Products = new();

    public static void Main(string[] args)
    {
        Console.WriteLine("+------------------------------+\n" +
                          "| Welcome to the Auction House |\n" +
                          "+------------------------------+");

        Users.LoadData();
        // Products.LoadData(); TODO: Need to implement DATA loading

        var exit = false;
        while (!exit)
        {
            Console.WriteLine("Main Menu\n" +
                              "---------\n" +
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
                    Users.SaveUsers();
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

        if (Users.CurrentUser!.Address == null)
        {
            Users.CurrentUser.Address = GetAddress();
            Users.SaveUsers();
        }

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
                    AdvertiseProduct();
                    break;
                case "2":
                    ListUserProducts();
                    break;
                case "3":
                    SearchProducts();
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

    private static void SearchProducts()
    {
        var searchPhrase = SearchString();
        var products = Products.Products.Where(p => p.UserEmail != Users.CurrentUser!.Email).ToList();

        if (searchPhrase != "ALL")
            products = products.Where(p => p.Name.Contains(searchPhrase) || p.Description.Contains(searchPhrase))
                .ToList();

        ProductManager.ListProducts(products);

        Console.WriteLine("PLace Bid on Product (yes/no):");
        while (true)
        {
            Console.Write("> ");
            var answer = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(answer)) ;
            else if (answer.ToUpper() == "YES") break;
            else if (answer.ToUpper() == "NO") return;
            Console.WriteLine("Invalid Input");
        }

        Console.WriteLine($"Please enter a non-negative integer between 1 and {products.Count}:");
        string? index;
        while (true)
        {
            Console.Write("> ");
            index = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(index) &&
                DataValidation.PositiveNonZeroIntegerValidation(index) &&
                int.Parse(index) <= products.Count) break;
            Console.WriteLine("Invalid index into product list");
        }

        Console.WriteLine($"DEBUG: {index}");

        var chosenProduct = products[int.Parse(index) - 1];

        Console.WriteLine(
            $"Bidding for {chosenProduct.Name} (regular price {(decimal)chosenProduct.Price! / 100:C}) current highest bid {(decimal)chosenProduct.BidAmount! / 100:C}");

        var bid = int.Parse(GetBidPrice().Replace(".", string.Empty).Remove(0, 1));

        if (chosenProduct.BidAmount > bid)
        {
            Console.WriteLine("Bid wasn't high enough");
            return;
        }

        chosenProduct.BidAmount = bid;
        chosenProduct.BidderName = Users.CurrentUser!.Name;
        chosenProduct.BidderEmail = Users.CurrentUser!.Name;

        Console.WriteLine($"Your bid of {(decimal)bid! / 100:C} for {chosenProduct.Name} is placed");

        Console.WriteLine("Delivery Instructions");
        Console.WriteLine("---------------------");
        Console.WriteLine("(1) Click and Collect");
        Console.WriteLine("(2) Home Delivery");

        Console.WriteLine("PLease select an option between 1 and 2");
        string? choise;
        while (true)
        {
            Console.Write("> ");
            choise = Console.ReadLine();
            if (choise is "1" or "2") break;
            Console.WriteLine("Invalid Input");
        }

        if (choise == "1")
        {
            Console.WriteLine("Delivery Window start (dd/mm/yyyy hh:mm)");
            var startDateTime = GetCollectTime(DateTime.Now);

            Console.WriteLine("Delivery Window end (dd/mm/yyyy hh:mm)");
            var endDateTime = GetCollectTime(startDateTime);

            Console.WriteLine("Thank you for yor successful bid. If successful, " +
                              $"the item will be provided via collection between {startDateTime.TimeOfDay} on {startDateTime.Date}" +
                              $"and {endDateTime.TimeOfDay} on {endDateTime.Date}");

            chosenProduct.Delivery = $"Collection between {startDateTime.TimeOfDay} on {startDateTime.Date}" +
                                     $"and {endDateTime.TimeOfDay} on {endDateTime.Date}";
        }
        else
        {
            Console.WriteLine("Please provide a Delivery Address");
            var deliverAddress = GetAddress();
            chosenProduct.Delivery =
                $"Delivered to {deliverAddress.StreetNumber}, {deliverAddress.StreetName} {deliverAddress.StreetSuffix}, {deliverAddress.CityName}, {deliverAddress.Postcode}";
        }
    }

    private static void ListUserProducts()
    {
        Products.ListUserProducts(Users.CurrentUser!.Email);
    }


    private static void AdvertiseProduct()
    {
        var output = $"Product Advertisement for {Users.CurrentUser?.Name}({Users.CurrentUser?.Email})";
        Console.WriteLine(output);
        Console.WriteLine(new string('-', output.Length));

        var productName = GetProductName();
        var productDescription = GetProductDescription(productName);
        var productPrice = int.Parse(GetProductPrice().Replace(".", string.Empty).Remove(0, 1));

        Products.AddProduct(productName, productDescription, productPrice, Users.CurrentUser!.Email);

        Console.WriteLine(
            $"Successfully added product {productName}, {productDescription}, {(decimal)productPrice / 100:C}.\n");
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

    private static string SearchString()
    {
        while (true)
        {
            Console.WriteLine("Search Phrase:");
            Console.Write("> ");
            var phrase = Console.ReadLine();

            if (!string.IsNullOrWhiteSpace(phrase)) return phrase;
            Console.WriteLine("Search Phrase can't be empty");
        }
    }

    private static DateTime GetCollectTime(DateTime beforeTime)
    {
        while (true)
        {
            Console.Write("> ");
            var dateTime = Console.ReadLine();
            if (!DateTime.TryParse(dateTime, out var dateTimeOut))
            {
                Console.WriteLine("Please enter a valid date and time");
                continue;
            }

            if (dateTimeOut >= beforeTime.AddHours(1)) return dateTimeOut;
            Console.WriteLine("Delivery window must be at least one hour in the future");
        }
    }

    private static string GetProductDescription(string name)
    {
        while (true)
        {
            Console.WriteLine("Product name:");
            Console.Write("> ");
            var description = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(description))
            {
                Console.WriteLine("Product Description can't be empty");
                continue;
            }

            if (description != name) return description;
            Console.WriteLine("Product Description can't be same as Product Name");
        }
    }

    private static string GetProductPrice()
    {
        while (true)
        {
            Console.WriteLine("Product price ($d.cc):");
            Console.Write("> ");
            var price = Console.ReadLine();

            if (!string.IsNullOrWhiteSpace(price) && DataValidation.MoneyValidation(price)) return price;
            Console.WriteLine("Product price is invalid");
        }
    }

    private static string GetBidPrice()
    {
        while (true)
        {
            Console.WriteLine("Bid price ($d.cc):");
            Console.Write("> ");
            var price = Console.ReadLine();

            if (!string.IsNullOrWhiteSpace(price) && DataValidation.MoneyValidation(price)) return price;
            Console.WriteLine("Bid can't be empty");
        }
    }

    private static string GetProductName()
    {
        while (true)
        {
            Console.WriteLine("Product name:");
            Console.Write("> ");
            var name = Console.ReadLine();

            if (!string.IsNullOrWhiteSpace(name)) return name;
            Console.WriteLine("Product name can't be empty");
        }
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