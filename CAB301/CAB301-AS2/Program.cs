namespace CAB301_AS2;


class Program
{
    static int TEST_SETS = 20;

    static void Main(string[] args)
    {
        using (StreamWriter outputFile = new StreamWriter("data.txt", true))
        {
            outputFile.WriteLine("TEST: {#} - {Tool Count} : {Basic Operations}");
            for (int i = 1000; i <= TEST_SETS * 1000; i += 1000)
            {   
                outputFile.WriteLine(string.Concat("SET LENGTH: ", i.ToString()));
                for (int j = 0; j < TEST_SETS; j++)
                {
                    // Create Collection
                    ToolCollection collection = new ToolCollection();
                    // Create Random Set
                    int[] randomSet = GenerateRandomArray(i);
                    // Add all tools
                    foreach (int item in randomSet)
                    {
                        collection.Insert(new Tool(item.ToString(), 100));
                    }
                    (ITool[] allTools, int basicCount) = collection.ToArrayCount();
                    outputFile.WriteLine(string.Concat("TEST: ", j + 1, " - ", i.ToString(), " : ", basicCount.ToString()));
                }
            } 
        }  
    }

    static int[] GenerateRandomArray(int size)
    {
        int[] A = new int[size];
        int seed = (int)DateTime.Now.Ticks;
        Random rnd = new Random(seed);
        for (int i = 0; i < A.Length; i++) A[i] = rnd.Next(Int32.MaxValue);
        return A;
    }
}
