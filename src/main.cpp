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
           gl.matrix_stack.print_ctm();
           printf("push matrix before draw\n");
           gl.matrix_stack.push_matrix();
           switch( event.key.keysym.sym )
           {
	   	    case SDLK_1:
                    printf("\n\nstack test!!!\n");
                    printf("stack size: %d\n", gl.matrix_stack.size());
                    gl.matrix_stack.print_ctm();
                    printf("push\n");
                    gl.matrix_stack.push_matrix();
                    printf("stack size: %d\n", gl.matrix_stack.size());
                    gl.matrix_stack.print_ctm();
                    printf("rotate x\n");
                    gl.matrix_stack.rotate_x(1.0);
                    gl.matrix_stack.print_ctm();
                    printf("pop\n");
                    gl.matrix_stack.pop_matrix();
                    printf("stack size: %d\n", gl.matrix_stack.size());
                    gl.matrix_stack.print_ctm();

                    printf("push\n");
                    gl.matrix_stack.push_matrix();
                    printf("stack size: %d\n", gl.matrix_stack.size());
                    gl.matrix_stack.print_ctm();
                    printf("rotate y\n");
                    gl.matrix_stack.rotate_y(1.0);
                    gl.matrix_stack.print_ctm();
                    printf("pop\n");
                    gl.matrix_stack.pop_matrix();
                    printf("stack size: %d\n", gl.matrix_stack.size());
                    gl.matrix_stack.print_ctm();
                    printf("\n\nend stack test!!!\n");
	   		    break;
	   	    case SDLK_2:
                printf("circle \n\n\n");
                gl.matrix_stack.print_ctm();
                gl.matrix_stack.scale(0.5, 0.5, 1.0);
                gl.matrix_stack.print_ctm();
	   		    gl.circle();
                gl.matrix_stack.print_ctm();
	   		    break;
	   	    case SDLK_3:
                printf("cube animation\n\n\n");
                gl.matrix_stack.print_ctm();
                gl.matrix_stack.scale(0.5, 0.5, 1.0);
                gl.matrix_stack.print_ctm();
                for(int i = 0; i < 720; i++)
                {
                    gl.matrix_stack.rotate_x(1.0);
                    gl.matrix_stack.rotate_y(1.0);
                    gl.cube();
                    SDL_UpdateTexture(texture, NULL, gl.image, WIDTH  * sizeof(uint32_t));	
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    usleep(25000);
                    gl.clear_image(Color(1.0, 1.0, 1.0));
                }
                gl.matrix_stack.print_ctm();
	   		    break;
	   	    case SDLK_4:
	   		    gl.face();
	   		    break;
	   	    case SDLK_5:
	   		    gl.faces();
	   		    break;
	   	    case SDLK_6:
	   		    gl.persp_initials();
	   		    break;
	   	    case SDLK_7:
	   		    gl.face_test();
	   		    break;
	   	    case SDLK_8:
	   		    gl.ortho_test();
	   		    break;
	   	    case SDLK_9:
	   		    gl.persp_multi_cubes();
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
        printf("pop matrix after draw\n");
        gl.matrix_stack.pop_matrix();

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
