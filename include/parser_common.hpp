#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace paser {

struct Token {
    std::size_t id{};
    std::string form;
    std::string lemma;
    std::string upos;
    std::string xpos;
    std::string feats;
    std::size_t head{};
    std::string deprel;
};

struct Sentence {
    std::vector<Token> tokens;
};

struct SyntagmSpan {
    std::string label;      // NP, VP, PP, ADJP, ADVP, CP...
    std::size_t begin{};    // token index inclusive
    std::size_t end{};      // token index inclusive
    float score{};          // confidence score
    std::string source;     // rule|onnx|hybrid
};

struct ParseResult {
    Sentence sentence;
    std::vector<SyntagmSpan> spans;
    std::string debug_trace;
};

} // namespace paser
