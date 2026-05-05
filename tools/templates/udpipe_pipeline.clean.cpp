#include "udpipe_pipeline.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace paser {

static std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

static std::string guess_upos(const std::string& token) {
    const std::string t = to_lower(token);
    if (t == "o" || t == "a" || t == "os" || t == "as" || t == "um" || t == "uma") return "DET";
    if (t == "com" || t == "de" || t == "em" || t == "para" || t == "por") return "ADP";
    if (t == "e" || t == "ou" || t == "mas") return "CCONJ";
    if (t == "foi" || t == "será" || t == "é" || t == "analisou" || t == "venceu" || t == "recebeu") return "VERB";
    if (!t.empty() && std::ispunct(static_cast<unsigned char>(t.back()))) return "PUNCT";
    return "NOUN";
}

Sentence UDPipePipeline::analyze_text(const std::string& text) const {
    (void)config_;
    Sentence sentence;
    std::istringstream iss(text);
    std::string w;
    std::size_t idx = 1;
    while (iss >> w) {
        Token tk;
        tk.id = idx++;
        tk.form = w;
        tk.lemma = to_lower(w);
        tk.upos = guess_upos(w);
        tk.xpos = "_";
        tk.feats = "_";
        tk.head = (tk.id > 1) ? tk.id - 1 : 0;
        tk.deprel = (tk.upos == "VERB") ? "root" : "dep";
        sentence.tokens.push_back(std::move(tk));
    }
    return sentence;
}

} // namespace paser
