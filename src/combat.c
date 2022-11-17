#include "combat.h"

void turn(Entity *self);

void combat(Entity *player, Entity *enemy)
{
    Combat->player = *player;
    Combat->enemy = *enemy;
    int player_turn;
    int enemy_turn;
    int turn;
    int round;
    Spell player_hand[7];
    Spell enemy_hand[7]; //hand is a max size of 8 is filled with 8 random random spell from deck

    while (!(player->health == 0 || enemy->health == 0))
    {
        for(turn = 0; turn <= 1; turn++){
            /*
            player does something
            */
           /*
           enemy does something
           */
        }
        //draw a spell from 
       round++;
    }
 
}

void turn(Entity *self){

}