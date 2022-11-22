#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "entity.h"

typedef enum {
    DRAGON,
    UNDEAD,
    GOLEM,
    SENTINEL,
    MERMAID
}MonsterType;

Entity *monster_new(char *filename, MonsterType type, Vector3D position,Vector3D rotation);


#endif