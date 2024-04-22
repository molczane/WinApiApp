#include <windows.h>
#include <shellapi.h>
#include <string>
#include <unordered_map>

#define WM_TRAYICON (WM_USER + 1)
#define MY_TRAY_ICON_ID 1001

#define WM_TRAY_ICON (WM_USER + 1)

static std::unordered_map<int, std::wstring> _keyMap = {
    {VK_BACK, L"BACKSPACE"},
    {VK_TAB, L"TAB"},
    {VK_RETURN, L"ENTER"},
    {VK_SHIFT, L"SHIFT"},
    {VK_CONTROL, L"CTRL"},
    {VK_MENU, L"ALT"},
    {VK_PAUSE, L"PAUSE"},
    {VK_CAPITAL, L"CAPS LOCK"},
    {VK_ESCAPE, L"ESC"},
    {VK_SPACE, L"SPACE"},
    {VK_PRIOR, L"PAGE UP"},
    {VK_NEXT, L"PAGE DOWN"},
    {VK_END, L"END"},
    {VK_HOME, L"HOME"},
    {VK_LEFT, L"LEFT ARROW"},
    {VK_UP, L"UP ARROW"},
    {VK_RIGHT, L"RIGHT ARROW"},
    {VK_DOWN, L"DOWN ARROW"},
    {VK_SELECT, L"SELECT"},
    {VK_PRINT, L"PRINT"},
    {VK_EXECUTE, L"EXECUTE"},
    {VK_SNAPSHOT, L"PRINT SCREEN"},
    {VK_INSERT, L"INSERT"},
    {VK_DELETE, L"DELETE"},
    {VK_HELP, L"HELP"},
    {VK_LWIN, L"LEFT WINDOWS"},
    {VK_RWIN, L"RIGHT WINDOWS"},
    {VK_APPS, L"APPLICATION"},
    {VK_SLEEP, L"SLEEP"},
    {VK_NUMPAD0, L"NUMPAD 0"},
    {VK_NUMPAD1, L"NUMPAD 1"},
    {VK_NUMPAD2, L"NUMPAD 2"},
    {VK_NUMPAD3, L"NUMPAD 3"},
    {VK_NUMPAD4, L"NUMPAD 4"},
    {VK_NUMPAD5, L"NUMPAD 5"},
    {VK_NUMPAD6, L"NUMPAD 6"},
    {VK_NUMPAD7, L"NUMPAD 7"},
    {VK_NUMPAD8, L"NUMPAD 8"},
    {VK_NUMPAD9, L"NUMPAD 9"},
    {VK_MULTIPLY, L"*"},
    {VK_ADD, L"+"},
    {VK_SEPARATOR, L"SEPARATOR"},
    {VK_SUBTRACT, L"-"},
    {VK_DECIMAL, L"."},
    {VK_DIVIDE, L"/"},
    {VK_F1, L"F1"},
    {VK_F2, L"F2"},
    {VK_F3, L"F3"},
    {VK_F4, L"F4"},
    {VK_F5, L"F5"},
    {VK_F6, L"F6"},
    {VK_F7, L"F7"},
    {VK_F8, L"F8"},
    {VK_F9, L"F9"},
    {VK_F10, L"F10"},
    {VK_F11, L"F11"},
    {VK_F12, L"F12"},
    {VK_NUMLOCK, L"NUM LOCK"},
    {VK_SCROLL, L"SCROLL LOCK"},
    {VK_LSHIFT, L"LEFT SHIFT"},
    {VK_RSHIFT, L"RIGHT SHIFT"},
    {VK_LCONTROL, L"LEFT CTRL"},
    {VK_RCONTROL, L"RIGHT CTRL"},
    {VK_LMENU, L"LEFT ALT"},
    {VK_RMENU, L"RIGHT ALT"},
    {VK_BROWSER_BACK, L"BROWSER BACK"},
    {VK_BROWSER_FORWARD, L"BROWSER FORWARD"},
    {VK_BROWSER_REFRESH, L"BROWSER REFRESH"},
    {VK_BROWSER_STOP, L"BROWSER STOP"},
    {VK_BROWSER_SEARCH, L"BROWSER SEARCH"},
    {VK_BROWSER_FAVORITES, L"BROWSER FAVORITES"},
    {VK_BROWSER_HOME, L"BROWSER HOME"},
    {VK_VOLUME_MUTE, L"VOLUME MUTE"},
    {VK_VOLUME_DOWN, L"VOLUME DOWN"},
    {VK_VOLUME_UP, L"VOLUME UP"},
    {VK_MEDIA_NEXT_TRACK, L"NEXT TRACK"},
    {VK_MEDIA_PREV_TRACK, L"PREVIOUS TRACK"},
    {VK_MEDIA_STOP, L"STOP"},
    {VK_MEDIA_PLAY_PAUSE, L"PLAY/PAUSE"},
    {VK_LAUNCH_MAIL, L"LAUNCH MAIL"},
    {VK_LAUNCH_MEDIA_SELECT, L"LAUNCH MEDIA SELECT"},
    {VK_LAUNCH_APP1, L"LAUNCH APP1"},
    {VK_LAUNCH_APP2, L"LAUNCH APP2"},
    {0x41, L"A LETTER"},
    {0x42, L"B LETTER"},
    {0x43, L"C LETTER"},
    {0x44, L"D LETTER"},
    {0x45, L"E LETTER"},
    {0x46, L"F LETTER"},
    {0x47, L"G LETTER"},
    {0x48, L"H LETTER"},
    {0x49, L"I LETTER"},
    {0x4A, L"J LETTER"},
    {0x4B, L"K LETTER"},
    {0x4C, L"L LETTER"},
    {0x4D, L"M LETTER"},
    {0x4E, L"N LETTER"},
    {0x4F, L"O LETTER"},
    {0x50, L"P LETTER"},
    {0x51, L"Q LETTER"},
    {0x52, L"R LETTER"},
    {0x53, L"S LETTER"},
    {0x54, L"T LETTER"},
    {0x55, L"U LETTER"},
    {0x56, L"V LETTER"},
    {0x57, L"W LETTER"},
    {0x58, L"X LETTER"},
    {0x59, L"Y LETTER"},
    {0x5A, L"Z LETTER"}
};

COLORREF customColors[16];

CHOOSECOLOR cc;

HFONT hFont;

#define ID_TURNOFFON_CIRCLE 303
#define ID_PICK_COLOR 301
#define ID_TURNOFF_APP 302
#define ID_HIDE 304
#define ID_SHOW 305
#define ID_SHOW_KEYS 306

NOTIFYICONDATA g_notifyIconData;

const int TIMER_ID = 7;
const int TIMER_INTERVAL = 2;

int CircleRadius = 50;
int CircleRadiusOld = 51;
const int TIMER_CIRCLE_ID = 10;
const int TIMER_HELP_ID = 11;
int TIMER_CIRCLE_INTERVAL = 20;
int isCircleTimerSet = 1;
int showKeys = 1;

HMENU hPopupMenu;

int keyCount = 0;
std::wstring tabOfKeys[5];
const int TIMER_KEY_IDS[5] = { 101, 102, 103, 104, 105 };
int keyTimeleftS[5] = { 5000, 5000, 5000, 5000, 5000 };
const int TIMER_KEY_INTERVAL = 20;

std::wstring Help1 = L"Ctrl + P - pick color";
std::wstring Help2 = L"Ctrl + shift + 4 - turn off";
std::wstring Help3 = L"Ctrl + O - hide help";

HHOOK g_hKeyboardHook = NULL;
HWND g_hwndDisplay = NULL;

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {

    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKbStruct = (KBDLLHOOKSTRUCT*)lParam;
        // Obsługa zdarzenia klawiatury
        if (wParam == WM_KEYDOWN) {
            int keyCode = pKbStruct->vkCode;
            std::wstring keyName;

            // Sprawdź, czy istnieje mapowanie dla danego kodu klawisza
            auto it = _keyMap.find(keyCode);
            if (it != _keyMap.end()) {
                keyName = it->second;
            }
            else {
                // Jeśli nie ma mapowania, użyj domyślnej wartości
                keyName = L"UNKNOWN";
            }

            tabOfKeys[keyCount % 5] = keyName;
            if (showKeys == 1)
                SetTimer(g_hwndDisplay, TIMER_KEY_IDS[keyCount++ % 5], TIMER_KEY_INTERVAL, NULL);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Procedura okna
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {
        g_notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
        g_notifyIconData.hWnd = hwnd;
        g_notifyIconData.uID = MY_TRAY_ICON_ID;
        g_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        g_notifyIconData.uCallbackMessage = WM_USER + 1; // Definiowanie niestandardowego komunikatu
        g_notifyIconData.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        lstrcpyn(g_notifyIconData.szTip, TEXT("TEST"),
            sizeof(g_notifyIconData.szTip) / sizeof(g_notifyIconData.szTip[0])); // Tekst wyświetlany po najechaniu myszą na ikonę
        // Dodanie ikony do zasobnika systemowego
        Shell_NotifyIcon(NIM_ADD, &g_notifyIconData);
        hPopupMenu = CreatePopupMenu();
        AppendMenu(hPopupMenu, MF_STRING, 1, L"&Exit");
        AppendMenu(hPopupMenu, MF_STRING, 2, L"&Open config file");
        AppendMenu(hPopupMenu, MF_STRING, 3, L"&Reload config");
        AppendMenu(hPopupMenu, MF_STRING, 4, L"&Pick color");
        // kolor
        ZeroMemory(&cc, sizeof(CHOOSECOLOR)); // Wyzerowanie całej struktury
        cc.lStructSize = sizeof(CHOOSECOLOR); // Ustawienie rozmiaru struktury
        cc.hwndOwner = hwnd; // Ustawienie uchwytu okna właściciela, w którym ma być wyświetlone okno dialogowe
        cc.lpCustColors = customColors;
        cc.rgbResult = RGB(255, 255, 0); // Opcjonalnie, ustawienie domyślnego koloru wyświetlanego w oknie dialogowym
        cc.Flags = CC_FULLOPEN | CC_RGBINIT; // Ustawienie flag, w tym przypadku pełne otwarcie okna dialogowego i inicjalizacja koloru RGB
        // Ustawienie przezroczystości
        hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
        SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
        SetTimer(hwnd, TIMER_CIRCLE_ID, TIMER_CIRCLE_INTERVAL, NULL);
        SetTimer(hwnd, TIMER_HELP_ID, TIMER_CIRCLE_INTERVAL, NULL);
        SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 100, LWA_COLORKEY | LWA_ALPHA);
        RegisterHotKey(hwnd, ID_TURNOFFON_CIRCLE, MOD_CONTROL | MOD_SHIFT, 'S');
        RegisterHotKey(hwnd, ID_TURNOFF_APP, MOD_CONTROL | MOD_SHIFT, '4');
        RegisterHotKey(hwnd, ID_SHOW_KEYS, MOD_CONTROL | MOD_SHIFT, 'L');
        RegisterHotKey(hwnd, ID_HIDE, MOD_CONTROL, 'O');
        RegisterHotKey(hwnd, ID_SHOW, MOD_CONTROL, 'Y');
        RegisterHotKey(hwnd, ID_PICK_COLOR, MOD_CONTROL, 'P');
        
    }
        break;
    case WM_TIMER: {
        if(wParam == TIMER_ID)
            InvalidateRect(hwnd, NULL, TRUE);
        if (wParam == TIMER_CIRCLE_ID)
        {
            if (CircleRadius > 25 && CircleRadiusOld - CircleRadius > 0)
            {
                CircleRadiusOld--;
                CircleRadius--;
            }
            if (CircleRadius < 50 && CircleRadius - CircleRadiusOld > 0)
            {
                CircleRadiusOld++;
                CircleRadius++;
            }
            if (CircleRadius == 50)
            {
                CircleRadiusOld = 51;
            }
            if (CircleRadius == 25)
            {
                CircleRadiusOld = 24;
            }
                
        }
        if (wParam == TIMER_HELP_ID)
        {
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = 100; // Dolny róg
            rect.top = 0;
            rect.right = 200; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie

            DrawText(hdc, Help1.c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            rect.bottom -= 20;
            DrawText(hdc, Help2.c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            rect.bottom -= 20;
            DrawText(hdc, Help3.c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół


            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        if (wParam == TIMER_KEY_IDS[0])
        {
            //if (showKeys == 1)
                if(keyTimeleftS[0] > 5)
                    keyTimeleftS[0] -= 100; 
                else
                {
                    keyTimeleftS[0] = 5000;
                    KillTimer(hwnd, TIMER_KEY_IDS[0]);
                }
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = rect.bottom - 20; // Dolny róg
            rect.top = rect.bottom - 20;
            rect.right = 100; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie
            DrawText(hdc, tabOfKeys[0].c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół

            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        if (wParam == TIMER_KEY_IDS[1])
        {
            //if (showKeys == 1)
                if (keyTimeleftS[1] > 5)
                    keyTimeleftS[1] -= 100;
                else
                {
                    keyTimeleftS[1] = 5000;
                    KillTimer(hwnd, TIMER_KEY_IDS[1]);
                }
            
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = rect.bottom - 40; // Dolny róg
            rect.top = rect.bottom - 20;
            rect.right = 100; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie
            DrawText(hdc, tabOfKeys[1].c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            

            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        if (wParam == TIMER_KEY_IDS[2])
        {
            //if (showKeys == 1)
                if (keyTimeleftS[2] > 5)
                    keyTimeleftS[2] -= 100;
                else
                {
                    keyTimeleftS[2] = 5000;
                    KillTimer(hwnd, TIMER_KEY_IDS[2]);
                }
            
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = rect.bottom - 60; // Dolny róg
            rect.top = rect.bottom - 20;
            rect.right = 100; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie
            DrawText(hdc, tabOfKeys[2].c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            

            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        if (wParam == TIMER_KEY_IDS[3])
        {
            //if (showKeys == 1)
                if (keyTimeleftS[3] > 5)
                    keyTimeleftS[3] -= 100;
                else
                {
                    keyTimeleftS[3] = 5000;
                    KillTimer(hwnd, TIMER_KEY_IDS[3]);
                }
            //InvalidateRect(hwnd, NULL, TRUE);
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = rect.bottom - 80; // Dolny róg
            rect.top = rect.bottom - 20;
            rect.right = 100; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie
            DrawText(hdc, tabOfKeys[3].c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            

            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        if (wParam == TIMER_KEY_IDS[4])
        {
            //if (showKeys == 1)
                if (keyTimeleftS[4] > 5)
                    keyTimeleftS[4] -= 100;
                else
                {
                    keyTimeleftS[4] = 5000;
                    KillTimer(hwnd, TIMER_KEY_IDS[4]);
                }
            //InvalidateRect(hwnd, NULL, TRUE);
            HDC hdc = GetDC(NULL); // Pobierz uchwyt do kontekstu urządzenia całego ekranu
            SetTextColor(hdc, RGB(255, 255, 255)); // Ustaw kolor tekstu
            SetBkMode(hdc, TRANSPARENT); // Ustaw tryb tła na transparentny

            // Wybierz odpowiednią czcionkę
            
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // Określ położenie i rozmiar obszaru, na którym ma być narysowany tekst (lewy dolny róg)
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.left = 0; // Lewy róg
            rect.bottom = rect.bottom - 100; // Dolny róg
            rect.top = rect.bottom - 20;
            rect.right = 100; // Prawy róg (możesz zmienić to w zależności od potrzeb)

            FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            // Narysuj tekst na ekranie
            DrawText(hdc, tabOfKeys[4].c_str(), -1, &rect, DT_SINGLELINE | DT_LEFT | DT_BOTTOM); // Wyśrodkuj tekst na lewo i na dół
            

            // Zwolnij zasoby
            SelectObject(hdc, hOldFont);
            ReleaseDC(NULL, hdc); // Zwolnij kontekst urządzenia
        }
        break;
    }
    case WM_PAINT:
    {
        POINT cursosPos;
        GetCursorPos(&cursosPos);

        // Oblicz współrzędne koła (np. środek w miejscu myszki)
        int circleX = cursosPos.x;
        int circleY = cursosPos.y;

        RECT rect;

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, WhiteBrush);
        DeleteObject(WhiteBrush);

        HBRUSH YellowBrush = CreateSolidBrush(cc.rgbResult);
        HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, YellowBrush);
        
        Ellipse(hdc, circleX - CircleRadius, circleY - CircleRadius, circleX + CircleRadius, circleY + CircleRadius);
        SelectObject(hdc, OldBrush);
        DeleteObject(YellowBrush);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_COMMAND: {
        // Obsługa kliknięć w menu kontekstowe
        switch (LOWORD(wParam)) {
        case 1:
            Shell_NotifyIcon(NIM_DELETE, &g_notifyIconData);
            // Zakończenie aplikacji po zamknięciu okna
            PostQuitMessage(0);
            break;
        case 2: {
            HINSTANCE result = ShellExecute(NULL, L"edit", L"config.ini", NULL, NULL, SW_SHOWNORMAL);
            break;
        }
        case 3:
        {
            UINT Circle, R, G, B;
            INT _default = 0;
            // Retrieve the value from the INI file
            Circle = GetPrivateProfileInt(L"Circle", L"Speed", _default, L"./config.ini");
            R = GetPrivateProfileInt(L"Circle", L"R", _default, L"./config.ini");
            G = GetPrivateProfileInt(L"Circle", L"G", _default, L"./config.ini");
            B = GetPrivateProfileInt(L"Circle", L"B", _default, L"./config.ini");

            
            TIMER_CIRCLE_INTERVAL = Circle;
            KillTimer(hwnd, TIMER_CIRCLE_ID);
            SetTimer(hwnd, TIMER_CIRCLE_ID, TIMER_CIRCLE_INTERVAL, NULL);
            cc.rgbResult = RGB(R, G, B);
            
        }
        break;
        case 4:
            if (ChooseColor(&cc)) { // Wywołanie funkcji ChooseColor
                // Pobranie wybranego koloru
                COLORREF color = cc.rgbResult;
                // Tutaj możesz wykonać operacje na wybranym kolorze
            }
            break;
        }
        break;
    }
    case WM_TRAY_ICON: {
        // Obsługa zdarzeń z ikoną w zasobniku systemowym
        switch (lParam) {
        case WM_RBUTTONDOWN: {
            // Wyświetlenie menu kontekstowego na kliknięcie prawym przyciskiem myszy na ikonie
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(hwnd); // Upewnij się, że okno jest na pierwszym planie
            TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
            break;
        }
        }
        break;
    }
    case WM_HOTKEY: {
        // Obsługa zdarzenia skrótu klawiszowego
        int idHotkey = wParam;
        switch (idHotkey) {
        case ID_TURNOFFON_CIRCLE:
            // Wykonaj akcję po naciśnięciu skrótu klawiszowego Ctrl+Shift+S
            if (isCircleTimerSet == 1)
            {
                KillTimer(hwnd, TIMER_CIRCLE_ID);
                CircleRadius = 50;
                isCircleTimerSet = 0;
            }
            else
            {
                SetTimer(hwnd, TIMER_CIRCLE_ID, TIMER_CIRCLE_INTERVAL, NULL);
                isCircleTimerSet = 1;
            }
            break;
        case ID_SHOW:
        {
            SetTimer(hwnd, TIMER_HELP_ID, TIMER_CIRCLE_INTERVAL, NULL);
            break;
        }
        case ID_HIDE:
        {
            KillTimer(hwnd, TIMER_HELP_ID);
            break;
        }
        case ID_SHOW_KEYS:
        {
            if (showKeys == 1)
                showKeys = 0;
            else 
                showKeys = 1;
            break;
        }
        case ID_PICK_COLOR:
            if (ChooseColor(&cc)) { // Wywołanie funkcji ChooseColor
                // Pobranie wybranego koloru
                COLORREF color = cc.rgbResult;
                // Tutaj możesz wykonać operacje na wybranym kolorze
            }
            break;
        case ID_TURNOFF_APP :
        {
            Shell_NotifyIcon(NIM_DELETE, &g_notifyIconData);
            // Zakończenie aplikacji po zamknięciu okna
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;
        }
        default:
            break;
        }
        break;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_NCHITTEST: // Przechwytywanie zdarzenia kliknięcia myszą
        return HTTRANSPARENT; // Przekazanie kliknięcia do okien znajdujących się pod przezroczystym oknem
    case WM_DESTROY:
        // Usunięcie ikony z zasobnika systemowego przed zamknięciem aplikacji
        Shell_NotifyIcon(NIM_DELETE, &g_notifyIconData);
        // Zakończenie aplikacji po zamknięciu okna
        DeleteObject(hFont);
        PostQuitMessage(0);
        break;
    default:
        // Domyślna procedura obsługi komunikatów
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Rejestrowanie klasy okna
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"TransparentWindow";
    RegisterClass(&wc);

    // Tworzenie okna
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_TRANSPARENT, // Style rozszerzone
        L"TransparentWindow",                             // Nazwa klasy okna
        NULL,                                             // Tytuł okna
        WS_POPUP,                                         // Style okna
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), // Wymiary okna (pełny ekran)
        NULL, NULL, hInstance, NULL);
   
    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, hInstance, 0);
    if (!g_hKeyboardHook) {
        MessageBox(NULL, L"Failed to install keyboard hook.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    g_hwndDisplay = hwnd;

    // Wyświetlanie okna
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);


    // Pętla główna komunikatów
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

