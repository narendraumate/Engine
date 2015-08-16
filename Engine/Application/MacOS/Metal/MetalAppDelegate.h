//
//  MetalAppDelegate.h
//  Engine
//
//  Created by Narendra Umate on 8/15/15.
//
//

#ifndef MetalAppDelegate_h
#define MetalAppDelegate_h

#import <MetalKit/MetalKit.h>
#import "MetalView.h"
#import "MacWindow.h"

/*@interface MetalAppDelegate : NSResponder <NSApplicationDelegate>

@property (strong, nonatomic) MacWindow *window;
@property (strong, nonatomic) MetalView *view;

@end*/

@interface MetalAppDelegate : NSObject
{
	NSString* title;
	int width;
	int height;

	MacWindow* window;
	MetalView* view;
}

- (id)initWithTitle:(NSString*)applicationTitle width:(int)applicationWidth height:(int)applicationHeight;

@end

#endif /* MetalAppDelegate_h */
