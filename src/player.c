#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_vgraphics.h"
#include "gf3d_camera.h"
#include "gf3d_lights.h"
#include "gf3d_particle.h"
#include "gf3d_draw.h"

#include "gf2d_mouse.h"
#include "combat.h"
#include "player.h"

void player_think(Entity *self);
void player_update(Entity *self);
void player_collison(Entity *self, Entity *other);

Entity *player_new(Vector3D position,Vector3D rotation)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    
    ent->think = player_think;
    ent->update = player_update;
    ent->model = gf3d_model_load("models/player.model");
    ent->collison = player_collison;
    //ent->bounds = gfc_box(ent->mat.position.x,ent->mat.position.y,ent->mat.position.z,2,2,2);
    ent->bounds = gfc_sphere(ent->mat.position.x,ent->mat.position.y,ent->mat.position.z,1.2);
    ent->mat.scale = vector3d(1.5,1.5,1.5);
    ent->max_health = 1000;
    ent->health = 1000;
    ent->max_mana = 500;
    ent->mana = 500;
    ent->color = gfc_color(0,95,157,220);
    ent->school = EARTH_SCHOOL;

    gf3d_model_mat_set_position(&ent->mat,position);
    gf3d_model_mat_set_rotation(&ent->mat,rotation);

    ent->hidden = 0;
    return ent;
}


void player_think(Entity *self)
{
    Vector3D pre_combat_pos;
    Vector3D forward = {0};
    Vector3D right = {0};
    Vector2D w;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    w = vector2d_from_angle(self->mat.rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    w = vector2d_from_angle(self->mat.rotation.z - GFC_HALF_PI);
    right.x = w.x;
    right.y = w.y;
    if(!self->in_combat) // if not in combat
    {
        if (keys[SDL_SCANCODE_W])
        {   
            gf3d_model_mat_move(&self->mat,forward);
        }
        if (keys[SDL_SCANCODE_S])
        {
            gf3d_model_mat_move(&self->mat,vector3d(-forward.x,-forward.y,-forward.z));
        }
        if (keys[SDL_SCANCODE_D])
        {
            gf3d_model_mat_move(&self->mat,right);
        }
        if (keys[SDL_SCANCODE_A])    
        {
            gf3d_model_mat_move(&self->mat,vector3d(-right.x,-right.y,-right.z));
        }
        if (keys[SDL_SCANCODE_O])
        {
            slog("position: %f,%f,%f",self->mat.position.x,self->mat.position.y,self->mat.position.z);
            slog("rotation: %f,%f,%f",self->mat.rotation.x,self->mat.rotation.y,self->mat.rotation.z);
        }
    }

        if (keys[SDL_SCANCODE_G])    
        {
            self->in_combat = 0;
            self->mat.position.x = 0;
            self->mat.position.y = 0;
            self->mat.position.z = 1.5;
            entity_free(self->enemy);
        }
    
    //hard coded bounds, to be adjusted later
    if(self->mat.position.x > 144.3) self->mat.position.x = 144.2;
    if(self->mat.position.x < -144.3) self->mat.position.x = -144.2;
    if(self->mat.position.y > 144.3) self->mat.position.y = 144.2;
    if(self->mat.position.y < -144.3) self->mat.position.y = -144.2;
}

void player_update(Entity *self)
{
    Vector3D forward = {0};
    Vector3D position;
    Vector3D combat_position;
    Vector3D rotation;
    Vector3D combat_rotation;
    Vector2D w;
    
    if (!self)return;
    
    vector3d_copy(position,self->mat.position);
    vector3d_copy(rotation,self->mat.rotation);
    vector3d_copy(combat_position,self->mat.position);
    vector3d_copy(combat_rotation,self->mat.rotation);
    //hard coded camera position adjustment, also change later
    position.x += 20;
    position.z += 10;

    //rotation.z = M_PI/2;
    rotation.x += 0.32;
    
    gf3d_camera_set_position(position);
    gf3d_camera_set_rotation(rotation);
    self->bounds = gfc_sphere(self->mat.position.x,self->mat.position.y,self->mat.position.z,1);
    if(self->in_combat){
        combat_position.x += 11;
        combat_position.z += 12;
        combat_rotation.x += 0.60;
        self->mat.position.z = 2001.5;
        self->mat.position.x = 12;
        self->mat.position.y = 0;
        gf3d_camera_set_position(combat_position);
        gf3d_camera_set_rotation(combat_rotation);
    }
}

void player_collison(Entity *self, Entity *other){
    other->in_combat = 1;
    self->enemy = other;
}



/*eol@eof*/
