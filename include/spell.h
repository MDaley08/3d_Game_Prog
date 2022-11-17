#ifndef __SPELL_H__
#define __SPELL_H__

#include "entity.h"

typedef enum{
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

typedef struct {
    SpellSchool school;
    SpellType   attack;
}Spell;
/*
Spell *spell_new();
void *fireball(Entity *enemy); // casts a fireball does x damage - fire
void *burn(Entity *enemy); // damages enemy for x over 3 rounds - fire
void *quench(Entity *self); // removes a damage over time from spell - water
void *purify(Entity *self); // removes a hex from self - light
void *heal(Entity *self); // heals self for x amount - light
void *shield(Entity *self); // reduces damage by x amount - earth
void *weaken(Entity *enemy); // reduces damage of enemy next void - dark
void *drain(Entity *enemy); // does x damage to enemy and restores half to self - dark
*/


#endif