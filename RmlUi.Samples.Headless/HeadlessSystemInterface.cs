using RmlUi.Core;

namespace RmlUi.Samples.Headless;

public class HeadlessSystemInterface : SystemInterface
{
    public override double GetElapsedTime()
    {
        throw new NotImplementedException();
    }

    public override int TranslateString(out string translated, in string input)
    {
        throw new NotImplementedException();
    }

    public override void JoinPath(out string translatedPath, in string documentPath, in string path)
    {
        throw new NotImplementedException();
    }

    public override bool LogMessage(LogType type, in string message)
    {
        throw new NotImplementedException();
    }

    public override void SetMouseCursor(in string cursorName)
    {
        throw new NotImplementedException();
    }

    public override void SetClipboardText(in string text)
    {
        throw new NotImplementedException();
    }

    public override void GetClipboardText(out string text)
    {
        throw new NotImplementedException();
    }

    public override void ActivateKeyboard(float caretPositionX, float caretPositionY, float lineHeight)
    {
        throw new NotImplementedException();
    }

    public override void DeactivateKeyboard()
    {
        throw new NotImplementedException();
    }
}