#include <iostream>
#include <string>
#include <Windows.h>

std::string executeCommand(const std::string& command) {
    std::string output;
    HANDLE hReadPipe, hWritePipe;

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        return "";
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.hStdInput = nullptr;
    si.hStdOutput = hWritePipe;
    si.hStdError = hWritePipe;
    si.dwFlags |= STARTF_USESTDHANDLES;

    if (!CreateProcessA(nullptr, const_cast<char*>(command.c_str()), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        return "";
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(hWritePipe);

    CHAR buffer[4096];
    DWORD bytesRead;
    while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
        if (bytesRead == 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        output += buffer;
    }

    CloseHandle(hReadPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return output;
}

int main() {
    std::string command = "cd /d Z:/internet\\ shop\\ 2.0 && node server";
    std::string output = executeCommand(command);

    std::cout << "Command output: " << output << std::endl;

    return 0;
}
