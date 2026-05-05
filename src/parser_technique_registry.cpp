#include "parser_technique_registry.hpp"

namespace paser {

TechniqueMap build_default_techniques(const OnnxModelConfig& onnx_cfg) {
    TechniqueMap out;

    auto rule = std::make_shared<RuleChunkerTechnique>();
    auto dep = std::make_shared<DependencyProjectorTechnique>();
    auto cky = std::make_shared<ChartCKYTechnique>();
    auto sr = std::make_shared<ShiftReduceTechnique>();
    auto nn = std::make_shared<NeuralOnnxTechnique>(onnx_cfg);

    out.emplace(rule->name(), rule);
    out.emplace(dep->name(), dep);
    out.emplace(cky->name(), cky);
    out.emplace(sr->name(), sr);
    out.emplace(nn->name(), nn);

    std::vector<std::shared_ptr<IParserTechnique>> techniques{rule, dep, cky, sr, nn};
    auto hybrid = std::make_shared<HybridRerankTechnique>(techniques);
    out.emplace(hybrid->name(), hybrid);

    return out;
}

} // namespace paser
