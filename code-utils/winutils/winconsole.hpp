#pragma once

#include <windows.h>
#include <string>

namespace g_utils {
    namespace wincutils {
// CONSOLE HANDLE, INTERNAL
        class WinConsole {
        public:
            ~WinConsole() = default;

            static WinConsole & getWinConsole();

            HANDLE & getHandle() { return this->m_HndConsole; }
        
        private:
            WinConsole() {
                this->m_HndConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                if (this->m_HndConsole == INVALID_HANDLE_VALUE) {
                    throw "Invalid Windows handle value.";
                }
                if(!GetConsoleScreenBufferInfo(this->m_HndConsole, &(this->m_ConScrBuffInfo))) {
                    throw "Couldn't load screen buffer info.";
                }
            }
        
        private:
            static WinConsole *WinHndl;

            HANDLE m_HndConsole;
            CONSOLE_SCREEN_BUFFER_INFO m_ConScrBuffInfo;
        };

        WinConsole WinConsole::*WinHndl = nullptr;

        WinConsole & WinConsole::getWinConsole() {
            if (WinConsole::WinHndl == nullptr) {
                WinConsole::WinHndl = new WinConsole();
            }
            return *WinConsole::WinHndl;
        }

// COLORS
        enum class WinColors : WORD {
            BLACK = 0
            , BLUE = 1
            , GREEN = 2
            , CYAN = 3
            , RED = 4
            , PURPLE = 5
            , YELLOW = 6
            , LIGHT_GRAY = 7
            , GRAY = 8
            , LIGHT_BLUE = 9
            , LIGHT_GREEN = 10
            , LIGHT_CYAN = 11
            , LIGHT_RED = 12
            , VIOLET = 13
            , LIGHT_YELLOW = 14
            , WHITE = 15
        };

// CHANGING COLORS
        void SetTextColor(WinColors color) {
            SetConsoleTextAttribute(WinConsole::getWinConsole().getHandle(),
                std::underlying_type<WinColors>::type(color));
        }

        void SetBackgroundColor(WinColors color) {
            SetConsoleTextAttribute(WinConsole::getWinConsole().getHandle(),
                (16 * std::underlying_type<WinColors>::type(color)));
        }
        
        void SetConsoleColor(WinColors foreground, WinColors background) {
            SetConsoleTextAttribute(WinConsole::getWinConsole().getHandle(),
                ((16 * std::underlying_type<WinColors>::type(background))
                + std::underlying_type<WinColors>::type(foreground)));
        }

// CURSOR MANAGEMENT
        class Cursor {
        public:
            void SetCursorPos(int cursor_xpos, int cursor_ypos) {
                SetConsoleCursorPosition(WinConsole::getWinConsole().getHandle(), COORD(cursor_xpos, cursor_ypos));
            }

            void SetDefaultCursorPos(int cursor_xpos, int cursor_ypos) {
                this->m_DefaultCursorPos = COORD(cursor_xpos, cursor_ypos);
            }

            void RestoreCursorPos() {
                SetConsoleCursorPosition(WinConsole::getWinConsole().getHandle(), this->m_DefaultCursorPos);
            }

        private:
            COORD m_DefaultCursorPos;
        };

// KEYBOARD KEY MAPPINGS
        enum class KeyboardKeys {

            // ARROW KEYS
            KEY_ARROW_CHAR = 224
            , KEY_ARROW_UP = 72
            , KEY_ARROW_DOWN = 80
            , KEY_ARROW_LEFT = 75
            , KEY_ARROW_RIGHT = 77
        };
    }
}