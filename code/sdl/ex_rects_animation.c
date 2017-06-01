#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define TRUE 1
#define FALSE 0

#define SQUARE_SIDE_SIZE 200

#define N_RECT 2

int isClickingOnAny(SDL_MouseButtonEvent *bt, SDL_Rect* r)
{
	int i;
	for (i = 0; i < N_RECT; i++)
	{
		if ((bt->x) >= r[i].x && (bt->x) <= r[i].x + r[i].w
			&& (bt->y) >= r[i].y && (bt->y) <= r[i].y + r[i].h)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void move(SDL_Rect *r, int dx, int dy)
{
	r->x += dx;
	r->y += dy;
}

int main()
{
	/* INIT */
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("Ocorreu um erro ao iniciar o SDL!\n");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Animated Rects", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Ocorreu um erro ao iniciar uma janela!\n");
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* EXEC */
	double speed[] = {0.7, 0.3};
	int state[] = {UP, DOWN};
	unsigned long stateDistance[] = {0, 0};
	unsigned long dt, lastTime = SDL_GetTicks();
	SDL_Rect r[] = {{10, 10, 60, 50}, {500, 400, 50, 50}};
	SDL_Event e;
	while (1)
	{
		dt = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
		if (SDL_WaitEventTimeout(&e, 16))
		{
			if (e.type == SDL_QUIT)
				break;

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_MouseButtonEvent *bt = (SDL_MouseButtonEvent *)&e;
				if (isClickingOnAny(bt, r))
					break;
			}
		}

		//Background
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
		SDL_RenderFillRect(renderer, NULL);
		int i;
		for (i = 0; i < N_RECT; i++)
		{
			int dx = (int)round(dt * speed[i] * cos(state[i] * M_PI / 2));
			int dy = (int)round(dt * speed[i] * sin(state[i] * M_PI / 2));
			move(&r[i], dx, dy);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
			stateDistance[i] += dx ? abs(dx) : abs(dy);

			SDL_RenderFillRect(renderer, &r[i]);

			if (stateDistance[i] >= SQUARE_SIDE_SIZE)
			{
				state[i] = (state[i] + 1) % 4;
				stateDistance[i] = 0;
			}
		}

		SDL_RenderPresent(renderer);
	}

	/* FINALIZATION */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
