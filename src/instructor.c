#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_config.h"

#include "monster.h"

void instructor_think(Entity *self);
void instructor_update(Entity *self);
void instructor_collison(Entity *self, Entity *other);

Entity *instructor_new(Vector3D position,Vector3D rotation)
{
    SJson *json,*mjson;
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no instructor for you!");
        return NULL;
    }
    ent->type = INSTRUCTOR;
    ent->think = instructor_think; //load from json(we will keep as monster for now, later each monster will have own think function)
    ent->update = instructor_update; //load from json
    ent->model = gf3d_model_load("models/player.model");//defaulting to cube, later each will have unique model
    ent->bounds = gfc_sphere(ent->mat.position.x,ent->mat.position.y,ent->mat.position.z,20);//default for cube
    ent->collison = instructor_collison;//all will use
    ent->mat.scale = vector3d(1.5,1.5,1.5);
    ent->color = gfc_color(1,0.1,0.2,1);

    gf3d_model_mat_set_position(&ent->mat,position);
    gf3d_model_mat_set_rotation(&ent->mat,rotation);

    ent->hidden = 0;
    return ent;
}

void instructor_think(Entity *self)
{  
}

void instructor_update(Entity *self)
{
    Vector3D start_pos;
    vector3d_copy(start_pos,self->mat.position);
    self->bounds = gfc_sphere(self->mat.position.x,self->mat.position.y,self->mat.position.z,20);
}

void instructor_collison(Entity *self, Entity *other)
{
    other->interacting = 1;
}

/*eol@eof*/
