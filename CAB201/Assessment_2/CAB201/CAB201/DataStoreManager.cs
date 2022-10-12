using System.IO.Compression;
using System.Text;

namespace CAB201;

public abstract class DataStoreManager
{
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
        if (System.IO.File.Exists(file)) return System.IO.File.ReadAllLines(@file);
        else {
            System.IO.File.Create(file);
            return new string[] {};
        }
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
    private const string DataFile = "user.csv";
    private List<User> Users { get; set; } = new List<User>();
    
    public User? CurrentUser { get; private set; }

    public void LoadData()
    {
        Users.Clear();
        foreach (var row in CsvParser(DataFile))
        {
            this.Users.Add(
                new User(DecodeFrom64(row[0]), DecodeFrom64(row[1]), DecodeFrom64(row[2]))
                );
        }
    }

    public bool CheckEmailExists(string? email)
    {
        return (this.Users.Count(p => string.Equals(p.Email, email)) > 0);
    }

    public void AddUser(string name, string email, string password)
    {
        this.Users.Add(new User(name, email, password));
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

            data += $"{b64Name},{b64Email},{b64Password}" + Environment.NewLine;
        }
        AppendData(data, DataFile);
    }

    public bool UserLogin(string? email, string? password)
    {
        var selectedUsers = this.Users.Where(p => p.Email == email).ToArray();
        if (selectedUsers.Count() != 1) return false;
        var selectedUser = selectedUsers[0];
        if (selectedUser.Password != password) return false;
        this.CurrentUser = selectedUser;
        return true;
    }

    public void LogoutUser()
    {
        this.CurrentUser = null;
    }
}
