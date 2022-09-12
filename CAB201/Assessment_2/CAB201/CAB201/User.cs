using System.Net.Security;

namespace CAB201;

public class User
{
    public string Name { get; set; }
    public string Email { get; set; }
    public string Password { get; set; }

    public User(string name, string email, string password)
    {
        this.Name = name;
        this.Email = email;
        this.Password = password;
    }
}
