 #ifndef APPLICATION_H_
 #define APPLICATION_H_

#include <PixelToaster.h>
#include <drawlib.h>

class DrawLib;

class Application : public PixelToaster::Listener
{
public:

    DrawLib* dl;
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
    
    void circle();
    void square();
    void cube();
    void face();
    void faces();
    void persp_initials();
    void face_test();
    void ortho_test();
    void ortho_test_scale();
    void ortho_test_rotate();
    void ortho_cube();
    void ortho_cube2();
    void persp_cube();
    void persp_multi_cubes();
    

private:
    PixelToaster::Display display;
    bool quit;
};
 
#endif //APPLICATION_H_
