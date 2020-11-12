#include <PixelToaster.h>

class Application : public Listener
{
public:

    Application();
    int run();

protected:

    void onKeyDown( DisplayInterface & display, Key key );
    void onKeyPressed( DisplayInterface & display, Key key );
    void onKeyUp( DisplayInterface & display, Key key );
    void onMouseButtonDown( DisplayInterface & display, Mouse mouse );
    void onMouseButtonUp( DisplayInterface & display, Mouse mouse );
    void onMouseMove( DisplayInterface & display, Mouse mouse );
    void onActivate( DisplayInterface & display, bool active );
    void onClose( DisplayInterface & display );

private:
    Display display;
    bool quit;
};
