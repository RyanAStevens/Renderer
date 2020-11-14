 #ifndef APPLICATION_H_
 #define APPLICATION_H_

#include <PixelToaster.h>

class Application : public PixelToaster::Listener
{
public:

    Application();
    int run();

protected:

    void onKeyDown( PixelToaster::DisplayInterface & display, PixelToaster::Key key );
    void onKeyPressed( PixelToaster::DisplayInterface & display, PixelToaster::Key key );
    void onKeyUp( PixelToaster::DisplayInterface & display, PixelToaster::Key key );
    void onMouseButtonDown( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse );
    void onMouseButtonUp( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse );
    void onMouseMove( PixelToaster::DisplayInterface & display, PixelToaster::Mouse mouse );
    void onActivate( PixelToaster::DisplayInterface & display, bool active );
    bool onClose( PixelToaster::DisplayInterface & display );

private:
    PixelToaster::Display display;
    bool quit;
};
 
#endif //APPLICATION_H_
