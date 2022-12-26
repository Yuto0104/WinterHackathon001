#include "application.h"
#include "renderer.h"
#include "2Dparticle.h"

#include <assert.h>

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̃R���X�g���N�^
//��������������������������������������������������������������
C2DEffect::C2DEffect() :
	m_info({}),
	m_nTime(0)			// ����
{
}

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̃f�X�g���N�^
//��������������������������������������������������������������
C2DEffect::~C2DEffect()
{
}

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̐���
//��������������������������������������������������������������
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

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̏�����
//��������������������������������������������������������������
HRESULT C2DEffect::Init()
{
	CObject2D::Init();

	//�I�u�W�F�N�g�̏�����
	CObject2D::SetPos(m_info.pos);
	CObject2D::SetCol(m_info.col);
	CObject2D::LoadTex(m_info.numTex);
	CObject2D::SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

	return S_OK;
}

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̍X�V
//��������������������������������������������������������������
void C2DEffect::Update()
{
	CObject2D::Update();

	Behavior(m_info.infoProperty);

	// �ړ��ʂ̐���
	{
		D3DXVECTOR3 pos = CObject2D::GetPos();
		pos += m_info.move;

		CObject2D::SetPos(pos);
	}

	// ��������
	m_nTime++;
	if (m_nTime >= m_info.destroyTime)
	{
		CObject2D::Uninit();
		return;
	}
}

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̕`��
//��������������������������������������������������������������
void C2DEffect::Draw()
{
	CObject2D::Draw();
}

//��������������������������������������������������������������
// 2D�G�t�F�N�g�̃v���p�e�B�ɉ���������
//��������������������������������������������������������������
void C2DEffect::Behavior(std::vector<std::string>& prop)
{
	for (auto p : prop)
	{
		// �F�̕ψ�
		if (p == "ColorTransition")
		{
			D3DXCOLOR col = CObject2D::GetCol();

			col.r += (m_info.destCol.r - col.r) / (m_info.destroyTime * m_info.colAttenuation);
			col.g += (m_info.destCol.g - col.g) / (m_info.destroyTime * m_info.colAttenuation);
			col.b += (m_info.destCol.b - col.b) / (m_info.destroyTime * m_info.colAttenuation);

			CObject2D::SetCol(col);
			continue;
		}

		// �e�N�X�`���̊g��
		if (p == "Scaling")
		{
			D3DXVECTOR3 scale = CObject2D::GetSize();
			scale.x += m_info.scalingSpeed;
			scale.y += m_info.scalingSpeed;

			CObject2D::SetSize(scale);
			continue;
		}

		// ���̎��Ԃ𒴂���ƁA����
		if (p == "Falling")
		{
			m_nTime++;
			if (m_nTime <= m_info.delayTime)
			{
				m_info.move.y += m_info.gravityPower;
			}
			continue;
		}

		// �w�肵���ʒu�Ɍ������Ĉړ�
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