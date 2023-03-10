#pragma once

class SceneManager;
// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase(){}
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void End() {}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// シーン終了
	virtual bool IsEnd() { return false; }

};

