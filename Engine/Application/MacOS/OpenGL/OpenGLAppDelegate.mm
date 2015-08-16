//
//  OpenGLAppDelegate.m
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#import "OpenGLAppDelegate.h"

@implementation OpenGLAppDelegate

- (id)initWithTitle:(NSString*)applicationTitle width:(int)applicationWidth height:(int)applicationHeight
{
    if (self = [super init])
	{
		title = applicationTitle;
		width = applicationWidth;
		height = applicationHeight;

		// create a reference rect
        NSRect contentSize = NSMakeRect(0.0f, 0.0f, width, height);

        // allocate window
        window = [[[MacWindow alloc] initWithContentRect:contentSize
											 styleMask:NSTitledWindowMask
											   backing:NSBackingStoreBuffered
												 defer:YES] autorelease];

        // allocate view
        view = [[[OpenGLView alloc] initWithFrame:contentSize] autorelease];
    }
    return self;
}
/*----------------------------------------------------------------------------*/
- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
	// change window settings
    // attach the view to the window
	[window centerOnScreen];
	[window setTitle:title];
	[window awakeFromNib];
////[window toggleWindowFullscreen:self];
    [window setContentView:view];
	[view setWidth:width];
	[view setHeight:height];
	[view setTitle:title];
	[view awakeFromNib];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	// Implement this.
	//getSettings()->setWidth(applicationWidth);
	//getSettings()->setHeight(applicationHeight);
	//getSettings()->setTitle([applicationTitle UTF8String]);

	initializeMain();

	// Implement this.
	//getRenderer()->setContextObj(cglContext);

    // make the window visible.
    [window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application
{
	return YES;
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	deinitializeMain();
}

@end
