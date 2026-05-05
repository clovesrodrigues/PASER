#include "parser_chart_cky.hpp"

namespace paser {

ParseResult ChartCKYTechnique::apply(const Sentence& sentence) const {
    ParseResult result;
    result.sentence = sentence;

    if (!sentence.tokens.empty()) {
        result.spans.push_back({"CP", 0, sentence.tokens.size() - 1, 0.60f, "chart"});
    }

    result.debug_trace = "ChartCKYTechnique: placeholder full-span CP";
    return result;
}

} // namespace paser
