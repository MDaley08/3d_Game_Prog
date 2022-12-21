#ifndef __SPELL_H__
#define __SPELL_H__

#include "gf2d_sprite.h"
#include "entity.h"

typedef enum {
    FIRE = 0,
    WATER,
    EARTH,
    LIGHT,
    DARK
}SpellSchool;

typedef enum{
    CHARM = 0,
    HEX,
    WARD,
    ATTACK
}SpellType;

typedef struct Spell_S {
    char        *spell_name;
    SpellSchool school;
    SpellType   type;
    Sprite      cardSprite;
    void        (*spell)(struct Entity_S *caster);
}Spell;

Spell *spell_new();
void *fireball(Entity *enemy); // casts a fireball does x damage - fire
void *burn(Entity *enemy); // damages enemy for x over 3 rounds - fire
void *quench(Entity *self); // removes a damage over time from self - water
void *flush(Entity *self); // reshuffles hand - water
void *purify(Entity *self); // removes a hex from self - light
void *heal(Entity *self); // heals self for x amount - light
void *shield(Entity *self); // reduces damage by x amount - earth
void *entangle(Entity *self); // forces enemy to pass and next spell costs x% - earth
void *weaken(Entity *enemy); // reduces damage of enemy next void - dark
void *drain(Entity *enemy); // does x damage to enemy and restores half to self - dark

#endif