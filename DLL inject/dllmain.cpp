#include "pch.h"
#include <windows.h>

// Prototipa��o da fun��o que criar� a janela
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Fun��o que cria e exibe a janela
void CreateMyWindow()
{
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    // Registro da classe da janela
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc; // Fun��o que processar� as mensagens da janela
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Cria��o da janela
    HWND hwnd = CreateWindowEx(
        0,                            // Op��es de estilo
        CLASS_NAME,                   // Nome da classe da janela
        L"Janela Dentro do Jogo",     // T�tulo da janela
        WS_OVERLAPPEDWINDOW,          // Estilo da janela

        // Tamanho e posi��o da janela
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Janela pai
        NULL,       // Menu
        GetModuleHandle(NULL),  // Handle da inst�ncia
        NULL        // Par�metro de cria��o adicional
    );

    if (hwnd == NULL)
    {
        return;
    }

    // Exibe a janela
    ShowWindow(hwnd, SW_SHOW);
}

// Processador de mensagens da janela
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

// Ponto de entrada da DLL
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Chama a fun��o para criar a janela ao injetar a DLL
        CreateMyWindow();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
