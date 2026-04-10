#include <SDL.h>
#include <emscripten.h>
#include <graphics_lib.h>
#include <draw_routines.h>
#include <projection.h>
#include <math.h>

#define WIDTH  640
#define HEIGHT 640

enum CameraMode { ORBIT = 0, FPS = 1 };

struct FpsCam {
    float yaw   = 0.0f;
    float pitch = 0.0f;
    float eye_x = 0.0f;
    float eye_y = 0.0f;
    float eye_z = 3.0f;
    bool  w = false, a = false, s = false, d = false;
};

struct AppState {
    SDL_Window*   win;
    SDL_Renderer* sdl_renderer;
    SDL_Texture*  texture;
    GraphicsLib*  gl;
    render_status (*draw_func)(GraphicsLib*);
    CameraMode    cam_mode;
    FpsCam        fps;
};

static AppState app;

static void reset_orbit()
{
    app.gl->initialize();
    app.gl->push_matrix();
    app.gl->scale(0.5f, 0.5f, 0.5f);
    app.gl->set_view(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0));
}

static void apply_fps_camera()
{
    FpsCam& c = app.fps;

    float gaze_x =  cosf(c.pitch) * sinf(c.yaw);
    float gaze_y =  sinf(c.pitch);
    float gaze_z = -cosf(c.pitch) * cosf(c.yaw);
    // right vector is perpendicular to gaze in the XZ plane
    float right_x =  cosf(c.yaw);
    float right_z =  sinf(c.yaw);

    const float speed = 0.05f;
    if (c.w) { c.eye_x += gaze_x * speed; c.eye_y += gaze_y * speed; c.eye_z += gaze_z * speed; }
    if (c.s) { c.eye_x -= gaze_x * speed; c.eye_y -= gaze_y * speed; c.eye_z -= gaze_z * speed; }
    if (c.a) { c.eye_x -= right_x * speed; c.eye_z -= right_z * speed; }
    if (c.d) { c.eye_x += right_x * speed; c.eye_z += right_z * speed; }

    app.gl->set_view(
        Vector3(c.eye_x, c.eye_y, c.eye_z),
        Vector3(gaze_x,  gaze_y,  gaze_z),
        Vector3(0.0f, 1.0f, 0.0f)
    );
}

static void main_loop()
{
    if (app.cam_mode == FPS)
        apply_fps_camera();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // orbit: left-drag rotates the object
        if (app.cam_mode == ORBIT
            && event.type == SDL_MOUSEMOTION
            && (event.motion.state & SDL_BUTTON_LMASK))
        {
            app.gl->rotate_x(event.motion.xrel);
            app.gl->rotate_y(event.motion.yrel);
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_1: app.draw_func = &square;            break;
                case SDLK_2: app.draw_func = &cube;              break;
                case SDLK_3: app.draw_func = &persp_multi_cubes; break;
                case SDLK_4: app.draw_func = &faces;             break;
                case SDLK_5: app.draw_func = &persp_initials;    break;
                case SDLK_p: app.gl->projection->set_projection(PERSPECTIVE);  break;
                case SDLK_o: app.gl->projection->set_projection(ORTHOGRAPHIC); break;
            }
        }
    }

    app.gl->clear_image(Color(1.0, 1.0, 1.0));
    app.draw_func(app.gl);

    SDL_UpdateTexture(app.texture, NULL, app.gl->image, WIDTH * sizeof(uint32_t));
    SDL_RenderClear(app.sdl_renderer);
    SDL_RenderCopy(app.sdl_renderer, app.texture, NULL, NULL);
    SDL_RenderPresent(app.sdl_renderer);
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
void set_scene(int scene)
{
    switch (scene)
    {
        case 1: app.draw_func = &square;            break;
        case 2: app.draw_func = &cube;              break;
        case 3: app.draw_func = &persp_multi_cubes; break;
        case 4: app.draw_func = &faces;             break;
        case 5: app.draw_func = &persp_initials;    break;
    }
}

EMSCRIPTEN_KEEPALIVE
void set_projection(int mode)
{
    if (mode == 0) app.gl->projection->set_projection(ORTHOGRAPHIC);
    else           app.gl->projection->set_projection(PERSPECTIVE);
}

EMSCRIPTEN_KEEPALIVE
void set_camera_mode(int mode)
{
    app.cam_mode = (CameraMode)mode;
    if (mode == FPS)
    {
        app.fps = FpsCam();
    }
    else
    {
        reset_orbit();
    }
}

EMSCRIPTEN_KEEPALIVE
void fps_mouse_move(int dx, int dy)
{
    const float sensitivity = 0.003f;
    app.fps.yaw   += dx * sensitivity;
    app.fps.pitch -= dy * sensitivity;
    if (app.fps.pitch >  1.4f) app.fps.pitch =  1.4f;
    if (app.fps.pitch < -1.4f) app.fps.pitch = -1.4f;
}

// key: 0=W 1=A 2=S 3=D, pressed: 1=down 0=up
EMSCRIPTEN_KEEPALIVE
void fps_key_state(int key, int pressed)
{
    bool p = (bool)pressed;
    switch (key)
    {
        case 0: app.fps.w = p; break;
        case 1: app.fps.a = p; break;
        case 2: app.fps.s = p; break;
        case 3: app.fps.d = p; break;
    }
}

} // extern "C"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    app.win = SDL_CreateWindow(
        "Renderer",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, 0
    );
    app.sdl_renderer = SDL_CreateRenderer(app.win, -1, SDL_RENDERER_ACCELERATED);
    app.texture = SDL_CreateTexture(
        app.sdl_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC,
        WIDTH, HEIGHT
    );

    app.gl = new GraphicsLib(ORTHOGRAPHIC, WIDTH, HEIGHT);
    app.gl->push_matrix();
    app.gl->scale(0.5f, 0.5f, 0.5f);
    app.draw_func = &cube;
    app.cam_mode  = ORBIT;

    emscripten_set_main_loop(main_loop, 0, 1);
    return 0;
}
