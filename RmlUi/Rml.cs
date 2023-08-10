using System.Runtime.InteropServices;
using RmlUi.Core;

namespace RmlUi;

public static partial class Rml
{
    public static void Initialise() => RmlInitialise();

    public static void Shutdown() => RmlShutdown();

    public static void SetSystemInterface(SystemInterface systemInterface) =>
        RmlSetSystemInterface((nint)systemInterface);

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "RmlInitialise")]
    private static partial void RmlInitialise();

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "RmlShutdown")]
    private static partial void RmlShutdown();

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "RmlSetSystemInterface")]
    private static partial void RmlSetSystemInterface(nint ptr);
}