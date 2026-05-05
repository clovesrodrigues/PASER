#pragma once

#include "parser_techniques_base.hpp"

namespace paser {

class DependencyProjectorTechnique final : public IParserTechnique {
public:
    std::string name() const override { return "dependency_projector"; }
    ParseResult apply(const Sentence& sentence) const override;
};

} // namespace paser
