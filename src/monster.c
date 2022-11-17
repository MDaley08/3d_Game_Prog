#include "simple_logger.h"
#include "monster.h"

void monster_think(Entity *self);
void monster_update(Entity *self);
void monster_collison(Entity *self, Entity *other);

Entity *monster_new(Vector3D position,Vector3D rotation)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    
    ent->think = monster_think;
    ent->update = monster_update;
    ent->model = gf3d_model_load("models/player.model");
    //ent->bounds = gfc_box(0,0,0,2,2,2);
    ent->bounds = gfc_sphere(ent->mat.position.x,ent->mat.position.y,ent->mat.position.z,1);
    ent->collison = monster_collison;
    ent->mat.scale = vector3d(1.5,1.5,1.5);
    ent->color = gfc_color(1,0,0,1);
    ent->max_health = 2000;
    ent->health = 2000;
    ent->max_mana = 500;
    ent->mana = 500;

    gf3d_model_mat_set_position(&ent->mat,position);
    gf3d_model_mat_set_rotation(&ent->mat,rotation);

    ent->hidden = 0;
    return ent;
}

void monster_think(Entity *self)
{  
}

void monster_update(Entity *self)
{
    self->bounds = gfc_sphere(self->mat.position.x,self->mat.position.y,self->mat.position.z,1);
    if(self->in_combat){
        self->mat.position.z = 2000.9;
        self->mat.position.x = -12;
    }
}

void monster_collison(Entity *self, Entity *other){
    other->in_combat = 1;
}

/*eol@eof*/
