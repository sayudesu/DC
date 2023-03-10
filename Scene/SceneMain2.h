#pragma once
#include "SceneBase.h"

class DrawMapStage1;
class PlayerNew;
class Collision;
class SelectMenu;
class Fireworks;

class SlideSelect;

class SceneMain2 : public SceneBase
{
public:
	SceneMain2();
	virtual~SceneMain2();

	virtual void Init();
	virtual void End();
	virtual SceneBase* Update() override;
	virtual void Draw();
public:
	//ゲームクリア後の選択を受け取る
	void GetSceneStage(bool scene) { m_isSceneStage = scene; }
	void GetSceneRetry(bool scene) { m_isSceneRetry = scene; }
	void GetSceneTitle(bool scene) { m_isSceneTitle = scene; }
	void GetSceneDead(bool scene) { m_isSceneDead = scene; }
private:
	void GameClear();//ゲームをクリアした場合
private:
	void FadeIn();//フェイドイン
	void FadeOut();//フェイドアウト
private:

	//プレイヤー画像
	int m_hPlayer;
	int m_hPlayerIdle;
	int m_hPlayerLighting;
	int m_hPlayerHealthBer;

	int m_hMusicBgm;//BGM用ハンドル

	float m_fadeValue;//画面の明るさ調整

	bool m_isFadeIn;//フェイドインしたかどうか
	bool m_isFadeOut;//フェイドアウトしたかどうか

	bool m_isSceneStage;//画面が暗くなった後にシーンの切り替え
	bool m_isSceneRetry;//画面が暗くなった後にシーンの切り替え
	bool m_isSceneTitle;//画面が暗くなった後にシーンの切り替え
	bool m_isSceneDead;//画面が暗くなった後にシーンの切り替

	bool m_isGameClear;

	DrawMapStage1* m_pStage;
	PlayerNew* m_pPlayer;
	Collision* m_pCollision;
	SelectMenu* m_pMenu;
	SlideSelect* m_pSlidSelect;
	Fireworks* m_pFireworks;


};



