using System.Text;

namespace CAB201;

public abstract class DataStoreManager
{
    private const string DataFile = "data.csv";

    protected static string EncodeTo64(string? toEncode)
    {
        var toEncodeAsBytes = Encoding.ASCII.GetBytes(toEncode!);
        return Convert.ToBase64String(toEncodeAsBytes);
    }

    protected static string DecodeFrom64(string encodedData)
    {
        var encodedDataAsBytes = Convert.FromBase64String(encodedData);
        return Encoding.ASCII.GetString(encodedDataAsBytes);
    }

    private static IEnumerable<string> ReadCsv(string file)
    {
        if (File.Exists(file)) return File.ReadAllLines(file);

        File.Create(file).Dispose();
        return new string[] { };
    }

    protected static List<string[]> CsvParser(string file)
    {
        return ReadCsv(file).Select(row => row.Split(",")).ToList();
    }


    protected static void ClearFile(string file)
    {
        File.WriteAllText(file, string.Empty);
    }

    protected static void AppendData(string data, string file)
    {
        File.AppendAllText(file, data);
    }
}

public class UserManager : DataStoreManager
{
    private const string DataFile = "users.csv";
    private List<User> Users { get; } = new();

    public User? CurrentUser { get; private set; }

    public void LoadData()
    {
        Users.Clear();
        foreach (var row in CsvParser(DataFile))
        {
            var newUser = new User(
                DecodeFrom64(row[0]),
                DecodeFrom64(row[1]),
                DecodeFrom64(row[2])
            );
            if (row[4] != string.Empty)
                newUser.Address = new Address(
                    int.TryParse(row[3], out var i) ? i : null,
                    int.Parse(DecodeFrom64(row[4])),
                    DecodeFrom64(row[5]),
                    DecodeFrom64(row[6]),
                    DecodeFrom64(row[7]),
                    DecodeFrom64(row[8]),
                    int.Parse(DecodeFrom64(row[9]))
                );
            Users.Add(newUser);
        }
    }

    public bool CheckEmailExists(string? email)
    {
        return Users.Count(p => string.Equals(p.Email, email)) > 0;
    }

    public void AddUser(string name, string email, string password)
    {
        Users.Add(new User(name, email, password));
    }

    public void SaveUsers()
    {
        ClearFile(DataFile);
        var data = "";
        foreach (var user in Users)
        {
            var b64Name = EncodeTo64(user.Name);
            var b64Email = EncodeTo64(user.Email);
            var b64Password = EncodeTo64(user.Password);

            var b64UnitNumber = "";
            var b64StreetNumber = "";
            var b64StreetName = "";
            var b64CityName = "";
            var b64State = "";
            var b64Postcode = "";
            var b64StreetSuffix = "";

            if (user.Address != null)
            {
                if (user.Address.UnitNumber != null) b64UnitNumber = EncodeTo64(user.Address.UnitNumber.ToString());

                b64StreetNumber = EncodeTo64(user.Address.StreetNumber.ToString());
                b64StreetName = EncodeTo64(user.Address.StreetName);
                b64StreetSuffix = EncodeTo64(user.Address.StreetSuffix);
                b64CityName = EncodeTo64(user.Address.CityName);
                b64State = EncodeTo64(user.Address.State);
                b64Postcode = EncodeTo64(user.Address.Postcode.ToString());
            }

            data += $"{b64Name},{b64Email},{b64Password},{b64UnitNumber},{b64StreetNumber},{b64StreetName}," +
                    $"{b64StreetSuffix},{b64CityName},{b64State},{b64Postcode}" + Environment.NewLine;
        }

        AppendData(data, DataFile);
    }

    public bool UserLogin(string? email, string? password)
    {
        var selectedUsers = Users.Where(p => p.Email == email).ToArray();
        if (selectedUsers.Count() != 1) return false;
        var selectedUser = selectedUsers[0];
        if (selectedUser.Password != password) return false;
        CurrentUser = selectedUser;
        return true;
    }

    public User GetUserFromEmail(string email)
    {
        return Users.First(p => p.Email == email);
    }

    public void LogoutUser()
    {
        CurrentUser = null;
    }
}

public class ProductManager : DataStoreManager
{
    private const string DataFile = "products.csv";

    public List<Product> Products { get; } = new();

    public void AddProduct(string name, string description, int price, string userEmail)
    {
        Products.Add(new Product(name, description, price, userEmail));
    }

    public void ListUserProducts(string userEmail)
    {
        var usersProducts = Products.Where(p => p.UserEmail == userEmail).ToList();


        if (usersProducts.Count == 0)
        {
            Console.WriteLine("No products are available for display");
            return;
        }

        // TODO: ODER THE PRODUCTS
        ListProducts(usersProducts);
    }

    public static void ListProducts(IEnumerable<Product> productsList)
    {
        Console.WriteLine("Item #	Product name	Description	List price	Bidder name	Bidder email	Bid amt");
        foreach (var (product, index) in productsList.Select((value, i) => (value, i)))
        {
            Console.Write($"{index + 1}    ");
            Console.Write($"{product.Name}    ");
            Console.Write($"{product.Description}    ");
            Console.Write($"{(decimal)product.Price / 100:C}    ");

            if (product.BidderEmail != null)
            {
                Console.Write($"{product.BidderEmail}    ");
                Console.Write($"{product.BidderName}    ");
                Console.Write($"{(decimal)product.BidAmount! / 100:C}    ");
            }
            else
            {
                Console.Write("    -	-	-");
            }

            Console.Write("\n");
        }

        Console.WriteLine("\n");
    }


    public void SaveProducts()
    {
        ClearFile(DataFile);
        var data = "";
        foreach (var product in Products)
        {
            var b64Name = EncodeTo64(product.Name);
            var b64Description = EncodeTo64(product.Description);
            var b64Price = EncodeTo64(product.Price.ToString());
            var b64UserEmail = EncodeTo64(product.UserEmail);
            var b64BidderEmail = EncodeTo64(product.BidderEmail);
            var b64BidAmount = EncodeTo64(product.BidAmount.ToString());
            var b64Delivery = EncodeTo64(product.Delivery);
            var b64Purchased = EncodeTo64(product.Purchased.ToString());

            data +=
                $"{b64Name},{b64Description},{b64Price},{b64UserEmail},{b64BidderEmail},{b64BidAmount},{b64Delivery},{b64Purchased}" +
                Environment.NewLine;
        }

        AppendData(data, DataFile);
    }
}