#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>
 
@interface OpenGLView : NSOpenGLView
{
@private
	CVDisplayLinkRef displayLink;
	int applicationWidth;
	int applicationHeight;
	NSString* applicationTitle;
}

- (void)drawRect:(NSRect)bounds;
- (CVReturn)render;
- (CGLContextObj)willStartDrawing;
- (void)didFinishDrawing:(CGLContextObj) cglContext;
- (void)setWidth:(int) width;
- (void)setHeight:(int) height;
- (void)setTitle:(NSString*) title;

static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink,
									const CVTimeStamp* now,
									const CVTimeStamp* outputTime,
									CVOptionFlags flagsIn,
									CVOptionFlags* flagsOut,
									void* displayLinkContext);

@end
