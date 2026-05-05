#include "parser_shift_reduce.hpp"

namespace paser {

ParseResult ShiftReduceTechnique::apply(const Sentence& sentence) const {
    ParseResult result;
    result.sentence = sentence;

    for (std::size_t i = 0; i < sentence.tokens.size(); ++i) {
        if (sentence.tokens[i].upos == "ADP" && i + 1 < sentence.tokens.size()) {
            result.spans.push_back({"PP", i, i + 1, 0.68f, "shift_reduce"});
        }
    }

    result.debug_trace = "ShiftReduceTechnique: PP by ADP + next token";
    return result;
}

} // namespace paser
