#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>
 
@interface OpenGLView : NSOpenGLView
{
@private
	CVDisplayLinkRef displayLink;
	Engine::Renderer* m_renderer;
}

- (void)setRenderer:(Engine::Renderer*) renderer;

@end
