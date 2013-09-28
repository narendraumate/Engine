#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>

#import "OpenGLFramework.h"
#import "OpenGLView.h"
#import "OpenGLWindow.h"

#include <iostream>
#include <vector>

void OpenGLFramework::initializeWindow(const int& width, const int& height, const char* applicationName)
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

	id view = [[[OpenGLView alloc] init] autorelease];
	[window setContentView:view];
	[view awakeFromNib];

	[window makeKeyAndOrderFront:nil];
	[NSApp activateIgnoringOtherApps:YES];
	[NSApp run];
	}
}

void OpenGLFramework::deinitializeWindow()
{
	@autoreleasepool
	{
	}
}

/*----------------------------------------------------------------------------*/

static const float vertexPositions[] =
{
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

static GLuint position_buffer_object, vertex_array_object, shader_program;

void OpenGLFramework::initializeOpenGL(const CGLContextObj& contextObject)
{
	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertexPositions, GL_STATIC_DRAW);

	std::vector<GLuint> shaders;
	shaders.push_back(Shader::LoadShader(GL_VERTEX_SHADER, "pass_along.vert"));
	shaders.push_back(Shader::LoadShader(GL_FRAGMENT_SHADER, "uniform_color.frag"));
	shader_program = Shader::CreateProgram(shaders);
	std::for_each(shaders.begin(), shaders.end(), glDeleteShader);

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
}

void OpenGLFramework::deinitializeOpenGL(const CGLContextObj& contextObject)
{

}

void OpenGLFramework::render(const CGLContextObj& contextObject)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	CGLFlushDrawable(contextObject);
}

void OpenGLFramework::reshape(const CGLContextObj& contextObject, const int& width, const int& height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}