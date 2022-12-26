//=============================================================================
//
// �`���[�g���A���N���X(game.cpp)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "tutorial.h"
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

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CMesh3D *CTutorial::m_pMesh3D = nullptr;									// ���b�V���N���X
D3DXCOLOR CTutorial::fogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			// �t�H�O�J���[
float CTutorial::fFogStartPos = 0.0f;										// �t�H�O�̊J�n�_
float CTutorial::fFogEndPos = 0.0f;											// �t�H�O�̏I���_
float CTutorial::fFogDensity = 0.0f;										// �t�H�O�̖��x
bool CTutorial::m_bGame = false;											// �Q�[���̏�

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CTutorial::CTutorial() : m_mode(TUTORIAL_PUSH)
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CTutorial::Init()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �d�͂̒l��ݒ�
	CCalculation::SetGravity(10.0f);

	CDosukoi *pDosukoi = new CDosukoi;
	pDosukoi->Init();
	pDosukoi->SetTutorial(true);

	// �v���C���[�̐���
	CPlayer *pPlayer1 = CPlayer::Create();
	pPlayer1->SetPos(D3DXVECTOR3(70.0f, 45.0f, 0.0f));
	pPlayer1->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pPlayer1->SetNumber(0);
	CModel3D *pModel = pPlayer1->GetModel();
	pModel->SetModelID(3);

	// �v���C���[2�̐���
	CPlayer *pPlayer2 = CPlayer::Create();
	pPlayer2->SetPos(D3DXVECTOR3(-70.0f, 45.0f, 0.0f));
	pPlayer2->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));
	pPlayer2->SetNumber(1);
	pPlayer2->SetNumber(0);
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

	m_pObj.resize(2);
	m_pObj[0] = CObject2D::Create();
	m_pObj[0]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pObj[0]->SetSize(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));
	m_pObj[0]->LoadTex(16);

	m_pObj[1] = CObject2D::Create();
	m_pObj[1]->SetPos(D3DXVECTOR3(1000.0f, 690.0f, 0.0f));
	m_pObj[1]->SetSize(D3DXVECTOR3(350.0f, 150.0f, 0.0f));
	m_pObj[1]->LoadTex(9);

	m_bGame = true;

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CTutorial::Uninit()
{// �}�E�X�̎擾
	CMouse *pMouse = CApplication::GetMouse();

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

	// �ÓI�ϐ��̏�����
	if (m_pMesh3D != nullptr)
	{
		m_pMesh3D = nullptr;
	}

	// �X�R�A�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V���s��
//=============================================================================
void CTutorial::Update()
{
#ifdef _DEBUG
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CApplication::SetNextMode(CApplication::MODE_TITLE);
	}

	if (pKeyboard->GetPress(DIK_LSHIFT))
	{
		CCamera *pCamera = CApplication::GetCamera();
		pCamera->Zoom();
	}

#endif // _DEBUG

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		switch (m_mode)
		{
		case CTutorial::TUTORIAL_PUSH:
			m_pObj[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pObj[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			break;

		case CTutorial::TUTORIAL_END:
			break;

		default:
			assert(false);
			break;
		}
		//CApplication::SetNextMode(CApplication::MODE_TITLE);
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CTutorial::Draw()
{
}
