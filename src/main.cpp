#include <SDL.h>
#include <graphics_lib.h>
#include <draw_routines.h>
#include <projection.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 640 

int main(int argc, char *argv[]) 
{
    double rotate_deg = 400.0;
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100;
    enum render_status (*draw_func_p)(GraphicsLib *gl_p) = &square;
    
    SDL_Event event;
    bool quit = false;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello, there!!!", posX, posY, WIDTH, HEIGHT, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //make the window black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 

    //create Graphics Library object
    GraphicsLib gl = GraphicsLib(ORTHOGRAPHIC, WIDTH, HEIGHT);
	
    gl.push_matrix();
    gl.scale(0.5, 0.5, 0.5);

    while (!quit)
	{
        SDL_WaitEvent(&event);
        
        gl.clear_image(Color(1.0, 1.0, 1.0));
       
        if(SDL_MOUSEMOTION == event.type)
        {
                printf("mouse @ %d,%d\n", event.motion.xrel, event.motion.yrel);
                gl.rotate_x(event.motion.xrel);
                gl.rotate_y(event.motion.yrel);
                draw_func_p(&gl);
        }
	    else if(SDL_KEYDOWN == event.type)
	    {
           switch( event.key.keysym.sym )
           {
            case SDLK_1:
	   		    draw_func_p = &square;
	   		    break;
	   	    case SDLK_2:
	   		    draw_func_p = &persp_multi_cubes;
	   		    break;
	   	    case SDLK_3:
	   		    draw_func_p = &face;
	   		    break;
	   	    case SDLK_4:
	   		    draw_func_p = &faces;
	   		    break;
	   	    case SDLK_5:
	   		    draw_func_p = &persp_initials;
	   		    break;
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
	   	    




/*
            case SDLK_1:

                printf("square\n");
                gl.print_ctm();
                gl.push_matrix();
                gl.scale(0.5, 0.5, 1.0);
	   		    square(&gl);
                gl.print_ctm();
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;
	   	    case SDLK_2:
                printf("cube anime\n");
                gl.print_ctm();
                gl.push_matrix();
                gl.scale(0.5, 0.5, 0.5);
                for(double i = 100.0; i < rotate_deg; i += 1.0)
                {
                    gl.rotate_x(1.0);
                    gl.rotate_y(1.0);
                    persp_multi_cubes(&gl);
                    SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    usleep(10*1000);
                    gl.clear_image(Color(1.0, 1.0, 1.0));
                }
                gl.print_ctm();
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;
	   	    case SDLK_3:
                printf("face\n");
                gl.push_matrix();
	   		    face(&gl);
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;
	   	    case SDLK_4:
                printf("faces\n");
                gl.push_matrix();
	   		    faces(&gl);
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;
	   	    case SDLK_5:
                printf("persp_initials\n");
                gl.push_matrix();
	   		    persp_initials(&gl);
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;
	   	    case SDLK_6:
                printf("persp_multi_cubes\n");
                gl.push_matrix();
	   		    persp_multi_cubes(&gl);
                gl.pop_matrix();
                gl.print_ctm();
	   		    break;

            */
