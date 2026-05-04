#pragma once

#include "parser_techniques_base.hpp"

namespace paser {

class RuleChunkerTechnique final : public IParserTechnique {
public:
    std::string name() const override { return "rule_chunker"; }
    ParseResult apply(const Sentence& sentence) const override;
};

} // namespace paser
