//
//  TestAppDelegate.h
//  Test
//
//  Created by Ian Field on 17/06/2011.
//  Copyright 2011 University of Reading Student. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TestAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end
