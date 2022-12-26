//=============================================================================
//
// �Q�[���N���X(game.cpp)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "game.h"
#include "score.h"
#include "calculation.h"
#include "keyboard.h"
#include "mouse.h"
#include "application.h"
#include "camera.h"
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "model3D.h"
#include "mesh.h"
#include "bg.h"
#include "debug_proc.h"
#include "model_obj.h"
#include "sphere.h"
#include "player.h"
#include "model3D.h"
#include "dosukoi.h"
#include "collision_rectangle3D.h"
#include "sound.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;										// �X�R�A�C���X�^���X
CMesh3D *CGame::m_pMesh3D = nullptr;									// ���b�V���N���X
CModelObj *CGame::m_pField = nullptr;									// �t�B�[���h����p�̃N���X
CDosukoi *CGame::m_pDosukoi = nullptr;									// �ǂ�����
CCollision_Rectangle3D *CGame::m_pColliField = nullptr;					// �t�B�[���h�̏Փ˔���
D3DXCOLOR CGame::fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// �t�H�O�J���[
float CGame::fFogStartPos = 0.0f;										// �t�H�O�̊J�n�_
float CGame::fFogEndPos = 0.0f;											// �t�H�O�̏I���_
float CGame::fFogDensity = 0.0f;										// �t�H�O�̖��x
bool CGame::m_bGame = false;											// �Q�[���̏�

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CGame::Init()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �d�͂̒l��ݒ�
	CCalculation::SetGravity(10.0f);

	CSound *pSound = CApplication::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	m_pDosukoi = new CDosukoi;
	m_pDosukoi->Init();

	// �t�B�[���h����
	m_pField = CModelObj::Create();
	m_pField->SetPos(D3DXVECTOR3(0.0f, 45.0f, 0.0f));
	m_pField->SetObjType(CObject::OBJTYPE_FIELD);
	m_pColliField = CCollision_Rectangle3D::Create();
	m_pColliField->SetParent(m_pField);
	m_pColliField->SetSize(D3DXVECTOR3(240.0f, 60.0f, 240.0f));

	// �v���C���[�̐���
	CPlayer *pPlayer1 = CPlayer::Create();
	pPlayer1->SetPos(D3DXVECTOR3(70.0f, 45.0f, 0.0f));
	pPlayer1->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pPlayer1->SetNumber(0);
	pPlayer1->SetVSNumber(1);
	CModel3D *pModel = pPlayer1->GetModel();
	pModel->SetModelID(3);

	// �v���C���[2�̐���
	CPlayer *pPlayer2 = CPlayer::Create();
	pPlayer2->SetPos(D3DXVECTOR3(-70.0f, 45.0f, 0.0f));
	pPlayer2->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	pPlayer2->SetNumber(1);
	pPlayer2->SetVSNumber(0);
	CModel3D *pModel2 = pPlayer2->GetModel();
	pModel2->SetModelID(4);

	// �n�ʂ̐ݒ�
	m_pMesh3D = CMesh3D::Create();
	m_pMesh3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetSize(D3DXVECTOR3(5000.0f, 0, 5000.0f));
	m_pMesh3D->SetBlock(CMesh3D::DOUBLE_INT(10, 10));
	m_pMesh3D->SetSplitTex(true);

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

	// �}�E�X�J�[�\��������
	pMouse->SetShowCursor(false);

	// �t�H�O�̐��l�ݒ�
	fogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �t�H�O�J���[
	fFogStartPos = 1.0f;								// �t�H�O�̊J�n�_
	fFogEndPos = 100000.0f;								// �t�H�O�̏I���_
	fFogDensity = 0.00001f;								// �t�H�O�̖��x

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, fogColor);

	// �t�H�O�͈̔͐ݒ�
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// �t�H�O�̖��x�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));

	m_bGame = true;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CGame::Uninit()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	CSound *pSound = CApplication::GetSound();

	pSound->StopSound();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// �}�E�X�J�[�\�����o��
	pMouse->SetShowCursor(true);

	// �J�����̒Ǐ]�ݒ�
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetFollowTarget(false);
	pCamera->SetTargetPosR(false);

	// ���s�̎擾
	int nNumPlayer = m_pDosukoi->GetNumber();

	if (nNumPlayer == 0)
	{
		CApplication::SetVictoryFlag(true);
	}
	else 
	{
		CApplication::SetVictoryFlag(false);
	}

	// �ÓI�ϐ��̏�����
	if (m_pMesh3D != nullptr)
	{
		m_pMesh3D = nullptr;
	}

	if (m_pColliField != nullptr)
	{
		m_pColliField->Uninit();
		m_pColliField = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CGame::Update()
{
#ifdef _DEBUG
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		CCamera *pCamera = CApplication::GetCamera();
		pCamera->Zoom();
	}

#endif // _DEBUG

	if (!m_bGame)
	{
		CApplication::SetNextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CGame::Draw()
{

}
