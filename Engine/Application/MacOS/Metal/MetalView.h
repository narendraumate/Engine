//
//  MetalView.h
//  Engine
//
//  Created by Narendra Umate on 8/15/15.
//
//

#ifndef MetalView_h
#define MetalView_h

#import <MetalKit/MetalKit.h>
#import <QuartzCore/CAMetalLayer.h>

@interface MetalView : NSView
{
@private
	//TODO Enable id<MTLDevice> device;
	//TODO Enable CAMetalLayer* metalLayer;
	int applicationWidth;
	int applicationHeight;
	NSString* applicationTitle;
}

- (void)setWidthLocal:(int) width;
- (void)setHeightLocal:(int) height;
- (void)setTitleLocal:(NSString*) title;

@property (nonatomic, strong) id<MTLDevice> device; // TODO Disable
@property (nonatomic, strong) CAMetalLayer *metalLayer; // TODO Disable

@end


#endif /* MetalView_h */
