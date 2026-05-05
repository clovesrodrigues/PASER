#pragma once

#include "parser_techniques_base.hpp"

#include <memory>
#include <vector>
#include <utility>

namespace paser {

class HybridRerankTechnique final : public IParserTechnique {
public:
    explicit HybridRerankTechnique(std::vector<std::shared_ptr<IParserTechnique>> techniques)
        : techniques_(std::move(techniques)) {}

    std::string name() const override { return "hybrid_rerank"; }
    ParseResult apply(const Sentence& sentence) const override;

private:
    std::vector<std::shared_ptr<IParserTechnique>> techniques_;
};

} // namespace paser
