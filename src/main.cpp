#include <SDL.h>
#include <graphics_lib.h>
#include <projection.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 640 

int main(int argc, char *argv[]) 
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100;
    
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
	
    while (!quit)
	{
        SDL_WaitEvent(&event);

	    if(SDL_KEYDOWN == event.type)
	    {
           gl.clear_image(Color(1.0, 1.0, 1.0));
           switch( event.key.keysym.sym )
           {
	   	    case SDLK_1:
	   		    printf("DRAW SQUARE !!!!! Before\n");
	   		    gl.square();
	   		    printf("DRAW SQUARE !!!!! After\n");
	   		    break;
	   	    case SDLK_2:
	   		    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nDRAW CIRCLE!!!!! Before\n");
	   		    gl.circle();
	   		    printf("DRAW CIRCLE!!!!! After\n");
	   		    break;
	   	    case SDLK_3:
	   		    printf("DRAW CUBE\n");

            gl.matrix_stack.push_matrix();
            gl.matrix_stack.scale(0.5, 0.5, 1.0);
            for(int i = 0; i < 720; i++)
            {
                printf("i=%d\n", i);
                gl.matrix_stack.rotate_x(1.0);
                gl.matrix_stack.rotate_y(1.0);
	   		    gl.cube();
	   		    //gl.circle();
                SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                usleep(25000);
                gl.clear_image(Color(1.0, 1.0, 1.0));
            }
            gl.matrix_stack.pop_matrix();
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

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}
