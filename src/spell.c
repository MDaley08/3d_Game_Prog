#include "simple_logger.h"
#include "spell.h"
#include "combat.h"

void *fireball(Entity *caster){
    Uint16 mana_cost = 5;
    Uint16 total_damage = 50; 
    if(caster->mana >= mana_cost){
        if (caster->enemy->school == EARTH_SCHOOL) total_damage *= 1.2;
        caster->enemy->health -= total_damage;
        caster->mana -= mana_cost;
    }
    else{
        slog("not enough mana, couldn't cast fireball");
    }
}
void *burn(Entity *caster);
void *quench(Entity *caster); // removes a damage over time from self - water
void *flush(Entity *caster); // reshuffles hand - water
void *purify(Entity *caster); // removes a hex from self - light
void *heal(Entity *caster){
    Uint32 mana_cost = 8;
    Uint32 total_heal = 50;
    int health_difference;
    health_difference = caster->health - caster->max_health;
    if(caster->mana >= mana_cost){
        if(health_difference > 0) caster->health = caster->max_health;
        else caster->health += total_heal; 
        caster->mana -= mana_cost;
    }
    else{
        slog("not enough mana, couldn't cast heal");
    }
} // heals self for x amount - light
void *shield(Entity *cater); // reduces damage by x amount - earth
void *entangle(Entity *caster){
    Uint32 mana_cost = 15;
    Uint32 total_damage = 30;
    Uint32 mana_drain = 5;
    if(caster->mana >= mana_cost){
        if(caster->enemy->school == WATER_SCHOOL) total_damage *= 1.2;
        caster->enemy->health -= total_damage; //damages enemy
        if(caster->enemy->mana >= mana_drain) caster->enemy->mana -= mana_drain; //drains mana
        //turn = caster->ent_turn; //gives turn control back to caster(need to figure this out still)
        caster->mana -= mana_cost;
    }
} // does x earth damage forces enemy to pass and drains some of opponents mana - earth
void *weaken(Entity *caster); // reduces damage of enemy next void - dark
void *drain(Entity *caster){
    Uint32 mana_cost = 10;
    Uint32 total_damage = 60;
    if(caster->mana >= mana_cost){
        if(caster->enemy->school != LIGHT_SCHOOL) total_damage *= 1.1;
        caster->enemy->health -= total_damage; //damages enemy
        caster->health += total_damage / 2;
        caster->mana -= mana_cost;
    }
}


