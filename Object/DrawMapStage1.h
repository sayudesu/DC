#pragma once

class DrawMapStage1
{
public:

	DrawMapStage1();
	virtual~DrawMapStage1();

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

	//}bvwiForest
	int m_hForest[9];
	int m_hForestCut[9];//wiΨθζθ


	//S[ζ
	int m_hMapChip1;//ζf[^
	int m_hBox;// π`ζ
};

