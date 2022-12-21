#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "spell.h"

//Spell *deck[20];

/**
 * @brief Create a new player entity
 * @param position where to spawn the aguman at
 * @return NULL on error, or an player entity pointer on success
 */
Entity *player_new(Vector3D position,Vector3D rotation);

#endif
