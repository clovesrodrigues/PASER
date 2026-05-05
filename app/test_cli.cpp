#include "parser_technique_registry.hpp"
#include "udpipe_pipeline.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

static std::string default_text() {
    return "O pesquisador analisou os dados com cuidado.";
}

static std::string load_text(int argc, char** argv) {
    if (argc > 1) {
        std::ifstream in(argv[1]);
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

    std::cout << "Digite o texto e finalize com CTRL+D (Linux/macOS) ou CTRL+Z (Windows).\n";
    std::cout << "Digite o texto e finalize com CTRL+D:\n";
    std::ostringstream ss;
    ss << std::cin.rdbuf();
    return ss.str();
}

int main(int argc, char** argv) {
    std::string text = load_text(argc, argv);
    if (text.empty()) {
        text = default_text();
        std::cout << "[INFO] Nenhum texto recebido. Usando texto padrão:\n" << text << "\n\n";
    }
    const std::string text = load_text(argc, argv);

    paser::UDPipePipeline udpipe({"udpipe/portuguese-bosque-ud-2.5-191206.udpipe"});
    auto sentence = udpipe.analyze_text(text);

    if (sentence.tokens.empty()) {
        std::cerr << "[ERRO] Não foi possível tokenizar o texto.\n";
        return 1;
    }

    std::cout << "Tokens (simulação UDPipe atual):\n";
    for (const auto& tk : sentence.tokens) {
        std::cout << tk.id << "\t" << tk.form << "\tUPOS=" << tk.upos
                  << "\tHEAD=" << tk.head << "\tDEPREL=" << tk.deprel << "\n";
    }

    paser::OnnxModelConfig onnx_cfg{"onnx/models/context_classifier.onnx"};
    auto techniques = paser::build_default_techniques(onnx_cfg);

    std::cout << "\nResumo de técnicas disponíveis: " << techniques.size() << "\n";
    paser::OnnxModelConfig onnx_cfg{"onnx/models/context_classifier.onnx"};
    auto techniques = paser::build_default_techniques(onnx_cfg);

    for (const auto& [name, technique] : techniques) {
        auto result = technique->apply(sentence);
        std::cout << "\n=== Technique: " << name << " ===\n";
        std::cout << result.debug_trace << "\n";
        if (result.spans.empty()) {
            std::cout << "(sem spans para esta técnica)\n";
        }
        for (const auto& span : result.spans) {
            std::cout << "[" << span.label << " " << span.begin << "-" << span.end
                      << " score=" << span.score << " source=" << span.source << "]\n";
        }
    }

    return 0;
}
