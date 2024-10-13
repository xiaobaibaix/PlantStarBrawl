#pragma once
#include "Scene.h"
#include "Vector2D.h"
#include "Animation.h"
#include "SceneManager.h"


class SelectScene :
	public Scene
{
public:
	friend class SceneManager;
	friend class GameScene;


	SelectScene();
	~SelectScene();

	void on_enter()override;
	void on_update(int delta_time)override;
	void on_draw(const Camera& camera)override;
	void on_input(const ExMessage& msg)override;
	void on_exit()override;

public:

	enum class PlayerType
	{
		Begin = 0,
		Peashooter,
		Sunflower,
		Invalid
	};

private:
	POINT pos_img_vs = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1p = { 0 };
	POINT pos_img_2p = { 0 };
	POINT pos_img_1p_desc = { 0 };
	POINT pos_img_2p_desc = { 0 };
	POINT pos_img_1p_name = { 0 };
	POINT pos_img_2p_name = { 0 };
	POINT pos_animation_1p = { 0 };
	POINT pos_animation_2p = { 0 };
	POINT pos_img_1p_gravestone = { 0 };
	POINT pos_img_2p_gravestone = { 0 };
	POINT pos_1p_selector_btn_left = { 0 };
	POINT pos_1p_selector_btn_right = { 0 };
	POINT pos_2p_selector_btn_left = { 0 };
	POINT pos_2p_selector_btn_right = { 0 };

	Animation player_animation_1;
	Animation player_animation_2;

	PlayerType plaer_type_1 = PlayerType::Peashooter;
	PlayerType plaer_type_2 = PlayerType::Sunflower;

	bool isUp_left_1 = false;
	bool isUp_right_1 = false;
	bool isUp_left_2 = false;
	bool isUp_right_2 = false;

	IMAGE* but_left_1 = nullptr;
	IMAGE* but_right_1 = nullptr;
	IMAGE* but_left_2 = nullptr;
	IMAGE* but_right_2 = nullptr;


	LPCTSTR str_peashooter = L"Íã¶¹»úÇ¹";
	LPCTSTR str_sunflower = L"ÏòÈÕ¿ûÅÚ";

	int roll_length = 0;

private:
	void put_text(int x, int t, LPCTSTR str);

};