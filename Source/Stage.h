#pragma once

#include "Graphics/Shader.h"
#include "Collision.h"

// 探すべきオブジェクトのタイプ
enum FindObjectType {

    // 通常のなんでもないオブジェクト（ステージ）
    None,

    // 探し出されるオブジェクト
    Find,
};

//ステージ
class Stage {
public:
    Stage() {}
    virtual ~Stage() {}

    //更新処理
    virtual void Update(float elapsedTime) = 0;

    //描画処理
    virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

    //レイキャスト
    virtual bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit) = 0;

    void SetFindObjectType(FindObjectType type) { m_findObjectType = type; }

    FindObjectType GetFindObjectType() { return m_findObjectType; }

protected:
    FindObjectType m_findObjectType;
};
