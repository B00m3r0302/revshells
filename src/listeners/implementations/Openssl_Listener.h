#pragma once
#include "../../core/InterfaceListener.h"

class Openssl : public IListener {
public:
  std::string name() const override { return "openssl"; }
  std::string command(const Options &o) const override {
    return "openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem "
           "-days 30 -nodes; openssl s_server -quiet -key key.pem -cert "
           "cert.pem -port " +
           std::to_string(o.port);
  }
};
