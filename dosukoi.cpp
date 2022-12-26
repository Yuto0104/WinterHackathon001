//=============================================================================
//
// どすこいクラス(dosukoi.cpp)
// Author : 冨所知生
// 概要 : 相撲のルールの生成、管理を行う。
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "dosukoi.h"

int CDosukoi::m_MaxMash = 0;
int CDosukoi::m_PlayerNumber = 0;
bool CDosukoi::m_bSiai = false;
//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CDosukoi::CDosukoi()
{
	m_MaxMash = 0;
}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CDosukoi::~CDosukoi()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CDosukoi::Init()
{
	// ランダムに最大数を決める
	m_MaxMash = rand() % 50 + 100;
	m_MaxMash = 10;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CDosukoi::Uninit()
{
	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新を行う
//=============================================================================
void CDosukoi::Update()
{

}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CDosukoi::Draw()
{

}
