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

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CGame::m_pScore = nullptr;										// �X�R�A�C���X�^���X
CMesh3D *CGame::m_pMesh3D = nullptr;									// ���b�V���N���X
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

	// �v���C���[�̐���
	CPlayer *pPlayer = CPlayer::Create();
	CModel3D *pModel = pPlayer->GetModel();
	pModel->SetModelID(0);
	
	// �X�R�A�̐���
	m_pScore = CScore::Create(10, false);
	m_pScore->SetScore(0);
	m_pScore->SetPos(D3DXVECTOR3(1280.0f, m_pScore->GetSize().y / 2.0f, 0.0f));

	// �n�ʂ̐ݒ�
	m_pMesh3D = CMesh3D::Create();
	m_pMesh3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh3D->SetSize(D3DXVECTOR3(5000.0f, 0, 5000.0f));
	m_pMesh3D->SetBlock(CMesh3D::DOUBLE_INT(10, 10));
	m_pMesh3D->SetSplitTex(true);
	m_pMesh3D->LoadTex(1);

	// �J�����̒Ǐ]�ݒ�(�ڕW : �v���C���[)
	CCamera *pCamera = CApplication::GetCamera();
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -500.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �X�J�C�{�b�N�X�̐ݒ�
	CSphere *pSphere = CSphere::Create();
	pSphere->SetRot(D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f));
	pSphere->SetSize(D3DXVECTOR3(100.0f, 0, 100.0f));
	pSphere->SetBlock(CMesh3D::DOUBLE_INT(100, 100));
	pSphere->SetRadius(50000.0f);
	pSphere->SetSphereRange(D3DXVECTOR2(D3DX_PI * 2.0f, D3DX_PI * -0.5f));

	// �}�E�X�J�[�\��������
	//pMouse->SetShowCursor(false);

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
