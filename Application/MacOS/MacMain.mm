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
	char applicationName[] = "Renderer";
	int applicationWidth = 800;
	int applicationHeight = 600;
/*----------------------------------------------------------------------------*/
    // create an autorelease pool
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // make sure the application singleton has been instantiated
    NSApplication* application = [NSApplication sharedApplication];

	[application setPresentationOptions:NSApplicationPresentationDefault];
	[application setActivationPolicy:NSApplicationActivationPolicyRegular];
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
	// instantiate our application delegate
    id applicationDelegate = [[[AppDelegate alloc] initWithTitle:nsApplicationName
														   width:applicationWidth
														  height:applicationHeight] autorelease];

    // assign our delegate to the NSApplication
    [application setDelegate:applicationDelegate];

    // call the run method of our application
    [application run];

    // drain the autorelease pool
    [pool drain];

    // execution never gets here ..
    return 0;
}

@end
