#include "core/platform/tray_bridge.h"

#if defined(EUI_TRAY_WINAPI)
#define TRAY_WINAPI 1
#define EUI_TRAY_HAS_BACKEND 1
#elif defined(EUI_TRAY_APPKIT)
#define EUI_TRAY_HAS_BACKEND 1
#elif defined(EUI_TRAY_APPINDICATOR)
#define TRAY_APPINDICATOR 1
#define EUI_TRAY_HAS_BACKEND 1
#else
#define EUI_TRAY_HAS_BACKEND 0
#endif

#if EUI_TRAY_HAS_BACKEND

#if defined(EUI_TRAY_APPKIT)

#import <Cocoa/Cocoa.h>

static int g_initialized = 0;
static int g_show_requested = 0;
static int g_exit_requested = 0;
static NSStatusItem* g_status_item = nil;
static NSMenu* g_menu = nil;

@interface EUITrayTarget : NSObject <NSApplicationDelegate>
- (void)show:(id)sender;
- (void)exit:(id)sender;
@end

@implementation EUITrayTarget
- (void)show:(id)sender {
    (void)sender;
    g_show_requested = 1;
}

- (void)exit:(id)sender {
    (void)sender;
    g_exit_requested = 1;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender {
    (void)sender;
    g_exit_requested = 1;
    return NSTerminateCancel;
}

- (BOOL)applicationShouldHandleReopen:(NSApplication*)sender hasVisibleWindows:(BOOL)hasVisibleWindows {
    (void)sender;
    if (!hasVisibleWindows) {
        g_show_requested = 1;
    }
    return YES;
}
@end

static EUITrayTarget* g_target = nil;

static NSImage* eui_tray_image(const char* icon_path) {
    NSImage* image = nil;
    if (icon_path != 0 && icon_path[0] != '\0') {
        NSString* path = [NSString stringWithUTF8String:icon_path];
        if (path != nil) {
            image = [[[NSImage alloc] initWithContentsOfFile:path] autorelease];
        }
    }
    if (image == nil) {
        image = [NSImage imageNamed:NSImageNameApplicationIcon];
    }
    [image setSize:NSMakeSize(18.0, 18.0)];
    [image setTemplate:YES];
    return image;
}

static void eui_tray_rebuild_menu(void) {
    [g_menu release];
    g_menu = [[NSMenu alloc] initWithTitle:@""];
    [g_menu setAutoenablesItems:NO];

    NSMenuItem* show_item = [[NSMenuItem alloc] initWithTitle:@"Show"
                                                       action:@selector(show:)
                                                keyEquivalent:@""];
    [show_item setTarget:g_target];
    [g_menu addItem:show_item];
    [show_item release];

    [g_menu addItem:[NSMenuItem separatorItem]];

    NSMenuItem* exit_item = [[NSMenuItem alloc] initWithTitle:@"Exit"
                                                       action:@selector(exit:)
                                                keyEquivalent:@""];
    [exit_item setTarget:g_target];
    [g_menu addItem:exit_item];
    [exit_item release];
}

int eui_tray_init(const char* icon_path) {
    if (g_initialized) {
        return 1;
    }

    @autoreleasepool {
        [NSApplication sharedApplication];
        g_show_requested = 0;
        g_exit_requested = 0;
        g_target = [[EUITrayTarget alloc] init];
        [NSApp setDelegate:g_target];
        eui_tray_rebuild_menu();

        g_status_item = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
        if (g_status_item == nil) {
            [g_menu release];
            g_menu = nil;
            [g_target release];
            g_target = nil;
            return 0;
        }
        [g_status_item retain];

        NSImage* image = eui_tray_image(icon_path);
        NSStatusBarButton* button = [g_status_item button];
        if (button == nil) {
            [[NSStatusBar systemStatusBar] removeStatusItem:g_status_item];
            [g_status_item release];
            g_status_item = nil;
            [g_menu release];
            g_menu = nil;
            [g_target release];
            g_target = nil;
            return 0;
        }
        [button setImage:image];
        [button setImagePosition:NSImageOnly];
        [button setToolTip:@"EUI NEO"];
        [g_status_item setMenu:g_menu];
        if ([g_status_item respondsToSelector:@selector(setVisible:)]) {
            [g_status_item setVisible:YES];
        }
        g_initialized = 1;
    }
    return 1;
}

int eui_tray_is_initialized(void) {
    return g_initialized;
}

void eui_tray_poll(int blocking) {
    if (!g_initialized) {
        return;
    }

    @autoreleasepool {
        NSDate* until = blocking ? [NSDate distantFuture] : [NSDate distantPast];
        NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:until
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES];
        if (event != nil) {
            [NSApp sendEvent:event];
        }
    }
}

int eui_tray_consume_show_requested(void) {
    int requested = g_show_requested;
    g_show_requested = 0;
    return requested;
}

int eui_tray_consume_exit_requested(void) {
    int requested = g_exit_requested;
    g_exit_requested = 0;
    return requested;
}

void eui_tray_shutdown(void) {
    if (!g_initialized) {
        return;
    }

    @autoreleasepool {
        if (g_status_item != nil) {
            [[NSStatusBar systemStatusBar] removeStatusItem:g_status_item];
            [g_status_item release];
            g_status_item = nil;
        }
        if ([NSApp delegate] == g_target) {
            [NSApp setDelegate:nil];
        }
        [g_menu release];
        g_menu = nil;
        [g_target release];
        g_target = nil;
        g_initialized = 0;
        g_show_requested = 0;
        g_exit_requested = 0;
    }
}

#else

#if defined(_MSC_VER) && defined(EUI_TRAY_WINAPI)
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

#include "tray.h"

#if defined(_MSC_VER) && defined(EUI_TRAY_WINAPI)
#pragma warning(pop)
#endif

static int g_initialized = 0;
static int g_show_requested = 0;
static int g_exit_requested = 0;
static struct tray g_tray;

static void eui_tray_show(struct tray_menu* item) {
    (void)item;
    g_show_requested = 1;
}

static void eui_tray_exit(struct tray_menu* item) {
    (void)item;
    g_exit_requested = 1;
}

static struct tray_menu g_menu[] = {
    {"Show", 0, 0, eui_tray_show, 0},
    {"-", 0, 0, 0, 0},
    {"Exit", 0, 0, eui_tray_exit, 0},
    {0, 0, 0, 0, 0}
};

int eui_tray_init(const char* icon_path) {
    if (g_initialized) {
        return 1;
    }

    g_show_requested = 0;
    g_exit_requested = 0;
    g_tray.icon = (char*)(icon_path != 0 ? icon_path : "");
    g_tray.menu = g_menu;

    if (tray_init(&g_tray) != 0) {
        return 0;
    }

    g_initialized = 1;
    tray_update(&g_tray);
    return 1;
}

int eui_tray_is_initialized(void) {
    return g_initialized;
}

void eui_tray_poll(int blocking) {
    if (!g_initialized) {
        return;
    }

#if defined(EUI_TRAY_WINAPI)
    (void)blocking;
#else
    if (tray_loop(blocking ? 1 : 0) != 0) {
        g_exit_requested = 1;
    }
#endif
}

int eui_tray_consume_show_requested(void) {
    int requested = g_show_requested;
    g_show_requested = 0;
    return requested;
}

int eui_tray_consume_exit_requested(void) {
    int requested = g_exit_requested;
    g_exit_requested = 0;
    return requested;
}

void eui_tray_shutdown(void) {
    if (!g_initialized) {
        return;
    }

    tray_exit();
    g_initialized = 0;
    g_show_requested = 0;
    g_exit_requested = 0;
}

#endif

#else

int eui_tray_init(const char* icon_path) {
    (void)icon_path;
    return 0;
}

int eui_tray_is_initialized(void) {
    return 0;
}

void eui_tray_poll(int blocking) {
    (void)blocking;
}

int eui_tray_consume_show_requested(void) {
    return 0;
}

int eui_tray_consume_exit_requested(void) {
    return 0;
}

void eui_tray_shutdown(void) {
}

#endif
