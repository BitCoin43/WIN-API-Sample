#include <windows.h>
#include <wininet.h>
#include <iostream>

#pragma comment(lib, "wininet.lib")

void PostData(const char* url, const char* data)
{
    HINTERNET hInternet, hConnect;
    DWORD dwBytes;

    hInternet = InternetOpen(L"POST Test", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    if (hInternet == NULL) {
        std::cout << "InternetOpen failed (" << GetLastError() << ")\n";
        return;
    }

    hConnect = InternetConnectA(hInternet, url, INTERNET_DEFAULT_HTTP_PORT, NULL,
        NULL, INTERNET_SERVICE_HTTP, 0, 1);

    if (hConnect == NULL) {
        std::cout << "InternetConnect failed (" << GetLastError() << ")\n";
        return;
    }

    HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/",
        NULL, NULL, NULL, 0, 0);

    if (hRequest == NULL) {
        std::cout << "HttpOpenRequest failed (" << GetLastError() << ")\n";
        return;
    }

    BOOL bRequest = HttpSendRequestA(hRequest, NULL, 0, nullptr, 0);

    if (!bRequest) {
        std::cout << "HttpSendRequest failed (" << GetLastError() << ")\n";
        return;
    }

    // Читаем и выводим ответ.
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        std::cout.write(buffer, bytesRead);
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
}

int main() {
    PostData("http://127.0.0.1:5000/main", "");
    return 0;
}