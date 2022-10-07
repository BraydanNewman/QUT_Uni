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
        if (!(emailSplit[1].Contains('.'))) return false;
        if (emailSplit[1].Last() == ".".ToCharArray()[0] || emailSplit[1][0] == ".".ToCharArray()[0]) return false;
        return Regex.Matches(emailSplit[1].Split('.').Last(), "^[a-zA-Z]*$").Count == 1;
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
        // TODO: Need to change list of suffixes to non abbreviation
        string[] suffixList = { "AL", "AMB", "APPR", "ARC", "ART", "AV", "BAY", "BEND", "BRAE", "BRK", "BVD", "BWK", 
            "BWL", "BYP", "CCL", "CCS", "CCT", "CHA", "CL", "CNR", "COM", "CON", "CR", "CROS", "CRSE", "CRST", "CRY", 
            "CT", "CV", "DALE", "DELL", "DENE", "DIV", "DOM", "DR", "EAST", "EDG", "ENT", "ESP", "EXTN", "FLTS", 
            "FORD", "FWY", "GATE", "GDN", "GLA", "GLN", "GLY", "GRA", "GRN", "GV", "GWY", "HILL", "HLW", "HTH", "HTS", 
            "HUB", "HWY", "ID", "JCT", "LA", "LNK", "LOOP", "LWR", "LWY", "MALL", "MEW", "MWS", "NOOK", "NTH", "OUT", 
            "PATH", "PDE", "PD", "PKT", "PKW", "PL", "PLZ", "PRM", "PS", "PSG", "PT", "PUR", "PWAY", "QD", "QU", "RCH", 
            "RD", "RDG", "REST", "REST", "RET", "RIDE", "RISE", "RND", "ROW", "RSG", "RTN", "RUN", "SLO", "SQ", "ST", 
            "STH", "STP", "STPS", "SUB", "TCE", "THRU", "TOR", "TRK", "TRL", "TURN", "TWY", "UPR", "VLY", "VST", "VW", 
            "WAY", "WD", "WEST", "WK", "WKWY", "WTRS", "WRY", "WYD", };
        return suffixList.Any(s => s.Equals(suffix.ToUpper()));
    }

    public static bool StateValidation(string state)
    {
        string[] states = { "QLD", "NSW", "VIC", "TAS", "SA", "WA", "NT", "ACT", };
        return states.Any(s => s.Equals(state.ToUpper()));
    }

    public static bool PositiveNonZeroIntegerValidation(string? number)
    {
        // Positive Non-Zero Integer
        if (int.TryParse(number, out var digit)) return false;
        return digit > 0;
    }
}