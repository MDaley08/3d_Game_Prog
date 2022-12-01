#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gfc_color.h"
#include "gfc_primitives.h"

#include "gf3d_model.h"

typedef enum
{
    ES_idle = 0,
    ES_hunt,
    ES_dead,
    ES_attack
}EntityState;

typedef enum 
{
    FIRE_SCHOOL = 0,
    WATER_SCHOOL,
    EARTH_SCHOOL,
    LIGHT_SCHOOL,
    DARK_SCHOOL,

}EntitySchool;


typedef struct Entity_S
{
    Uint8       _inuse;     /**<keeps track of memory usage*/
    ModelMat    mat;   /**<orientation matrix for the model*/
    Color       color;      /**<default color for the model*/
    Model      *model;      /**<pointer to the entity model to draw  (optional)*/
    Uint8       hidden;     /**<if true, not drawn*/
    Uint8       selected;
    Color       selectedColor;      /**<Color for highlighting*/
    char        *name;
    
    Sphere      bounds; // for collisions
    int         team;  //same team dont clip
    int         clips;  // if false, skip collisions

    void       (*think)(struct Entity_S *self); /**<pointer to the think function*/
    void       (*update)(struct Entity_S *self); /**<pointer to the update function*/
    void       (*draw)(struct Entity_S *self); /**<pointer to an optional extra draw funciton*/
    void       (*damage)(struct Entity_S *self, float damage, struct Entity_S *inflictor); /**<pointer to the think function*/
    void       (*onDeath)(struct Entity_S *self); /**<pointer to an funciton to call when the entity dies*/
    void       (*free)(struct Entity_S *self); /**<pointer to the custom free function, necessar when there is custom data*/
    void       (*collison)(struct Entity_S *self, struct Entity_S *other); /**<pointer to collision function*/
    
    EntityState state;
    
    
    Vector3D        velocity;
    Vector3D        acceleration;

    EntitySchool    school;
    int          health;     /**<entity dies when it reaches zero*/
    Uint32          mana;       // used to cast spells
    Uint32          max_health; // maximum health entity can have
    Uint32          max_mana;   // maximum mana entity can have
    Uint8           in_combat;  // flag that is set if entity is in combat
    Uint8           ent_turn;
    //SpellSchool school;     // school of the entity,
    // WHATEVER ELSE WE MIGHT NEED FOR ENTITIES
    struct Entity_S *enemy;    /**<entity to target for weapons / ai*/
    
    void *data;   /**<IF an entity needs to keep track of extra data, we can do it here*/
}Entity;

/**
 * @brief initializes the entity subsystem
 * @param maxEntities the limit on number of entities that can exist at the same time
 */
void entity_system_init(Uint32 maxEntities);

/**
 * @brief provide a pointer to a new empty entity
 * @return NULL on error or a valid entity pointer otherwise
 */
Entity *entity_new();

/**
 * @brief free a previously created entity from memory
 * @param self the entity in question
 */
void entity_free(Entity *self);


/**
 * @brief Draw an entity in the current frame
 * @param self the entity in question
 */
void entity_draw(Entity *self);

/**
 * @brief draw ALL active entities
 */
void entity_draw_all();

/**
 * @brief Call an entity's think function if it exists
 * @param self the entity in question
 */
void entity_think(Entity *self);

/**
 * @brief run the think functions for ALL active entities
 */
void entity_think_all();

/**
 * @brief run the update functions for ALL active entities
 */
void entity_update_all();

/**
 * @brief check if there entity coliding with something
 * @param ent entity being checked for collison
 */
void entity_collision_check(Entity *ent);

/**
 * @brief parses entity manager to check for collision
 */
void entity_collison_check_all();

#endif
