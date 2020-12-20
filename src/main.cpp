#include <SDL.h>
#include <graphics_lib.h>
#include <projection.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[]) {
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100;
    
    SDL_Event event;
    bool quit = false;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello, There!!!", posX, posY, WIDTH, HEIGHT, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //make the window black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT); 

    //create Graphics Library object
    GraphicsLib gl = GraphicsLib(PERSPECTIVE, WIDTH, HEIGHT);

    gl.set_background_color(Color(0, 0, 255));
	
	while (!quit)

	 {
	     SDL_WaitEvent(&event);

	     if(SDL_KEYDOWN == event.type)
	     {
            switch( event.key.keysym.sym )
            {
			    case SDLK_1:
				    printf("onKeyDown calling ortho_test\n");
				    gl.ortho_test();
				    break;
			    case SDLK_2:
				    printf("onKeyDown calling ortho_test_scale\n");
				    gl.ortho_test_scale();
				    break;
			    case SDLK_3:
				    printf("onKeyDown calling ortho_test_rotate\n");
				    gl.ortho_test_rotate();
				    break;
			    case SDLK_4:
				    printf("onKeyDown calling face_test\n");
				    gl.face_test();
				    break;
			    case SDLK_5: 
				    printf("onKeyDown calling faces\n");
				    gl.faces();
				    break;
			    case SDLK_6:
				    printf("onKeyDown calling ortho_cube\n");
				    gl.ortho_cube();
				    break;
			    case SDLK_7:
				    printf("onKeyDown calling ortho_cube2\n");
				    gl.ortho_cube2();
				    break;
			    case SDLK_8:
				    printf("onKeyDown calling persp_cube\n");
				    gl.persp_cube();
				    break;
			    case SDLK_9:
				    printf("onKeyDown calling persp_multi_cubes\n");
				    gl.persp_multi_cubes();
				    break;
			    case SDLK_0:
				    printf("onKeyDown calling persp_initials\n");
				    gl.persp_initials();
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
