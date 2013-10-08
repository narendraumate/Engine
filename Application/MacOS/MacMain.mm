#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>

#import "OpenGLView.h"
#import "OpenGLWindow.h"
#import "MacMain.h"

#include <iostream>
#include <vector>

void initializeWindow(const int& width, const int& height, const char* applicationName)
{
	@autoreleasepool
	{
		NSString* nsApplicationName = [[[NSString alloc] initWithUTF8String:applicationName] autorelease];
		[NSApplication sharedApplication];
		[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

		id menubar = [[NSMenu new] autorelease];
		id appMenuItem = [[NSMenuItem new] autorelease];
		[menubar addItem:appMenuItem];
		[NSApp setMainMenu:menubar];
		id appMenu = [[NSMenu new] autorelease];
		id quitTitle = [@"Quit " stringByAppendingString:nsApplicationName];
		id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
													  action:@selector(terminate:)
											   keyEquivalent:@"q"] autorelease];
		[appMenu addItem:quitMenuItem];
		[appMenuItem setSubmenu:appMenu];

		id window = [[[OpenGLWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
													 styleMask:NSTitledWindowMask
													   backing:NSBackingStoreBuffered
														 defer:NO] autorelease];
		[window centerOnScreen];
		[window setTitle:nsApplicationName];
		[window awakeFromNib];
		//[window toggleWindowFullscreen:nil];

		id view = [[[OpenGLView alloc] 	init] autorelease];
		[window setContentView:view];
		[view awakeFromNib];

		[window makeKeyAndOrderFront:nil];
		[NSApp activateIgnoringOtherApps:YES];
		[NSApp run];
	}
}

int main(int argc, const char * argv[])
{
	initializeWindow(800, 600, "Renderer");
	return 0;
}
