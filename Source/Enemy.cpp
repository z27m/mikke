#include "Enemy.h"
#include "Graphics/Graphics.h"
#include "EnemyManager.h"



//デバッグプリミティブ描画
void Enemy::DrawDebugPrimitive() {
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    //衝突判定用のデバッグ球を描画
    //debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawCylinder(position, radius, height,DirectX::XMFLOAT4(0, 0, 0, 1));
}

//自分自身を破棄
void Enemy::Destroy() {
    //敵マネージャーの削除に自分自身のアドレスを渡す
    EnemyManager::Instance().Remove(this);
}

