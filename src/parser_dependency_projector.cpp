#include "parser_dependency_projector.hpp"

namespace paser {

ParseResult DependencyProjectorTechnique::apply(const Sentence& sentence) const {
    ParseResult result;
    result.sentence = sentence;

    for (std::size_t i = 0; i < sentence.tokens.size(); ++i) {
        const auto& tk = sentence.tokens[i];
        if (tk.upos == "VERB" || tk.upos == "AUX") {
            std::size_t begin = i;
            std::size_t end = i;
            if (i + 1 < sentence.tokens.size()) end = i + 1;
            result.spans.push_back({"VP", begin, end, 0.70f, "dependency"});
        }
    }

    result.debug_trace = "DependencyProjectorTechnique: VP seeds by VERB/AUX";
    return result;
}

} // namespace paser
