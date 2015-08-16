//
//  OpenGLAppDelegate.h
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#ifndef OpenGLAppDelegate_h
#define OpenGLAppDelegate_h

#import <Cocoa/Cocoa.h>
#import "OpenGLView.h"
#import "MacWindow.h"

@interface OpenGLAppDelegate : NSObject
{
	NSString* title;
	int width;
	int height;

	MacWindow* window;
	OpenGLView* view;
}

- (id)initWithTitle:(NSString*)applicationTitle width:(int)applicationWidth height:(int)applicationHeight;



@end

#endif /* OpenGLAppDelegate_h */
