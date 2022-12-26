//=============================================================================
//
// ���U���g�N���X(result.cpp)
// Author : �������l
// �T�v : ���U���g�N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "result.h"
#include "keyboard.h"
#include "object2D.h"
#include "camera.h"
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "model3D.h"
#include "debug_proc.h"
#include "model_obj.h"
#include "sphere.h"
#include "player.h"
#include "model3D.h"
#include "dosukoi.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^

// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CResult::CResult()
{
	m_nextMode = CApplication::MODE_NONE;		// ���ɐݒ肷�郂�[�h
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CResult::Init()
{
	CSound *pSound = CApplication::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	// �v���C���[�̐���
	CPlayer *pPlayer1 = CPlayer::Create();
	pPlayer1->SetPos(D3DXVECTOR3(70.0f, 45.0f, 0.0f));
	pPlayer1->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.4f, 0.0f));
	pPlayer1->SetNumber(0);
	CModel3D *pModel = pPlayer1->GetModel();
	pModel->SetModelID(3);

	// �v���C���[2�̐���
	CPlayer *pPlayer2 = CPlayer::Create();
	pPlayer2->SetPos(D3DXVECTOR3(-70.0f, 45.0f, 0.0f));
	pPlayer2->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.4f, 0.0f));
	pPlayer2->SetNumber(1);
	CModel3D *pModel2 = pPlayer2->GetModel();
	pModel2->SetModelID(4);

	// �J�����̒Ǐ]�ݒ�(�ڕW : �v���C���[)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 130.0f, -400.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 50.0f, 100.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���f���̐ݒu
	CModelObj::LoadFile("data/FILE/BG_model.txt");

	// �X�J�C�{�b�N�X�̐ݒ�
	CSphere *pSphere = CSphere::Create();
	pSphere->SetRot(D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f));
	pSphere->SetSize(D3DXVECTOR3(100.0f, 0, 100.0f));
	pSphere->SetBlock(CMesh3D::DOUBLE_INT(100, 100));
	pSphere->SetRadius(50000.0f);
	pSphere->SetSphereRange(D3DXVECTOR2(D3DX_PI * 2.0f, D3DX_PI * -0.5f));
	pSphere->LoadTex(1);

	// ���̃e�N�X�`��
	m_pFist = CObject3D::Create();
	m_pFist->SetPos(D3DXVECTOR3(0.0f, 500.0f, 0.0f));
	m_pFist->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
	m_pFist->SetSize(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	m_pFist->SetBillboard(true);
	m_pFist->LoadTex(12);

	// ���ɍs�����[�h�̐ݒ�
	m_nextMode = CApplication::MODE_TITLE;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CResult::Uninit()
{
	CSound *pSound = CApplication::GetSound();
	pSound->StopSound();

	if (m_pFist != nullptr)
	{
		m_pFist->Uninit();
		m_pFist = nullptr;
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CResult::Update()
{
	// ���͏��̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	D3DXVECTOR3 pos = m_pFist->GetPos();

	if (pos.y - m_pFist->GetSize().y >= 45.0f)
	{
		pos.y -= 5.0f;
		m_pFist->SetPos(pos);
	}

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CApplication::SetNextMode(m_nextMode);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CResult::Draw()
{

}

