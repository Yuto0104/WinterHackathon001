//=============================================================================
//
// �Q�[���N���X(game.h)
// Author : �������l
// �T�v : �Q�[���N���X�̊Ǘ����s��
//
//=============================================================================
#ifndef _GAME_H_		// ���̃}�N����`������ĂȂ�������
#define _GAME_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "scene_mode.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CPlayer;
class CMesh3D;
class CModelObj;
class CCollision_Rectangle3D;
class CDosukoi;

//=============================================================================
// �Q�[���N���X
// Author : �������l
// �T�v : �Q�[���������s���N���X
//=============================================================================
class CGame : public CSceneMode
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static void SetGame(const bool bGame) { m_bGame = bGame; }		// �Q�[���̏󋵂̐ݒ�
	static CScore *GetScore() { return m_pScore; }					// �X�R�A�̎擾
	static CMesh3D *GetMesh() { return m_pMesh3D; }					// ���b�V���̃Q�b�^�[

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CGame();
	~CGame() override;

	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CScore *m_pScore;						// �X�R�A�N���X
	static CMesh3D *m_pMesh3D;						// ���b�V���N���X
	static CModelObj *m_pField;						// �t�B�[���h����p�̃N���X
	static CCollision_Rectangle3D *m_pColliField;	// �t�B�[���h�̏Փ˔���
	static CDosukoi *m_pDosukoi;					// �ǂ�����
	static D3DXCOLOR fogColor;						// �t�H�O�J���[
	static float fFogStartPos;						// �t�H�O�̊J�n�_
	static float fFogEndPos;						// �t�H�O�̏I���_
	static float fFogDensity;						// �t�H�O�̖��x
	static bool m_bGame;							// �Q�[���̏�

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;					// ������
	void Uninit() override;						// �I��
	void Update() override;						// �X�V
	void Draw() override;						// �`��
};

#endif



