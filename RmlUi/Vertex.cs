using System.Runtime.InteropServices;

namespace RmlUi;

[StructLayout(LayoutKind.Sequential)]
public readonly struct Vertex
{
    public readonly Vector2f Position;
    public readonly Colourb Colour;
    public readonly Vector2f TexCoord;
}