using System.Numerics;
using System.Runtime.InteropServices;

namespace RmlUi;

[StructLayout(LayoutKind.Sequential)]
public readonly struct Vector2f
{
    public readonly float X;
    public readonly float Y;

    public Vector2f()
    {
    }

    public Vector2f(float x, float y)
    {
        X = x;
        Y = y;
    }

    public static implicit operator Vector2(Vector2f self) => new(self.X, self.Y);

    public static implicit operator Vector2f(Vector2 other) => new(other.X, other.Y);
}