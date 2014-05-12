#include "../Main.h"

#include <GL/gl.h>
#include <GL/glx.h>

#include <unistd.h> // TODO Remove

static int attributeList[] = { GLX_RGBA, None };

static Bool WaitForNotify(Display *d, XEvent *e, char *arg) {
	return (e->type == MapNotify) && (e->xmap.window == (Window)arg);
}

int main()
{
	char applicationName[] = "Renderer";
	int applicationWidth = 1280;
	int applicationHeight = 720;

	getSettings()->setWidth(applicationWidth);
	getSettings()->setHeight(applicationHeight);
	getSettings()->setTitle(applicationName);

	Display *dpy;
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	Window win;
	GLXContext cx;
	XEvent event;
	/* get a connection */
	dpy = XOpenDisplay(0);
	/* get an appropriate visual */
	vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeList);
	/* create a GLX context */
	cx = glXCreateContext(dpy, vi, 0, GL_FALSE);
	/* create a color map */
	cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen),
	 vi->visual, AllocNone);
	/* create a window */
	swa.colormap = cmap;
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask;
	win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, applicationWidth, applicationHeight,
						0, vi->depth, InputOutput, vi->visual,
						CWBorderPixel|CWColormap|CWEventMask, &swa);
	XMapWindow(dpy, win);
	XIfEvent(dpy, &event, WaitForNotify, (char*)win);
	/* connect the context to the window */
	glXMakeCurrent(dpy, win, cx);

#if defined(WORKING_SAMPLE)
	/* New Loop */
	initializeMain();
	while(runMain());
	deinitializeMain();
#else
	/* Original Loop */
	while (1)
	{
		glClearColor(0.5,0.5,0.5,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
#endif // (WORKING_SAMPLE)

	return 0;
}
