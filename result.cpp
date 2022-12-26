//=============================================================================
//
// リザルトクラス(result.cpp)
// Author : 唐﨑結斗
// 概要 : リザルトクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "result.h"
#include "keyboard.h"
#include "object2D.h"
#include "camera.h"
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "model3D.h"
#include "debug_proc.h"
#include "model_obj.h"
#include "sphere.h"
#include "player.h"
#include "model3D.h"
#include "dosukoi.h"
#include "sound.h"

//=============================================================================
// コンストラクタ

// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CResult::CResult()
{
	m_nextMode = CApplication::MODE_NONE;		// 次に設定するモード
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CResult::Init()
{
	CSound *pSound = CApplication::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	// プレイヤーの生成
	CPlayer *pPlayer1 = CPlayer::Create();
	pPlayer1->SetPos(D3DXVECTOR3(70.0f, 45.0f, 0.0f));
	pPlayer1->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.4f, 0.0f));
	pPlayer1->SetNumber(0);
	CModel3D *pModel = pPlayer1->GetModel();
	pModel->SetModelID(3);

	// プレイヤー2の生成
	CPlayer *pPlayer2 = CPlayer::Create();
	pPlayer2->SetPos(D3DXVECTOR3(-70.0f, 45.0f, 0.0f));
	pPlayer2->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.4f, 0.0f));
	pPlayer2->SetNumber(1);
	CModel3D *pModel2 = pPlayer2->GetModel();
	pModel2->SetModelID(4);

	// カメラの追従設定(目標 : プレイヤー)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 130.0f, -400.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 50.0f, 100.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// モデルの設置
	CModelObj::LoadFile("data/FILE/BG_model.txt");

	// スカイボックスの設定
	CSphere *pSphere = CSphere::Create();
	pSphere->SetRot(D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f));
	pSphere->SetSize(D3DXVECTOR3(100.0f, 0, 100.0f));
	pSphere->SetBlock(CMesh3D::DOUBLE_INT(100, 100));
	pSphere->SetRadius(50000.0f);
	pSphere->SetSphereRange(D3DXVECTOR2(D3DX_PI * 2.0f, D3DX_PI * -0.5f));
	pSphere->LoadTex(1);

	// 拳のテクスチャ
	m_pFist = CObject3D::Create();
	m_pFist->SetPos(D3DXVECTOR3(0.0f, 500.0f, 0.0f));
	m_pFist->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
	m_pFist->SetSize(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	m_pFist->SetBillboard(true);
	m_pFist->LoadTex(12);

	// 次に行くモードの設定
	m_nextMode = CApplication::MODE_TITLE;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CResult::Uninit()
{
	CSound *pSound = CApplication::GetSound();
	pSound->StopSound();

	if (m_pFist != nullptr)
	{
		m_pFist->Uninit();
		m_pFist = nullptr;
	}

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CResult::Update()
{
	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	D3DXVECTOR3 pos = m_pFist->GetPos();

	if (pos.y - m_pFist->GetSize().y >= 45.0f)
	{
		pos.y -= 5.0f;
		m_pFist->SetPos(pos);
	}

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CApplication::SetNextMode(m_nextMode);
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CResult::Draw()
{

}

