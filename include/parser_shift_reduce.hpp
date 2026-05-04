#pragma once

#include "parser_techniques_base.hpp"

namespace paser {

class ShiftReduceTechnique final : public IParserTechnique {
public:
    std::string name() const override { return "shift_reduce"; }
    ParseResult apply(const Sentence& sentence) const override;
};

} // namespace paser
