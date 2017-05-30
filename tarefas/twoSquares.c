// Falta testar

#include <SDL2/SDL.h>
#include <assert.h>

int main (int argc, char* args[]) {

        /* INITIALIZATION */

	int err = SDL_Init(SDL_INIT_EVERYTHING);
	assert(err == 0);

	SDL_Window* window = SDL_CreateWindow("twoSquares", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	assert(window != NULL);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
        assert(renderer != NULL);

	/* EXECUTION */
	
	SDL_Rect r1 = {10, 90, 50, 50}, r2 = {330, 90, 50, 50};
	SDL_Event e;
	
	int speed1 = 15, speed2 = 10;
	
	while(1) {
	
		SDL_PollEvent(&e);
		
		/* Eventos */
		if(e.type == SDL_QUIT) {
			break;
		}
		if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
			if((me->x >= r1.x) && (me->x <= r1.x + 50) && (me->y >= r1.y) && (me->y <= r1.y + 50)) {
				speed1 = 0;
			}
			else if((me->x >= r2.x) && (me->x <= r2.x + 50) && (me->y >= r2.y) && (me->y <= r2.y + 50)) {
				speed2 = 0;
			}
		}
		
		/* Animações */
		if((r1.x >= 10 && r1.x < 260) && (r1.y == 90 || r1.y == 340)) r1.x += speed1;
		else r1.y += speed1;
		if((r1.x == 10 && r1.y == 90) || (r1.x == 260 && r1.y == 340)) speed1 *= -1;
		
		if((r2.x >= 330 && r2.x < 580) && (r2.y == 90 || r2.y == 340)) r2.x += speed2;
		else r2.y += speed2;
		if((r2.x == 330 && r2.y == 90) || (r2.x == 580 && r2.y == 340)) speed2 *= -1;
		
		/* Redesenho */
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                SDL_RenderFillRect(renderer, NULL);
		
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(renderer, &r1);
		
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0x00);
                SDL_RenderFillRect(renderer, &r2);
        
                SDL_RenderPresent(renderer);
	
	}
	
	/* FINALIZATION */

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
