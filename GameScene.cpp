#include "GameScene.h"
#include "SceneManager.h"
#include "util.h"
#include "Platform.h"
#include "Bullet.h"
#include "Player.h"

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

extern SceneManager scene_manager;
extern std::vector<Platform> platforms;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::on_enter()
{
	std::cout << "进入游戏" << std::endl;
	mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

	sky_pos.x = -(img_sky.getwidth() - getwidth()) / 2;
	sky_pos.y = -(img_sky.getheight() - getheight()) / 2;
	hill_pos.x = -(img_hills.getwidth() - getwidth()) / 2;
	hill_pos.y=-(img_hills.getheight() - getheight()) / 2;

	platforms.resize(4);

	Platform *large_form=&platforms.at(0);
	large_form->img = &img_platform_large;
	large_form->pos.x = (getwidth() - img_platform_large.getwidth()) / 2;
	large_form->pos.y = 500;
	large_form->shape.y = large_form->pos.y + 50;
	large_form->shape.left = large_form->pos.x+30;
	large_form->shape.right= large_form->pos.x+ img_platform_large.getwidth()- 30;

	Platform* min1_form = &platforms.at(1);
	min1_form->img = &img_platform_small;
	min1_form->pos.x = (getwidth()/2 - img_platform_small.getwidth()) / 2;
	min1_form->pos.y = 350;
	min1_form->shape.y = min1_form->pos.y + 20;
	min1_form->shape.left = min1_form->pos.x + 30;
	min1_form->shape.right = min1_form->pos.x + img_platform_small.getwidth() - 30;

	Platform* min2_form = &platforms.at(2);
	min2_form->img = &img_platform_small;
	min2_form->pos.x = getwidth() / 2+(getwidth()/2 - img_platform_small.getwidth()) / 2;
	min2_form->pos.y = 350;
	min2_form->shape.y = min2_form->pos.y + 20;
	min2_form->shape.left = min2_form->pos.x + 30;
	min2_form->shape.right = min2_form->pos.x + img_platform_small.getwidth() - 30;

	Platform* min3_form = &platforms.at(3);
	min3_form->img = &img_platform_small;
	min3_form->pos.x = (getwidth() - img_platform_small.getwidth()) / 2;
	min3_form->pos.y = 250;
	min3_form->shape.y = min3_form->pos.y + 20;
	min3_form->shape.left = min3_form->pos.x + 30;
	min3_form->shape.right = min3_form->pos.x + img_platform_small.getwidth() - 30;

	player_bar1 = new StateBar({0,600});
	player_bar2 = new StateBar({0,600});
}

void GameScene::on_update(int delta_time)
{
	if (player1)player1->on_update(delta_time);
	if (player2)player2->on_update(delta_time);

	if(player_bar1&& player1)player_bar1->on_update(delta_time, *player1);
	if(player_bar2&& player2)player_bar2->on_update(delta_time,*player2);

	check_collision();//检查碰撞

	if (!player1->is_living&&!is_win) {
		is_win = true;
		winbar.setWinid(Player::PlayerId::p1);
		winbar.setStop(false);
	}
	else if (!player2->is_living&&!is_win) {
		is_win=true;
		winbar.setWinid(Player::PlayerId::p2);
		winbar.setStop(false);
	}

	if (is_win) {
		winbar.on_update(delta_time);
		if (winbar.getPos().x > 1280&& !is_con) {
			winbar.setStop(true);
		}
	}
}

void GameScene::on_draw(const Camera& camera)
{
	putImage_alpha(camera,sky_pos.x, sky_pos.y, &img_sky);
	putImage_alpha(camera,hill_pos.x, hill_pos.y, &img_hills);

	for (int i = 0; i < 4;i++) {
		platforms.at(i).on_draw(camera);
	}
	if (is_debug) {
		settextcolor(RED);
		outtextxy(0, 0, _T("tab键取消调试模式"));
	}

	if (player1)player1->on_draw(camera);
	if (player2)player2->on_draw(camera);
	//玩家一子弹渲染
	for (Bullet* bullet : player1->getBullet_list()) {
		if (!bullet)break;
		if (!bullet->getRemove())bullet->on_draw(camera);
	}
	//玩家二子弹渲染
	for (Bullet* bullet : player2->getBullet_list()) {
		if (!bullet)break;
		if (!bullet->getRemove())bullet->on_draw(camera);
	}

	player_bar1->on_draw();
	player_bar2->on_draw();

	if (is_win)winbar.on_draw();
}


void GameScene::on_input(const ExMessage& msg)
{
	switch (msg.message) {
	case WM_KEYUP:
		switch (msg.vkcode)
		{
		case VK_TAB:
			is_debug = !is_debug;
			break;
		case VK_ESCAPE:
			scene_manager.switch_to(SceneManager::Scenetype::Select);
			mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
			mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
			break;
		case VK_RETURN :
			if (is_win) {
				is_con = true;
				winbar.setStop(false);
				reset();
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (player1)player1->on_input(msg);
	if (player2)player2->on_input(msg);
}

void GameScene::on_exit()
{
	std::cout << "退出游戏" << std::endl;

	delete player1;
	delete player2;

	player1 = nullptr;
	player2 = nullptr;

	delete player_bar1;
	delete player_bar2;

	player_bar1 = nullptr;
	player_bar2 = nullptr;

}

void GameScene::setPlayer(SelectScene::PlayerType p1, SelectScene::PlayerType p2)
{
	switch (p1)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		player1 = new Peashooter(Player::PlayerId::p1);
		player_bar1->setImg(&img_avatar_peashooter);
		break;
	case SelectScene::PlayerType::Sunflower:
		player1 = new Sunflower(Player::PlayerId::p1);
		player_bar1->setImg(&img_avatar_sunflower);
		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	switch (p2)
	{
	case SelectScene::PlayerType::Begin:
		break;
	case SelectScene::PlayerType::Peashooter:
		player2 = new Peashooter(Player::PlayerId::p2);
		player_bar2->setImg(&img_avatar_peashooter);
		break;
	case SelectScene::PlayerType::Sunflower:
		player2 = new Sunflower(Player::PlayerId::p2);
		player_bar2->setImg(&img_avatar_sunflower);

		break;
	case SelectScene::PlayerType::Invalid:
		break;
	default:
		break;
	}
	player1->setPos({ 280,50 });
	player2->setPos({ 900,50 });

	player_bar1->setPos({ (getwidth()/2-player_bar1->getSize().x-player_bar1->getLength())/2,player_bar1->getPos().y});
	player_bar2->setPos({ getwidth() / 2+(getwidth() / 2 - player_bar1->getSize().x - player_bar1->getLength()) / 2,player_bar1->getPos().y });

}

void GameScene::reset()
{
	player1->reset();
	player2->reset();

}

void GameScene::check_collision()
{
	std::vector<Player::BulletType> bullet_type_list;
	if (player2->is_living) {
		bullet_type_list = player1->collision_bullet(*player2);
		if (!bullet_type_list.empty()) {
			for (const Player::BulletType type : bullet_type_list) {
				switch (type)
				{
				case Player::BulletType::valid:
					break;
				case Player::BulletType::PeaBullet:
					player1->on_collision_to(Player::BulletType::PeaBullet);
					player2->on_collision_from(Player::BulletType::PeaBullet);
					break;
				case Player::BulletType::SunBullet:
					player1->on_collision_to(Player::BulletType::SunBullet);
					player2->on_collision_from(Player::BulletType::SunBullet);
					break;
				case Player::BulletType::SunBulletEx:
					player1->on_collision_to(Player::BulletType::SunBulletEx);
					player2->on_collision_from(Player::BulletType::SunBulletEx);
					break;
				default:
					break;
				}

			}
			bullet_type_list.clear();
		}
	}
	if (player1->is_living) {
		bullet_type_list = player2->collision_bullet(*player1);
		if (!bullet_type_list.empty()) {
			for (const Player::BulletType type : bullet_type_list) {
				switch (type)
				{
				case Player::BulletType::valid:
					break;
				case Player::BulletType::PeaBullet:
					player2->on_collision_to(Player::BulletType::PeaBullet);
					player1->on_collision_from(Player::BulletType::PeaBullet);
					break;
				case Player::BulletType::SunBullet:
					player2->on_collision_to(Player::BulletType::SunBullet);
					player1->on_collision_from(Player::BulletType::SunBullet);
					break;
				case Player::BulletType::SunBulletEx:
					player2->on_collision_to(Player::BulletType::SunBulletEx);
					player1->on_collision_from(Player::BulletType::SunBulletEx);
					break;
				default:
					break;
				}

			}
		}
	}
	
}
