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
#include "application.h"
#include "game.h"
#include "sound.h"

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
	m_EndCnt = 0;
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

	m_bTutorial = false;

	nCnt = 0;
	m_NokotaCnt = 0;
	m_HackeyoiCnt = 0;
	m_bBegin = true;
	m_bSiai = true;
	m_PlayerNumber = -1;

	if (!m_bTutorial)
	{
		// UI�̐���
		m_UI.resize(3);
		m_UI[0] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);
		m_UI[1] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 11);
		m_UI[2] = ObjCreate(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 13);

		CSound *pSound = CApplication::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_HAKEYOI);

		// �����_���ɍő吔�����߂�
		m_MaxMash = rand() % 50 + 100;
	}

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

	// �͂�����`��
	if (m_UI[0] != nullptr)
	{
		m_UI[0]->SetSize(D3DXVECTOR3(m_HackeyoiCnt * 6, m_HackeyoiCnt, m_size.z));

		if (m_HackeyoiCnt <= 100)
		{
			m_HackeyoiCnt++;
		}
		else if (nCnt >= 150)
		{
			// UI�̔j��
			m_UI[0]->Uninit();
			m_UI[0] = nullptr;

			CSound *pSound = CApplication::GetSound();

			pSound->PlaySound(CSound::SOUND_LABEL_SE_NOKOTA);
		}
	}
	
	// �̂������I
	if (m_UI[1] != nullptr)
	{
		if (nCnt >= 160)
		{
			m_UI[1]->SetSize(D3DXVECTOR3(900.0f,150.0f,0.0f));

			if (nCnt >= 220)
			{
				// �������J�n����
				m_bBegin = false;

				// UI�̔j��
				m_UI[1]->Uninit();
				m_UI[1] = nullptr;
			}
		}
	}
	
	// �������I��������
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
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CDosukoi::Draw()
{

}
