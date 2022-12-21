#include "simple_logger.h"
#include "combat.h"
#include "gfc_shape.h"
#include "gf2d_sprite.h"
#include "gf2d_mouse.h"
#include "gf2d_font.h"
#include "spell.h"
#include "gf2d_draw.h"
#include "gfc_audio.h"

typedef struct
{
    Uint8   slot_id;
    Uint16  card_pos;
    Rect    slot_rect;
    Uint8   in_use;
    Sprite  *card_image;
    void    (*spell)(struct Entity_S *caster);
}Slot;

static Slot *slot_list = NULL;

Uint8 turn;
Uint8 player_turn;
Uint8 enemy_turn;

void player_action();
void slot_init();
void slot_assign(Sprite *cardImage, void *spellCast);
void slot_close();

void combat(Entity *player)
{

    
    //make player and enemy turn random in future
    Entity *enemy = player->enemy;
    //player_turn = player->ent_turn = 0;
    //enemy_turn = enemy->ent_turn = 1;
    turn = player_turn;
    if (!(player->health <= 0 || player->enemy->health <= 0))
    {
        if (turn == player_turn) // player turn
        {
            player_action(player);
            turn = enemy_turn;
        }
        if (turn == enemy_turn)
        {
            //fireball(enemy);
            turn = player_turn;
        }
    }
    else
    {
        //hard coding what occurs after death of enemy. need to resolve later
        player->in_combat = 0;
        player->mat.position.x = 0;
        player->mat.position.y = 0;
        player->mat.position.z = 1.5;
        entity_free(enemy);
    }
}

void player_action(Entity *self)
{
    Sprite *fireball_sprite;
    Sprite *heal_sprite;
    Sprite *shield_sprite;
    Sprite *flush_sprite;
    Sprite *drain_sprite;
    int cast;
    int status;

    fireball_sprite = gf2d_sprite_load_image("images/cards/fireball.png");
    heal_sprite = gf2d_sprite_load_image("images/cards/heal.png");
    shield_sprite = gf2d_sprite_load_image("images/cards/shield.png");
    drain_sprite = gf2d_sprite_load_image("images/cards/drain.png");
    Rect card_pos1 = gfc_rect(100,200,150,200);
    int i;
    int card_pos = 150;

    Sprite *cards = {fireball_sprite,drain_sprite};
    void   *spells = {fireball,drain};
    // how slots occurs look at if statements for how to make dynamic  

    for(i = 0; i < 1; i++){ // how images are drawn and in rect check for mouse and click. also debug
        slot_assign(&cards[i],&spells[i]);
        gf2d_sprite_draw_simple(slot_list[i].card_image,vector2d(slot_list[i].card_pos,200),vector2d(0.43,0.43),3);
        if(gf2d_mouse_in_rect(slot_list[i].slot_rect)){
            if(gf2d_mouse_button_pressed(0)){
            slot_list[i].spell(self);
            } 
        }  
    }

    // while(status){
    //     if(slot_list[i].in_use){
    //         if(gf2d_mouse_in_rect(slot_list[i].slot_rect)){
    //             if(gf2d_mouse_button_pressed(0)){
    //                 slot_list[i].spell(self);
    //             }
    //         }
    //     }
    // }

/*
    for(i = 0; i < 4; i++)
    {
        card_pos += 170;
        gf2d_sprite_draw_simple(&cards[i],vector2d(card_pos,200),vector2d(0.43,0.43),3);
    }
    if(gf2d_mouse_in_rect(gfc_rect(320,200,150,200))){
        if(gf2d_mouse_button_pressed(0)){
            fireball(self);
        } 
    }
    if(gf2d_mouse_in_rect(gfc_rect(490,200,150,200))){
        if(gf2d_mouse_button_pressed(0)){
            heal(self);
        } 
    }
*/
}

void slot_init()
{
    int i;
    int card_pos = 320;//initial position to start placing card, hard coded
    slot_list = (Slot *) gfc_allocate_array(sizeof(Slot), 5); //allocating block of memory for list, 5 slots large
    for(i = 0; i < 4; i++){//player hand will have 5 slots at a time
        slot_list[i].card_pos = card_pos;
        slot_list[i].slot_id = i;
        slot_list[i].in_use = 0;
        slot_list[i].slot_rect = gfc_rect(slot_list[i].card_pos,200,150,200);
        card_pos += 170;
    }
}
void slot_assign(Sprite *cardImage, void *spellCast)
{
    int i;
    for(i = 0; i < 4; i++){ // 5 for all the slots to cycle through
        if (!slot_list[i].in_use){
            slot_list[i].in_use = 1;
            slot_list[i].card_image = cardImage;
            slot_list[i].spell = spellCast;  
        }

    }
}
// void slot_test(int val1, char* val2){
//     int i;
//     for(i = 0; i < 5; i++){ // 5 for all the slots to cycle through
//         if (test_list[i].status)continue;//slot in use skip
//         test_list[i].test1 = val1;
//         test_list[i].test2 = val2;
//         test_list[i].status = true;
//         slog(test_list[i].test2);
//         break;
//     }
    
// }