#include "parser_teste.h"

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style) {
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);

    m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                                 wxDefaultSize, wxTE_MULTILINE);
    bSizer2->Add(m_textCtrl1, 0, wxALL | wxEXPAND, 5);

    m_staticText1 = new wxStaticText(this, wxID_ANY,
                                     _("DIGITE O TEXTO PARA ANALISE DE PARSER OU ESCOLHA UM ARQUIVO .TXT"),
                                     wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    m_staticText1->Wrap(-1);
    bSizer2->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    m_filePicker1 = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a file"),
                                         _("*.txt"), wxDefaultPosition, wxDefaultSize,
                                         wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL);
    bSizer2->Add(m_filePicker1, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_radioBtn1 = new wxRadioButton(this, wxID_ANY, _("rule_chunker"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_radioBtn2 = new wxRadioButton(this, wxID_ANY, _("dependency_projector"), wxDefaultPosition, wxDefaultSize, 0);
    m_radioBtn3 = new wxRadioButton(this, wxID_ANY, _("shift_reduce"), wxDefaultPosition, wxDefaultSize, 0);
    m_radioBtn4 = new wxRadioButton(this, wxID_ANY, _("hybrid_rerank"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer4->Add(m_radioBtn1, 0, wxALL, 5);
    bSizer4->Add(m_radioBtn2, 0, wxALL, 5);
    bSizer4->Add(m_radioBtn3, 0, wxALL, 5);
    bSizer4->Add(m_radioBtn4, 0, wxALL, 5);
    bSizer2->Add(bSizer4, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    m_button2 = new wxButton(this, wxID_ANY, _("PROCESSAR DADOS"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer2->Add(m_button2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), wxTAB_TRAVERSAL);
    bSizer2->Add(m_panel2, 1, wxEXPAND | wxALL, 5);

    bSizer1->Add(bSizer2, 1, wxEXPAND, 5);
    this->SetSizer(bSizer1);
    this->Layout();
    this->Centre(wxBOTH);

    m_textCtrl1->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::texto_entrada), NULL, this);
    m_filePicker1->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MyFrame1::file_changed), NULL, this);
    m_radioBtn1->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MyFrame1::paser_opt_01), NULL, this);
    m_radioBtn2->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MyFrame1::paser_opt_02), NULL, this);
    m_radioBtn3->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MyFrame1::paser_opt_03), NULL, this);
    m_radioBtn4->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(MyFrame1::paser_opt_04), NULL, this);
    m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::entrada_dados), NULL, this);
}

MyFrame1::~MyFrame1() {}
