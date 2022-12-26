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

//=============================================================================
// どすこいクラス
// Author : 冨所知生
// 概要 : 相撲のルールを生成する
//=============================================================================
class CDosukoi : public CSuper
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

	static void SetWinPlayer(int Number) { m_PlayerNumber = Number; }
	static int GetMaxMash() { return m_MaxMash; }

	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
private:
	static int m_MaxMash;			// 最大連打数の管理
	static int m_PlayerNumber;		// プレイヤーのナンバー
};

#endif

