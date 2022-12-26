//=============================================================================
//
// �ǂ������N���X(dosukoi.cpp)
// Author : �y���m��
// �T�v : ���o�̃��[�����Ǘ�����
//
//=============================================================================
#ifndef _DOSUKOI_H_		// ���̃}�N����`������ĂȂ�������
#define _DOSUKOI_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "super.h"
#include "object2D.h"

#include <vector>

//=============================================================================
// �ǂ������N���X
// Author : �y���m��
// �T�v : ���o�̃��[���𐶐�����
//=============================================================================
class CDosukoi : public CObject2D
{
public:
	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CDosukoi();
	~CDosukoi() override;

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

	static void SetWinPlayer(int Number) { m_PlayerNumber = Number; SetSiai(true); }
	static void SetSiai(bool siai) { m_bSiai = siai; }
	static int GetNumber() { return m_PlayerNumber; }
	static int GetMaxMash() { return m_MaxMash; }
	static bool GetSiai() { return m_bSiai; }
	static bool GetBegin() { return m_bBegin; }

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
private:
	static int m_MaxMash;			// �ő�A�Ő��̊Ǘ�
	static int m_PlayerNumber;		// �v���C���[�̃i���o�[
	static bool m_bSiai;			// ����
	static bool m_bBegin;			// �J�n

	std::vector<CObject2D*> m_UI;

	D3DXVECTOR3 m_size;

	int nCnt;
	int m_HackeyoiCnt;
	int m_NokotaCnt;
};

#endif

