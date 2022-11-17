#include "gf2d_draw.h"
#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "ui.h"
#include "combat.h"

void ui_draw(Entity *player)
{
    float health_bar = 500;
    float mana_bar = 300;
    char  health_string[6];
    char  mana_string[6];
    char  position_string[20];
    if(!player)return;
    // HP Bar Draw
    sprintf(health_string,"%u",player->health);
    gf2d_draw_rect_filled(gfc_rect(60,10,(float)player->health/player->max_health * health_bar,20), gfc_color8(255,0,0,200));
    gf2d_draw_rect(gfc_rect(60,10,health_bar,20), gfc_color8(255,255,255,200));
    gf2d_font_draw_line_tag(health_string,FT_H1,gfc_color(1,1,1,1), vector2d(5,6));
    // Mana Bar Draw
    sprintf(mana_string,"%u",player->mana);
    gf2d_draw_rect_filled(gfc_rect(60,40,(float)player->mana/player->max_mana * mana_bar,20), gfc_color8(0,0,255,200));
    gf2d_draw_rect(gfc_rect(60,40,mana_bar,20), gfc_color8(255,255,255,200));
    gf2d_font_draw_line_tag(mana_string,FT_H1,gfc_color(1,1,1,1), vector2d(5,32));

    if(player->health == 0){ // hp bar on death
        gf2d_draw_rect_filled(gfc_rect(60,10,health_bar,30), gfc_color8(1,1,1,255));
        gf2d_draw_rect(gfc_rect(60,10,health_bar,30), gfc_color8(255,255,255,255));
        gf2d_font_draw_line_tag("GAME OVER",FT_Normal,gfc_color(1,1,1,1), vector2d(260,10));
    }
    if(player->in_combat){
        gf2d_font_draw_line_tag("we are in combat",FT_H1,gfc_color(1,1,1,1), vector2d(5,400));
        gf2d_font_draw_line_tag("we are in c",FT_H1,gfc_color(1,1,1,1), vector2d(5,400));
    }
}

/*eol@eof*/