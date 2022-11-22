#ifndef __COMBAT_H__
#define __COMBAT_H__

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

typedef struct {
    char        *spell_name;
    SpellSchool school;
    SpellType   attack;
    Sprite      cardSprite;
    void        (*effect)(struct Entity_S *self, struct Entity_S *other);
}Spell;
typedef struct
{
    Uint8 round;
    Entity *player;
    Entity *enemy;
}Combat;

void combat(Entity *self, Entity *enemy);

Spell *spell_new();
void *fireball(Entity *enemy); // casts a fireball does x damage - fire
void *burn(Entity *enemy); // damages enemy for x over 3 rounds - fire
void *quench(Entity *self); // removes a damage over time from self - water
void *flus(Entity *self); // reshuffles hand - water
void *purify(Entity *self); // removes a hex from self - light
void *heal(Entity *self); // heals self for x amount - light
void *shield(Entity *self); // reduces damage by x amount - earth
void *entagle(Entity *self); // forces enemy to pass and next spell costs x% - earth
void *weaken(Entity *enemy); // reduces damage of enemy next void - dark
void *drain(Entity *enemy); // does x damage to enemy and restores half to self - dark

#endif