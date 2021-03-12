#include "rendering.h"
#include "Ray.h"

#define rnd() (float)rand() / (float)RAND_MAX
const int NUMRAYS = 360;
const int NUMSEGS = 10;

class Global {
	public:
	Window w;
	int xres = 800;
	int yres = 800;
	Ray r[NUMRAYS];
	LineSegment l[NUMSEGS];
	Global()
	{
		srand(time(NULL));
		float angle = 1.0f;
		for(int i=0; i<NUMRAYS; i++) {
			r[i].move((float)xres / 2.0f, (float)yres / 2.0f);
			r[i].setAngle(angle);
			angle += 1.0f;
		}
		for(int i=0; i<NUMSEGS; i++) {
			l[i].setCoords(rand() % xres, rand() % yres, rand() % xres, rand() % yres);
		}		
	}

	void draw()
	{
		int scale = 100;
		for(int i=0; i<NUMRAYS; i++) {
			bool intersection = false;
			for(int j=0; j<NUMSEGS; j++) {
				r[i].rayToLineIntersection(l[j]);
			}
			if(r[i].intersectionPt != NULL && r[i].curDist != 0.0f) {
				w.setColor(255, 255, 255, 100);
				w.drawLine(r[i].pos[0], r[i].pos[1], r[i].intersectionPt[0], r[i].intersectionPt[1]);
				w.setColor(255, 0, 0);
				w.fillCircle(r[i].intersectionPt[0], r[i].intersectionPt[1], 10.0f);
				intersection = true;
			} else {
				w.setColor(255, 255, 255);
				w.drawLine(r[i].pos[0], r[i].pos[1], r[i].pos[0] + r[i].dir[0]*scale, r[i].pos[1] + r[i].dir[1]*scale);
			}
			r[i].update();
		}
		w.setColor(0, 0, 255);
		for(int i=0; i<NUMSEGS; i++) {
			w.drawLine(l[i].pt1[0], l[i].pt1[1], l[i].pt2[0], l[i].pt2[1]);
		}
	}
};

Global g;

void checkMouse(SDL_Event);
bool handleInput(SDL_Event);
bool keyboardInput(SDL_Event);
void render();
void physics();

int main()
{
	srand(time(NULL));
	char title[] = {"Ray Casting"};
	(g.w).init(g.xres, g.yres, title);
	bool leave = false;
	while(!leave) {
		SDL_Event e;
		checkMouse(e);
		leave = handleInput(e);
		(g.w).preRender();
		render();
		(g.w).postRender();
		physics();
	}
	return 0;
}

void physics()
{
}

void render()
{
	g.draw();
}

bool keyboardInput(SDL_Event e)
{
	static bool shift_down = false;
	// Key up
	if(e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
			case SDLK_LSHIFT:
				shift_down = false;
				//printf("Shift key released\n");
				break;
		}
	}
	// Handle keyboard input
	switch(e.key.keysym.sym) {
		case SDLK_LSHIFT:
			shift_down = true;
			break;
		case SDLK_ESCAPE:
			return true;
			break;
	}
	return false;
}
void checkMouse(SDL_Event e)
{
	static int mousex, mousey;
	static bool lbutton_down=false, rbutton_down=false;
	if(e.type == SDL_MOUSEMOTION) {
		// Mouse moved
		SDL_GetMouseState(&mousex, &mousey);
		for(int i=0; i<NUMRAYS; i++) {
			g.r[i].move(mousex, mousey);
		}
	}

	if(e.type == SDL_MOUSEBUTTONDOWN) {
		// Mouse click
		if(e.button.button == SDL_BUTTON_LEFT) {
		}
	}

	if(e.type == SDL_MOUSEBUTTONUP) {
		// Button release
		lbutton_down = false;
		rbutton_down = false;
	}
}
bool handleInput(SDL_Event e)
{
	// Handles all events in queue
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT)
			return true;
		else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			if(keyboardInput(e))
				return true;
		// Always check mouse
		checkMouse(e);
	}

	return false;
}

