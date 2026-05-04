#include "parser_hybrid_rerank.hpp"

namespace paser {

ParseResult HybridRerankTechnique::apply(const Sentence& sentence) const {
    ParseResult best;
    best.sentence = sentence;
    float best_sum = -1.0f;

    for (const auto& t : techniques_) {
        ParseResult current = t->apply(sentence);
        float sum = 0.0f;
        for (const auto& s : current.spans) sum += s.score;
        if (sum > best_sum) {
            best = std::move(current);
            best_sum = sum;
        }
    }

    best.debug_trace += " | HybridRerankTechnique: selected highest score sum";
    return best;
}

} // namespace paser
