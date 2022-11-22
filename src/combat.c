#include "combat.h"
#include "gfc_shape.h"
#include "gf2d_sprite.h"
#include "gf2d_mouse.h"

void combat(Entity *player, Entity *enemy)
{
    /*
    Rect cards[5];
    int i;
    Sprite *fireball;
    Sprite *heal;
    Sprite *shield;
    Sprite *flush;
    Sprite *drain;

    fireball = gf2d_sprite_load_image("images/cards/Drain.png");
    fireball = gf2d_sprite_load_image("images/cards/Drain.png");
    fireball = gf2d_sprite_load_image("images/cards/Drain.png");
    fireball = gf2d_sprite_load_image("images/cards/Drain.png");
    fireball = gf2d_sprite_load_image("images/cards/Drain.png");
    */
    //make player and enemy turn random in future
    int player_turn = 0;
    int enemy_turn = 1;
    int turn;
    int round;
    //Spell player_hand[7];
    //Spell enemy_hand[7]; //hand is a max size of 8 is filled with 8 random random spell from deck

    turn = player_turn;
    while (!(player->health == 0 || enemy->health == 0))
    {
        /*
        for(i = 0; i < 5; i++){
            cards[i] = gfc_rect((card_pos + 170),200,150,200);
            gf2d_draw_rect(cards[i],gfc_color(255,255,255,255));
            card_pos += 170;
        }
        if (turn == player_turn) // player turn
        {
            turn = enemy_turn;
        }
        */
        if (turn == enemy_turn){
            //fireball
            Uint32 damage = 50;
            if(enemy->mana >= 5){
                player->health -= damage;
                enemy->mana -= 5;
            }
            turn = player_turn;
        }

        //draw a spell from 
       round++;
    }
 
}