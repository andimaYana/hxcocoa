/*
	NSFont.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h> // for NSStringEncoding
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSCell.h> // for NSControlSize

@class NSFontDescriptor, NSAffineTransform, NSGraphicsContext;

/********* NSGlyph *********/
/* This is the Application Kit glyph ID.
*/
typedef unsigned int NSGlyph;

enum {
    NSControlGlyph = 0x00FFFFFF, // An NSGlyph value representing control characters (i.e. tab, line breaks, etc)
    NSNullGlyph = 0x0 // An NSGlyph value representing glyphs removed by the layout process
};

/********* Font Matrix *********/
/* This is a font matrix value representing [1 0 0 1 0 0].
*/
APPKIT_EXTERN const Float *NSFontIdentityMatrix;

/********* Glyph packing *********/
/* Other glyph packing modes are deprecated.
*/
enum {
    NSNativeShortGlyphPacking = 5
};
typedef NSUInteger NSMultibyteGlyphPacking;

/********* Screen Font Rendering Mode *********/
enum {
    NSFontDefaultRenderingMode = 0, // Determines the actual mode based on the user preference settings
    NSFontAntialiasedRenderingMode = 1, // Antialiased, floating-point advancements rendering mode (synonym to printerFont)
    NSFontIntegerAdvancementsRenderingMode = 2, // integer advancements rendering mode
    NSFontAntialiasedIntegerAdvancementsRenderingMode = 3 // Antialiased, integer advancements rendering mode
};
typedef NSUInteger NSFontRenderingMode;

extern class NSFont extends NSObject, implements NSCopying, NSCoding> {
    /* All instance variables are private */
    NSString *_name;
    Float _size;
    NSInteger _retainCount;
    struct __fFlags {
        unsigned int _isScreenFont:1;
        unsigned int _systemFontType:8;
        unsigned int _reserved1:4;
        unsigned int _matrixIsIdentity:1;
        unsigned int _renderingMode:3;
        unsigned int _inInstanceCache:1;
        unsigned int _reserved2:14;
    } _fFlags;
    id _private;
}

/********* Factory *********/
+ (NSFont *)fontWithName:(NSString *)fontName size:(Float)fontSize;
+ (NSFont *)fontWithName:(NSString *)fontName matrix:(const Float *)fontMatrix;
/* Instantiates an NSFont object matching fontDescriptor. If fontSize is greater than 0.0, it has precedence over NSFontSizeAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor size:(Float)fontSize;

/* Instantiates an NSFont object matching fontDescriptor. If textTransform is non-nil, it has precedence over NSFontMatrixAttribute in fontDescriptor.
*/
+ (NSFont *)fontWithDescriptor:(NSFontDescriptor *)fontDescriptor textTransform:(NSAffineTransform *)textTransform;

/********* Meta Font *********/
/* User font settings
*/
+ (NSFont *)userFontOfSize:(Float)fontSize;	// Aqua Application font
+ (NSFont *)userFixedPitchFontOfSize:(Float)fontSize; // Aqua fixed-pitch font
+ (void)setUserFont:(NSFont *)aFont;	// set preference for Application font.
+ (void)setUserFixedPitchFont:(NSFont *)aFont; // set preference for fixed-pitch.

/* UI font settings
*/
+ (NSFont *)systemFontOfSize:(Float)fontSize;	// Aqua System font
+ (NSFont *)boldSystemFontOfSize:(Float)fontSize; // Aqua System font (emphasized)
+ (NSFont *)labelFontOfSize:(Float)fontSize; // Aqua label font

+ (NSFont *)titleBarFontOfSize:(Float)fontSize;
+ (NSFont *)menuFontOfSize:(Float)fontSize;
+ (NSFont *)menuBarFontOfSize:(Float)fontSize;
+ (NSFont *)messageFontOfSize:(Float)fontSize;
+ (NSFont *)paletteFontOfSize:(Float)fontSize;
+ (NSFont *)toolTipsFontOfSize:(Float)fontSize;
+ (NSFont *)controlContentFontOfSize:(Float)fontSize;

/* UI font size settings
*/
+ (Float)systemFontSize; // size of the standard System font.
+ (Float)smallSystemFontSize; // size of standard small System font.
+ (Float)labelFontSize;	// size of the standard Label Font.

+ (Float)systemFontSizeForControlSize:(NSControlSize)controlSize;

/********* Core font attribute *********/
- (NSString *)fontName;
- (Float)pointSize;
- (const Float *)matrix;
- (NSString *)familyName;
- (NSString *)displayName;
- (NSFontDescriptor *)fontDescriptor;
- (NSAffineTransform *)textTransform;

/********* Glyph coverage *********/
- (NSUInteger)numberOfGlyphs;
- (NSStringEncoding)mostCompatibleStringEncoding;
- (NSGlyph)glyphWithName:(NSString *)aName;
- (NSCharacterSet *)coveredCharacterSet;

/********* Font instance-wide metrics *********/
/* These methods return scaled numbers.  If the font was created with a matrix, the matrix is applied automatically; otherwise the coordinates are multiplied by size.
*/
- (NSRect)boundingRectForFont;
- (NSSize)maximumAdvancement;

- (Float)ascender;
- (Float)descender;
- (Float)leading;

- (Float)underlinePosition;
- (Float)underlineThickness;
- (Float)italicAngle;
- (Float)capHeight;
- (Float)xHeight;
- (BOOL)isFixedPitch;

/********* Glyph metrics *********/
- (NSRect)boundingRectForGlyph:(NSGlyph)aGlyph;
- (NSSize)advancementForGlyph:(NSGlyph)ag;

// bulk query
- (void)getBoundingRects:(NSRectArray)bounds forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forGlyphs:(const NSGlyph *)glyphs count:(NSUInteger)glyphCount;
- (void)getAdvancements:(NSSizeArray)advancements forPackedGlyphs:(const void *)packedGlyphs length:(NSUInteger)length; // only supports NSNativeShortGlyphPacking

/********* NSGraphicsContext-related *********/
- (void)set;
- (void)setInContext:(NSGraphicsContext *)graphicsContext;

/********* Rendering mode *********/
- (NSFont *)printerFont;
- (NSFont *)screenFont; // Same as screenFontWithRenderingMode:NSFontDefaultRenderingMode
- (NSFont *)screenFontWithRenderingMode:(NSFontRenderingMode)renderingMode;
- (NSFontRenderingMode)renderingMode;

/********* Vertical mode *********/
/* Returns a vertical version of the receiver if such a configuration is supported.  Returns the receiver if no vertical variant available.  A vertical font applies appropriate rotation to the text matrix in -setInContext:, returns vertical metrics, and enables the vertical glyph substitution feature by default. */
- (NSFont *)verticalFont NS_AVAILABLE_MAC(10_7);

/* Returns YES if a vertical variant */
- (BOOL)isVertical NS_AVAILABLE_MAC(10_7);
}

/********* Glyph packing *********/
/* Take a buffer of NSGlyphs, of some given length, and a packing type, and a place to put some packed glyphs.  Pack up the NSGlyphs according to the NSMultibyteGlyphPacking, null-terminate the bytes, and then put them into the output buffer.  Return the count of bytes output, including the null-terminator.  The output buffer (packedGlyphs) provided by the caller is guaranteed to be at least "count*4+1" bytes long. This function only supports NSNativeShortGlyphPacking on Mac OS X.
*/
APPKIT_EXTERN NSInteger NSConvertGlyphsToPackedGlyphs(NSGlyph *glBuf, NSInteger count, NSMultibyteGlyphPacking packing, char *packedGlyphs);

/********* Notifications *********/
/* This notification is posted when the antialias threshold is changed by the user.
*/
APPKIT_EXTERN NSString *NSAntialiasThresholdChangedNotification;

/* This notification is posted when the available font set is modified as a result of activation/deactivation.
*/
APPKIT_EXTERN NSString *NSFontSetChangedNotification;


/********* Deprecated API *********/
// The remaining portion is deprecated on Mac OS X 10.4 and Later.
#if !__LP64__
#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4
/* Only NSNativeShortGlyphPacking is supported on Mac OS X.
*/
enum {
    NSOneByteGlyphPacking,
    NSJapaneseEUCGlyphPacking,
    NSAsciiWithDoubleByteEUCGlyphPacking,
    NSTwoByteGlyphPacking,
    NSFourByteGlyphPacking,
};

enum _NSGlyphRelation {
    NSGlyphBelow = 1,
    NSGlyphAbove = 2
};
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_4 */
typedef NSUInteger  NSGlyphRelation;

extern class NSFont (NSFontDeprecated)
+ (void)useFont:(NSString *)fontName NS_DEPRECATED_MAC(10_0, 10_4); // This is now automatically handled by Quartz.
- (Float)widthOfString:(NSString *)string NS_DEPRECATED_MAC(10_0, 10_4); // This API never returns correct value. Use NSStringDrawing API instead.
- (BOOL)isBaseFont NS_DEPRECATED_MAC(10_0, 10_4);
- (NSDictionary *)afmDictionary NS_DEPRECATED_MAC(10_0, 10_4);
- (BOOL)glyphIsEncoded:(NSGlyph)aGlyph NS_DEPRECATED_MAC(10_0, 10_4); // Can be deduced by aGlyph < [NSFont numberOfGlyphs] since only NSNativeShortGlyphPacking is supported.
- (Float)defaultLineHeightForFont NS_DEPRECATED_MAC(10_0, 10_4); // Use -[NSLayoutManager defaultLineHeightForFont:] instead.
+ (NSArray *)preferredFontNames NS_DEPRECATED_MAC(10_0, 10_4); // NSFontCascadeListAttribute offers more powerful font substitution management
+ (void)setPreferredFontNames:(NSArray *)fontNameArray NS_DEPRECATED_MAC(10_0, 10_4);
- (NSString *)encodingScheme NS_DEPRECATED_MAC(10_0, 10_4);
- (NSMultibyteGlyphPacking) glyphPacking NS_DEPRECATED_MAC(10_0, 10_4);

// The context-sensitive inter-glyph spacing is now performed at the typesetting stage.
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph precededByGlyph:(NSGlyph)prevGlyph isNominal:(BOOL *)nominal NS_DEPRECATED_MAC(10_0, 10_4);
- (Int)positionsForCompositeSequence:(NSGlyph *)someGlyphs numberOfGlyphs:(Int)numGlyphs pointArray:(NSPointArray)points NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)curGlyph struckOverGlyph:(NSGlyph)prevGlyph metricsExist:(BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph struckOverRect:(NSRect)aRect metricsExist:(BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)aGlyph forCharacter:(unichar)aChar struckOverRect:(NSRect)aRect NS_DEPRECATED_MAC(10_0, 10_4);
- (NSPoint)positionOfGlyph:(NSGlyph)thisGlyph withRelation:(NSGlyphRelation)rel toBaseGlyph:(NSGlyph)baseGlyph totalAdvancement:(NSSizePointer)adv metricsExist:(BOOL *)exist NS_DEPRECATED_MAC(10_0, 10_4);
}

APPKIT_EXTERN NSString *NSAFMFamilyName         NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFontName           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFormatVersion      NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMFullName           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMNotice             NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMVersion            NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMWeight             NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMEncodingScheme     NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMCharacterSet       NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMCapHeight          NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMXHeight            NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMAscender           NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMDescender          NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMUnderlinePosition  NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMUnderlineThickness NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMItalicAngle        NS_DEPRECATED_MAC(10_0, 10_4);
APPKIT_EXTERN NSString *NSAFMMappingScheme      NS_DEPRECATED_MAC(10_0, 10_4);
#endif /* !__LP64__ */
