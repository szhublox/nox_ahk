#include "main.h"

void init_codes(Display *display) {
    init_code(display, '`', 0, SPELL_BLINK);
    init_code(display, '1', 0, SPELL_TELEPORT_TO_TARGET);
    init_code(display, '2', 0, SPELL_COUNTERSPELL);
    init_code(display, '3', 0, SPELL_INVERSION);
    init_code(display, '4', 0, SPELL_REFLECTIVE_SHIELD);
    init_code(display, '5', 0, SPELL_HASTE);
    init_code(display, '6', 0, SPELL_WALL);

    init_code(display, 'q', 0, SPELL_MISSILES_OF_MAGIC);
    init_code(display, 'w', 0, SPELL_BURN);
    init_code(display, 'e', 0, SPELL_FIREBALL);
    init_code(display, 'r', 0, SPELL_RING_OF_FIRE);
    init_code(display, 't', 0, SPELL_DEATH_RAY);
    init_code(display, 'y', 0, SPELL_ENERGY_BOLT);

    init_code(display, 'a', 0, SPELL_ANCHOR);
    init_code(display, 's', 0, SPELL_SLOW);
    init_code(display, 'd', 0, SPELL_CONFUSE);
    init_code(display, 'f', 0, SPELL_FUMBLE);
    init_code(display, 'g', 0, SPELL_RUN);

    init_code(display, '5', MOD_CTRL, SPELL_DETONATE_SEEN_TRAPS);

    init_code(display, 'q', MOD_CTRL, SPELL_SWAP_LOCATION);
    init_code(display, 'w', MOD_CTRL, SPELL_DRAIN_MANA);
    init_code(display, 'e', MOD_CTRL, SPELL_INVULNERABILITY);
    init_code(display, 'r', MOD_CTRL, SPELL_SHOCK);
    init_code(display, 't', MOD_CTRL, SPELL_INVISIBLITY);
    init_code(display, 'y', MOD_CTRL, SPELL_LIGHTNING);

    init_code(display, 'a', MOD_ALT, SPELL_MOONGLOW);
    init_code(display, 's', MOD_ALT, SPELL_LIGHT);
    init_code(display, 'd', MOD_ALT, SPELL_FEAR);
    init_code(display, 'f', MOD_ALT, SPELL_LOCK);

    init_code(display, 'a', MOD_CTRL, SPELL_LESSER_HEAL);
    init_code(display, 's', MOD_CTRL, SPELL_TRIGGER_TRAP);
    init_code(display, 'd', MOD_CTRL, SPELL_PUSH);
    init_code(display, 'f', MOD_CTRL, SPELL_PULL);

    init_code(display, 'q', MOD_CTRL | MOD_SHIFT, SPELL_PROTECT_FROM_FIRE);
    init_code(display, 'w', MOD_CTRL | MOD_SHIFT, SPELL_PROTECT_FROM_SHOCK);
    init_code(display, 'e', MOD_CTRL | MOD_SHIFT, SPELL_PROTECT_FROM_POISON);

    init_code(display, 'a', MOD_CTRL | MOD_SHIFT, SPELL_FORCE_FIELD);
    init_code(display, 's', MOD_CTRL | MOD_SHIFT, SPELL_TELEKINESIS);
    init_code(display, 'd', MOD_CTRL | MOD_SHIFT, SPELL_EARTHQUAKE);
    init_code(display, 'f', MOD_CTRL | MOD_SHIFT, SPELL_DISPEL_UNDEAD);

    init_code(display, 'q', MOD_CTRL | MOD_SHIFT | MOD_ALT, SPELL_OBLITERATION);

    init_code(display, '1', MOD_CTRL, SPELL_TELEPORT_TO_MARKER_1);
    init_code(display, '2', MOD_CTRL, SPELL_TELEPORT_TO_MARKER_2);
    init_code(display, '3', MOD_CTRL, SPELL_TELEPORT_TO_MARKER_3);
    init_code(display, '4', MOD_CTRL, SPELL_TELEPORT_TO_MARKER_4);
    init_code(display, '1', MOD_ALT, SPELL_MARK_LOCATION_1);
    init_code(display, '2', MOD_ALT, SPELL_MARK_LOCATION_2);
    init_code(display, '3', MOD_ALT, SPELL_MARK_LOCATION_3);
    init_code(display, '4', MOD_ALT, SPELL_MARK_LOCATION_4);
}
