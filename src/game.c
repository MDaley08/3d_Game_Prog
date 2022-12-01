#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_input.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gfc_audio.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_particle.h"
#include "gf3d_draw.h"
#include "gf3d_lights.h"

#include "gf2d_sprite.h"
#include "gf2d_font.h"
#include "gf2d_draw.h"
#include "gf2d_actor.h"
#include "gf2d_mouse.h"
#include "gf2d_windows.h"
#include "gf2d_windows_common.h"

#include "entity.h"
#include "player.h"
#include "world.h"
#include "ui.h"
#include "monster.h"
#include "combat.h"

extern int __DEBUG;

static int _done = 0;
static Window *_quit = NULL;

void onCancel(void *data)
{
    _quit = NULL;
}

void onExit(void *data)
{
    _done = 1;
    _quit = NULL;
}

void exitGame()
{
    _done = 1;
}

void exitCheck()
{
    if (_quit)return;
    _quit = window_yes_no("Exit?",onExit,onCancel,NULL);
}

int main(int argc,char *argv[])
{
    int a;
    World *w;
    World *arena;
    Entity *player;
    Entity *monster;

    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"--debug") == 0)
        {
            __DEBUG = 1;
        }
    }
    
    init_logger("gf3d.log",0);    
    gfc_input_init("config/input.cfg");
    slog("gf3d begin");
    gf3d_vgraphics_init("config/setup.cfg");
    gfc_audio_init(256,16,4,1,1,1);
    gf2d_font_init("config/font.cfg");
    gf3d_draw_init();//3D
    gf2d_draw_manager_init(10000);//2D
    gf2d_actor_init(1024);
    gf2d_windows_init(128,"config/windows.cfg");
    gf2d_mouse_load("actors/mouse.actor");
    entity_system_init(1024);
    
    slog_sync();
    
        
    w = world_load("config/testworld.json");
    arena = world_load("config/arena.json");
    
    SDL_SetRelativeMouseMode(SDL_TRUE);
    slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));
    player = player_new(vector3d(0,0,1.5),vector3d(M_PI,0,M_PI/2));
    monster_new("config/monster.json",UNDEAD,vector3d(-50,0,1.5),vector3d(M_PI,0,M_PI/2));
    monster_new("config/monster.json",GOLEM,vector3d(-50,20,1.5),vector3d(M_PI,0,M_PI/2));
    monster_new("config/monster.json",DRAGON,vector3d(-50,40,1.5),vector3d(M_PI,0,M_PI/2));
    monster_new("config/monster.json",MERMAID,vector3d(-50,-20,1.5),vector3d(M_PI,0,M_PI/2));
    monster_new("config/monster.json",SENTINEL,vector3d(-50,-40,1.5),vector3d(M_PI,0,M_PI/2));
    
    
    // main game loop
    slog("gf3d main loop begin");
    while(!_done)
    {
        gfc_input_update();
        gf2d_mouse_update();
        gf2d_font_update();
        gf2d_windows_update_all();
        world_run_updates(w);
        world_run_updates(arena);
        entity_think_all();
        entity_update_all();
        entity_collison_check_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());


    
        
        gf3d_vgraphics_render_start();

            //3D draws
                
                world_draw(w);
                world_draw(arena);
                entity_draw_all();
                ui_draw(player);
                if(player->in_combat)combat(player);
                //2D draws
                gf2d_windows_draw_all();
                gf2d_mouse_draw();
                //if(player->in_combat)combat(player);
        gf3d_vgraphics_render_end();

        if ((gfc_input_command_down("exit"))&&(_quit == NULL))
        {
            exitCheck();
        }
        
    }    
    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
