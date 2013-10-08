#include "MacMain.h"
#include "OpenGLView.h"
#include "../Main.h"

@implementation OpenGLView

- (void)awakeFromNib
{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAOpenGLProfile,
		NSOpenGLProfileVersion3_2Core,
		NSOpenGLPFASupersample,
		NSOpenGLPFASampleBuffers, 1,
		NSOpenGLPFASamples, 32,
		0
	};

	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];

	if (!pixelFormat)
	{
		NSLog(@"No OpenGL pixel format");
		[NSApp terminate:self];
	}

	NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

	[self setPixelFormat:pixelFormat];
	[self setOpenGLContext:context];

	[pixelFormat release];
	[context release];
}

- (void)prepareOpenGL
{
	GLint vsync = 1;
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];

	[[self openGLContext] setValues:&vsync forParameter:NSOpenGLCPSwapInterval];
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	CVDisplayLinkSetOutputCallback(displayLink, &displayLinkCallback, self);
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext,
													  cglPixelFormat);
	initializeMain();	// TODO: Pass Width, Height and ApplicationName
	getRenderer()->setContextObj(cglContext);

	CVDisplayLinkStart(displayLink);
}

- (void)update
{
	CGLContextObj cglContext = [self willStartDrawing];
	[super update];
	[self didFinishDrawing:cglContext];
}

- (void)reshape
{
	CGLContextObj cglContext = [self willStartDrawing];
	[super reshape];

	getRenderer()->resize([self bounds].size.width, [self bounds].size.height);

	[self didFinishDrawing:cglContext];
}

- (void)dealloc
{
	CVDisplayLinkRelease(displayLink);

	deinitializeMain();

	[super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
	[self render];
}
/*----------------------------------------------------------------------------*/
- (CVReturn)render
{
	CGLContextObj cglContext = [self willStartDrawing];

	runMain();

	[self didFinishDrawing:cglContext];
	return kCVReturnSuccess;
}

- (CGLContextObj)willStartDrawing
{
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLSetCurrentContext(cglContext);
	CGLLockContext(cglContext);
	return cglContext;
}

- (void)didFinishDrawing:(CGLContextObj) cglContext
{
	CGLUnlockContext(cglContext);
}
/*----------------------------------------------------------------------------*/
static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink,
									const CVTimeStamp* now,
									const CVTimeStamp* outputTime,
									CVOptionFlags flagsIn,
									CVOptionFlags* flagsOut,
									void* displayLinkContext)
{
	[(OpenGLView*)displayLinkContext render];
	return kCVReturnSuccess;
}

@end
