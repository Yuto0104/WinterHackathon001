//=============================================================================
//
// タイトルクラス(title.cpp)
// Author : 唐�ｱ結斗
// 概要 : タイトルクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "title.h"
#include "application.h"
#include "keyboard.h"
#include "object2D.h"

//=============================================================================
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTitle::CTitle() : m_pTitleLog(nullptr),
m_pPressEnter(nullptr)
{

}

//=============================================================================
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化
// Author : 唐�ｱ結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CTitle::Init()
{
	// タイトルロゴ
	m_pTitleLog = CObject2D::Create();
	m_pTitleLog->SetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f));
	m_pTitleLog->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTitle::Uninit()
{
	if (m_pTitleLog != nullptr)
	{// タイトルロゴの終了
		m_pTitleLog->Uninit();
		m_pTitleLog = nullptr;
	}

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐�ｱ結斗
// 概要 : 更新を行う
//=============================================================================
void CTitle::Update()
{
	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CApplication::SetNextMode(CApplication::MODE_GAME);
	}
}

//=============================================================================
// 描画
// Author : 唐�ｱ結斗
// 概要 : 描画を行う
//=============================================================================
void CTitle::Draw()
{

}