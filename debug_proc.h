//=============================================================================
//
// デバック表示クラス(debug_proc.h)
// Author : 唐�ｱ結斗
// 概要 : デバック表示生成を行う
//
//=============================================================================
#ifndef _DEBUG_PROC_H_			// このマクロ定義がされてなかったら
#define _DEBUG_PROC_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//=============================================================================
// デバック表示クラス
// Author : 唐�ｱ結斗
// 概要 : デバック表示生成を行うクラス
//=============================================================================
class CDebugProc
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static void Print(const char *pFormat, ...);		// 文字列の登録
	static void Draw(void);								// 表示

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CDebugProc();
	~CDebugProc();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	void Init();				// 初期化
	void Uninit();				// 終了	

private:
	//--------------------------------------------------------------------
	// 静的メンバ変数
	//--------------------------------------------------------------------
	static LPD3DXFONT	m_pFont;			// フォント情報
	static char			m_aStr[0xfff];		// 登録文字列
};

#endif


