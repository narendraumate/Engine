//
//  OpenGLView.mm
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#include "MacMain.h"
#include "OpenGLView.h"

@implementation OpenGLView
/*----------------------------------------------------------------------------*/
- (void)setWidth:(int) width
{
	applicationWidth = width;
}

- (void)setHeight:(int) height
{
	applicationHeight = height;
}

- (void)setTitle:(NSString*) title
{
	applicationTitle = title;
}
/*----------------------------------------------------------------------------*/
- (void)awakeFromNib
{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAOpenGLProfile,
		NSOpenGLProfileVersion4_1Core,
		NSOpenGLPFASupersample,
		NSOpenGLPFASampleBuffers, 1,
		NSOpenGLPFASamples, 32,
		0
	};

	NSOpenGLPixelFormat* pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs] autorelease];

	if (!pixelFormat)
	{
		NSLog(@"No OpenGL pixel format");
		[NSApp terminate:self];
	}

	NSOpenGLContext* context = [[[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil] autorelease];

	CGLEnable([context CGLContextObj], kCGLCECrashOnRemovedFunctions);

	[self setPixelFormat:pixelFormat];

	[self setOpenGLContext:context];

	[self setWantsBestResolutionOpenGLSurface:YES];
}

- (void)prepareOpenGL
{
	[super prepareOpenGL];

	GLint vsync = 1;
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];

	[[self openGLContext] setValues:&vsync forParameter:NSOpenGLCPSwapInterval];
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	CVDisplayLinkSetOutputCallback(displayLink, &displayLinkCallback, self);
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
	CVDisplayLinkStart(displayLink);
}

- (void)update
{
	[super update];

	CGLContextObj cglContext = [self willStartDrawing];

	[self didFinishDrawing:cglContext];
}

- (void)reshape
{
	[super reshape];

	CGLContextObj cglContext = [self willStartDrawing];

	// Implement this.
	//if (getRenderer())
	//{
	//	getRenderer()->resize([self bounds].size.width, [self bounds].size.height);
	//}

	[self didFinishDrawing:cglContext];
}

- (void)dealloc
{
	// Stop the display link BEFORE releasing anything in the view
	// otherwise the display link thread may call into the view and crash
	// when it encounters something that has been release
	CVDisplayLinkStop(displayLink);

	CVDisplayLinkRelease(displayLink);

	[super dealloc];
}
/*----------------------------------------------------------------------------*/
- (CVReturn)render
{
	CGLContextObj cglContext = [self willStartDrawing];

	runMain();

	[self didFinishDrawing:cglContext];

	return kCVReturnSuccess;
}

- (void)drawRect:(NSRect)bounds
{
	// Called during resize operations

	// Avoid flickering during resize by drawiing

	[self render];
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
