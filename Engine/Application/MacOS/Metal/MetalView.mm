//
//  MetalView.mm
//  Engine
//
//  Created by Narendra Umate on 8/15/15.
//
//

#import "MetalView.h"

@implementation MetalView
/*----------------------------------------------------------------------------*/
- (void)setWidthLocal:(int) width
{
	applicationWidth = width;
}

- (void)setHeightLocal:(int) height
{
	applicationHeight = height;
}

- (void)setTitleLocal:(NSString*) title
{
	applicationTitle = title;
}
/*----------------------------------------------------------------------------*/
+ (id)layerClass
{
	return [CAMetalLayer class];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
	if ((self = [super initWithCoder:aDecoder]))
	{
		_metalLayer = (CAMetalLayer *)[self layer];
		_device = MTLCreateSystemDefaultDevice();
		_metalLayer.device = _device;
		_metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
	}

	return self;
}

- (void)didMoveToWindow
{
	[self redraw];
}

- (void)redraw
{
	id<CAMetalDrawable> drawable = [self.metalLayer nextDrawable];

	id<MTLTexture> texture = drawable.texture;

	MTLRenderPassDescriptor *passDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
	passDescriptor.colorAttachments[0].texture = texture;
	passDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
	passDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
	passDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(1.0, 0.0, 0.0, 1.0);

	id<MTLCommandQueue> commandQueue = [self.device newCommandQueue];
	id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
	id <MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:passDescriptor];
	[commandEncoder endEncoding];

	[commandBuffer presentDrawable:drawable];
	[commandBuffer commit];
}

@end
