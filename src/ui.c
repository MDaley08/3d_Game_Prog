#include "gf2d_draw.h"
#include "gf2d_sprite.h"
#include "gf3d_model.h"
#include "gf2d_mouse.h"
#include "gf2d_font.h"

#include "combat.h"
#include "ui.h"

void ui_draw(Entity *player)
{
    float player_health_bar = 300;
    Rect card_pos1 = gfc_rect(100,200,150,200);
    int i;
    int card_pos;
    float mana_bar = 175;
    char  player_health_string[6];
    char  mana_string[6];
    char  enemy_health_string[12];
    card_pos = 150;

    if(!player)return;

    // HP Bar Draw
    sprintf(player_health_string,"%u",player->health);
    gf2d_draw_rect_filled(gfc_rect(65,720,(float)player->health/player->max_health * player_health_bar,22), gfc_color8(255,0,0,220));
    gf2d_draw_rect(gfc_rect(65,720,player_health_bar,22), gfc_color8(255,255,255,255));
    gf2d_font_draw_line_tag(player_health_string,FT_H3,gfc_color(1,1,1,1), vector2d(5,718));

    // Mana Bar Draw
    sprintf(mana_string,"%u",player->mana);
    gf2d_draw_rect_filled(gfc_rect(65,688,(float)player->mana/player->max_mana * mana_bar,22), gfc_color8(0,0,255,220));
    gf2d_draw_rect(gfc_rect(65,688,mana_bar,22), gfc_color8(255,255,255,255));
    gf2d_font_draw_line_tag(mana_string,FT_H3,gfc_color(1,1,1,1), vector2d(5,688));
    
    Sprite *fireball;
    Sprite *heal;
    Sprite *shield;
    Sprite *flush;
    Sprite *drain;

    fireball = gf2d_sprite_load_image("images/cards/fireball.png");
    heal = gf2d_sprite_load_image("images/cards/heal.png");
    shield = gf2d_sprite_load_image("images/cards/shield.png");
    flush = gf2d_sprite_load_image("images/cards/flush.png");
    drain = gf2d_sprite_load_image("images/cards/drain.png");
    
    Sprite *cards = {fireball,heal,shield,flush,drain};
    if(player->in_combat){
        
        //enemy info
        sprintf(enemy_health_string,"%u/%u",player->enemy->health, player->enemy->max_health);
        gf2d_draw_rect_filled(gfc_rect(940,15,180,75), gfc_color8(0,95,157,220));
        gf2d_draw_rect(gfc_rect(940,15,180,75),gfc_color(255,255,255,255));
        gf2d_draw_rect(card_pos1,gfc_color(255,255,255,255));
        gf2d_font_draw_line_tag(player->enemy->name,FT_H3,gfc_color(1,1,1,1), vector2d(950,25));
        gf2d_font_draw_line_tag(enemy_health_string,FT_H5,gfc_color(255,0,0,255), vector2d(970,60));

        for(i = 0; i < 5; i++){
            card_pos += 170;
            gf2d_sprite_draw_simple(&cards[i],vector2d(card_pos,200),vector2d(0.43,0.43),3);
        }
       
        if(gf2d_mouse_in_rect(gfc_rect(940,15,180,75))){
            if(gf2d_mouse_button_pressed(0)){
                
                player->enemy->selected = 1;
            }
        }
    }
}

/*eol@eof*/