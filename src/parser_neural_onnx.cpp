#include "parser_neural_onnx.hpp"

namespace paser {

ParseResult NeuralOnnxTechnique::apply(const Sentence& sentence) const {
    ParseResult result;
    result.sentence = sentence;

    // Placeholder: estrutura pronta para encaixar ONNX Runtime real depois.
    for (std::size_t i = 0; i < sentence.tokens.size(); ++i) {
        const auto& tk = sentence.tokens[i];
        if (tk.upos == "NOUN") {
            result.spans.push_back({"NP", i, i, 0.82f, "onnx"});
        }
    }

    result.debug_trace = "NeuralOnnxTechnique: mock scores using model=" + config_.model_path;
    return result;
}

} // namespace paser
