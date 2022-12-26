//=============================================================================
//
// �v���C���[�N���X(player.cpp)
// Author : �������l
// �T�v : �v���C���[�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "player.h"
#include "game.h"
#include "mesh.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"
#include "keyboard.h"
#include "calculation.h"
#include "move.h"
#include "debug_proc.h"
#include "model3D.h"
#include "line.h"
#include "dosukoi.h"
#include "joypad.h"
#include "collision_rectangle3D.h"
#include "sound.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CPlayer * CPlayer::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CPlayer *pPlayer = nullptr;

	// �������̉��
	pPlayer = new CPlayer;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pPlayer != nullptr);

	// ���l�̏�����
	pPlayer->Init();

	// �C���X�^���X��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CPlayer::CPlayer() : m_pMove(nullptr),
m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_fSpeed(0.0f)
{

}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CPlayer::Init()
{
	// ������
	CModelObj::Init();

	// �ړ��N���X�̃������m��
	m_pMove = new CMove;
	assert(m_pMove != nullptr);
	m_pMove->SetMoving(0.2f, 1.0f, 0.1f, 0.1f);
	m_MashCount = 0;
	m_Rotate = false;

	// ���̓����蔻��̐ݒ�
	m_pCollision = CCollision_Rectangle3D::Create();
	m_pCollision->SetParent(this);
	m_pCollision->SetPos(D3DXVECTOR3(0.0f, 30.0f, 0.0f));
	m_pCollision->SetSize(D3DXVECTOR3(30.0f, 60.0f, 30.0f));

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(CObject::OBJETYPE_PLAYER);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CPlayer::Uninit()
{
	if (m_pMove != nullptr)
	{// �I������
	 // �������̉��
		delete m_pMove;
		m_pMove = nullptr;
	}

	if (m_pCollision != nullptr)
	{// �I������
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	// �I������
	CModelObj::Uninit();

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CPlayer::Update()
{// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();

	// �X�V����
	CModelObj::Update();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �����̏󋵂��擾
	if (!CDosukoi::GetBegin()
		&& CApplication::GetMode() == CApplication::MODE_GAME)
	{
		// �ړ�
		pos += Move();

		// �A��
		Mash();
	}
	
	// �������I��������
	if(!CDosukoi::GetSiai())
	{
		int Loser = 0;

		switch (CDosukoi::GetNumber())
		{
		case 0:
			Loser = 1;
			break;
		case 1:
			Loser = 0;
			break;
		}

		if (Loser == m_Number && CApplication::GetMode() == CApplication::MODE_GAME)
		{
			// �s�k�������̏���
			Lose();
		}
	}

	// ��]
	Rotate();

	// �ʒu�̐ݒ�
	SetPos(pos);

	// ���f���Ƃ̓����蔻��
	bool bCollision = m_pCollision->Collision(CObject::OBJETYPE_PLAYER, true);

	if (bCollision)
	{// �v���C���[�ƏՓ�
		CPlayer *pPlayer = (CPlayer*)m_pCollision->GetCollidedObj();
		D3DXVECTOR3 pos = pPlayer->GetPos();
		D3DXVECTOR3 move = Move() - pPlayer->GetMove()->GetMove();
		D3DXVECTOR3 myColliSize = m_pCollision->GetSize();
		pos += move;
		pPlayer->SetPos(pos);

		// �L�[�{�[�h�̎擾
		CJoypad *pJoypad = CApplication::GetJoy();
		pJoypad->Vibration(20, 50000, m_Number);
	}

	// ���f���Ƃ̓����蔻��
	bCollision = m_pCollision->Collision(CObject::OBJTYPE_FIELD, false);
	
	if (!bCollision
		&& CApplication::GetMode() == CApplication::MODE_GAME)
	{
		// ���������v���C���[�̎w��
		CDosukoi::SetWinPlayer(m_VSNumber);
	}

	// ���b�V���̓����蔻��
	CMesh3D *pMesh = CGame::GetMesh();

	// �ʒu�̎擾
	pos = GetPos();

#ifdef _DEBUG

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{// �s�k����
		CDosukoi::SetWinPlayer(m_VSNumber);
	}

	// �f�o�b�N�\��
	CDebugProc::Print("�v���C���[�̈ʒu | X : %.3f | Y : %.3f | Z : %.3f |\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("�v���C���[�̘A�Ő� %d \n", m_MashCount);
#endif // _DEBUG
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CPlayer::Draw()
{
	// �`��
	CModelObj::Draw();
}

//=============================================================================
// �����̐ݒ�
// Author : �������l
// �T�v : �����̐ݒ�
//=============================================================================
void CPlayer::SetRot(const D3DXVECTOR3 &rot)
{
	CModelObj::SetRot(rot);
	m_rotDest = rot;
}

//=============================================================================
// �ړ�
// Author : �������l
// �T�v : �L�[���͂ŕ��������߂āA�ړ��x�N�g�����Z�o����
//=============================================================================
D3DXVECTOR3 CPlayer::Move()
{
	// �ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	// �L�[�{�[�h�̎擾
	CJoypad *pJoypad = CApplication::GetJoy();

	if (pJoypad->GetTrigger(CJoypad::JOYKEY_B, m_Number) || pJoypad->GetTrigger(CJoypad::JOYKEY_A, m_Number) 
		|| pJoypad->GetTrigger(CJoypad::JOYKEY_X, m_Number) || pJoypad->GetTrigger(CJoypad::JOYKEY_Y, m_Number))
	{// �ړ������̍X�V
		CSound *pSound = CApplication::GetSound();

		pSound->PlaySound(CSound::SOUND_LABEL_SE_PON);

		if (pJoypad->GetTrigger(CJoypad::JOYKEY_B, m_Number) || pJoypad->GetTrigger(CJoypad::JOYKEY_A, m_Number))
		{
			// �p�x�����Z
			m_rotDest.y -= (rand() % 20 - 15) * 0.01f;
		}
		else
		{
			// �p�x�����Z
			m_rotDest.y += (rand() % 20 - 15) * 0.01f;
		}

		float rot = GetRot().y - D3DX_PI;

		// �ړI�̌����̕␳
		if (rot >= D3DX_PI)
		{// �ړ������̐��K��
			rot -= D3DX_PI * 2;
		}
		else if (rot <= -D3DX_PI)
		{// �ړ������̐��K��
			rot += D3DX_PI * 2;
		}

		// �ړ��ʂ̌v�Z
		move = D3DXVECTOR3(sinf(rot), 0.0f, cosf(rot));
	}

	// �ړ����̌v�Z
	m_pMove->Moving(move);

	// �ړ����̎擾
	D3DXVECTOR3 moveing = m_pMove->GetMove();

	// �f�o�b�N�\��
	CDebugProc::Print("�ړ��x�N�g�� : %.3f\n", m_pMove->GetMoveLength());

	// �ړI�̌����̕␳
	if (m_rotDest.y - GetRot().y >= D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - GetRot().y <= -D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.y += D3DX_PI * 2;
	}

	return moveing;
}

//=============================================================================
// ��]
// Author : �������l
// �T�v : �ړI�̌����܂ŉ�]����
//=============================================================================
void CPlayer::Rotate()
{
	// �����̎擾
	D3DXVECTOR3 rot = GetRot();

	// �����̍X�V
	rot.y += (m_rotDest.y - rot.y) * 0.5f;

	// �����̐��K��
	rot.y = CCalculation::RotNormalization(rot.y);

	rot.z += (m_rotDest.z - rot.z) * 0.5f;

	rot.z = CCalculation::RotNormalization(rot.z);

	rot.x += (m_rotDest.x - rot.x) * 0.5f;

	rot.x = CCalculation::RotNormalization(rot.x);

	// �����̐ݒ�
	SetRot(rot);
}

//============================================================================
// �A�ł̊Ǘ�����
// Author : �y���m��
// �T�v : �A�Ő����Ǘ�����
//============================================================================
void CPlayer::Mash()
{
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CApplication::GetKeyboard();
	CJoypad *pJoypad = CApplication::GetJoy();

	if (pJoypad->GetTrigger(CJoypad::JOYKEY_B, m_Number) || pJoypad->GetTrigger(CJoypad::JOYKEY_A, m_Number)
		|| pJoypad->GetTrigger(CJoypad::JOYKEY_X, m_Number) || pJoypad->GetTrigger(CJoypad::JOYKEY_Y, m_Number))
	{
		m_MashCount++;
	}

	// �A�Ő��̍ő吔�̎擾
	int MaxMash = CDosukoi::GetMaxMash();

	// �A�Ő��̍ő吔�̔���
	if (m_MashCount >= MaxMash * 0.5f && m_Rotate == false)
	{
		m_Rotate = true;
	}

	// �A�Ő��̍ő吔
	if (m_MashCount >= MaxMash)
	{
		// ���������v���C���[�̎w��
		CDosukoi::SetWinPlayer(m_Number);
	}
}

//=============================================================================
// �s�k
// Author : �y���m��
// �T�v : �s�k�������̏���
//=============================================================================
void CPlayer::Lose()
{
	m_rotDest.x = D3DX_PI * 0.5f;

	// �ړI�̌����̕␳
	if (m_rotDest.x - GetRot().x >= D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.x -= D3DX_PI * 2;
	}
	else if (m_rotDest.x - GetRot().x <= -D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.x += D3DX_PI * 2;
	}

	m_rotDest.z = -D3DX_PI * 0.1f;

	// �ړI�̌����̕␳
	if (m_rotDest.z - GetRot().z >= D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.z -= D3DX_PI * 2;
	}
	else if (m_rotDest.z - GetRot().z <= -D3DX_PI)
	{// �ړ������̐��K��
		m_rotDest.z += D3DX_PI * 2;
	}
}