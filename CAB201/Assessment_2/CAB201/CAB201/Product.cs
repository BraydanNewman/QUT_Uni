namespace CAB201;

public class Product
{
    public Product(string name, string description, int price, string userEmail)
    {
        Name = name;
        Description = description;
        Price = price;
        UserEmail = userEmail;
        Purchased = false;
        BidAmount = 0;
    }

    public string Name { get; set; }

    public string Description { get; set; }

    public int Price { get; set; }

    public string UserEmail { get; set; }

    public string? BidderEmail { get; set; }

    public string? BidderName { get; set; }

    public int? BidAmount { get; set; }

    public string? Delivery { get; set; }

    public bool Purchased { get; set; }
}