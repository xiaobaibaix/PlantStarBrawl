
#include "util.h"
#include "Atlas.h"
#include "Vector2D.h"
#include "common.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SelectScene.h"
#include "Platform.h"

#pragma comment(lib,"Winmm.lib")

extern const int fps;
extern const int WIN_W;
extern const int WIN_H;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* select_scene = nullptr;

SceneManager scene_manager;
std::vector<Platform> platforms;
bool is_debug = false;
						
IMAGE img_vs;
IMAGE img_1p;
IMAGE img_2p;
IMAGE img_1p_desc;
IMAGE img_2p_desc;
IMAGE img_gravestone_left;
IMAGE img_gravestone_right;
IMAGE img_selector_tip;
IMAGE img_selector_background;
IMAGE img_1p_selector_btn_idle_left;
IMAGE img_1p_selector_btn_idle_right;
IMAGE img_1p_selector_btn_down_left;
IMAGE img_1p_selector_btn_down_right;
IMAGE img_2p_selector_btn_idle_left;
IMAGE img_2p_selector_btn_idle_right;
IMAGE img_2p_selector_btn_down_left;
IMAGE img_2p_selector_btn_down_right;
IMAGE img_peashooter_selector_background_left;
IMAGE img_peashooter_selector_background_right;
IMAGE img_sunflower_selector_background_left;
IMAGE img_sunflower_selector_background_right;

IMAGE img_sky;
IMAGE img_hills;
IMAGE img_platform_large;
IMAGE img_platform_small;

IMAGE img_menu_background;

IMAGE img_1p_cursor;
IMAGE img_2p_cursor;

Atlas atlas_peashooter_idle_left;
Atlas atlas_peashooter_idle_right;
Atlas atlas_peashooter_run_left;
Atlas atlas_peashooter_run_right;
Atlas atlas_peashooter_attack_left;
Atlas atlas_peashooter_attack_right;
Atlas atlas_peashooter_die_left;
Atlas atlas_peashooter_die_right;

Atlas atlas_sunflower_idle_left;
Atlas atlas_sunflower_idle_right;
Atlas atlas_sunflower_run_left;
Atlas atlas_sunflower_run_right;
Atlas atlas_sunflower_attack_left;
Atlas atlas_sunflower_attack_right;
Atlas atlas_sunflower_die_left;
Atlas atlas_sunflower_die_right;

IMAGE img_pea;
Atlas atlas_pea_break;

Atlas atlas_sun;
Atlas atlas_sun_explode;
Atlas atlas_sun_ex;
Atlas atlas_sun_ex_explode;
Atlas atlas_sun_text;

Atlas atlas_run_effect;
Atlas atlas_jump_effect;
Atlas atlas_land_effect;

IMAGE img_1p_winner;
IMAGE img_2p_winner;
IMAGE img_winner_bar;

IMAGE img_avatar_peashooter;
IMAGE img_avatar_sunflower;



void SwitchInputMethod() {
	keybd_event(VK_CONTROL, 0, 0, 0); // 模拟 Ctrl 键按下
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 模拟 Ctrl 键释放
}

void flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); i++) {
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

void load_game_resources() {
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_vs, _T("./resources/VS.png"));
	loadimage(&img_1p, _T("./resources/1p.png"));
	loadimage(&img_2p, _T("./resources/2p.png"));
	loadimage(&img_1p_desc, _T("resources/1p_desc.png"));
	loadimage(&img_2p_desc, _T("resources/2p_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1p_selector_btn_idle_right, _T("resources/1p_selector_btn_idle.png"));
	flip_image(&img_1p_selector_btn_idle_right, &img_1p_selector_btn_idle_left);
	loadimage(&img_1p_selector_btn_down_right, _T("resources/1p_selector_btn_down.png"));
	flip_image(&img_1p_selector_btn_down_right, &img_1p_selector_btn_down_left);
	loadimage(&img_2p_selector_btn_idle_right, _T("resources/2p_selector_btn_idle.png"));
	flip_image(&img_2p_selector_btn_idle_right, &img_2p_selector_btn_idle_left);
	loadimage(&img_2p_selector_btn_down_right, _T("resources/2p_selector_btn_down.png"));
	flip_image(&img_2p_selector_btn_down_right, &img_2p_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));
	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_1p_cursor, _T("resources/1p_cursor.png"));
	loadimage(&img_2p_cursor, _T("resources/2p_cursor.png"));

	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flip_atlas(atlas_peashooter_attack_right, atlas_peashooter_attack_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flip_atlas(atlas_sunflower_attack_right, atlas_sunflower_attack_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));

	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1p_winner, _T("resources/1p_winner.png"));
	loadimage(&img_2p_winner, _T("resources/2p_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winnner_bar.png"));

	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}


int main() {

	srand(time(0));
	ExMessage msg;

	initgraph(WIN_W, WIN_H, EW_SHOWCONSOLE);
	load_game_resources();

	setbkmode(TRANSPARENT);
	settextstyle(28, 0, _T("IPix"));


	game_scene = new GameScene();
	menu_scene = new MenuScene();
	select_scene = new SelectScene();

	scene_manager.set_current_scene(menu_scene);

	//SwitchInputMethod();

	DWORD start_time = GetTickCount();
	DWORD end_time = GetTickCount();
	BeginBatchDraw();
	while (true) {
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}

		scene_manager.on_update(end_time - start_time);

		cleardevice();
		scene_manager.on_draw();
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_start_time - frame_end_time;
		if (frame_delta_time < 1000 / fps) {
			Sleep(1000 / fps - frame_delta_time);
		}
		start_time =end_time;
		end_time = GetTickCount();
	}
	EndBatchDraw();

	return 0;
}
