using System.Runtime.InteropServices;

namespace RmlUi;

[StructLayout(LayoutKind.Sequential)]
public readonly struct Colourb
{
    public readonly byte Red;
    public readonly byte Green;
    public readonly byte Blue;
    public readonly byte Alpha;
}