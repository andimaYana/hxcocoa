//
//  AlbumPickerController
//  Wwx
//
//  Source generated by Haxe Objective-C target
//


#import <UIKit/UIKit.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>

#import "Array.h"
#import "FBAlbum.h"
#import "String.h"
#import "AlbumPickerController.h"
#import "haxe/Log.h"
#import "AlbumTableViewCell.h"
#import <QuartzCore/QuartzCore.h>

@interface AlbumPickerController : UIViewController <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) ALAssetsLibrary *library;
@property (nonatomic, strong) NSMutableArray *groups;
@property (nonatomic, strong) NSMutableArray *fb_albums;
@property (nonatomic, strong) NSMutableArray *movies;
@property (nonatomic, strong) UIActivityIndicatorView *activityView;
@property (nonatomic) BOOL loadingFacebook;
@property (nonatomic) id delegate;
// Dynamic method defined with an objc method and a block property
- (void) localAlbumPicked:(ALAssetsGroup*)album;
@property (nonatomic,copy) void(^hx_dyn_localAlbumPicked)(ALAssetsGroup*);
// Dynamic method defined with an objc method and a block property
- (void) facebookAlbumPicked:(FBAlbum*)album;
@property (nonatomic,copy) void(^hx_dyn_facebookAlbumPicked)(FBAlbum*);
// Dynamic method defined with an objc method and a block property
- (void) selectMovieAtPath:(NSString*)path;
@property (nonatomic,copy) void(^hx_dyn_selectMovieAtPath)(NSString*);
- (void) loadView;
- (void) viewDidLoad;
- (void) viewDidAppear:(BOOL)animated;
- (int) tableView:(UITableView*)tableView numberOfRowsInSection:(int)section;
- (UITableViewCell*) tableView:(UITableView*)tableView_ cellForRowAtIndexPath:(NSIndexPath*)indexPath;
- (float) tableView:(UITableView*)tableView heightForRowAtIndexPath:(NSIndexPath*)indexPath;
- (void) tableView:(UITableView*)tableView_ didSelectRowAtIndexPath:(NSIndexPath*)indexPath;
- (int) numberOfSectionsInTableView:(UITableView*)tableView;
- (UIView*) tableView:(UITableView*)tableView_ viewForHeaderInSection:(int)section;
- (float) tableView:(UITableView*)tableView heightForHeaderInSection:(int)section;
- (void) loginToFacebook;
- (void) update;
- (BOOL) canSwipeLeft;
- (BOOL) canSwipeRight;

@end




@protocol AlbumPickerDelegate<NSObject>




@end

