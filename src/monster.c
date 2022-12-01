#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_config.h"

#include "monster.h"

void monster_think(Entity *self);
void monster_update(Entity *self);
void monster_collison(Entity *self, Entity *other);

Entity *monster_new(char *filename, MonsterType type, Vector3D position,Vector3D rotation)
{
    SJson *json,*mjson;
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    json = sj_load(filename);
    if (!json)
    {
        slog("failed to load json file (%s) for monster data",filename);
        free(ent);
        return NULL;
    }
    mjson = NULL;
    switch (type)
    {
    case DRAGON:
        mjson = sj_object_get_value(json,"dragon");
        break;
    case MERMAID:
        mjson = sj_object_get_value(json,"mermaid");
        break;
    case GOLEM:
        mjson = sj_object_get_value(json,"golem");
        break;
    case SENTINEL:
        mjson = sj_object_get_value(json,"sentinel");
        break;
    case UNDEAD:
        mjson = sj_object_get_value(json,"undead");
        break;
    }
    if (!mjson)
    {
        slog("failed to find monster object in %s monster condig",filename);
        free(ent);
        sj_free(json);
        return NULL;
    }

    ent->name = sj_get_string_value(sj_object_get_value(mjson,"name"));
    ent->think = monster_think; //load from json(we will keep as monster for now, later each monster will have own think function)
    ent->update = monster_update; //load from json
    ent->model = gf3d_model_load(sj_get_string_value(sj_object_get_value(mjson,"model")));//defaulting to cube, later each will have unique model
    ent->bounds = gfc_sphere(ent->mat.position.x,ent->mat.position.y,ent->mat.position.z,1);//default for cube
    ent->collison = monster_collison;//all will use
    ent->mat.scale = vector3d(1.5,1.5,1.5);
    ent->selectedColor = gfc_color(0,95,157,220);
    ent->color = sj_value_as_color(sj_object_get_value(mjson,"color"));
    sj_get_integer_value(sj_object_get_value(mjson,"max_health"),&ent->max_health);
    sj_get_integer_value(sj_object_get_value(mjson,"health"),&ent->health); 
    sj_get_integer_value(sj_object_get_value(mjson,"max_mana"),&ent->max_mana);//load from json
    sj_get_integer_value(sj_object_get_value(mjson,"mana"),&ent->mana);//load from json
    sj_get_integer_value(sj_object_get_value(mjson,"school"),&ent->school);//load from json

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
    Vector3D start_pos;
    vector3d_copy(start_pos,self->mat.position);
    self->bounds = gfc_sphere(self->mat.position.x,self->mat.position.y,self->mat.position.z,1.2);
    if(self->in_combat){
        self->mat.position.z = 2001.5;
        self->mat.position.x = -12;
        self->mat.position.y = 0;
    }
}

void monster_collison(Entity *self, Entity *other){
    other->in_combat = 1;
    self->enemy = other;
}

/*eol@eof*/
