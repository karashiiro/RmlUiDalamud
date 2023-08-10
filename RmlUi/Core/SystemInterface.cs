using System.Runtime.InteropServices;

namespace RmlUi.Core;

public abstract partial class SystemInterface : IDisposable
{
    private nint _ptr;

    public SystemInterface()
    {
        _ptr = SystemInterfaceShimAlloc(GetElapsedTime, TranslateString, JoinPath, LogMessage, SetMouseCursor,
            SetClipboardText, GetClipboardText, ActivateKeyboard, DeactivateKeyboard);
    }

    public abstract double GetElapsedTime();

    public abstract int TranslateString(out string translated, in string input);

    public abstract void JoinPath(out string translatedPath, in string documentPath, in string path);

    public abstract bool LogMessage(LogType type, in string message);

    public abstract void SetMouseCursor(in string cursorName);

    public abstract void SetClipboardText(in string text);

    public abstract void GetClipboardText(out string text);

    public abstract void ActivateKeyboard(float caretPositionX, float caretPositionY, float lineHeight);

    public abstract void DeactivateKeyboard();

    private void ReleaseUnmanagedResources()
    {
        SystemInterfaceShimFree(_ptr);
        _ptr = IntPtr.Zero;
    }

    public void Dispose()
    {
        ReleaseUnmanagedResources();
        GC.SuppressFinalize(this);
    }

    ~SystemInterface()
    {
        ReleaseUnmanagedResources();
    }

    private delegate double ManagedGetElapsedTime();

    private delegate int ManagedTranslateString([MarshalAs(UnmanagedType.LPStr)] out string translated,
        [MarshalAs(UnmanagedType.LPStr)] in string input);

    private delegate void ManagedJoinPath([MarshalAs(UnmanagedType.LPStr)] out string translatedPath,
        [MarshalAs(UnmanagedType.LPStr)] in string documentPath, [MarshalAs(UnmanagedType.LPStr)] in string path);

    [return: MarshalAs(UnmanagedType.Bool)]
    private delegate bool ManagedLogMessage(LogType type, [MarshalAs(UnmanagedType.LPStr)] in string message);

    private delegate void ManagedSetMouseCursor([MarshalAs(UnmanagedType.LPStr)] in string cursorName);

    private delegate void ManagedSetClipboardText([MarshalAs(UnmanagedType.LPStr)] in string text);

    private delegate void ManagedGetClipboardText([MarshalAs(UnmanagedType.LPStr)] out string text);

    private delegate void ManagedActivateKeyboard(float caretPositionX, float caretPositionY, float lineHeight);

    private delegate void ManagedDeactivateKeyboard();

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "SystemInterfaceShimAlloc")]
    private static partial nint SystemInterfaceShimAlloc(ManagedGetElapsedTime getElapsedTime,
        ManagedTranslateString translateString, ManagedJoinPath joinPath, ManagedLogMessage logMessage,
        ManagedSetMouseCursor setMouseCursor, ManagedSetClipboardText setClipboardText,
        ManagedGetClipboardText getClipboardText, ManagedActivateKeyboard activateKeyboard,
        ManagedDeactivateKeyboard deactivateKeyboard);

    [LibraryImport("RmlUi.Native.dll", EntryPoint = "SystemInterfaceShimFree")]
    private static partial void SystemInterfaceShimFree(nint ptr);
}