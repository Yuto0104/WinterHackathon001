//=============================================================================
//
// �ǂ������N���X(dosukoi.cpp)
// Author : �y���m��
// �T�v : ���o�̃��[���̐����A�Ǘ����s���B
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "dosukoi.h"
#include "2Dparticle.h"

int CDosukoi::m_MaxMash = 0;
int CDosukoi::m_PlayerNumber = 0;
bool CDosukoi::m_bSiai = true;
bool CDosukoi::m_bBegin = true;
bool CDosukoi::m_bTutorial = false;

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CDosukoi::CDosukoi()
{
	m_MaxMash = 0;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CDosukoi::~CDosukoi()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
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
		nCnt = 0;

		// UI�̐���
		m_UI.resize(2);
		m_UI[0] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);
		m_UI[1] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 11);
	}

		// �����_���ɍő吔�����߂�
		m_MaxMash = rand() % 50 + 100;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CDosukoi::Uninit()
{
	if (!m_UI.empty())
	{
		m_UI.clear();
	}


	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CDosukoi::Update()
{
	if (m_bTutorial)
	{
		return;
	}

	nCnt++;

	if (m_UI[0] != nullptr)
	{
		m_UI[0]->SetSize(D3DXVECTOR3(m_HackeyoiCnt * 6, m_HackeyoiCnt, m_size.z));

		if (m_HackeyoiCnt <= 200)
		{
			m_HackeyoiCnt++;
		}
		else if (nCnt >= 250)
		{
			// UI�̔j��
			m_UI[0]->Uninit();
			m_UI[0] = nullptr;
		}
	}
	
	if (m_UI[1] != nullptr)
	{
		m_UI[1]->SetSize(D3DXVECTOR3(m_NokotaCnt * 6, m_NokotaCnt, m_size.z));

		if (nCnt > 250 && m_NokotaCnt <= 150)
		{
			m_NokotaCnt += 2;
		}
		if(nCnt >=  350)
		{
			// �������J�n����
			m_bBegin = false;

			// UI�̔j��
			m_UI[1]->Uninit();
			m_UI[1] = nullptr;
		}
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CDosukoi::Draw()
{

}
