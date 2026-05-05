#include "parser_teste.h"

#include "parser_technique_registry.hpp"
#include "udpipe_pipeline.hpp"

#include <fstream>
#include <sstream>

class ParserFrame final : public MyFrame1 {
public:
    ParserFrame() : MyFrame1(nullptr) {
        auto* sizer = new wxBoxSizer(wxVERTICAL);
        result_output_ = new wxTextCtrl(result_panel(), wxID_ANY, wxEmptyString,
                                        wxDefaultPosition, wxDefaultSize,
                                        wxTE_MULTILINE | wxTE_READONLY);
        sizer->Add(result_output_, 1, wxEXPAND | wxALL, 5);
        result_panel()->SetSizer(sizer);
    }

protected:
    void entrada_dados(wxCommandEvent&) override {
        const wxString direct = text_input()->GetValue();
        wxString input = direct;
        if (input.IsEmpty() && !file_picker()->GetPath().IsEmpty()) {
            std::ifstream in(file_picker()->GetPath().ToStdString());
            std::ostringstream ss;
            ss << in.rdbuf();
            input = ss.str();
        }

        paser::UDPipePipeline udpipe({"udpipe/portuguese-bosque-ud-2.5-191206.udpipe"});
        const auto sentence = udpipe.analyze_text(input.ToStdString());

        paser::OnnxModelConfig cfg{"onnx/models/context_classifier.onnx"};
        auto techniques = paser::build_default_techniques(cfg);

        std::string chosen = "rule_chunker";
        if (rb2()->GetValue()) chosen = "dependency_projector";
        else if (rb3()->GetValue()) chosen = "shift_reduce";
        else if (rb4()->GetValue()) chosen = "hybrid_rerank";

        auto it = techniques.find(chosen);
        if (it == techniques.end()) return;

        const auto result = it->second->apply(sentence);
        std::ostringstream out;
        out << "Tecnica: " << chosen << "\n" << result.debug_trace << "\n";
        for (const auto& s : result.spans) {
            out << "[" << s.label << " " << s.begin << "-" << s.end
                << " score=" << s.score << " source=" << s.source << "]\n";
        }
        result_output_->SetValue(out.str());
    }

private:
    wxTextCtrl* result_output_ = nullptr;
};

class ParserApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new ParserFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(ParserApp);
