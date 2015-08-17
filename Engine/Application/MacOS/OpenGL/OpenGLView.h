//
//  OpenGLView.h
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#include "../../Main.h"

@interface OpenGLView : NSOpenGLView
{
@private
	CVDisplayLinkRef displayLink;
	int applicationWidth;
	int applicationHeight;
	NSString* applicationTitle;
}

- (void)setWidth:(int) width;
- (void)setHeight:(int) height;
- (void)setTitle:(NSString*) title;

@end
