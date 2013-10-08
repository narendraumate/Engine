#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>
 
@interface OpenGLView : NSOpenGLView
{
@private
	CVDisplayLinkRef displayLink;
	Engine::Renderer* m_renderer;
}

- (CVReturn)render;
- (CGLContextObj)willStartDrawing;
- (void)didFinishDrawing:(CGLContextObj) cglContext;
- (void)setRenderer:(Engine::Renderer*) renderer;

static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink,
									const CVTimeStamp* now,
									const CVTimeStamp* outputTime,
									CVOptionFlags flagsIn,
									CVOptionFlags* flagsOut,
									void* displayLinkContext);

@end
