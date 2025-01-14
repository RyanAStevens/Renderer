#include <SDL.h>
#include <graphics_lib.h>
#include <draw_routines.h>
#include <projection.h>
#ifdef _WIN32
#include <Windows.h>
#endif

#define WIDTH 640
#define HEIGHT 640 

int main(int argc, char *argv[]) 
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100;
    enum render_status (*draw_func_p)(GraphicsLib *gl_p) = &cube;
    
    SDL_Event event;
    bool quit = false;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello, SUPER FARTS!!!", posX, posY, WIDTH, HEIGHT, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 

    GraphicsLib gl = GraphicsLib(ORTHOGRAPHIC, WIDTH, HEIGHT);
   // GraphicsLib gl = GraphicsLib(PERSPECTIVE, WIDTH, HEIGHT);
	
    gl.push_matrix();
    gl.scale(0.5, 0.5, 0.5);
    while (!quit)
	{
        SDL_WaitEvent(&event);
        
        gl.clear_image(Color(1.0, 1.0, 1.0));
       
        draw_func_p(&gl);
        if(SDL_MOUSEMOTION == event.type)
        {
                gl.rotate_x(event.motion.xrel);
                gl.rotate_y(event.motion.yrel);
        }
	    if(SDL_KEYDOWN == event.type)
	    {
           switch( event.key.keysym.sym )
           {
            case SDLK_1:
	   		    draw_func_p = &square;
	   		    break;
	   	    case SDLK_2:
	   		    draw_func_p = &cube;
	   		    break;
	   	    case SDLK_3:
	   		    draw_func_p = &persp_multi_cubes;
	   		    break;
	   	    case SDLK_4:
	   		    draw_func_p = &faces;
	   		    break;
	   	    case SDLK_5:
	   		    draw_func_p = &persp_initials;
	   		    break;
	   	    case SDLK_p:
                gl.projection->set_projection(PERSPECTIVE);
	   		    break;
	   	    case SDLK_o:
                gl.projection->set_projection(ORTHOGRAPHIC);
	   		    break;
	   	    case SDLK_ESCAPE:
	   		    quit = true;
	   		    break;
	   	    case SDL_QUIT:
	   		    quit = true;
	   		    break;
           	default:
               	printf("key not recognized: %d\n", event.key.keysym.sym);
	     	}
	   }
       SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
       SDL_RenderClear(renderer);
       SDL_RenderCopy(renderer, texture, NULL, NULL);
       SDL_RenderPresent(renderer);
	}
    
    gl.pop_matrix();

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}
