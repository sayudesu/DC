#pragma once
#include "DrawMapStage1.h"
class DrawMapStage3 : public DrawMapStage1
{
public:
	DrawMapStage3();
	virtual~DrawMapStage3();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();
private:
	void DrawBackground();
	void DrawMap();
private:
	//}bvζ
	int m_hMap1;
	int m_hMap2;
	int m_hMap3;
	int m_hMap4;
	int m_hMap5;
	//}bvnΚAςq
	int m_hTiles;
	int m_hBlock;//nΚp
	//ςq
	int m_hLadderChip;
	int m_hLadder;

	int m_hForest[9];//}bvwiForest
	int m_hForestCut[9];//wiΨθζθ


	//S[ζ
	int m_hMapChip1;//ζf[^
	int m_hBox;// π`ζ
};

