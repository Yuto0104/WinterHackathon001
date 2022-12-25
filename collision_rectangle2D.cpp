//=============================================================================
//
// 2D矩形の衝突判定クラス(collision_rectangle2D.cpp)
// Author : 唐﨑結斗
// 概要 : 2D矩形の衝突判定生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "collision_rectangle2D.h"
#include "application.h"
#include "renderer.h"
#include "object.h"
#include "line.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CCollision_Rectangle2D * CCollision_Rectangle2D::Create()
{
	// オブジェクトインスタンス
	CCollision_Rectangle2D *pCollisionRectangle3D = nullptr;

	// メモリの解放
	pCollisionRectangle3D = new CCollision_Rectangle2D;

	// メモリの確保ができなかった
	assert(pCollisionRectangle3D != nullptr);

	// 数値の初期化
	pCollisionRectangle3D->Init();

	// インスタンスを返す
	return pCollisionRectangle3D;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CCollision_Rectangle2D::CCollision_Rectangle2D()
{
#ifdef _DEBUG
	m_pLine = nullptr;								// ライン情報
	lineCol = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);		// ラインの色
#endif // _DEBUG
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CCollision_Rectangle2D::~CCollision_Rectangle2D()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CCollision_Rectangle2D::Init()
{
	// 当たり判定の取得
	SetType(TYPE_RECTANGLE2D);

	// 位置の取得
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// サイズの取得
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

#ifdef _DEBUG
	// ライン情報
	m_pLine = new CLine*[4];

	for (int nCntLine = 0; nCntLine < 4; nCntLine++)
	{
		m_pLine[nCntLine] = CLine::Create();
	}
#endif // _DEBUG

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CCollision_Rectangle2D::Uninit()
{
#ifdef _DEBUG
	if (m_pLine != nullptr)
	{
		for (int nCntLine = 0; nCntLine < 4; nCntLine++)
		{
			m_pLine[nCntLine]->Uninit();
			m_pLine[nCntLine] = nullptr;
		}

		delete[] m_pLine;
		m_pLine = nullptr;
	}
#endif // _DEBUG

	// スコアの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 更新を行う
//=============================================================================
void CCollision_Rectangle2D::Update()
{

}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 描画を行う
//=============================================================================
void CCollision_Rectangle2D::Draw()
{
	if (GetUseFlag())
	{
#ifdef _DEBUG
		// ラインの更新
		SetLine();
#endif // _DEBUG
	}
}

//=============================================================================
// 当たり判定
// Author : 唐﨑結斗
// 概要 : 当たり判定
//=============================================================================
bool CCollision_Rectangle2D::Collision(CObject::EObjectType objeType, bool bExtrude)
{
#ifdef _DEBUG
	lineCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
#endif // _DEBUG

	// 先頭インスタンスの取得
	CCollision *pCollision = CCollision::GetTop();
	SetCollidedObj();
	bool bCollision = false;

	if (pCollision != nullptr)
	{
		while (pCollision)
		{// 現在のオブジェクトの次のオブジェクトを保管
			CCollision *pCollisionNext = pCollision->GetNext();
			CObject::EObjectType myObjeType = pCollision->GetParent()->GetObjType();

			if (myObjeType == objeType
				&& pCollision != this
				&& pCollision->GetUseFlag()
				&& !pCollision->GetDeathFlag())
			{
				switch (pCollision->GetType())
				{
				case CCollision::TYPE_RECTANGLE2D:
				case CCollision::TYPE_SPHERE:
					bCollision = ToRectangle(pCollision, bExtrude);
					break;

				default:
					assert(false);
					break;
				}
			}

			if (bCollision)
			{// 当たったオブジェクトの設定
				SetCollidedObj(pCollision->GetParent());
				break;
			}

			// 現在のオブジェクトの次のオブジェクトを更新
			pCollision = pCollisionNext;
		}
	}

	return bCollision;
}

//=============================================================================
// 矩形との当たり判定
// Author : 唐﨑結斗
// 概要 : 矩形との当たり判定
//=============================================================================
bool CCollision_Rectangle2D::ToRectangle(CCollision *pTarget, bool bExtrude)
{
	// 返り値用の変数
	bool bColision = false;

	// 自分の情報を取得する
	D3DXVECTOR3 pos = GetParent()->GetPos() + GetPos();
	D3DXVECTOR3 posOld = GetParent()->GetPosOld() + GetPos();
	D3DXVECTOR3 size = GetSize() / 2.0f;

	// 目標の情報取得
	D3DXVECTOR3 posTarget = pTarget->GetParent()->GetPos() + pTarget->GetPos();
	D3DXVECTOR3 sizeTarget = pTarget->GetSize() / 2.0f;

	if ((pos.x - size.x) < (posTarget.x + sizeTarget.x)
		&& (pos.x + size.x) > (posTarget.x - sizeTarget.x)
		&& (pos.y - size.y) < (posTarget.y + sizeTarget.y)
		&& (pos.y + size.y) > (posTarget.y - sizeTarget.y))
	{
		bColision = true;
	}

	if (pos.y - size.y  < posTarget.y + sizeTarget.y
		&& pos.y + size.y  > posTarget.y - sizeTarget.y)
	{// モデル内にいる(Y軸)
		if (posOld.x + size.y <= posTarget.x - sizeTarget.x
			&& pos.x + size.y  > posTarget.x - sizeTarget.x)
		{
			if (bExtrude)
			{// 押し出しを使用する
				pos.x = posTarget.x - sizeTarget.x - size.y;
			}
		}
		if (posOld.x - size.y >= posTarget.x + sizeTarget.x
			&& pos.x - size.y  < posTarget.x + sizeTarget.x)
		{
			if (bExtrude)
			{// 押し出しを使用する
				pos.x = posTarget.x + sizeTarget.x + size.y;
			}
		}
	}
	if (pos.x - size.x  < posTarget.x + sizeTarget.x
		&& pos.x + size.x  > posTarget.x - sizeTarget.x)
	{// モデル内にいる(X軸)
		if (posOld.y + size.y <= posTarget.y - sizeTarget.y
			&& pos.y + size.y  > posTarget.y - sizeTarget.y)
		{
			if (bExtrude)
			{// 押し出しを使用する
				pos.y = posTarget.y - sizeTarget.y - size.y;
			}
		}
		if (posOld.y - size.y >= posTarget.y + sizeTarget.y
			&& pos.y - size.y  < posTarget.y + sizeTarget.y)
		{
			if (bExtrude)
			{// 押し出しを使用する
				pos.y = posTarget.y + sizeTarget.y + size.y;
			}
		}
	}

	if (bColision)
	{// 位置の設定
		CObject *pParent = GetParent();
		pParent->SetPos(pos - GetPos());
#ifdef _DEBUG
		lineCol = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
#endif // DEBUG
	}
	
	return bColision;
}

#ifdef _DEBUG
//=============================================================================
// ラインの設置
// Author : 唐﨑結斗
// 概要 : ラインを矩形状に設置
//=============================================================================
void CCollision_Rectangle2D::SetLine()
{
	// 変数宣言
	CObject *pObject = GetParent();
	D3DXVECTOR3 pos = pObject->GetPos() + GetPos();
	const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 size = GetSize() / 2.0f;
	const D3DXCOLOR col = lineCol;

	// ラインの設定
	m_pLine[0]->SetLine(pos, rot, D3DXVECTOR3(-size.x, size.y, size.z), D3DXVECTOR3(size.x, size.y, size.z), col);
	m_pLine[1]->SetLine(pos, rot, D3DXVECTOR3(size.x, size.y, size.z), D3DXVECTOR3(size.x, -size.y, size.z), col);
	m_pLine[2]->SetLine(pos, rot, D3DXVECTOR3(size.x, -size.y, size.z), D3DXVECTOR3(-size.x, -size.y, size.z), col);
	m_pLine[3]->SetLine(pos, rot, D3DXVECTOR3(-size.x, -size.y, size.z), D3DXVECTOR3(-size.x, size.y, size.z), col);
}
#endif // DEBUG

