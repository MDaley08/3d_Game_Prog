#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "entity.h"

typedef enum {
    HUMAN = 0,
    FAIRY,
    UNDEAD,
    TROLL,
    ELF
}MonsterType;

Entity *monster_new(Vector3D position,Vector3D rotation);

#endif