#include "GLPGWindow.hpp"
#include "internal/GLPGWindowImpl_Xcb.hpp"

namespace GLPG {
    GLPGWindow* GLPGWindow::_instance = nullptr;
    GLPGWindowImpl* GLPGWindow::_windowImpl = nullptr;

    GLPGWindow::GLPGWindow() {
        _windowImpl = new GLPGWindowImpl_Xcb;
    }

    GLPGWindow::~GLPGWindow() {
        if (_windowImpl) {
            delete _windowImpl;
        }
        if (_instance) {
            delete _instance;
        }
    }

    GLPGWindow* GLPGWindow::GetInstance() {
        if (!_instance) {
            _instance = new GLPGWindow;
        }
        return _instance;
    }

    GLPGWindowImpl* GLPGWindow::GetImplInstance() {
        return _windowImpl;
    }

    bool GLPGWindow::CreateWindow(uint32_t width, uint32_t height) const {
        return _windowImpl->CreateWindowImpl(width, height);
    }

    uint32_t GLPGWindow::GetWindowWidth() const {
        return _windowImpl->GetWidthImpl();
    }

    uint32_t GLPGWindow::GetWindowHeight() const {
        return _windowImpl->GetHeightImpl();
    }

    void* GLPGWindow::GetWindowHandle() {
        return _windowImpl->GetWindowHandle();
    }

} // namespace GLPG
