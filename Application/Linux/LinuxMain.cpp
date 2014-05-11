#include "../Main.h"

#include <GL/gl.h>
#include <GL/glx.h>

Window createWindow( Display *dpy, GLXContext *ctx, unsigned int width, unsigned int height )
{
	int attrib[] = { GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		GLX_DOUBLEBUFFER,
		None };
	int scrnum;
	XSetWindowAttributes attr;
	unsigned long mask;
	Window root;
	Window win;
	XVisualInfo *visinfo;

	//printf("DefaultScreen\n");
	scrnum = DefaultScreen( dpy );
	//printf("RootWindow\n");
	root = RootWindow( dpy, scrnum );

	//printf("glXChooseVisual\n");
	visinfo = glXChooseVisual( dpy, scrnum, attrib );
	if (!visinfo) {
		//printf("Error: couldn't get an RGB, Double-buffered visual\n");
		//exit(1);
		return win;
	}

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	//printf("XCreateColormap\n");
	attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	//printf("XCreateWindow\n");
	win = XCreateWindow( dpy, root, 0, 0, width, height,
						0, visinfo->depth, InputOutput,
						visinfo->visual, mask, &attr );

	//printf("glXCreateContext\n");
	*ctx = glXCreateContext( dpy, visinfo, NULL, True );
	if (!(*ctx)) {
		//printf("Error: glXCreateContext failed\n");
		//exit(1);
		return win;
	}

	//printf("glXMakeCurrent\n");
	glXMakeCurrent( dpy, win, *ctx );

	return win;
}

int main( int argc, char *argv[] )
{
	char applicationName[] = "Renderer";
	int applicationWidth = 1280;
	int applicationHeight = 720;

	getSettings()->setWidth(applicationWidth);
	getSettings()->setHeight(applicationHeight);
	getSettings()->setTitle(applicationName);

	Display *dpy;
	GLXContext ctx;
	Window win;

	//printf("XOpenDisplay\n");
	dpy = XOpenDisplay(NULL);

	win = createWindow( dpy, &ctx, applicationWidth, applicationHeight );

	initializeMain();

	getRenderer()->setContextObj(ctx);

	XMapWindow( dpy, win );

	while(runMain());

	deinitializeMain();

	return 0;
}
