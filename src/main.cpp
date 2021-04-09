#include <SDL.h>
#include <graphics_lib.h>
#include <draw_routines.h>
#include <projection.h>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 640 

int main(int argc, char *argv[]) 
{
    double rotate_deg = 1080.0;
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

                printf("square\n");
                gl.matrix_stack.push_matrix();
                gl.matrix_stack.get_ctm().print();
                gl.matrix_stack.scale(0.5, 0.5, 1.0);
	   		    square(&gl);
                gl.matrix_stack.pop_matrix();
/*
                for(int i = 3; i <= 34; i++)
                {
                    printf("\n\ncircle with %d steps\n", i);
	   		        gl.circle(i);
                    SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    usleep(50*1000);
                    gl.clear_image(Color(1.0, 1.0, 1.0));
                }
*/
	   		    break;
                /*
	   	    case SDLK_2:
                printf("cube\n");
                gl.matrix_stack.push_matrix();
                gl.matrix_stack.scale(0.2, 0.2, 1.0);
                //gl.cube();
                for(double i = 108.0; i < rotate_deg; i += 1.0)
                {
                    gl.matrix_stack.rotate_x(1.0);
                    gl.matrix_stack.rotate_y(1.0);
                    gl.ortho_cube();
                    //gl.circle(int(30.0*i/rotate_deg));
                    SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    usleep(10*1000);
                    gl.clear_image(Color(1.0, 1.0, 1.0));
                }
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_3:
                printf("draw an orthographic cube\n");
                gl.matrix_stack.push_matrix();
                gl.ortho_cube();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_4:
                printf("face\n");
                gl.matrix_stack.push_matrix();
	   		    gl.face();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_5:
                printf("faces\n");
                gl.matrix_stack.push_matrix();
	   		    gl.faces();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_6:
                printf("persp_initials\n");
                gl.matrix_stack.push_matrix();
	   		    gl.persp_initials();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_7:
                printf("face_test\n");
                gl.matrix_stack.push_matrix();
	   		    gl.face_test();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_8:
                printf("ortho_test\n");
                gl.matrix_stack.push_matrix();
	   		    gl.ortho_test();
                gl.matrix_stack.pop_matrix();
	   		    break;
	   	    case SDLK_9:
                printf("persp_multi_cubes\n");
                gl.matrix_stack.push_matrix();
	   		    gl.persp_multi_cubes();
                gl.matrix_stack.pop_matrix();
	   		    break;
                */
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
