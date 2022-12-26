#ifndef _2DEFFECT_H_
#define _2DEFFECT_H_

#include "object2d.h"
#include <string>
#include <vector>

class C2DEffect : public CObject2D
{
public:
	//--------------------------------------
	// パーティクル情報の構造体
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 pos;						// 位置
		D3DXVECTOR3 destPos;					// 目的の位置
		D3DXVECTOR3 move;						// 移動量
		D3DXCOLOR col;							// 色
		D3DXCOLOR destCol;						// 目的の色
		std::vector<std::string> infoProperty;	// プロパティ
		int destroyTime;						// エフェクトを消す時間
		int delayTime;							// 遅延をする時間
		int numTex;								// テクスチャの種別番号
		float moveAttenuation;					// 移動の減衰量
		float colAttenuation;					// 色の減衰量
		float scalingSpeed;						// 拡大する速度
		float gravityPower;						// 落下の強さ
	};

	C2DEffect();
	~C2DEffect() override;

	static C2DEffect *Create(SInfo& info);									// 生成処理

	HRESULT Init() override;												// 初期化処理
	void Update() override;													// 更新処理
	void Draw() override;													// 描画処理
	void Behavior(std::vector<std::string>& prop);							// パーティクルの挙動

	//セッター
	void SetInfo(SInfo& info) { m_info = info; }
	void SetPath(std::string path) { m_path = path; }

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;			// 頂点バッファ
	SInfo m_info;										// パーティクルの情報
	std::string m_path;									// テクスチャのパス
	int m_nTime;										// 時間
};
#endif