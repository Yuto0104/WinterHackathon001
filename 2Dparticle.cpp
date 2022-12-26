#include "application.h"
#include "renderer.h"
#include "2Dparticle.h"

#include <assert.h>

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect::C2DEffect() :
	m_info({}),
	m_nTime(0)			// 時間
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect::~C2DEffect()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C2DEffect * C2DEffect::Create(SInfo& info)
{
	C2DEffect *pParticle = new C2DEffect;

	if (pParticle != nullptr)
	{
		pParticle->SetInfo(info);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT C2DEffect::Init()
{
	CObject2D::Init();

	//オブジェクトの初期化
	CObject2D::SetPos(m_info.pos);
	CObject2D::SetCol(m_info.col);
	CObject2D::LoadTex(m_info.numTex);
	CObject2D::SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Update()
{
	CObject2D::Update();

	Behavior(m_info.infoProperty);

	// 移動量の推移
	{
		D3DXVECTOR3 pos = CObject2D::GetPos();
		pos += m_info.move;

		CObject2D::SetPos(pos);
	}

	// 生存時間
	m_nTime++;
	if (m_nTime >= m_info.destroyTime)
	{
		CObject2D::Uninit();
		return;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Draw()
{
	CObject2D::Draw();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 2Dエフェクトのプロパティに応じた処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C2DEffect::Behavior(std::vector<std::string>& prop)
{
	for (auto p : prop)
	{
		// 色の変移
		if (p == "ColorTransition")
		{
			D3DXCOLOR col = CObject2D::GetCol();

			col.r += (m_info.destCol.r - col.r) / (m_info.destroyTime * m_info.colAttenuation);
			col.g += (m_info.destCol.g - col.g) / (m_info.destroyTime * m_info.colAttenuation);
			col.b += (m_info.destCol.b - col.b) / (m_info.destroyTime * m_info.colAttenuation);

			CObject2D::SetCol(col);
			continue;
		}

		// テクスチャの拡大
		if (p == "Scaling")
		{
			D3DXVECTOR3 scale = CObject2D::GetSize();
			scale.x += m_info.scalingSpeed;
			scale.y += m_info.scalingSpeed;

			CObject2D::SetSize(scale);
			continue;
		}

		// 一定の時間を超えると、落下
		if (p == "Falling")
		{
			m_nTime++;
			if (m_nTime <= m_info.delayTime)
			{
				m_info.move.y += m_info.gravityPower;
			}
			continue;
		}

		// 指定した位置に向かって移動
		if (p == "Vector")
		{
			D3DXVECTOR3 objPos = CObject2D::GetPos();
			D3DXVECTOR3 vec = m_info.destPos - objPos;
			D3DXVec3Normalize(&vec, &vec);

			objPos += vec * m_info.moveAttenuation;

			CObject2D::SetPos(objPos);
			continue;
		}
	}
}