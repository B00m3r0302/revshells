#include "../listeners/ListenerFactory.h"
#include "../payloads/PayloadFactory.h"
#include "../core/Options.h"
#include <iostream>
#include <string>

Platform stringToPlatform(const std::string& str) {
    if (str == "linux") return Platform::LINUX;
    if (str == "windows") return Platform::WINDOWS;
    if (str == "mac") return Platform::MAC;
    return Platform::LINUX;
}

PayloadType stringToPayloadType(const std::string& str) {
    if (str == "reverse") return PayloadType::REVERSE;
    if (str == "bind") return PayloadType::BIND;
    if (str == "msfvenom") return PayloadType::MSFVENOM;
    if (str == "hoaxshell") return PayloadType::HOAXSHELL;
    return PayloadType::REVERSE;
}

Encoding stringToEncoding(const std::string& str) {
    if (str == "base64") return Encoding::BASE64;
    if (str == "url") return Encoding::URL;
    if (str == "double_url") return Encoding::DOUBLE_URL;
    return Encoding::NONE;
}

void printUsage() {
    std::cout << "Usage: revshells [options]\n"
              << "Options:\n"
              << "  --host <host>          Target host/IP address\n"
              << "  --port <port>          Target port\n"
              << "  --platform <platform>  Target platform (linux, windows, mac)\n"
              << "  --type <type>          Payload type (reverse, bind, msfvenom, hoaxshell)\n"
              << "  --shell <shell>        Shell interpreter (bash, sh, powershell, cmd)\n"
              << "  --encoding <encoding>  Encoding (none, base64, url, double_url)\n"
              << "  --listener <listener>  Listener type\n"
              << "  --list-payloads        List available payloads\n"
              << "  --list-listeners       List available listeners\n"
              << "  --help                 Show this help message\n";
}

int main(int argc, char* argv[]) {
    Options opts;
    bool showHelp = false;
    bool listPayloads = false;
    bool listListeners = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            showHelp = true;
        } else if (arg == "--list-payloads") {
            listPayloads = true;
        } else if (arg == "--list-listeners") {
            listListeners = true;
        } else if (arg == "--host" && i + 1 < argc) {
            opts.host = argv[++i];
        } else if (arg == "--port" && i + 1 < argc) {
            opts.port = std::stoi(argv[++i]);
        } else if (arg == "--platform" && i + 1 < argc) {
            opts.platform = stringToPlatform(argv[++i]);
        } else if (arg == "--type" && i + 1 < argc) {
            opts.payloadType = stringToPayloadType(argv[++i]);
        } else if (arg == "--shell" && i + 1 < argc) {
            opts.interpreter = argv[++i];
        } else if (arg == "--encoding" && i + 1 < argc) {
            opts.encoding = stringToEncoding(argv[++i]);
        } else if (arg == "--listener" && i + 1 < argc) {
            opts.listenerType = argv[++i];
        }
    }
    
    PayloadFactory factory;
    
    if (showHelp) {
        printUsage();
        return 0;
    }
    
    if (listPayloads) {
        auto available = factory.available();
        std::cout << "Available payloads:" << std::endl;
        for (const auto& payload : available) {
            std::cout << "  - " << payload << std::endl;
        }
        return 0;
    }
    
    if (listListeners) {
        ListenerFactory listenerFactory;
        auto listeners = listenerFactory.available();
        std::cout << "Available listeners:" << std::endl;
        for (const auto& listener : listeners) {
            std::cout << "  - " << listener << std::endl;
        }
        return 0;
    }
    
    // Generate payload if host and port are provided
    if (!opts.host.empty() && opts.port > 0) {
        std::string payload = factory.generateByType(opts);
        std::cout << "Payload: " << payload << std::endl;
        
        // Also show listener command
        if (!opts.listenerType.empty()) {
            std::string listener = factory.listener(opts.listenerType, opts);
            std::cout << "Listener: " << listener << std::endl;
        } else {
            std::cout << "Listener: nc -lvnp " << opts.port << std::endl;
        }
    } else {
        std::cout << "RevShells - Reverse Shell Generator\n\n";
        printUsage();
    }
    
    return 0;
}
