namespace CAB201;

public class User
{
    public User(string name, string email, string password)
    {
        Name = name;
        Email = email;
        Password = password;
    }

    public string Name { get; set; }
    public string Email { get; set; }
    public string? Password { get; set; }

    public Address? Address { get; set; }
}