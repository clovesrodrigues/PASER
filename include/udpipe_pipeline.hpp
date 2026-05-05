#pragma once

#include "parser_common.hpp"

#include <string>
#include <utility>

namespace paser {

struct UDPipeConfig {
    std::string model_path; // ex.: udpipe/portuguese-bosque-ud-2.5-191206.udpipe
};

class UDPipePipeline {
public:
    explicit UDPipePipeline(UDPipeConfig config) : config_(std::move(config)) {}

    Sentence analyze_text(const std::string& text) const;
    const UDPipeConfig& config() const { return config_; }

private:
    UDPipeConfig config_;
};

} // namespace paser
