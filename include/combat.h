#ifndef __COMBAT_H__
#define __COMBAT_H__

#include "gf2d_sprite.h"
#include "entity.h"



extern int combat_round;
extern Uint8 turn;

void combat(Entity *player);

//Spell *spell_new();

#endif