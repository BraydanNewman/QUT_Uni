using System.Text.RegularExpressions;

namespace CAB201;

public static class DataValidation
{
    public static bool EmailValidation(string email)
    {
        var emailSplit = email.Split('@');
        if (emailSplit.Length != 2) return false;

        // Prefix Check
        if (Regex.Matches(emailSplit[0], "^[a-zA-Z0-9_.-]*$").Count != 1) return false;
        if (Regex.Matches(emailSplit[0], "[_.-]$").Count == 1) return false;

        // Suffix Check
        if (Regex.Matches(emailSplit[1], "^[a-zA-Z0-9.-]*$").Count != 1) return false;
        if (!emailSplit[1].Contains('.')) return false;
        if (emailSplit[1].Last() == ".".ToCharArray()[0] || emailSplit[1][0] == ".".ToCharArray()[0]) return false;
        return Regex.Matches(emailSplit[1].Split('.').Last(), "^[a-zA-Z]*$").Count == 1;
    }

    public static bool MoneyValidation(string money)
    {
        return Regex.Matches(money, @"^\$\d+.\d{2}$").Count != 0;
    }

    public static bool PasswordValidation(string password)
    {
        // Length Check
        if (password.Length < 8) return false;

        // White Space Check
        if (Regex.Matches(password, @"\s").Count != 0) return false;

        // Uppercase Check
        if (Regex.Matches(password, @"[A-Z]").Count == 0) return false;

        // Lowercase Check
        if (Regex.Matches(password, @"[a-z]").Count == 0) return false;

        // Digit Check
        if (Regex.Matches(password, @"[0-9]").Count == 0) return false;

        // Non-alphanumeric Check
        return Regex.Matches(password, @"\W|_").Count != 0;
    }

    public static bool StreetSuffixValidation(string suffix)
    {
        string[] suffixList =
        {
            "ALLEY", "AMBLE", "APPROACH", "ARCADE", "ARTERIAL", "AVENUE", "BAY", "BEND", "BRAE", "BREAK", "BOULEVARD",
            "BOARDWALK",
            "BOWL", "BYPASS", "CIRCLE", "CIRCUS", "CIRCUIT", "CHASE", "CLOSE", "CORNER", "COMMON", "CONCOURSE",
            "CRESCENT",
            "CROSS", "COURSE", "CREST", "CRUISEWAY", "COURTS", "COURT", "COVE", "DALE", "DELL", "DENE", "DIVIDE",
            "DOMAIN", "DRIVE",
            "EAST", "EDGE", "ENTRANCE", "ESPLANADE", "EXTENSION", "FLATS", "FORD", "FREEWAY", "GATE", "GARDEN",
            "GARDENS",
            "GLADES", "GLADE", "GLEN", "GULLY", "GRANGE", "GREEN", "GROVE", "GATEWAY", "HILL", "HOLLOW", "HEATH",
            "HEIGHTS", "HUB",
            "HIGHWAY", "ISLAND", "JUNCTION", "LANE", "LINK", "LOOP", "LOWER", "LANEWAY", "MALL", "MEW", "MEWS", "NOOK",
            "NORTH",
            "OUTLOOK", "PATH", "PARADE", "POCKET", "PARKWAY", "PLACE", "PLAZA", "PROMENADE", "PASS", "PASSAGE", "POINT",
            "PURSUIT",
            "PATHWAY", "QUADRANT", "QUAY", "REACH", "ROAD", "RIDGE", "RESERVE", "REST", "RETREAT", "RIDE", "RISE",
            "ROUND", "ROW",
            "RISING", "RETURN", "RUN", "SLOPE", "SQUARE", "STREET", "SOUTH", "STRIP", "STEPS", "SUBWAY", "TERRACE",
            "THROUGHWAY",
            "TOR", "TRACK", "TRAIL", "TURN", "TOLLWAY", "UPPER", "VALLEY", "VISTA", "VIEWS", "VIEW", "WAY", "WOOD",
            "WEST", "WALK",
            "WALKWAY", "WATERS", "WATERWAY", "WYND"
        };
        return suffixList.Any(s => s.Equals(suffix.ToUpper()));
    }

    public static bool StateValidation(string state)
    {
        string[] states = { "QLD", "NSW", "VIC", "TAS", "SA", "WA", "NT", "ACT" };
        return states.Any(s => s.Equals(state.ToUpper()));
    }

    public static bool PositiveNonZeroIntegerValidation(string? number)
    {
        // Positive Non-Zero Integer
        if (!int.TryParse(number, out var digit)) return false;
        return digit > 0;
    }
}