#pragma once

#include "../core/InterfacePayload.h"
#include "../core/Options.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class PayloadFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
    
    // Platform-specific generators
    std::string generateLinuxPayload(const Options& opts) const;
    std::string generateWindowsPayload(const Options& opts) const;
    std::string generateMacPayload(const Options& opts) const;
    
    // Encoding utilities
    std::string base64Encode(const std::string& input) const;
    std::string urlEncode(const std::string& input) const;
    std::string doubleUrlEncode(const std::string& input) const;
    
    // Apply encoding based on options
    std::string applyEncoding(const std::string& payload, const Options& opts) const;

public:
    PayloadFactory();
    
    // Main factory methods
    std::vector<std::string> available() const;
    std::string generate(const std::string& type, const Options& opts) const;
    std::string listener(const std::string& type, const Options& opts) const;
    
    // Generate by platform and type
    std::string generateByType(const Options& opts) const;
    
    // Get supported options
    std::vector<std::string> getSupportedShells() const;
    std::vector<std::string> getSupportedEncodings() const;
};