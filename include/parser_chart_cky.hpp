#pragma once

#include "parser_techniques_base.hpp"

namespace paser {

class ChartCKYTechnique final : public IParserTechnique {
public:
    std::string name() const override { return "chart_cky"; }
    ParseResult apply(const Sentence& sentence) const override;
};

} // namespace paser
