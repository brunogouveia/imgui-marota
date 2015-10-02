#ifdef OCGUI_IMPLEMENTATION__

#include <OCGui/OpenGLCanvas.h>

namespace OCGui
{
    OpenGLCanvas::OpenGLCanvas(std::string&& label, int width, int height):
        Widget(std::move(label)),
        m_drawCallback(NULL),
        m_width(width),
        m_height(height)
    {

    }

    OpenGLCanvas::~OpenGLCanvas() {}

    void OpenGLCanvas::Draw(Vec2&& position, Vec2&& size)
    {
        using namespace ImGui;
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;
        
        ImGuiState& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(m_label.c_str());
        
        ImVec2 pos = window->DC.CursorPos;
        
        const ImRect bb(pos, pos + ImVec2(m_width, m_height));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, &id))
            return;
        
        // Behavior
        const bool hovered = IsHovered(bb, id, true);
        if (hovered)
        {
            g.HoveredId = id;
            if ((!g.IO.KeyCtrl && !g.IO.KeyShift && !g.IO.KeyAlt))
            {
                if (g.IO.MouseClicked[0])
                {
                    SetActiveID(id, window);
                    FocusWindow(window);
                }
            }
        } else if (g.ActiveId == id) {
            if (g.IO.MouseClicked[0])
            {
                SetActiveID(0);
            }
        }
        
        bool held = false;
        if (g.ActiveId == id)
        {
            g.ActiveIdIsFocusedOnly = !g.IO.MouseDown[0];
            if (g.IO.MouseDown[0])
            {
                held = true;
            }
        }
        
        // RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
        Vec2 min = bb.Min;
        Vec2 max = bb.Max;
        //window->DrawList->AddCallback(drawCallback,bound);
        GetDrawCallback()(min, max);

    }
    
    bool OpenGLCanvas::HandleEvents(Vec2&& position, Vec2&& size)
    {
        return false;
    }

} /* OCGui */

#endif
