//
//  MacMain.m
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#import "MacMain.h"

@implementation MacMain

int main(int argc, char *argv[])
{
	// initialize settings
	char applicationName[] = "Engine";
	int applicationWidth = 1280;
	int applicationHeight = 720;

	// convert char array to NSString*
	NSString* nsApplicationName = [[[NSString alloc] initWithUTF8String:applicationName] autorelease];

	// make sure the application singleton has been instantiated
	NSApplication* application = [[NSApplication sharedApplication] autorelease];

	// create menubar
	id menubar = [[[NSMenu alloc] initWithTitle:nsApplicationName] autorelease];
	id appMenuItem = [[[NSMenuItem alloc] init] autorelease];
	[menubar addItem:appMenuItem];

	id appMenu = [[[NSMenu alloc] init] autorelease];
	id quitTitle = [[@"Quit " stringByAppendingString:nsApplicationName] autorelease];
	id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
												  action:@selector(terminate:)
										   keyEquivalent:@"q"] autorelease];
	[appMenu addItem:quitMenuItem];
	[appMenuItem setSubmenu:appMenu];
	[application setMainMenu:menubar];

	// instantiate our application delegate
#if EnableOpenGL
	id applicationDelegate = [[[OpenGLAppDelegate alloc] initWithTitle:nsApplicationName
																 width:applicationWidth
																height:applicationHeight] autorelease];
#endif

#if EnableMetal
	id applicationDelegate = [[[MetalAppDelegate alloc] initWithTitle:nsApplicationName
																width:applicationWidth
															   height:applicationHeight] autorelease];
#endif

	// assign our delegate to the NSApplication
	[application setDelegate:applicationDelegate];

	// call the run method of our application
	[application run];

	// execution never gets here ..
	return 0;
}

@end
