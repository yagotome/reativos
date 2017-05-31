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
	
	float speed1 = 2, speed2 = 1;
	int dir1=0, dir2=0, dt = 0, time = SDL_GetTicks();

	while(1) {

		SDL_WaitEventTimeout(&e, 1);
		dt = SDL_GetTicks() - time;
		time = SDL_GetTicks();
		
		/* Eventos */
		if(e.type == SDL_QUIT) {
			/* FINALIZATION */
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 0;
		}
		if(e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
			if((me->x >= r1.x) && (me->x <= r1.x + 50) && (me->y >= r1.y) && (me->y <= r1.y + 50)) {
				speed1 = 0;
			}
			else if((me->x >= r2.x) && (me->x <= r2.x + 50) && (me->y >= r2.y) && (me->y <= r2.y + 50)) {
				speed2 = 0;
			}
			if(speed1 == 0 && speed2 == 0) {
				while(1) {
					SDL_WaitEvent(&e);
					if(e.type == SDL_QUIT) {
						/* FINALIZATION */
						SDL_DestroyWindow(window);
						SDL_Quit();
						return 0;
					}
				}
			}
		}

		/* Animações */
		if(dir1 == 0) {
			r1.x += speed1 * dt;
			if(r1.x > 260) {
				r1.x = 260 ;
				dir1 = 1;
			}
		}
		else if(dir1 == 1) {
			r1.y += speed1 * dt;
			if(r1.y > 340) {
				r1.y = 340;
				dir1 = 2;
			}
		}
		else if(dir1 == 2) {
			r1.x -= speed1 * dt;
			if(r1.x < 10) {
				r1.x = 10;
				dir1 = 3;
			}
		}
		else {
			r1.y -= speed1 * dt;
			if(r1.y < 90) {
				r1.y = 90;
				dir1 = 0;
			}
		}

		if(dir2 == 0) {
			r2.x += speed2 * dt;
			if(r2.x > 580) {
				r2.x = 580;
				dir2 = 1;
			}
		}
		else if(dir2 == 1) {
			r2.y += speed2 * dt;
			if(r2.y > 340) {
				r2.y = 340;
				dir2 = 2;
			}
		}
		else if(dir2 == 2) {
			r2.x -= speed2 * dt;
			if(r2.x < 330) {
				r2.x = 330;
				dir2 = 3;
			}
		}
		else {
			r2.y -= speed2 * dt;
			if(r2.y < 90) {
				r2.y = 90;
				dir2 = 0;
			}
		}
		
		/* Redesenho */
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
		SDL_RenderFillRect(renderer, NULL);
		
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderFillRect(renderer, &r1);
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
		SDL_RenderFillRect(renderer, &r2);
        
		SDL_RenderPresent(renderer);
	
	}
}
