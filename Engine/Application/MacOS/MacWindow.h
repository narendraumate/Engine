//
//  MacWindow.h
//  Application
//
//  Created by Narendra Umate on 10/8/13.
//
//

#import <Cocoa/Cocoa.h>

@interface MacWindow : NSWindow
@property (nonatomic, assign, getter=isFullscreen) BOOL fullscreen;
@property (nonatomic, assign) NSRect windowedFrame;
@property (nonatomic, retain) NSString* windowedTitle;

- (void)initAttributes;
- (void)deinitAttributes;
- (void)applyAttributesBasedOnState;
- (void)applyFullscreenAttribute:(BOOL)fullscreen;
- (IBAction)toggleWindowFullscreen:(id)sender;
- (void)centerOnScreen;
@end
