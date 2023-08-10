#pragma once
#include <RmlUi/Core/SystemInterface.h>

#include "DllUtils.h"

typedef double (*ManagedGetElapsedTime)();
typedef int (*ManagedTranslateString)(char* translated, const char* input);
typedef void (*ManagedJoinPath)(char* translated_path, const char* document_path, const char* path);
typedef bool (*ManagedLogMessage)(int type, const char* message);
typedef void (*ManagedSetMouseCursor)(const char* cursor_name);
typedef void (*ManagedSetClipboardText)(const char* text);
typedef void (*ManagedGetClipboardText)(char* text);
typedef void (*ManagedActivateKeyboard)(float caret_position_x, float caret_position_y, float line_height);
typedef void (*ManagedDeactivateKeyboard)();

class SystemInterfaceShim : public Rml::SystemInterface
{
public:
    SystemInterfaceShim(const ManagedGetElapsedTime get_elapsed_time, const ManagedTranslateString translate_string,
                        const ManagedJoinPath join_path, const ManagedLogMessage log_message,
                        const ManagedSetMouseCursor set_mouse_cursor, const ManagedSetClipboardText set_clipboard_text,
                        const ManagedGetClipboardText get_clipboard_text,
                        const ManagedActivateKeyboard activate_keyboard,
                        const ManagedDeactivateKeyboard deactivate_keyboard)
    {
        this->get_elapsed_time = get_elapsed_time;
        this->translate_string = translate_string;
        this->join_path = join_path;
        this->log_message = log_message;
        this->set_mouse_cursor = set_mouse_cursor;
        this->set_clipboard_text = set_clipboard_text;
        this->get_clipboard_text = get_clipboard_text;
        this->activate_keyboard = activate_keyboard;
        this->deactivate_keyboard = deactivate_keyboard;
    }

    double GetElapsedTime() override
    {
        return get_elapsed_time();
    }

    int TranslateString(Rml::String& translated, const Rml::String& input) override
    {
        // TODO: out std::string?
        return translate_string(nullptr, input.c_str());
    }

    void JoinPath(Rml::String& translated_path, const Rml::String& document_path, const Rml::String& path) override
    {
        // TODO: out std::string?
        join_path(nullptr, document_path.c_str(), path.c_str());
    }

    bool LogMessage(const Rml::Log::Type type, const Rml::String& message) override
    {
        return log_message(type, message.c_str());
    }

    void SetMouseCursor(const Rml::String& cursor_name) override
    {
        set_mouse_cursor(cursor_name.c_str());
    }

    void GetClipboardText(Rml::String& text) override
    {
        // TODO: out std::string?
        get_clipboard_text(nullptr);
    }

    void ActivateKeyboard(const Rml::Vector2f caret_position, const float line_height) override
    {
        activate_keyboard(caret_position.x, caret_position.y, line_height);
    }

    void DeactivateKeyboard() override
    {
        deactivate_keyboard();
    }

private:
    ManagedGetElapsedTime get_elapsed_time;
    ManagedTranslateString translate_string;
    ManagedJoinPath join_path;
    ManagedLogMessage log_message;
    ManagedSetMouseCursor set_mouse_cursor;
    ManagedSetClipboardText set_clipboard_text;
    ManagedGetClipboardText get_clipboard_text;
    ManagedActivateKeyboard activate_keyboard;
    ManagedDeactivateKeyboard deactivate_keyboard;
};

extern "C" {
inline DllExport SystemInterfaceShim* SystemInterfaceShimAlloc(const ManagedGetElapsedTime get_elapsed_time,
                                                               const ManagedTranslateString translate_string,
                                                               const ManagedJoinPath join_path,
                                                               const ManagedLogMessage log_message,
                                                               const ManagedSetMouseCursor set_mouse_cursor,
                                                               const ManagedSetClipboardText set_clipboard_text,
                                                               const ManagedGetClipboardText get_clipboard_text,
                                                               const ManagedActivateKeyboard activate_keyboard,
                                                               const ManagedDeactivateKeyboard deactivate_keyboard)
{
    return new SystemInterfaceShim(get_elapsed_time, translate_string, join_path, log_message, set_mouse_cursor,
                                   set_clipboard_text, get_clipboard_text, activate_keyboard, deactivate_keyboard);
}

inline DllExport void SystemInterfaceShimFree(const SystemInterfaceShim* instance)
{
    delete instance;
}
}
