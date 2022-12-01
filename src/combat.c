#include "combat.h"
#include "gfc_shape.h"
#include "gf2d_sprite.h"
#include "gf2d_mouse.h"
#include "gf2d_font.h"
#include "spell.h"


Uint8 turn;
void player_action();
void combat(Entity *player)
{
    //make player and enemy turn random in future
    Entity *enemy = player->enemy;
    Uint8 player_turn = player->ent_turn = 0;
    Uint8 enemy_turn = enemy->ent_turn = 1;
    turn = player_turn;
    if (!(player->health <= 0 || player->enemy->health <= 0))
    {
        if (turn == player_turn) // player turn
        {
            player_action();
            if(gf2d_mouse_button_pressed(0)){
                entangle(player);
                turn = enemy_turn;
            }
            
        }
        if (turn == enemy_turn){
            fireball(enemy);
            turn = player_turn;
        }
        //draw a spell from 
    }
    else{
        player->in_combat = 0;
    }
}

void player_action(){
    Sprite *fireball_sprite;
    Sprite *heal_sprite;
    Sprite *shield_sprite;
    Sprite *flush_sprite;
    Sprite *drain_sprite;

    fireball_sprite = gf2d_sprite_load_image("images/cards/fireball.png");
    heal_sprite = gf2d_sprite_load_image("images/cards/heal.png");
    shield_sprite = gf2d_sprite_load_image("images/cards/shield.png");
    flush_sprite = gf2d_sprite_load_image("images/cards/flush.png");
    drain_sprite = gf2d_sprite_load_image("images/cards/drain.png");
    Rect card_pos1 = gfc_rect(100,200,150,200);
    int i;
    int card_pos;
    card_pos = 150;
    Sprite *cards = {fireball_sprite,heal_sprite,shield_sprite,flush_sprite,drain_sprite};

    for(i = 0; i < 5; i++){
        card_pos += 170;
        gf2d_sprite_draw_simple(&cards[i],vector2d(card_pos,200),vector2d(0.43,0.43),3);
    }

}

void card_slot(Spell *spell){

}