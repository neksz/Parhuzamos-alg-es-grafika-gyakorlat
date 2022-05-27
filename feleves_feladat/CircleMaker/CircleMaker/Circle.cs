using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;

namespace ShapeGen
{
    internal class Circle
    {
        private int scale;
        private int borderSize;

        protected int resolution = 28;
        protected string path = "Output";

        protected byte[] imageBuffer = new byte[0];

        private static int circleCount;

        private int positionX;
        private int positionY;

        private byte[] circleCoords;

        private int coordCount = 0;

        private bool randomColors;

        private Random rnd = new Random();

        public Color Background { get; set; } = new Color(0, 0, 0, 255);
        public Color Line { get; set; } = new Color(255, 255, 255, 255);
        public static int CircleCount { get => circleCount; set => circleCount = value; }

        public Circle(int resolution, string path, Color? shape = null, Color? background = null)
        {
            try
            {
                CircleCount++;

                this.imageBuffer = new byte[resolution * resolution * 4];

                SetRandomAttributes();

                if (shape != null)
                {
                    Line = shape;
                }

                if (background != null)
                {
                    Background = background;
                }
                this.resolution = resolution;
                this.path = path;

                //Need to store 1438 pixel`s coordinates to draw a max scale circle, 1438*4*2 bytes
                this.circleCoords = new byte[11504];

                WriteToByteArray();
            }
            catch (Exception)
            {
                throw;
            }
        }

        protected void SetRandomAttributes()
        {
            int maxScale = (int)Math.Floor((double)resolution / 2) - 1;

            scale = rnd.Next(10, maxScale + 1);

            Background = new Color((byte)rnd.Next(127), (byte)rnd.Next(127), (byte)rnd.Next(127));
            Line = new Color((byte)rnd.Next(127, 256), (byte)rnd.Next(127, 256), (byte)rnd.Next(127, 256));

            int maxPosition = ((resolution / 2) - scale - 1) * 2;

            positionX = rnd.Next(maxPosition + 1);
            positionY = rnd.Next(maxPosition + 1);
        }

        //Stores the circles coordinates in circleCoords
        protected void WriteToByteArray()
        {
            double degreeRadian;
            int x, y;
            int byteIndex = 0;
            byte[] tempCoords;
            int[] lastCoords = new int[2];

            for (double i = 0.0; i < 360.0; i += 0.1)
            {
                degreeRadian = i * Math.PI / 180;

                x = (int)(scale * Math.Cos(degreeRadian));
                y = (int)(scale * Math.Sin(degreeRadian));

                var isSameAsLastCoord = lastCoords[0] == x && lastCoords[1] == y;

                //If the pixel is the same as the last one skips it
                if (!isSameAsLastCoord || i == 0.0)
                {
                    try
                    {
                        tempCoords = BitConverter.GetBytes(x);
                        Buffer.BlockCopy(tempCoords, 0, circleCoords, byteIndex, tempCoords.Length);
                        byteIndex += 4;
                        tempCoords = BitConverter.GetBytes(y);
                        Buffer.BlockCopy(tempCoords, 0, circleCoords, byteIndex, tempCoords.Length);
                        byteIndex += 4;
                        coordCount += 2;

                        lastCoords[0] = x;
                        lastCoords[1] = y;
                    }
                    catch (Exception)
                    {
                        throw;
                    }
                }
            }
        }

        public void DrawToBitmap()
        {
            try
            {
                if (scale >= 100 || scale < 10)
                {
                    throw new Exception("The scale must be between 10 and 99!");
                }

                //Draw background
                FillBitmapBackground(Background);

                int j = 0;
                int calculatedX, calculatedY;
                int lastCoordY = 0;

                //Draw circle
                while (j < coordCount)
                {
                    //Calculates the correct coordinate in our bitmap
                    calculatedX = positionX + ((int)(scale + BitConverter.ToInt32(circleCoords, j * 4)));
                    calculatedY = positionY + ((int)(scale - (BitConverter.ToInt32(circleCoords, (j + 1) * 4))));


                    var isTheTopPixel = calculatedY == positionY;
                    var isTheBottomPixel = calculatedY == (scale * 2 + positionY);
                    var isTheFirstCoord = j == 0;
                    var isOnTheLeftSide = calculatedX < scale + positionX;

                    PlotPixel(calculatedX, calculatedY, Line);

                    j += 2;
                }

                Trace.WriteLine($"\t{CircleCount}. circle done");
                int r, g, b;
                r = Line.r;
                g = Line.g;
                b = Line.b;
                string fileName = $"Circle_{r},{g},{b}_{CircleCount}.png";
                SaveBitmap(fileName);
            }
            catch (Exception)
            {
                throw;
            }
        }

        protected void PlotPixel(int x, int y, Color pixel)
        {
            int stride = resolution * 4;

            imageBuffer[x * 4 + y * stride] = pixel.b;
            imageBuffer[x * 4 + y * stride + 1] = pixel.g;
            imageBuffer[x * 4 + y * stride + 2] = pixel.r;
            imageBuffer[x * 4 + y * stride + 3] = pixel.a;
        }

        protected void SaveBitmap(string fileName)
        {
            unsafe
            {
                fixed (byte* ptr = imageBuffer)
                {
                    using Bitmap image = new(resolution, resolution, resolution * 4, PixelFormat.Format32bppRgb, new IntPtr(ptr));

                    string finalPath = Path.Combine(path, fileName);
                    if (!Directory.Exists(path))
                    {
                        Directory.CreateDirectory(path);
                    }

                    image.Save(finalPath);
                }
            }
        }

        protected void FillBitmapBackground(Color background)
        {
            for (int y = 0; y < resolution; y++)
            {
                for (int x = 0; x < resolution; x++)
                {
                    PlotPixel(x, y, background);
                }
            }
        }
    }
}

internal class Color
{
    internal byte r;
    internal byte g;
    internal byte b;
    internal byte a;

    public Color(byte r, byte g, byte b, byte a = 255)
    {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }
}
