//
//  AppDelegate.m
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#import "AppDelegate.h"

@implementation AppDelegate

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
        window = [[OpenGLWindow alloc] initWithContentRect:contentSize
											 styleMask:NSTitledWindowMask
											   backing:NSBackingStoreBuffered
												 defer:YES];

        // allocate view
        view = [[OpenGLView alloc] initWithFrame:contentSize];
    }
    return self;
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
	// change window settings
    // attach the view to the window
	[window centerOnScreen];
	[window setTitle:title];
	[window awakeFromNib];
////[window toggleWindowFullscreen:self];
    [window setContentView:view];
	[view awakeFromNib];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    // make the window visible.
    [window makeKeyAndOrderFront:self];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application
{
	return YES;
}

- (void)applicationWillTerminate:(NSApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
	[view dealloc];
	////[window dealloc];
	////[self dealloc];
	[super dealloc];
}

- (void)dealloc
{
    // don’t forget to release allocated objects!
    [view release];
    [window release];
    [super dealloc];
}

@end
