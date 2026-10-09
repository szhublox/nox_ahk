#include <X11/Intrinsic.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"

#define MAX_SPELL_LENGTH 8

int PHONEMES[] = { 0, 87, 88, 89, 83, 84, 85, 79, 80, 81 };

int SPELLS[][8] = {
    { 6, 4, 8 },                // Blink
    { 2, 2, 8, 8 },             // Burn
    { 2, 3 },                   // Counterspell
    { 7, 9 },                   // Inversion
    { 3, 8, 1 },                // Lesser Heal
    { 4, 6, 8 },                // Light
    { 4, 6, 8, 8 },             // Moonglow
    { 4, 6, 3, 7 },             // Protect From Fire
    { 4, 6, 1, 9 },             // Protect From Poison
    { 6, 4, 3, 7 },             // Protect From Shock
    { 2, 2, 2 },                // Slow
    { 9, 9 },                   // Tag

    { 2, 2 },                   // Anchor
    { 7, 2, 9 },                // Channel Life
    { 6, 4, 6 },                // Confuse
    { 3, 3 },                   // Death Ray
    { 8, 6, 4, 8 },             // Detonate Seen Traps
    { 8, 7, 4, 1, 2, 3, 6, 9 }, // Dispel Undead
    { 8, 7, 2, 9 },             // Drain Man
    { 3, 4, 9, 1, 6, 7 },       // Earthquake
    { 2, 6, 4, 8 },             // Energy Bolt
    { 4, 4, 6, 6 },             // Fear
    { 2, 2, 8 },                // Fireball
    { 8, 4, 2, 6, 8, 4, 2, 6 }, // Force Field
    { 4, 6, 2, 4, 6, 2 },       // Fumble
    { 4, 6, 6 },                // Haste
    { 4, 6, 4, 6 },             // Invisibility
    { 3, 7, 1, 9, 8, 6, 2, 4 }, // Invulnerability
    { 2, 6, 4, 8, 4, 6, 2 },    // Lightning
    { 8, 2, 3 },                // Lock
    { 8, 2, 8 },                // Mark Location 1
    { 8, 2, 6 },                // Mark Location 2
    { 8, 2, 2 },                // Mark Location 3
    { 8, 2, 4 },                // Mark Location 4
    { 4, 8, 6, 8 },             // Missiles of Magic
    { 8, 8, 4, 4, 2, 2, 6, 6 }, // Obliteration
    { 8, 8, 2 },                // Pull
    { 8, 8, 8 },                // Push
    { 8, 2, 2, 1, 3 },          // Reflective Shield
    { 3, 2, 1, 8 },             // Ring of Fire
    { 6, 6, 6 },                // Run
    { 2, 6, 4, 4 },             // Shock
    { 8, 8, 2, 2 },             // Swap Location
    { 2, 8, 2, 8 },             // Telekinesis
    { 2, 8, 8 },                // Teleport to Marker 1
    { 2, 8, 6 },                // Teleport to Marker 2
    { 2, 8, 2 },                // Teleport to Marker 3
    { 2, 8, 4 },                // Teleport to Marker 4
    { 2, 8, 4, 6 },             // Teleport to Target
    { 2 },                      // Trigger Trap
    { 7, 8, 9 },                // Wall

    { 7, 9, 2 },                // Charm Creature
    { 1, 9 },                   // Cure Poison
    { 7, 9, 8, 2 },             // Fist of Vengeance
    { 3, 1, 2 },                // Force of Nature
    { 1, 8, 3 },                // Greater Heal
    { 6, 4, 6, 4 },             // Infravision
    { 1, 1 },                   // Meteor
    { 4, 2, 6, 2 },             // Pixie Swarm
    { 9, 1 },                   // Poison
    { 7, 2 },                   // Stun
    { 9, 1, 7 },                // Toxic Cloud
    { 8, 2, 4, 6 },             // Vampirism

    { 7, 3, 9, 1, 1 },          // Summon Bat
    { 7, 3, 9, 1, 6, 3, 8 },    // Summon Black Bear
    { 7, 3, 9, 1, 6, 3 },       // Summon Grizzly Bear
    { 7, 3, 9, 1, 6, 3, 2 },    // Summon Beholder
    { 7, 3, 9, 1, 8, 6 },       // Summon Carnivorous Plant
    { 7, 3, 9, 1, 8, 9 },       // Summon Large Cave Spider
    { 7, 3, 9, 1, 6 },          // Summon Cave Spider
    { 7, 3, 9, 1, 2, 8 },       // Summon Ember Demon
    { 7, 3, 9, 1, 6, 1, 8 },    // Summon Gargoyle
    { 7, 3, 9, 1, 2 },          // Summon Ghost
    { 7, 3, 9, 1, 8, 8 },       // Summon Giant Leech
    { 7, 3, 9, 1, 6, 1 },       // Summon Imp
    { 7, 3, 9, 1, 4 },          // Summon Mechanical Flyer
    { 7, 3, 9, 1, 2, 4 },       // Summon Mechanical Golem
    { 7, 3, 9, 1, 2, 6 },       // Summon Mimic
    { 7, 3, 9, 1, 6, 7, 2 },    // Summon Ogre
    { 7, 3, 9, 1, 6, 7, 8 },    // Summon Ogre Lord
    { 7, 3, 9, 1, 6, 7 },       // Summon Ogress
    { 7, 3, 9, 1, 6, 6 },       // Summon Scorpion
    { 7, 3, 9, 1, 6, 4 },       // Summon Shade
    { 7, 3, 9, 1, 6, 2 },       // Summon Skeleton
    { 7, 3, 9, 1, 2, 9 },       // Summon Skeleton Lord
    { 7, 3, 9, 1, 7 },          // Summon Spider
    { 7, 3, 9, 1, 9 },          // Summon Small Spider
    { 7, 3, 9, 1, 7, 8 },       // Summon Spitting Spider
    { 7, 3, 9, 1, 2, 1 },       // Summon Stone Golem
    { 7, 3, 9, 1, 6, 7, 3 },    // Summon Troll
    { 7, 3, 9, 1, 8, 2 },       // Summon Urchin
    { 7, 3, 9, 1, 3 },          // Summon Wasp
    { 7, 3, 9, 1, 2, 2 },       // Summon Will O' Wisp
    { 7, 3, 9, 1, 8, 4 },       // Summon Wolf
    { 7, 3, 9, 1, 8, 4, 2 },    // Summon Black Wolf
    { 7, 3, 9, 1, 8, 4, 8 },    // Summon White Wolf
    { 7, 3, 9, 1, 8, 3 },       // Summon Zombie
    { 7, 3, 9, 1, 8, 7 },       // Summon Vile Zombie
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
    #define TIMER_SPELL 45000
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

int query_modifier(Display *display) {
    char keymap[32];

    #define MAP_CTRL 37
    #define MAP_SHIFT 50
    #define MAP_ALT 64
    #define MAP_SUPER 133

    XQueryKeymap(display, keymap);
    return ((keymap[MAP_CTRL / 8] >> MAP_CTRL % 8) & 1) * MOD_CTRL
        + ((keymap[MAP_SHIFT / 8] >> MAP_SHIFT % 8) & 1) * MOD_SHIFT
        + ((keymap[MAP_ALT / 8] >> MAP_ALT % 8) & 1) * MOD_ALT
        + ((keymap[MAP_SUPER / 8] >> MAP_SUPER % 8) & 1) * MOD_SUPER;
}

struct queue_node {
    struct queue_node *next;
    int spell;
};

struct thread_args {
    Display *display;
    Window win;
    struct queue_node *node;
};

void queue_add(struct queue_node *node, int spell) {
    if (node->spell < 0) {
        node->spell = spell;
        return;
    }

    while (node->next)
        node = node->next;

    node->next = malloc(sizeof(struct queue_node));
    node->next->next = NULL;
    node->next->spell = spell;
}

void queue_clear(struct queue_node *node) {
    struct queue_node *next;

    if (node->spell >= 0)
        node->spell = -1;

    if (node->next) {
        next = node->next;
        node->next = NULL;
        node = next;

        while (node) {
            next = node->next;
            free(node);
            node = next;
        }
    }
}

void *event_check(void *data) {
    Window winFocus;
    XIEventMask evmasks;
    XEvent ev;
    XGenericEventCookie *cookie;
    int mod, revert;
    XIRawEvent *raw_ev;
    KeyCode keycode;
    struct thread_args *args;
    char *title;
    struct queue_node *node, *next;

    args = data;

    evmasks.deviceid = XIAllMasterDevices;
    evmasks.mask_len = XIMaskLen(XI_LASTEVENT);
    evmasks.mask = (unsigned char*) calloc(evmasks.mask_len, sizeof(char));
    XISetMask(evmasks.mask, XI_RawKeyPress);
    XISelectEvents(args->display, args->win, &evmasks, 1);

    XTestFakeKeyEvent(args->display, 77, True, 0); // NUM_LOCK
    init_codes(args->display);

    while (1) {
        XNextEvent(args->display, (XEvent*) &ev);
        cookie = (XGenericEventCookie*) &ev.xcookie;

        XGetInputFocus(args->display, &winFocus, &revert);

        XFetchName(args->display, winFocus, &title);
        if (!title || !(!strcmp(title, "Nox Game Window") || !strncmp(title, "OpenNox", 7))) {
            queue_clear(args->node);
            continue;
        }

        XSelectInput(args->display, winFocus, KeyPressMask);

        if (XGetEventData(args->display, cookie) && cookie->type == GenericEvent) {
            raw_ev = (XIRawEvent*) cookie->data;
            if (raw_ev->evtype != XI_RawKeyPress)
                continue;

            keycode = raw_ev->detail;
            mod = query_modifier(args->display);
            if (mod & MOD_SUPER) {
                queue_clear(args->node);
                continue;
            }

            for (int i = 0; i < MAX_SPELLS; i++) {
                if (spell_keys[i][ARRAY_KEY] == keycode && spell_keys[i][ARRAY_MOD] == mod) {
                    queue_add(args->node, spell_keys[i][ARRAY_SPELL]);
                    break;
                }
            }
        }

        XFreeEventData(args->display, cookie);
    }
}

int main() {
    pthread_t thread;
    Display *display;
    Window win;
    struct thread_args *args;
    struct queue_node *to_free;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "display not found\n");
        return 1;
    }

    win = DefaultRootWindow(display);
    args = malloc(sizeof(struct thread_args));
    args->display = display;
    args->win = win;
    args->node = malloc(sizeof(struct queue_node));
    args->node->next = NULL;
    args->node->spell = -1;

    pthread_create(&thread, NULL, event_check, args);

    while (1) {
        if (args->node->spell >= 0) {
            cast(args->display, SPELLS[args->node->spell]);
            if (args->node->next) {
                to_free = args->node;
                args->node = args->node->next;
                free(to_free);
            } else
                args->node->spell = -1;
        }
        usleep(1000);
    }

    XDestroyWindow(display, win);
}
