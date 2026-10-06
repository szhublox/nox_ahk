#include <X11/Intrinsic.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XTest.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
#define SPELL_PIXIE_SWARM 25
#define SPELL_METEOR 26
#define SPELL_FIST_OF_VENGEANCE 27
#define SPELL_TOXIC_CLOUD 27
#define SPELL_FORCE_OF_NATURE 28
#define SPELL_CHARM_CREATURE 29
#define SPELL_VAMPIRISM 30
#define SPELL_INFRAVISION 31
#define SPELL_GREATER_HEAL 32
#define SPELL_CURE_POISON 33
#define SPELL_STUN 34
#define SPELL_POISON 35
#define MAX_SPELLS (SPELL_POISON + 1)

#define MAX_SPELL_LENGTH 8

int PHONEMES[] = { 0, 87, 88, 89, 83, 84, 85, 79, 80, 81 };

#define MOD_CTRL (1 << 0)
#define MOD_ALT (1 << 1)
#define MOD_SHIFT (1 << 2)

int mod_ctrl = 0; // TODO
int mod_alt = 0; // TODO
int mod_shift = 0; // TODO

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
    #define TIMER_END 20000

    XTestFakeKeyEvent(display, 77, True, 0);

    for (int i = 0; i < MAX_SPELL_LENGTH && spell[i]; i++) {
        XTestFakeKeyEvent(display, PHONEMES[spell[i]], True, 0);
        usleep(TIMER_SPELL);
        XTestFakeKeyEvent(display, PHONEMES[spell[i]], False, 0);
        usleep(TIMER_SPELL);
        // XFlush(display);
    }

    XTestFakeKeyEvent(display, PHONEMES[5], True, 0);
    usleep(TIMER_END);
    XTestFakeKeyEvent(display, PHONEMES[5], False, 0);
    usleep(TIMER_END);
}

char down[256] = { 0 };

int main() {
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "display not found\n");
        return 1;
    }

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

    init_codes(display);

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
                int mod = MOD_CTRL * down[mod_ctrl] + MOD_ALT * down[mod_alt] + MOD_SHIFT * down[mod_shift];

                down[keycode] = 1;

                for (int i = 0; i < MAX_SPELLS; i++) {
                    if (spell_keys[i][ARRAY_KEY] == keycode && spell_keys[i][ARRAY_MOD] == mod) {
                        cast(display, SPELLS[spell_keys[i][ARRAY_SPELL]]);
                        break;
                    }
                }
            } else if (d_ev->evtype == XI_RawKeyRelease)
                down[keycode] = 0;
        }

        XFreeEventData(display, cookie);
    }

    XDestroyWindow(display, win);

    return 0;
}
