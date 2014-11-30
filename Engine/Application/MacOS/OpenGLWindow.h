#import <Cocoa/Cocoa.h>

@interface OpenGLWindow : NSWindow
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
