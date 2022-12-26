//=============================================================================
//
// タイトルクラス(title.cpp)
// Author : 唐﨑結斗
// 概要 : タイトルクラスの管理を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "title.h"
#include "bg.h"
#include "application.h"
#include "keyboard.h"
#include "object2D.h"
#include "2Dparticle.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CTitle::CTitle() : m_bOnce(true),
m_titleBehavior(TITLE_LOGOSKIP)
{
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CTitle::Init()
{
	CSound *pSound = CApplication::GetSound();

	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

	//----------------------------------------------------------------------
	// ２Dオブジェクト関係
	//----------------------------------------------------------------------
	auto ObjCreate = [](D3DXVECTOR3 pos, D3DXVECTOR3 size, int texNum){
		CObject2D* pObj = nullptr;
		pObj = CObject2D::Create();
		pObj->SetSize(size);
		pObj->SetPos(pos);
		pObj->LoadTex(texNum);
		return pObj;
	};

	// 背景の生成
	m_pBg = CBG::Create();
	m_pBg->LoadTex(7);

	// どすこいパラダイス
	// タイトルロゴの生成
	m_titleLogo.resize(2);
	m_titleLogo[0] = ObjCreate(D3DXVECTOR3(450.0f, -10.0f, 0.0f), D3DXVECTOR3(500.0f, 400.0f, 0.0f), 4);	// どすこい
	m_titleLogo[1] = ObjCreate(D3DXVECTOR3(800.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 5);	// パラダイス

	// PressEnterの生成
	m_pPressEnter = ObjCreate(D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f), 9);

	// セレクトの文字の生成
	m_selectLogo.resize(2);
	m_selectLogo[0] = ObjCreate(D3DXVECTOR3(400.0f, 550.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 13);	// タイトル
	m_selectLogo[1] = ObjCreate(D3DXVECTOR3(900.0f, 550.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 14);	// チュートリアル

	// 力士の生成
	m_pSumou = ObjCreate(D3DXVECTOR3(1400.0f, 600.0f, 0.0f), D3DXVECTOR3(100.0f, 170.0f, 0.0f), 8);
	m_rikishiCounter = 0;
	m_walkCounter = 0;

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CTitle::Uninit()
{
	if (!m_titleLogo.empty())
	{
		m_titleLogo.clear();
	}

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CTitle::Update()
{
	// 入力情報の取得
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// サウンドの取得
	CSound *pSound = CApplication::GetSound();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		switch (m_titleBehavior)
		{
		case TITLE_LOGOSKIP:
			m_titleLogo[0]->SetPos(D3DXVECTOR3(450.0f, 240.0f, 0.0f));
			m_titleLogo[1]->SetPos(D3DXVECTOR3(800.0f, 240.0f, 0.0f));
			m_titleLogoCounter = 100;
			m_titleBehavior = TITLE_PRESS_ENTER;
			break;

		case TITLE_PRESS_ENTER:
			m_pPressEnter->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
			m_selectLogo[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_selectLogo[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_titleBehavior = TITLE_SELECT;
			break;

		case TITLE_SELECT:
			switch (m_select)
			{
			case SELECT_GAME:
				pSound->StopSound(CSound::SOUND_LABEL_BGM000);
				CApplication::SetNextMode(CApplication::MODE_GAME);
				break;

			case SELECT_TUTORIAL:
				pSound->StopSound(CSound::SOUND_LABEL_BGM000);
				CApplication::SetNextMode(CApplication::MODE_TUTORIAL);
				break;

			default:
				assert(false);
				break;
			}
			break;

		default:
			assert(false);
			break;
		}
	}

	if (pKeyboard->GetTrigger(DIK_D))
	{
		m_select++;
	}
	if (pKeyboard->GetTrigger(DIK_A))
	{
		m_select--;
	}
	if (m_select > SELECT_MAX - 1 || m_select < 0)
	{
		m_select = 0;
	}

	if (m_titleBehavior == TITLE_SELECT)
	{
		switch (m_select)
		{
		case SELECT_GAME:
			m_selectLogo[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_selectLogo[1]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			break;

		case SELECT_TUTORIAL:
			m_selectLogo[0]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_selectLogo[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		default:
			assert(false);
			break;
		}
	}

	//----------------------------------------------------------------------

	if (m_bOnce)
	{	// １度しか通らないようにする
		// InitでSetColをしてもなぜか色が変わってくれないため、ここに書いてみる
		m_pPressEnter->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_selectLogo[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_selectLogo[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_bOnce = false;
	}

	m_titleLogoCounter++;

	// タイトルロゴ関係
	for (unsigned int i = 0; i < m_titleLogo.size(); i++)
	{
		D3DXVECTOR3 pos = m_titleLogo[i]->GetPos();

		if (m_titleLogoCounter <= 100)
		{	// タイトルロゴが下へ一定の位置まで降りる処理
			pos.y += 2.5f;
			m_titleLogo[i]->SetPos(pos);
		}
		else if (m_titleLogoCounter >= 100)
		{
			if (m_titleBehavior == TITLE_SELECT)
			{
				continue;
			}

			D3DXCOLOR col = m_pPressEnter->GetCol();
			col.a += 0.01f;
			m_pPressEnter->SetCol(col);
		}
	}

	// 力士が歩いてくる処理
	if ((m_titleLogoCounter % 50) == 0)
	{
		D3DXVECTOR3 pos = m_pSumou->GetPos();
		float move = 0.0f;

		// 力士の動く速度
		if (m_rikishiCounter == 0)
		{
			move = -5.0f;
		}
		else if (m_rikishiCounter == 1)
		{
			move = 5.0f;
		}

		// 力士がある一定の場所を過ぎた場合
		if (pos.x <= -200.0f)
		{
			m_rikishiCounter = 1;
		}
		else if (pos.x >= 1400.0f)
		{
			m_rikishiCounter = 0;
		}

		// 歩く度に傾きを入れるための処理
		if ((m_walkCounter % 1) == 0)
		{
			m_pSumou->SetRot(D3DXVECTOR3(0.0f,0.0f,-0.1f));
		}
		if ((m_walkCounter % 2) == 0)
		{
			m_pSumou->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
		}

		m_walkCounter++;
		pos.x += move;
		m_pSumou->SetPos(pos);
	}

	//----------------------------------------------------------------------

	// パーティクル（塩のつもり）
	if((m_titleLogoCounter % 10) == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			// 右から
			{
				C2DEffect::SInfo effectData = {};
				std::vector<std::string> list;

				effectData.pos = D3DXVECTOR3(1300.0f, 150.0f, 0.0f);
				effectData.move = D3DXVECTOR3(-6.0f, -5.0f, 0.0f);
				effectData.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				effectData.destroyTime = 300;
				effectData.delayTime = 100;
				effectData.gravityPower = (rand() % 100) * 0.01f + 0.2f;
				effectData.numTex = 6;

				list.push_back("Falling");
				effectData.infoProperty = list;
				C2DEffect::Create(effectData);
			}

			// 左から
			{
				C2DEffect::SInfo effectData = {};
				std::vector<std::string> list;

				effectData.pos = D3DXVECTOR3(-100.0f, 150.0f, 0.0f);
				effectData.move = D3DXVECTOR3(6.0f, -5.0f, 0.0f);
				effectData.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				effectData.destroyTime = 300;
				effectData.delayTime = 100;
				effectData.gravityPower = (rand() % 100) * 0.01f + 0.2f;
				effectData.numTex = 6;

				list.push_back("Falling");
				effectData.infoProperty = list;
				C2DEffect::Create(effectData);
			}
		}
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CTitle::Draw()
{

}