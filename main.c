#include <X11/Intrinsic.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XTest.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"

#define MAX_SPELL_LENGTH 8

int PHONEMES[] = { 0, 87, 88, 89, 83, 84, 85, 79, 80, 81 };

int mod_ctrl = 37;
int mod_alt = 64;
int mod_shift = 50;

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

    { 4, 2, 6, 2 },             // Pixie Swarm
    { 1, 1 },                   // Meteor
    { 7, 9, 8, 2 },             // Fist of Vengeance
    { 9, 1, 7 },                // Toxic Cloud
    { 3, 1, 2 },                // Force of Nature

    { 7, 9, 2 },                // Charm Creature
    { 8, 2, 4, 6 },             // Vampirism
    { 6, 4, 6, 4 },             // Infravision
    { 1, 8, 3 },                // Greater Heal
    { 1, 9 },                   // Cure Poison

    { 7, 2 },                   // Stun
    { 9, 1 },                   // Poison
};

#define ARRAY_KEY 0
#define ARRAY_MOD 1
#define ARRAY_SPELL 2
char spell_keys[MAX_SPELLS][3];

extern void init_codes(Display *display);

void init_code(Display *display, char key, int mod, int spell) {
    static int index = 0;

    spell_keys[index][ARRAY_KEY] = XKeysymToKeycode(display, key);
    spell_keys[index][ARRAY_MOD] = mod;
    spell_keys[index][ARRAY_SPELL] = spell;

    index++;
}

void cast(Display *display, int *spell) {
    #define TIMER_SPELL 40000
    #define TIMER_END 60000

    for (int i = 0; i < MAX_SPELL_LENGTH && spell[i]; i++) {
        XTestFakeKeyEvent(display, PHONEMES[spell[i]], True, 0);
        XFlush(display);
        usleep(TIMER_SPELL);
        XTestFakeKeyEvent(display, PHONEMES[spell[i]], False, 0);
        XFlush(display);
        usleep(TIMER_SPELL);
    }

    XTestFakeKeyEvent(display, PHONEMES[5], True, 0);
    XFlush(display);
    usleep(TIMER_END);
    XTestFakeKeyEvent(display, PHONEMES[5], False, 0);
    XFlush(display);
    usleep(TIMER_END);
}

char down[256] = { 0 };

int main() {
    Display *display;
    Window win, winFocus;
    XIEventMask evmasks;
    // char keymap[32];
    XEvent ev;
    XGenericEventCookie *cookie;
    int revert;
    XIRawEvent *raw_ev;
    KeyCode keycode;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "display not found\n");
        return 1;
    }

    win = DefaultRootWindow(display);

    evmasks.deviceid = XIAllMasterDevices;
    evmasks.mask_len = XIMaskLen(XI_LASTEVENT);
    evmasks.mask = (unsigned char*) calloc(evmasks.mask_len, sizeof(char));
    XISetMask(evmasks.mask, XI_RawKeyPress);
    XISetMask(evmasks.mask, XI_RawKeyRelease);
    XISelectEvents(display, win, &evmasks, 1);

    init_codes(display);

    while(1) {
        XNextEvent(display, (XEvent*) &ev);
        cookie = (XGenericEventCookie*) &ev.xcookie;

        XGetInputFocus(display, &winFocus, &revert);
        XSelectInput(display, winFocus, KeyPressMask);

        if (XGetEventData(display, cookie) && cookie->type == GenericEvent) {
            raw_ev = (XIRawEvent*) cookie->data;
            keycode = raw_ev->detail;

            if (raw_ev->evtype == XI_RawKeyPress) {
                int mod = MOD_CTRL * down[mod_ctrl] + MOD_ALT * down[mod_alt] + MOD_SHIFT * down[mod_shift];

                down[keycode] = 1;

                for (int i = 0; i < MAX_SPELLS; i++) {
                    if (spell_keys[i][ARRAY_KEY] == keycode && spell_keys[i][ARRAY_MOD] == mod) {
                        cast(display, SPELLS[spell_keys[i][ARRAY_SPELL]]);
                        break;
                    }
                }
            } else if (raw_ev->evtype == XI_RawKeyRelease)
                down[keycode] = 0;
        }

        XFreeEventData(display, cookie);
    }

    XDestroyWindow(display, win);

    return 0;
}
