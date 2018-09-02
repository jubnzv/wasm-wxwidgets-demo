#include <stdio.h>

#include "GraphicsEngine.h"

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/glew.h>

class wxGLCanvasSubClass: public wxGLCanvas {
        void Render();
public:
    wxGLCanvasSubClass(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
protected:
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT    (wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame *parent)
:wxGLCanvas(parent, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")){
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)){
    Render();
}

void wxGLCanvasSubClass::Render()
{
    SetCurrent();
    wxPaintDC(this);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    GraphicsEngine engine;
    engine.DisplaySample();

    SwapBuffers();
}

class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  wxT("wxWidgets window"),
        wxPoint(50,50), wxSize(200,200));
    new wxGLCanvasSubClass(frame);

    frame->Show(TRUE);
    return TRUE;
}
