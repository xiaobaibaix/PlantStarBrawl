#include "MenuScene.h"
#include "SceneManager.h"
#include "util.h"

extern IMAGE img_menu_background;
extern SceneManager scene_manager;
MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::on_enter()
{
	std::cout << "进入菜单" << std::endl;
	mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
}

void MenuScene::on_update(int delta_time)
{
}

void MenuScene::on_draw(const Camera& camera)
{
	putImage_alpha(0, 0, &img_menu_background);
}

void MenuScene::on_input(const ExMessage& msg)
{
	if (msg.message==WM_KEYUP) {
		scene_manager.switch_to(SceneManager::Scenetype::Select);
		mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
	}
}

void MenuScene::on_exit()
{
	std::cout << "退出菜单" << std::endl;
}
