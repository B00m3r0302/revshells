#pragma once

#include "../../core/InterfacePayload.h"
#include "../../core/Options.h"
#include <string>

class RustcatPayload : public IPayload {
public:
    std::string name() const override;
    std::string generate(const Options& opts) const override;
    std::string listener(const Options& opts) const override;
};