//
//  GLWindow.m
//  MTEngine-MacOS
//
//  Created by Marcin Skoczylas on 19/09/2020.
//
//

#import "GLWindow.h"
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <CoreVideo/CVDisplayLink.h>
#import "GLView.h"

@implementation GLWindow

- (void) close {
	[NSApp terminate:self];
	[super close];
}

- (BOOL) acceptsFirstResponder {
	return YES;
}

- (void) keyDown:(NSEvent*)event {
//	NSLog(@"GLWindow override keyDown");
	
//	if ([event keyCode] == kEscapeKey) {
//		[self close];
//	}
//	else {
//		[super keyDown:event];
//	}

	
	[super keyDown:event];
}

@end
