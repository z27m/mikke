#include <EnemyManager.h>
#include "Collision.h"



//更新処理
void EnemyManager::Update(float elapsedTime) {
    for (Enemy* enemy : enemies) {
        enemy->Update(elapsedTime);
    }

    //破棄処理
    for (Enemy* enemy : removes) {
        
        std::vector<Enemy*>::iterator it =
            std::find(enemies.begin(),
                enemies.end(), enemy);

        if (it != enemies.end()) {
            enemies.erase(it);
        }

        //弾丸の破棄処理
        delete enemy;
    }

    //破棄リストをクリア
    removes.clear();

    //敵同士の衝突処理
    CollisionEnemyVsEnemies();

}

//エネミー同士の衝突処理
void EnemyManager::CollisionEnemyVsEnemies() {
    //敵の数を取得
    
    //模範解答これ
    size_t enemyCount = enemies.size();

    //敵の数分回す　（カウンターi）
    for (int i = 0; i < GetEnemyCount(); ++i) {
        //敵Aを取得
        Enemy* enemyA = enemies.at(i);
        //敵の数ぶん回す　（カウンターｊ）
        for (int j = i+1; j < GetEnemyCount(); ++j) {
            //敵Ｂを取得
            Enemy* enemyB = enemies.at(j);
            //押し出し後の位置
            DirectX::XMFLOAT3 outPosition;
            //衝突処理　if文
            if (Collision::IntersectCylinderVsCylinder( //CylinderVsCylinder SphereVsSphere
                enemyA->GetPosition(), //敵Ａの位置
                enemyA->GetRadius(),//敵Ａの半径
                enemyA->GetHeight(),
                enemyB->GetPosition(),//敵Ｂの位置
                enemyB->GetRadius(),//敵Ｂの半径
                enemyB->GetHeight(),
                outPosition//押し出し後の位置
                )) 
             {
                //敵Ｂに押し出し後の位置を設定
                enemyB->SetPosition(outPosition);
             }
            
        }
    }
}

//描画処理
void EnemyManager :: Render(ID3D11DeviceContext* context, Shader* shader) {
    for (Enemy* enemy : enemies) {
        enemy->Render(context, shader);
    }
}



//デバッグプリミティブ描画
void EnemyManager::DrawDebugPrimitive() {
    for (Enemy* enemy : enemies) {
        enemy->DrawDebugPrimitive();
    }
}

//エネミー登録
void EnemyManager::Register(Enemy* enemy) {
    enemies.emplace_back(enemy);
}

//エネミー削除
void EnemyManager::Remove(Enemy* enemy) {
    //破棄リストに追加
    removes.insert(enemy);
}


//エネミー全削除
void EnemyManager::Clear() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

