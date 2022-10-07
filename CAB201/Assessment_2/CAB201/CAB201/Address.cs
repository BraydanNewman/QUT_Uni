namespace CAB201;

public class Address
{
    public Address(
        int? unitNumber, 
        int streetNumber, 
        string streetName, 
        string streetSuffix, 
        string cityName, 
        string state, 
        int postcode
        )
    {
        UnitNumber = unitNumber;
        StreetNumber = streetNumber;
        StreetName = streetName;
        StreetSuffix = streetSuffix;
        CityName = cityName;
        State = state;
        Postcode = postcode;
    }

    public int? UnitNumber { get; set; }
    public int StreetNumber { get; set; }
    public string StreetName { get; set; }
    public string StreetSuffix { get; set; }
    public string CityName { get; set; }
    public string State { get; set; }
    public int Postcode { get; set; }
    
    
}