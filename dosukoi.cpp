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
#include "2Dparticle.h"
#include "application.h"
#include "game.h"
#include "sound.h"

int CDosukoi::m_MaxMash = 0;
int CDosukoi::m_PlayerNumber = 0;
bool CDosukoi::m_bSiai = true;
bool CDosukoi::m_bBegin = true;
bool CDosukoi::m_bTutorial = false;

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CDosukoi::CDosukoi()
{
	m_MaxMash = 0;
	m_EndCnt = 0;
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CDosukoi::~CDosukoi()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CDosukoi::Init()
{
	auto ObjCreate = [](D3DXVECTOR3 pos, D3DXVECTOR3 size, int texNum) {
		CObject2D* pObj = nullptr;
		pObj = CObject2D::Create();
		pObj->SetSize(size);
		pObj->SetPos(pos);
		pObj->LoadTex(texNum);
		return pObj;
	};

	if (!m_bTutorial)
	{
		CSound *pSound = CApplication::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_HAKEYOI);
	}

	m_bTutorial = false;

	nCnt = 0;
	m_NokotaCnt = 0;
	m_HackeyoiCnt = 0;
	m_bBegin = true;
	m_bSiai = true;
	m_PlayerNumber = -1;

	if (!m_bTutorial)
	{
		// UIの生成
		m_UI.resize(3);
		m_UI[0] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);
		m_UI[1] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 11);
		m_UI[2] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 13);

		// ランダムに最大数を決める
		m_MaxMash = rand() % 50 + 400;
	}

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CDosukoi::Uninit()
{
	if (!m_UI.empty())
	{
		m_UI.clear();
	}


	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CDosukoi::Update()
{
	if (m_bTutorial)
	{
		return;
	}

	nCnt++;

	// はっけよ～い
	if (m_UI[0] != nullptr)
	{
		m_UI[0]->SetSize(D3DXVECTOR3(m_HackeyoiCnt * 6, m_HackeyoiCnt, m_size.z));

		if (m_HackeyoiCnt <= 100)
		{
			m_HackeyoiCnt++;
		}
		else if (nCnt >= 150)
		{
			// UIの破棄
			m_UI[0]->Uninit();
			m_UI[0] = nullptr;

			if (!m_bTutorial)
			{
				CSound *pSound = CApplication::GetSound();

				pSound->PlaySound(CSound::SOUND_LABEL_SE_NOKOTA);
			}
		}
	}
	
	// のこった！
	if (m_UI[1] != nullptr)
	{
		if (nCnt >= 160)
		{
			m_UI[1]->SetSize(D3DXVECTOR3(900.0f,150.0f,0.0f));

			if (nCnt >= 220)
			{
				// 試合を開始する
				m_bBegin = false;

				// UIの破棄
				m_UI[1]->Uninit();
				m_UI[1] = nullptr;
			}
		}
	}
	
	// 試合が終了した時
	if (!m_bSiai)
	{
		m_EndCnt++;

		if (m_EndCnt <= 200)
		{
			m_UI[2]->SetSize(D3DXVECTOR3(m_EndCnt * 6, m_EndCnt, m_size.z));
		}
		
		if (m_EndCnt == 260)
		{
			CGame::SetGame(false);
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CDosukoi::Draw()
{

}
