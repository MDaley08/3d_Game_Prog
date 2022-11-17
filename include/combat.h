#ifndef __COMBAT_H__
#define __COMBAT_H__

#include "entity.h"
#include "spell.h"

typedef struct
{
    Uint8 round;
    Entity *player;
    Entity *enemy;
}Combat;

Combat *combat_new(Entity *player, Entity *enemy);
void combat();

#endif