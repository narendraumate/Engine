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
	int applicationWidth = 1280;
	int applicationHeight = 720;
/*----------------------------------------------------------------------------*/
    // create an autorelease pool
    ////NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    // make sure the application singleton has been instantiated
    NSApplication* application = [[NSApplication sharedApplication] autorelease];

	[application setPresentationOptions:NSApplicationPresentationDefault];
	[application setActivationPolicy:NSApplicationActivationPolicyRegular];
/*----------------------------------------------------------------------------*/
	////[NSApplication sharedApplication];
	////[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

	NSString* nsApplicationName = [[[NSString alloc] initWithUTF8String:applicationName] autorelease];

	////id menubar = [[NSMenu new] autorelease];			// Avoiding new
	//..id appMenuItem = [[NSMenuItem new] autorelease];	// Avoiding new
	id menubar = [[[NSMenu alloc] init] autorelease];
	id appMenuItem = [[[NSMenuItem alloc] init] autorelease];
	
	[menubar addItem:appMenuItem];
	[NSApp setMainMenu:menubar];
	////id appMenu = [[NSMenu new] autorelease];			// Avoiding new
	id appMenu = [[[NSMenu alloc] init] autorelease];
	
	id quitTitle = [[@"Quit " stringByAppendingString:nsApplicationName] autorelease];
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
    ////[pool drain];

	// execution never gets here unless application stops instead of exiting
    return 0;
}

@end
