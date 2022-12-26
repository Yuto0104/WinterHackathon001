//=============================================================================
//
// プレイヤークラス(player.cpp)
// Author : 唐﨑結斗
// 概要 : プレイヤー生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "player.h"
#include "game.h"
#include "mesh.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"
#include "keyboard.h"
#include "calculation.h"
#include "move.h"
#include "debug_proc.h"
#include "model3D.h"
#include "line.h"
#include "dosukoi.h"
#include "joypad.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CPlayer * CPlayer::Create()
{
	// オブジェクトインスタンス
	CPlayer *pPlayer = nullptr;

	// メモリの解放
	pPlayer = new CPlayer;

	// メモリの確保ができなかった
	assert(pPlayer != nullptr);

	// 数値の初期化
	pPlayer->Init();

	// インスタンスを返す
	return pPlayer;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CPlayer::CPlayer() : m_pMove(nullptr),
m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_fSpeed(0.0f)
{

}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CPlayer::Init()
{
	// 初期化
	CModelObj::Init();

	// 移動クラスのメモリ確保
	m_pMove = new CMove;
	assert(m_pMove != nullptr);
	m_pMove->SetMoving(0.2f, 1.0f, 0.1f, 0.1f);
	m_MashCount = 0;
	m_Rotate = false;

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CPlayer::Uninit()
{
	if (m_pMove != nullptr)
	{// 終了処理
	 // メモリの解放
		delete m_pMove;
		m_pMove = nullptr;
	}

	// 終了処理
	CModelObj::Uninit();

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CPlayer::Update()
{// キーボードの取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// 更新処理
	CModelObj::Update();

	// 位置の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 移動
	pos += Move();

	// 回転
	Rotate();

	// 連打
	Mash();

	// 位置の設定
	SetPos(pos);

	// メッシュの当たり判定
	CMesh3D *pMesh = CGame::GetMesh();

	// 位置の取得
	pos = GetPos();

#ifdef _DEBUG
	// デバック表示
	CDebugProc::Print("プレイヤーの位置 | X : %.3f | Y : %.3f | Z : %.3f |\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("プレイヤーの連打数 %d \n", m_MashCount);
#endif // _DEBUG
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CPlayer::Draw()
{
	// 描画
	CModelObj::Draw();
}

//=============================================================================
// 向きの設定
// Author : 唐﨑結斗
// 概要 : 向きの設定
//=============================================================================
void CPlayer::SetRot(const D3DXVECTOR3 &rot)
{
	CModelObj::SetRot(rot);
	m_rotDest = rot;
}

//=============================================================================
// 移動
// Author : 唐﨑結斗
// 概要 : キー入力で方向を決めて、移動ベクトルを算出する
//=============================================================================
D3DXVECTOR3 CPlayer::Move()
{
	// 変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// キーボードの取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	// キーボードの取得
	CJoypad *pJoypad = CApplication::GetJoy();

	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(CJoypad::JOYKEY_B, m_Number))
	{// 移動方向の更新
		if (m_Rotate)
		{
			// 角度を加算
			m_rotDest.y += 0.2f;
		}

		float rot = GetRot().y - D3DX_PI;

		// 目的の向きの補正
		if (rot >= D3DX_PI)
		{// 移動方向の正規化
			rot -= D3DX_PI * 2;
		}
		else if (rot <= -D3DX_PI)
		{// 移動方向の正規化
			rot += D3DX_PI * 2;
		}

		// 移動量の計算
		move = D3DXVECTOR3(sinf(rot), 0.0f, cosf(rot));
	}

	// 移動情報の計算
	m_pMove->Moving(move);

	// 移動情報の取得
	D3DXVECTOR3 moveing = m_pMove->GetMove();

	// デバック表示
	CDebugProc::Print("移動ベクトル : %.3f\n", m_pMove->GetMoveLength());

	// 目的の向きの補正
	if (m_rotDest.y - GetRot().y >= D3DX_PI)
	{// 移動方向の正規化
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - GetRot().y <= -D3DX_PI)
	{// 移動方向の正規化
		m_rotDest.y += D3DX_PI * 2;
	}

	return moveing;
}

//=============================================================================
// 回転
// Author : 唐﨑結斗
// 概要 : 目的の向きまで回転する
//=============================================================================
void CPlayer::Rotate()
{
	// 向きの取得
	D3DXVECTOR3 rot = GetRot();

	// 向きの更新
	rot.y += (m_rotDest.y - rot.y) * 0.5f;

	// 向きの正規化
	rot.y = CCalculation::RotNormalization(rot.y);

	// 向きの設定
	SetRot(rot);
}

//============================================================================
// 連打の管理処理
// Author : 冨所知生
// 概要 : 連打数を管理する
//============================================================================
void CPlayer::Mash()
{
	// キーボードの取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		m_MashCount++;
	}

	// 連打数の最大数の取得
	int MaxMash = CDosukoi::GetMaxMash();

	// 連打数の最大数の半分
	if (m_MashCount >= MaxMash * 0.5f && m_Rotate == false)
	{
		m_Rotate = true;

		// 勝利したプレイヤーの指定
		CDosukoi::SetWinPlayer(m_Number);
	}

	// 連打数の最大数
	if (m_MashCount >= MaxMash)
	{
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			CApplication::SetNextMode(CApplication::MODE_RESULT);
		}
	}
}