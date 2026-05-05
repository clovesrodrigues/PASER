#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/frame.h>

class MyFrame1 : public wxFrame {
private:
protected:
    wxTextCtrl* m_textCtrl1;
    wxStaticText* m_staticText1;
    wxFilePickerCtrl* m_filePicker1;
    wxRadioButton* m_radioBtn1;
    wxRadioButton* m_radioBtn2;
    wxRadioButton* m_radioBtn3;
    wxRadioButton* m_radioBtn4;
    wxButton* m_button2;
    wxPanel* m_panel2;

    virtual void texto_entrada(wxCommandEvent& event) { event.Skip(); }
    virtual void file_changed(wxFileDirPickerEvent& event) { event.Skip(); }
    virtual void paser_opt_01(wxCommandEvent& event) { event.Skip(); }
    virtual void paser_opt_02(wxCommandEvent& event) { event.Skip(); }
    virtual void paser_opt_03(wxCommandEvent& event) { event.Skip(); }
    virtual void paser_opt_04(wxCommandEvent& event) { event.Skip(); }
    virtual void entrada_dados(wxCommandEvent& event) { event.Skip(); }

public:
    MyFrame1(wxWindow* parent, wxWindowID id = wxID_ANY,
             const wxString& title = _("ANALISE DE PARSER E SINTAGMAS"),
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxSize(900, 700),
             long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
    ~MyFrame1() override;

    wxTextCtrl* text_input() const { return m_textCtrl1; }
    wxFilePickerCtrl* file_picker() const { return m_filePicker1; }
    wxPanel* result_panel() const { return m_panel2; }
    wxRadioButton* rb1() const { return m_radioBtn1; }
    wxRadioButton* rb2() const { return m_radioBtn2; }
    wxRadioButton* rb3() const { return m_radioBtn3; }
    wxRadioButton* rb4() const { return m_radioBtn4; }
};
