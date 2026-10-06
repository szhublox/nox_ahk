#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SPELL_MISSILES_OF_MAGIC 0
#define SPELL_BURN 1
#define SPELL_FIREBALL 2
#define SPELL_RING_OF_FIRE 3
#define SPELL_SHOCK 4
#define SPELL_ENERGY_BOLT 5
#define SPELL_BLINK 6
#define SPELL_TELEPORT_TO_TARGET 7
#define SPELL_COUNTERSPELL 8
#define SPELL_INVERSION 9
#define SPELL_REFLECTIVE_SHIELD 10
#define SPELL_HASTE 11
#define SPELL_TELEKINESIS 12
#define SPELL_WALL 13
#define SPELL_SWAP_LOCATION 14
#define SPELL_DRAIN_MANA 15
#define SPELL_LESSER_HEAL 16
#define SPELL_MARK_LOCATION_1 17
#define SPELL_MARK_LOCATION_2 18
#define SPELL_MARK_LOCATION_3 19
#define SPELL_MARK_LOCATION_4 20
#define SPELL_TELEPORT_TO_MARKER_1 21
#define SPELL_TELEPORT_TO_MARKER_2 22
#define SPELL_TELEPORT_TO_MARKER_3 23
#define SPELL_TELEPORT_TO_MARKER_4 24

#define MAX_SPELL_LENGTH 7

int SPELL_KEYCODES[] = { 0, 87, 88, 89, 83, 84, 85, 79, 80, 81 };

int SPELLS[][8] = {
    { 4, 8, 6, 8 },             // Missiles of Magic
    { 2, 2, 8, 8 },             // Burn
    { 2, 2, 8 },                // Fireball
    { 3, 2, 1, 8 },             // Ring of Fire
    { 2, 6, 4, 4 },             // Shock
    { 2, 6, 4, 8 },             // Energy Bolt

    { 6, 4, 8 },                // Blink
    { 2, 8, 4, 6 },             // Teleport to Target
    { 2, 3 },                   // Counterspell
    { 7, 9 },                   // Inversion
    { 8, 2, 2, 1, 3 },          // Reflective Shield
    { 4, 6, 6 },                // Haste
    { 2, 8, 2, 8 },             // Telekinesis
    { 7, 8, 9 },                // Wall

    { 8, 8, 2, 2 },             // Swap Location
    { 8, 7, 2, 9 },             // Drain Man

    { 3, 8, 1 },                // Lesser Heal

    { 8, 2, 8 },                // Mark Location 1
    { 8, 2, 6 },                // Mark Location 2
    { 8, 2, 2 },                // Mark Location 3
    { 8, 2, 4 },                // Mark Location 4
    { 2, 8, 8 },                // Teleport to Marker 1
    { 2, 8, 6 },                // Teleport to Marker 2
    { 2, 8, 2 },                // Teleport to Marker 3
    { 2, 8, 4 },                // Teleport to Marker 4
};

char down[256] = { 0 };

void cast(Display *display, int *spell) {
    XTestFakeKeyEvent(display, 77, True, 0);

    for (int i = 0; i <= MAX_SPELL_LENGTH && spell[i]; i++) {
        XTestFakeKeyEvent(display, SPELL_KEYCODES[spell[i]], True, 0);
        usleep(40000);
        XTestFakeKeyEvent(display, SPELL_KEYCODES[spell[i]], False, 0);
        usleep(40000);
        XFlush(display);
    }

    XTestFakeKeyEvent(display, SPELL_KEYCODES[5], True, 0);
    usleep(40000);
    XTestFakeKeyEvent(display, SPELL_KEYCODES[5], False, 0);
}

int main() {
    Display* display = XOpenDisplay(NULL);
    if (!display)
        return 1;

    Window win;
    win = DefaultRootWindow(display);

    XIEventMask evmasks;
    XKeyEvent *keyevent;

    evmasks.deviceid = XIAllMasterDevices;
    evmasks.mask_len = XIMaskLen(XI_LASTEVENT);
    evmasks.mask = (unsigned char*)calloc(evmasks.mask_len, sizeof(char));

    XISetMask(evmasks.mask, XI_RawKeyPress);
    XISetMask(evmasks.mask, XI_RawKeyRelease);

    XISelectEvents(display, win, &evmasks, 1);

    XSync(display, False);

    char ch[32];

    while(1) {
        XEvent ev;
        XGenericEventCookie *cookie = (XGenericEventCookie*)&ev.xcookie;
        XNextEvent(display, (XEvent*)&ev);

        Window winFocus;
        int revert;
        XGetInputFocus(display, &winFocus, &revert);
        // XSelectInput(display, winFocus, KeyPressMask | KeyReleaseMask);

        if (XGetEventData(display, cookie)
                && cookie->type == GenericEvent
                && ev.type == 35) {
            XIDeviceEvent *d_ev = (XIDeviceEvent*) cookie->data;
            KeyCode keycode = d_ev->detail;

            if (d_ev->evtype == XI_RawKeyPress) {
                down[keycode] = 1;

                if (keycode == XKeysymToKeycode(display, 'q'))
                    cast(display, SPELLS[SPELL_MISSILES_OF_MAGIC]);
// q::Cast([4, 8, 6, 8])		;Missiles of Magic
// w::Cast([2, 2, 8, 8])		;Burn
// e::Cast([2, 2, 8])		;Fireball
// r::Cast([3, 2, 1, 8])		;Ring of Fire
// t::Cast([2, 6, 4, 4])		;Shock
// y::Cast([2, 6, 4, 8])		;Energy Bolt
//
// `::Cast([6, 4, 8])		;Blink
// 1::Cast([2, 8, 4, 6])		;Teleport to Target
// 2::Cast([2, 3])			;Counterspell
// 3::Cast([7, 9])			;Inversion
// 4::Cast([8, 2, 2, 1, 3])	;Reflective Shield
// 5::Cast([4, 6, 6])		;Haste
// 6::Cast([2, 8, 2, 8])		;Telekinesis
// 7::Cast([7, 8, 9])		;Wall
//
// ^q::Cast([8, 8, 2, 2])		;Swap Location
// ^w::Cast([8, 7, 2, 9])		;Drain Mana
//
// ^x::Cast([3, 8, 1])		;Lesser Heal
//
// ^1::Cast([8, 2, 8])		;Mark Location 1
// ^2::Cast([8, 2, 6])		;Mark Location 2
// ^3::Cast([8, 2, 2])		;Mark Location 3
// ^4::Cast([8, 2, 4])		;Mark Location 4
// !1::Cast([2, 8, 8])		;Teleport to Marker 1
// !2::Cast([2, 8, 6])		;Teleport to Marker 2
// !3::Cast([2, 8, 2])		;Teleport to Marker 3
// !4::Cast([2, 8, 4])		;Teleport to Marker 4
//

            }
            else if (d_ev->evtype == XI_RawKeyRelease)
                down[keycode] = 0;
        }

        XFreeEventData(display, cookie);
    }

    XDestroyWindow(display, win);

    return 0;
}
