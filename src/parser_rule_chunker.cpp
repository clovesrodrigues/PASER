#include "parser_rule_chunker.hpp"

namespace paser {

ParseResult RuleChunkerTechnique::apply(const Sentence& sentence) const {
    ParseResult result;
    result.sentence = sentence;

    for (std::size_t i = 1; i < sentence.tokens.size(); ++i) {
        const auto& a = sentence.tokens[i - 1];
        const auto& b = sentence.tokens[i];
        if (a.upos == "DET" && (b.upos == "NOUN" || b.upos == "PROPN")) {
            result.spans.push_back({"NP", i - 1, i, 0.75f, "rule"});
        }
    }

    result.debug_trace = "RuleChunkerTechnique: spans by DET+NOUN/PROPN";
    return result;
}

} // namespace paser
