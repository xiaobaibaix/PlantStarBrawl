#include "SelectScene.h"
#include "GameScene.h"

extern IMAGE img_vs;
extern IMAGE img_1p;
extern IMAGE img_2p;
extern IMAGE img_1p_desc;
extern IMAGE img_2p_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;

extern IMAGE img_1p_selector_btn_idle_left;
extern IMAGE img_1p_selector_btn_idle_right;
extern IMAGE img_1p_selector_btn_down_left;
extern IMAGE img_1p_selector_btn_down_right;

extern IMAGE img_2p_selector_btn_idle_left;
extern IMAGE img_2p_selector_btn_idle_right;
extern IMAGE img_2p_selector_btn_down_left;
extern IMAGE img_2p_selector_btn_down_right;

extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;

extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;

extern SceneManager scene_manager;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::on_enter()
{
	std::cout << "进入选择" << std::endl;
	player_animation_1.set_atlas(&atlas_peashooter_idle_right);
	player_animation_1.set_interval(100);
	player_animation_1.set_loop(true);

	player_animation_2.set_atlas(&atlas_sunflower_idle_left);
	player_animation_2.set_interval(100);
	player_animation_2.set_loop(true);

	but_left_1 = &img_1p_selector_btn_idle_left;
	but_right_1 =&img_1p_selector_btn_idle_right;
	but_left_2 = &img_2p_selector_btn_idle_left;
	but_right_2 = &img_2p_selector_btn_idle_right;

	static const int OFFSET_X = 50;

	pos_img_vs.x = (getwidth() - img_vs.getwidth()) / 2;
	pos_img_vs.y = (getheight() - img_vs.getheight()) / 2;
	pos_img_tip.x = (getwidth()-img_selector_tip.getwidth()) / 2;
	pos_img_tip.y = getheight() - 125;
	pos_img_1p.x = (getwidth() / 2 - img_1p.getwidth()) / 2 - OFFSET_X;
	pos_img_1p.y = 35;
	pos_img_2p.x = getwidth() / 2 + (getwidth() / 2 - img_2p.getwidth()) / 2 + OFFSET_X;
	pos_img_2p.y = 35;
	pos_img_1p_desc.x = (getwidth() / 2 - img_1p_desc.getwidth()) / 2 - OFFSET_X;
	pos_img_1p_desc.y = getheight() - 150;
	pos_img_2p_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2p_desc.getwidth()) / 2 + OFFSET_X;
	pos_img_2p_desc.y = getheight() - 150;
	pos_img_1p_name.y = 380;
	pos_img_2p_name.y = 380;

	pos_animation_1p.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X + OFFSET_X*2;
	pos_animation_1p.y= 150+OFFSET_X*2-20;
	pos_animation_2p.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X + OFFSET_X*2;
	pos_animation_2p.y = 150 + OFFSET_X*2-20;

	pos_img_1p_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2-OFFSET_X;
	pos_img_1p_gravestone.y= 150;
	pos_img_2p_gravestone.x = getwidth() / 2+(getwidth() / 2 - img_gravestone_left.getwidth()) / 2+ OFFSET_X;
	pos_img_2p_gravestone.y = 150;

	pos_1p_selector_btn_left.x = (getwidth() / 4 - img_1p_selector_btn_idle_left.getwidth() / 2) / 2- (OFFSET_X+15);
	pos_1p_selector_btn_left.y = 250;
	pos_1p_selector_btn_right.x = getwidth() / 4 + (getwidth() / 4 - img_1p_selector_btn_idle_left.getwidth() / 2) / 2- (OFFSET_X + 15);
	pos_1p_selector_btn_right.y = 250;
	pos_2p_selector_btn_left.x = getwidth() / 2+(getwidth() / 4 - img_1p_selector_btn_idle_left.getwidth() / 2) / 2+ (OFFSET_X)-10;
	pos_2p_selector_btn_left.y = 250;
	pos_2p_selector_btn_right.x= getwidth() / 2 +getwidth() / 4 + (getwidth() / 4 - img_1p_selector_btn_idle_left.getwidth() / 2) / 2+ (OFFSET_X)-10;
	pos_2p_selector_btn_right.y = 250;
}

void SelectScene::on_update(int delta_time)
{

	player_animation_1.on_update(delta_time);
	player_animation_2.on_update(delta_time);

	if (isUp_left_1||isUp_right_1) {
		switch (plaer_type_1)
		{
		case SelectScene::PlayerType::Begin:
			break;
		case SelectScene::PlayerType::Peashooter:
			player_animation_1.set_atlas(&atlas_peashooter_idle_right);
			break;
		case SelectScene::PlayerType::Sunflower:
			player_animation_1.set_atlas(&atlas_sunflower_idle_right);
			break;
		case SelectScene::PlayerType::Invalid:
			break;
		default:
			break;
		}
		isUp_left_1 = isUp_right_1 = false;
	}
	if(isUp_left_2||isUp_right_2){
		switch (plaer_type_2)
		{
		case SelectScene::PlayerType::Begin:
			break;
		case SelectScene::PlayerType::Peashooter:
			player_animation_2.set_atlas(&atlas_peashooter_idle_left);
			break;
		case SelectScene::PlayerType::Sunflower:
			player_animation_2.set_atlas(&atlas_sunflower_idle_left);
			break;
		case SelectScene::PlayerType::Invalid:
			break;
		default:
			break;
		}
		isUp_left_2 = isUp_right_2 = false;
	}
	roll_length += 1;
	if (roll_length>= img_peashooter_selector_background_right.getwidth()) {
		roll_length = 0;
	}
}

void SelectScene::on_draw(const Camera&camera)
{
	putImage_alpha(0, 0, &img_selector_background);

	switch (plaer_type_1)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		putImage_alpha(roll_length - img_peashooter_selector_background_right.getwidth(),
			0, &img_peashooter_selector_background_right);
		putImage_alpha(roll_length, 0,
			img_peashooter_selector_background_right.getwidth() - roll_length, 0,
			0, 0, &img_peashooter_selector_background_right);
		break;
	case SelectScene::PlayerType::Sunflower:
		putImage_alpha(roll_length - img_sunflower_selector_background_right.getwidth(),
			0, &img_sunflower_selector_background_right);
		putImage_alpha(roll_length, 0,
			img_sunflower_selector_background_right.getwidth() - roll_length, 0,
			0, 0, &img_sunflower_selector_background_right);
		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	switch (plaer_type_2)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		putImage_alpha(getwidth() - img_peashooter_selector_background_left.getwidth(),0,
			img_peashooter_selector_background_left.getwidth() - roll_length, 0,
			roll_length, 0,
			&img_peashooter_selector_background_left);
		putImage_alpha(getwidth() - roll_length, 0, &img_peashooter_selector_background_left);
		break;
	case SelectScene::PlayerType::Sunflower:
		putImage_alpha(getwidth()- img_sunflower_selector_background_left.getwidth(),0,
			img_sunflower_selector_background_left.getwidth()-roll_length,0,
			roll_length,0,
			&img_sunflower_selector_background_left);
		putImage_alpha(getwidth()-roll_length,0, &img_sunflower_selector_background_left);
		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	putImage_alpha(pos_img_vs.x, pos_img_vs.y, &img_vs);
	putImage_alpha(pos_img_1p.x, pos_img_1p.y, &img_1p);
	putImage_alpha(pos_img_2p.x, pos_img_2p.y, &img_2p);

	putImage_alpha(pos_img_1p_desc.x, pos_img_1p_desc.y, &img_1p_desc);
	putImage_alpha(pos_img_2p_desc.x, pos_img_2p_desc.y, &img_2p_desc);

	putImage_alpha(pos_img_1p_gravestone.x, pos_img_1p_gravestone.y, &img_gravestone_right);
	putImage_alpha(pos_img_2p_gravestone.x, pos_img_2p_gravestone.y, &img_gravestone_left);

	player_animation_1.on_draw(camera, pos_animation_1p.x, pos_animation_1p.y);
	player_animation_2.on_draw(camera, pos_animation_2p.x, pos_animation_2p.y);

	putImage_alpha(pos_1p_selector_btn_left.x, pos_1p_selector_btn_left.y,	but_left_1 );
	putImage_alpha(pos_1p_selector_btn_right.x, pos_1p_selector_btn_right.y,but_right_1);
	putImage_alpha(pos_2p_selector_btn_left.x, pos_2p_selector_btn_left.y,	but_left_2 );
	putImage_alpha(pos_2p_selector_btn_right.x, pos_2p_selector_btn_right.y,but_right_2);

	switch (plaer_type_1)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		pos_img_1p_name.x = pos_img_1p_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter)) / 2;
		put_text(pos_img_1p_name.x, pos_img_1p_name.y, str_peashooter);
		break;
	case SelectScene::PlayerType::Sunflower:
		pos_img_1p_name.x = pos_img_1p_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower)) / 2;
		put_text(pos_img_1p_name.x, pos_img_1p_name.y, str_sunflower);
		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	switch (plaer_type_2)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		pos_img_2p_name.x = pos_img_2p_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter)) / 2;
		put_text(pos_img_2p_name.x, pos_img_2p_name.y, str_peashooter);
		break;
	case SelectScene::PlayerType::Sunflower:
		pos_img_2p_name.x = pos_img_2p_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower)) / 2;
		put_text(pos_img_2p_name.x, pos_img_2p_name.y, str_sunflower);
		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	putImage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
}

void SelectScene::on_input(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
		case VK_LEFT:
			but_left_2 = &img_2p_selector_btn_down_left;
			break;
		case VK_RIGHT:
			but_right_2 = &img_2p_selector_btn_down_right;
			break;
		case 0x41:
			but_left_1 = &img_1p_selector_btn_down_left;
			break;
		case 0x44:
			but_right_1 = &img_1p_selector_btn_down_right;
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case VK_RETURN:
		{
			scene_manager.switch_to(SceneManager::Scenetype::Game);
			GameScene* game_scene = dynamic_cast<GameScene*>(scene_manager.current_state);
			if (game_scene) {
				game_scene->setPlayer(plaer_type_1, plaer_type_2);
			}
			break;
		}
		case VK_LEFT:
			but_left_2 = &img_2p_selector_btn_idle_left;
			plaer_type_2 = (PlayerType)((int)plaer_type_2 + 1);
			if (plaer_type_2 == PlayerType::Invalid) {
				plaer_type_2 = (PlayerType)((int)PlayerType::Begin + 1);
			}
			isUp_left_2 = true;
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case VK_RIGHT:
			but_right_2 = &img_2p_selector_btn_idle_right;
			plaer_type_2 = (PlayerType)((int)plaer_type_2 - 1);
			if (plaer_type_2 == PlayerType::Begin) {
				plaer_type_2 = (PlayerType)((int)(PlayerType::Invalid)-1);
			}
			isUp_right_2 = true;
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case 0x41:
			but_left_1= &img_1p_selector_btn_idle_left;
			plaer_type_1 = (PlayerType)((int)plaer_type_1 + 1);
			if (plaer_type_1 == PlayerType::Invalid) {
				plaer_type_1 = (PlayerType)((int)PlayerType::Begin + 1);
			}
			isUp_left_1 = true;
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case 0x44:
			but_right_1 = &img_1p_selector_btn_idle_right;
			plaer_type_1 = (PlayerType)((int)plaer_type_1 - 1);
			if (plaer_type_1 == PlayerType::Begin) {
				plaer_type_1 = (PlayerType)((int)(PlayerType::Invalid)-1);
			}
			isUp_right_1 = true;
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void SelectScene::on_exit()
{
	std::cout << "退出选择" << std::endl;
}

void SelectScene::put_text(int x, int y, LPCTSTR str)
{
	settextcolor(RGB(45, 45, 45));
	outtextxy(x + 3, y + 3, str);
	settextcolor(RGB(255, 255, 255));
	outtextxy(x , y , str);
}
