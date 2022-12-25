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

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CMesh3D *CGame::m_pMesh3D;								// ���b�V���N���X
D3DXCOLOR CGame::fogColor;								// �t�H�O�J���[
float CGame::fFogStartPos;								// �t�H�O�̊J�n�_
float CGame::fFogEndPos;								// �t�H�O�̏I���_
float CGame::fFogDensity;								// �t�H�O�̖��x
bool CGame::m_bGame = false;							// �Q�[���̏�

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
	/*pCamera->SetFollowTarget(m_pPlayer, 1.0);*/
	pCamera->SetPosVOffset(D3DXVECTOR3(0.0f, 0.0f, -500.0f));
	pCamera->SetPosROffset(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetViewType(CCamera::TYPE_PARALLEL);

	CObject3D *pObject = CObject3D::Create();
	pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0));
	pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0));

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
