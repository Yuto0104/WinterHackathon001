//=============================================================================
//
// どすこいクラス(dosukoi.cpp)
// Author : 冨所知生
// 概要 : 相撲のルールを管理する
//
//=============================================================================
#ifndef _DOSUKOI_H_		// このマクロ定義がされてなかったら
#define _DOSUKOI_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "super.h"
#include "object2D.h"

#include <vector>

//=============================================================================
// どすこいクラス
// Author : 冨所知生
// 概要 : 相撲のルールを生成する
//=============================================================================
class CDosukoi : public CObject2D
{
public:
	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CDosukoi();
	~CDosukoi() override;

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

	static void SetWinPlayer(int Number) { m_PlayerNumber = Number; SetSiai(false); }
	static void SetSiai(bool siai) { m_bSiai = siai; }
	static int GetNumber() { return m_PlayerNumber; }
	static int GetMaxMash() { return m_MaxMash; }
	static bool GetSiai() { return m_bSiai; }
	static bool GetBegin() { return m_bBegin; }

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
private:
	static int m_MaxMash;			// 最大連打数の管理
	static int m_PlayerNumber;		// プレイヤーのナンバー
	static bool m_bSiai;			// 試合
	static bool m_bBegin;			// 開始

	// UI
	std::vector<CObject2D*> m_UI;

	// サイズ
	D3DXVECTOR3 m_size;

	int nCnt;
	int m_HackeyoiCnt;
	int m_NokotaCnt;
	int m_EndCnt;
};

#endif

