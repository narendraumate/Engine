#include "OpenGLFramework.h"
#include "OpenGLView.h"

#define NSPIXFMT	NSOpenGLPixelFormat
#define NSCTX		NSOpenGLContext

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

	NSPIXFMT *pf = [[NSPIXFMT alloc] initWithAttributes:attrs];

	if (!pf)
	{
		NSLog(@"No OpenGL pixel format");
		[NSApp terminate:self];
	}

	NSCTX* context = [[NSCTX alloc] initWithFormat:pf shareContext:nil];

	[self setPixelFormat:pf];
	[self setOpenGLContext:context];

	[pf release];
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

	OpenGLFramework::initializeOpenGL(cglContext);

	CVDisplayLinkStart(displayLink);
}

- (CGLContextObj)willStartDrawing
{
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLSetCurrentContext(cglContext);
	CGLLockContext(cglContext);
	return cglContext;
}

- (void)didFinishDrawing: (CGLContextObj) cglContext;
{
	CGLUnlockContext(cglContext);
}

- (CVReturn)render
{
	CGLContextObj cglContext = [self willStartDrawing];
	OpenGLFramework::render(cglContext);
	[self didFinishDrawing:cglContext];

	return kCVReturnSuccess;
}

- (void)reshape
{
	CGLContextObj cglContext = [self willStartDrawing];
	[super reshape];
	OpenGLFramework::reshape(cglContext, [self bounds].size.width, [self bounds].size.height);
	[self didFinishDrawing:cglContext];
}

- (void)update
{
	CGLContextObj cglContext = [self willStartDrawing];
	[super update];
	[self didFinishDrawing:cglContext];
}

- (void)dealloc
{
	CVDisplayLinkRelease(displayLink);
	OpenGLFramework::deinitializeOpenGL((CGLContextObj)[[self openGLContext] CGLContextObj]);
	[super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
	[self render];
}

static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink,
const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn,
CVOptionFlags* flagsOut, void* displayLinkContext)
{
	[(OpenGLView*)displayLinkContext render];
	return kCVReturnSuccess;
}

@end
