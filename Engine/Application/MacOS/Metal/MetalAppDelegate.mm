//
//  MetalAppDelegate.mm
//  Engine
//
//  Created by Narendra Umate on 8/15/15.
//
//

#import "MetalAppDelegate.h"

@implementation MetalAppDelegate

/*- (BOOL)application:(NSApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	return YES;
}*/

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
		window = [[MacWindow alloc] initWithContentRect:contentSize
											  styleMask:NSTitledWindowMask
												backing:NSBackingStoreBuffered
												  defer:YES];

		// allocate view
		view = [[[MetalView alloc] initWithFrame:contentSize] autorelease];
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
	[view setWidthLocal:width];
	[view setHeightLocal:height];
	[view setTitleLocal:title];
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

@end
