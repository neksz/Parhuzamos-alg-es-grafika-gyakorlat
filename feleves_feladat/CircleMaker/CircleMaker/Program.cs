using ShapeGen;
using System.Diagnostics;

Stopwatch linearTime = Stopwatch.StartNew();
Circle[] circleArray = new Circle[1000];
for (int i = 0; i < 1000; i++)
{
    circleArray[i] = new(28, "Output");
    circleArray[i].DrawToBitmap();
}
Console.WriteLine($"Finished with linear in {linearTime.ElapsedMilliseconds} millisecond.");

Stopwatch parallelTime = Stopwatch.StartNew();
var taskList = new List<Task>();

for (int i = 0; i < 4; i++)
{
    taskList.Add(Task.Factory.StartNew(() => GenerateCircles(250)));
}
Task.WaitAll(taskList.ToArray());
Console.WriteLine($"Finished with parallel in {parallelTime.ElapsedMilliseconds} millisecond.");


static void GenerateCircles(int count)
{
    Circle[] circleArray = new Circle[count];
    for (int i = 0; i < count; i++)
    {
        circleArray[i] = new(28,"Output");
        circleArray[i].DrawToBitmap();
    }
}