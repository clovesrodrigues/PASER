#pragma once

#include "parser_chart_cky.hpp"
#include "parser_dependency_projector.hpp"
#include "parser_hybrid_rerank.hpp"
#include "parser_neural_onnx.hpp"
#include "parser_rule_chunker.hpp"
#include "parser_shift_reduce.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace paser {

using TechniqueMap = std::unordered_map<std::string, std::shared_ptr<IParserTechnique>>;

TechniqueMap build_default_techniques(const OnnxModelConfig& onnx_cfg);

} // namespace paser
