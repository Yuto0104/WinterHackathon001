//=============================================================================
//
// チュートリアルクラス(game.cpp)
// Author : 唐﨑結斗
// 概要 : ゲームクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "tutorial.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "camera.h"
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "model3D.h"
#include "mesh.h"
#include "bg.h"
#include "debug_proc.h"
#include "model_obj.h"
#include "sphere.h"
#include "player.h"
#include "model3D.h"
#include "dosukoi.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CMesh3D *CTutorial::m_pMesh3D = nullptr;									// メッシュクラス
D3DXCOLOR CTutorial::fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// フォグカラー
float CTutorial::fFogStartPos = 0.0f;										// フォグの開始点
float CTutorial::fFogEndPos = 0.0f;											// フォグの終了点
float CTutorial::fFogDensity = 0.0f;										// フォグの密度
bool CTutorial::m_bGame = false;											// ゲームの状況

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTutorial::CTutorial() : m_mode(TUTORIAL_PUSH)
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CTutorial::Init()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();
	CKeyboard *pKeybord = CApplication::GetKeyboard();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 重力の値を設定
	CCalculation::SetGravity(10.0f);

	CDosukoi *pDosukoi = new CDosukoi;
	pDosukoi->SetTutorial(true);
	pDosukoi->Init();

	// プレイヤーの生成
	CPlayer *pPlayer1 = CPlayer::Create();
	pPlayer1->SetPos(D3DXVECTOR3(70.0f, 45.0f, 0.0f));
	pPlayer1->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pPlayer1->SetNumber(0);
	CModel3D *pModel = pPlayer1->GetModel();
	pModel->SetModelID(3);

	// プレイヤー2の生成
	CPlayer *pPlayer2 = CPlayer::Create();
	pPlayer2->SetPos(D3DXVECTOR3(-70.0f, 45.0f, 0.0f));
	pPlayer2->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	pPlayer2->SetNumber(1);
	pPlayer2->SetVSNumber(0);
	CModel3D *pModel2 = pPlayer2->GetModel();
	pModel2->SetModelID(4);

	// 地面の設定
	m_pMesh3D = CMesh3D::Create();
	m_pMesh3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetSize(D3DXVECTOR3(5000.0f, 0, 5000.0f));
	m_pMesh3D->SetBlock(CMesh3D::DOUBLE_INT(10, 10));
	m_pMesh3D->SetSplitTex(true);

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

	// マウスカーソルを消す
	pMouse->SetShowCursor(false);

	// フォグの数値設定
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// フォグカラー
	fFogStartPos = 1.0f;								// フォグの開始点
	fFogEndPos = 100000.0f;								// フォグの終了点
	fFogDensity = 0.00001f;								// フォグの密度

	// フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// フォグカラーの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// フォグの範囲設定
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// フォグの密度の設定
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	m_pObj.resize(3);
	m_pObj[0] = CObject2D::Create();
	m_pObj[0]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObj[0]->SetSize(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));
	m_pObj[0]->LoadTex(16);

	m_pObj[1] = CObject2D::Create();
	m_pObj[1]->SetPos(D3DXVECTOR3(1000.0f, 690.0f, 0.0f));
	m_pObj[1]->SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));
	m_pObj[1]->LoadTex(9);

	m_pObj[2] = CObject2D::Create();
	m_pObj[2]->SetPos(D3DXVECTOR3(1000.0f, 100.0f, 0.0f));
	m_pObj[2]->SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));
	m_pObj[2]->LoadTex(17);
	m_pObj[2]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));

	m_bGame = true;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTutorial::Uninit()
{// マウスの取得
	CMouse *pMouse = CApplication::GetMouse();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// マウスカーソルを出す
	pMouse->SetShowCursor(true);

	// カメラの追従設定
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetFollowTarget(false);
	pCamera->SetTargetPosR(false);

	// 静的変数の初期化
	if (m_pMesh3D != nullptr)
	{
		m_pMesh3D = nullptr;
	}

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CTutorial::Update()
{
	// キーボードの取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

#ifdef _DEBUG   
	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CApplication::SetNextMode(CApplication::MODE_TITLE);
	}

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		CCamera *pCamera = CApplication::GetCamera();
		pCamera->Zoom();
	}

#endif // _DEBUG

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		switch (m_mode)
		{
		case CTutorial::TUTORIAL_PUSH:
			m_pObj[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pObj[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pObj[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_mode = TUTORIAL_END;
			break;

		case CTutorial::TUTORIAL_END:
			CApplication::SetNextMode(CApplication::MODE_TITLE);
			break;

		default:
			assert(false);
			break;
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CTutorial::Draw()
{
}
