#pragma once

#include "parser_techniques_base.hpp"

#include <string>
#include <vector>
#include <utility>

namespace paser {

struct OnnxModelConfig {
    std::string model_path;
    std::string input_name{"features"};
    std::string output_name{"logits"};
    std::size_t embedding_size{256};
};

class NeuralOnnxTechnique final : public IParserTechnique {
public:
    explicit NeuralOnnxTechnique(OnnxModelConfig config) : config_(std::move(config)) {}

    std::string name() const override { return "neural_onnx"; }
    ParseResult apply(const Sentence& sentence) const override;

    const OnnxModelConfig& config() const { return config_; }

private:
    OnnxModelConfig config_;
};

} // namespace paser
