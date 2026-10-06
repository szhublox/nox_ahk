#include "main.c"

void init_codes(Display *display) {
    init_code(display, 'q', 0, SPELL_PIXIE_SWARM);
    init_code(display, 'w', 0, SPELL_BURN);
    init_code(display, 'e', 0, SPELL_METEOR);
    init_code(display, 'r', 0, SPELL_FIST_OF_VENGEANCE);
    init_code(display, 't', 0, SPELL_TOXIC_CLOUD);
    init_code(display, 'y', 0, SPELL_FORCE_OF_NATURE);

    init_code(display, '`', 0, SPELL_BLINK);
    init_code(display, '1', 0, SPELL_CHARM_CREATURE);
    init_code(display, '2', 0, SPELL_COUNTERSPELL);
    init_code(display, '3', 0, SPELL_INVERSION);
    init_code(display, '4', 0, SPELL_VAMPIRISM);
    init_code(display, '5', 0, SPELL_INFRAVISION);
    init_code(display, '6', 0, SPELL_GREATER_HEAL);
    init_code(display, '7', 0, SPELL_CURE_POISON);

    init_code(display, 'q', MOD_CTRL, SPELL_STUN);
    init_code(display, 'w', MOD_CTRL, SPELL_POISON);

    init_code(display, 'x', MOD_CTRL, SPELL_LESSER_HEAL);
}
