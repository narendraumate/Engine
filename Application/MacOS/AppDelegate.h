//
//  AppDelegate.h
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#import <Cocoa/Cocoa.h>
#import "OpenGLView.h"
#import "OpenGLWindow.h"

@interface AppDelegate : NSObject
{
	NSString* title;
	int width;
	int height;

	OpenGLWindow* window;
	OpenGLView* view;
}

- (id)initWithTitle:(NSString*)title width:(int)applicationWidth height:(int)applicationHeight;
@end
