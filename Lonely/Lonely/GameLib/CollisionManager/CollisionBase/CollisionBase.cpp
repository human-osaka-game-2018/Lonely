/**
* @file CollisionBase.h
* @brief CollisionBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#include "CollisionBase.h"
#include "../CollisionManager.h"
#include "../../../Game/Scene/GameScene/Player/Sumahoneko.h"
#include "../../../Game/Scene/GameScene/Enemy/Pasoken.h"
//#include "../../../Game/Scene/GameScene/Stage/Stage.h"
#include "../../../Game/Scene/GameScene/StageObject/StageObject.h"
#include "../../../Game/Scene/GameScene/StageObject/StageMovableObject.h"
#include "../../../Game/Scene/GameScene/Trigger/TriggerBase.h"
#include "../../../Game/Scene/GameScene/Trigger/TriggerQR.h"
#include "../../../Game/Scene/GameScene/Trigger/TriggerMovable.h"
#include "../../../Game/Scene/GameScene/Trigger/TriggerCharging.h"

CollisionBase::CollisionBase()
{
}

CollisionBase::~CollisionBase()
{
}

//当たった時の処理
void CollisionBase::OnCollision(CollisionBase* collider, bool collisionStateIsRiding)
{
	//それぞれ何の当たり判定グループかを取得する
	int typeA = this->GetType();
	int typeB = collider->GetType();

	
	if (typeA == PLAYER)
	{
		//スマホ猫型にダウンキャストを行う
		Sumahoneko* sumahoneko = dynamic_cast<Sumahoneko*>(this->GetOwner());
		
		if (typeB == PLAYER_WITH_OBJECT)
		{
			StageMovableObject* movableObject = dynamic_cast<StageMovableObject*>(collider->GetOwner());
			
			if(collisionStateIsRiding == true)
			{
				//着地したかフラグをオンにする
				sumahoneko->SetIsLanded(true);
				//移動を制限する
				sumahoneko->RevertPositionY();
				movableObject->RevertPosition();
			}
			else if (collisionStateIsRiding == false)
			{
				//乗っていないなら、スマホ猫が動かしてる状態なので、特に何もしない
			}
			
		}
		else if (typeB == ENEMY) 
		{
			Pasoken* pasoken = dynamic_cast<Pasoken*>(collider->GetOwner());
			//スマホ猫はダメージを受ける
			sumahoneko->Damaged();
			if (collisionStateIsRiding == false) 
			{
				//移動させない
				sumahoneko->RevertPosition();
				pasoken->RevertPosition();
			}
			if (collisionStateIsRiding == true) 
			{	
				//着地したかフラグをオンにする
				sumahoneko->SetIsLanded(true);
				//上に乗っている
				sumahoneko->RevertPositionY();
			}

		}
		else if (typeB == STAGE_OBJECT)
		{
			StageObject* stageObject = dynamic_cast<StageObject*>(collider->GetOwner());
			if (collisionStateIsRiding == true) 
			{
				//着地したかフラグをオンにする
				sumahoneko->SetIsLanded(true);
				//ポジションを移動させない
				sumahoneko->RevertPositionY();
			}
			else if (collisionStateIsRiding == false)
			{
				//移動させない
				sumahoneko->RevertPosition();
			}
		}
		else if (typeB == TRIGGER)
		{
			TriggerBase* trigger = dynamic_cast<TriggerBase*>(collider->GetOwner());
			int triggerType = trigger->GetTriggerType();

			if (triggerType == TRIGGER_QR)
			{
				TriggerQR* triggerQR = dynamic_cast<TriggerQR*>(collider->GetOwner());
				triggerQR->CollidesWithPlayer();
			}
			else if (triggerType == TRIGGER_MOVABLE)
			{
				TriggerMovable* triggerMovableObject = dynamic_cast<TriggerMovable*>(collider->GetOwner());
				triggerMovableObject->CollidesWithPlayer();
			}
			else if (triggerType == TRIGGER_CHARGING)
			{
				TriggerCharging* triggerCharging = dynamic_cast<TriggerCharging*>(collider->GetOwner());
				triggerCharging->CollidesWithPlayer();
			}
		}

	}
	if (typeA == PLAYER_WITH_OBJECT)
	{
		StageMovableObject* movableObject = dynamic_cast<StageMovableObject*>(this->GetOwner());
		if (typeB == ENEMY)
		{
			Sumahoneko* sumahoneko = movableObject->GetPlayer();
			Pasoken* pasoken = dynamic_cast<Pasoken*>(this->GetOwner());
			movableObject->RevertPosition();
			sumahoneko->RevertPosition();
			pasoken->RevertPosition();
		}
		else if (typeB == STAGE_OBJECT)
		{
			Sumahoneko* sumahoneko = movableObject->GetPlayer();
			movableObject->RevertPosition();
			sumahoneko->RevertPosition();
		}
	}
	if (typeA == ENEMY)
	{
		Pasoken* pasoken = dynamic_cast<Pasoken*>(this->GetOwner());
		if (typeB == STAGE_OBJECT)
		{
			pasoken->RevertPosition();
		}
	}
}
