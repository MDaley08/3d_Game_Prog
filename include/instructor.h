#ifndef __INSTRUCTOR_H__
#define __INSTRUCTOR_H__

#include "entity.h"

/**
 * @brief Create a new instructor entity
 * @param position where to spawn the instructor at
 * @return NULL on error, or an instructor entity pointer on success
 */
Entity *instructor_new(Vector3D position,Vector3D rotation);

#endif
