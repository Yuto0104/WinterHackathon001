//=============================================================================
//
// �^�C�g���N���X(title.cpp)
// Author : �������l
// �T�v : �^�C�g���N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <mutex>

#include "title.h"
#include "bg.h"
#include "application.h"
#include "keyboard.h"
#include "object2D.h"
#include "2Dparticle.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTitle::CTitle() : m_bOnce(true)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CTitle::Init()
{
	auto ObjCreate = [](D3DXVECTOR3 pos, D3DXVECTOR3 size, int texNum){
		CObject2D* pObj = nullptr;
		pObj = CObject2D::Create();
		pObj->SetSize(size);
		pObj->SetPos(pos);
		pObj->LoadTex(texNum);
		return pObj;
	};

	m_pBg = CBG::Create();
	m_pBg->LoadTex(7);

	// �ǂ������p���_�C�X
	// �^�C�g�����S�̐���
	m_titleLogo.resize(2);
	m_titleLogo[0] = ObjCreate(D3DXVECTOR3(450.0f, -40.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 4);
	m_titleLogo[1] = ObjCreate(D3DXVECTOR3(800.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 300.0f, 0.0f), 5);

	m_pPressEnter = ObjCreate(D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f), 9);

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CTitle::Uninit()
{
	if (!m_titleLogo.empty())
	{
		m_titleLogo.clear();
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CTitle::Update()
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CApplication::SetNextMode(CApplication::MODE_GAME);
	}

	//----------------------------------------------------------------------

	m_titleLogoCounter++;
	for (unsigned int i = 0; i < m_titleLogo.size(); i++)
	{
		D3DXVECTOR3 pos = m_titleLogo[i]->GetPos();

		if (m_bOnce)
		{	// �P�x�����ʂ�Ȃ��悤�ɂ���
			// Init��SetCol�����Ă��Ȃ����F���ς���Ă���Ȃ����߁A�����ɏ����Ă݂�
			m_pPressEnter->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_bOnce = false;
		}

		if (m_titleLogoCounter <= 100)
		{	// �^�C�g�����S�����ֈ��̈ʒu�܂ō~��鏈��
			pos.y += 2.5f;
			m_titleLogo[i]->SetPos(pos);
		}
		else if (m_titleLogoCounter >= 100)
		{
			D3DXCOLOR col = m_pPressEnter->GetCol();
			col.a += 0.01f;
			m_pPressEnter->SetCol(col);
		}
	}

	//----------------------------------------------------------------------

	// �p�[�e�B�N���i���̂���j
	if((m_titleLogoCounter % 10) == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			// �E����
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

			// ������
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
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CTitle::Draw()
{

}