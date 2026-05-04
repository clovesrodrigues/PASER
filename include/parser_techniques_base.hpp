#pragma once

#include "parser_common.hpp"

#include <string>

namespace paser {

class IParserTechnique {
public:
    virtual ~IParserTechnique() = default;

    virtual std::string name() const = 0;
    virtual ParseResult apply(const Sentence& sentence) const = 0;
};

} // namespace paser
