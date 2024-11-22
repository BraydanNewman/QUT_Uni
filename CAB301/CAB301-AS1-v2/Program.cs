class Program
{
    static void Main()
    {
        int colectionCapacity = 4;

        MemberCollection members = new MemberCollection(colectionCapacity);

        Member m1 = new Member("a", "c");
        Member m2 = new Member("a", "b");
        Member m3 = new Member("a", "a");
        Member m4 = new Member("a", "d");

        // Console.WriteLine(m1.CompareTo(m2));

        members.Add(m1);
        members.Add(m2);
        // members.Clear();
        members.Add(m3);
        members.Add(m4);

        Console.WriteLine(members.ToString());

        // Console.WriteLine(members.Search("a", "a"));
        // Console.WriteLine(members.Search("a", "g"));

        members.Delete("b", "a");

        Console.WriteLine(members.ToString());

        Console.WriteLine(members.Search("d", "a"));

    }
}