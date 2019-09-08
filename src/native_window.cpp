#include "native_window.hpp"

using namespace glpg;
nativeWindow::nativeWindow(uint32_t w, uint32_t h)
{
    windowWidth = w;
    windowHeight = h;
}

bool nativeWindow::createNativeWindow()
{
    bool ret;
#ifdef __linux__
    ret = createNativeXcbWindow();
#elif defined _WIN32
    ret = createNativeWin32Window();
#endif
    if (!ret) {
        std::cout << "Failed to create Native Window" << std::endl;
        return false;
    }
    return true;
}

#ifdef __linux__
bool nativeWindow::createNativeXcbWindow()
{
    xcbConnection = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(xcbConnection)) {
        std::cout << "Failed to create XCB Connection" << std::endl;
        return false;
    }
    xcbScreen = xcb_setup_roots_iterator(xcb_get_setup(xcbConnection)).data;
    xcbWindow = xcb_generate_id(xcbConnection);

    xcb_create_window(xcbConnection, XCB_COPY_FROM_PARENT, xcbWindow,
                      xcbScreen->root, 0, 0, windowWidth, windowHeight,
                      10, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      xcbScreen->root_visual, 0, NULL);
    xcb_map_window(xcbConnection, xcbWindow);
    xcb_flush(xcbConnection);

    return true;
}

xcb_window_t nativeWindow::getNativeHandle() const
{
    return xcbWindow;
}
#elif defined _WIN32

HDC nativeWindow::getNativeHandle() const
{
    return (GetDC(hWindow));
}

static LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
	{
	case WM_CREATE:
	break;

	case WM_CLOSE:
		OutputDebugString("Closing the Window");
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
bool nativeWindow::createNativeWin32Window()
{
    hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = windowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Window Class";
    wc.style = CS_OWNDC;

    if (!RegisterClass(&wc)) {
        std::cout << "Failed to register Window Class for Win32 Window" << std::endl;
        return false;
    }

    hWindow = CreateWindow("Window Class", "Test", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           0, 0, 800, 600, 0, 0, hInstance, 0);
    return true;
}
#endif
