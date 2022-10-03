using System.Text.RegularExpressions;

namespace CAB201;

public static class DataValidation
{
    public static bool EmailValidation(string? email)
    {
        if (string.IsNullOrEmpty(email)) return false;
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

    public static bool PasswordValidation(string? password)
    {
        if (string.IsNullOrEmpty(password)) return false;

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
}