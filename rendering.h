#ifndef RENDERING_H
#define RENDERING_H
#include <SDL2/SDL.h>

class Window {
	private:
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_Renderer* rend;
	int xres;
	int yres;
	//SDL_Texture* message[NUM_PARTICLES];
	SDL_Event e;
	
	public:
	inline Window()
	{
		window = NULL;
		screen_surface = NULL;
		rend = NULL;
		//for(int i=0; i<NUM_PARTICLES; i++)
		//        message[i] = NULL;
	}
	inline ~Window()
	{
		SDL_FreeSurface(screen_surface);
		SDL_DestroyWindow(window);
		SDL_Quit();
		printf("Successful exit\n");
	}
	inline int init(int xres, int yres, char title[])
	{
		this->xres = xres;
		this->yres = yres;
		if(SDL_Init(SDL_INIT_VIDEO) == -1) {
			printf("ERROR SDL_INIT: %s\n", SDL_GetError());
			return 1;
		}

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				xres, yres, SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("ERROR DISPLAYING WINDOW: %s\n", SDL_GetError());
			return 1;
		}

		rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(rend == NULL) {
			printf("ERROR RENDERER: %s\n", SDL_GetError());
			return 1;
		}
		//TTF_Init();

		return 0;
	}
	inline void setColor(int r, int g, int b, int a=255)
	{
		SDL_SetRenderDrawColor(rend, r, g, b, a);
	}
	inline void preRender()
	{
		setColor(0, 0, 0);
		SDL_RenderClear(rend);
	}
	inline void postRender()
	{
		// Show renderer
		SDL_RenderPresent(rend);
	}
	// Drawing functions
	inline void drawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(rend, x1, y1, x2, y2);
	}
	inline void drawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(rend, x, y);
	}
	inline void drawRect(int x, int y, int w, int h)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderDrawRect(rend, &rect);
	}
	inline void fillRect(int x, int y, int w, int h)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		SDL_RenderFillRect(rend, &rect);
	}
	inline void drawArc(int xc, int yc, int x, int y) 
	{ 
		drawPoint(xc+x, yc+y); 
		drawPoint(xc-x, yc+y); 
		drawPoint(xc+x, yc-y); 
		drawPoint(xc-x, yc-y); 
		drawPoint(xc+y, yc+x); 
		drawPoint(xc-y, yc+x); 
		drawPoint(xc+y, yc-x); 
		drawPoint(xc-y, yc-x); 
	}
	inline void drawCircle(int xc, int yc, int r) 
	{ 
		int x = 0, y = r; 
		int d = 3 - 2 * r; 
		drawArc(xc, yc, x, y); 
		while (y >= x) { 
			// for each pixel we will 
			// draw all eight pixels 
			  
			x++; 

			// check for decision parameter 
			// and correspondingly  
			// update d, x, y 
			if (d > 0) { 
			    y--;  
			    d = d + 4 * (x - y) + 10; 
			} 
			else
			    d = d + 4 * x + 6; 
			drawArc(xc, yc, x, y); 
		} 
	}
	inline void fillArc(int xc, int yc, int x, int y) 
	{ 
		drawLine(xc+x, yc+y, xc-x, yc+y); 
		drawLine(xc+x, yc-y, xc-x, yc-y); 
		drawLine(xc+y, yc+x, xc-y, yc+x); 
		drawLine(xc+y, yc-x, xc-y, yc-x); 
	}
	inline void fillCircle(int xc, int yc, int r) 
	{ 
		int x = 0, y = r; 
		int d = 3 - 2 * r; 
		fillArc(xc, yc, x, y); 
		while (y >= x) { 
			// for each pixel we will 
			// draw all eight pixels 
			  
			x++; 

			// check for decision parameter 
			// and correspondingly  
			// update d, x, y 
			if (d > 0) { 
			    y--;  
			    d = d + 4 * (x - y) + 10; 
			} 
			else
			    d = d + 4 * x + 6; 
			fillArc(xc, yc, x, y); 
		} 
	}

	/*
	   void drawText(int x, int y, int w, int h, const char* mes, int size, int i)
	   {
	   int extra = strlen(mes);
	   if(message[i] == NULL) {
	   TTF_Font* Sans = TTF_OpenFont("./Roboto-Black.ttf", size+extra);
	   if(Sans == NULL) {
	   printf("ERROR FONT: %s\n", SDL_GetError());
	   return;
	   }
	   SDL_Color BLACK = {0,0,0};
	   SDL_Surface* surface = TTF_RenderText_Solid(Sans, mes, BLACK);
	   message[i] = SDL_CreateTextureFromSurface(rend, surface);
	   SDL_FreeSurface(surface);
	   }
	   SDL_Rect Message_rect;
	   Message_rect.x = x+extra;
	   Message_rect.y = y+extra;
	   Message_rect.w = w+extra;
	   Message_rect.h = h;
	   SDL_RenderCopy(rend, message[i], NULL, &Message_rect);
	   }
	   */
};

#endif
