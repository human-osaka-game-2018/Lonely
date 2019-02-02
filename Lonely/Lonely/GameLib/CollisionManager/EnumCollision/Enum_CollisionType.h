/**
* @file Enum_CollisionType.h
* @brief CollisionTypeのEnumを定義するファイル
* @author shion-sagawa
*/
#pragma once

/**
* @brief 当たり判定のグループ分け（使う際に変えてもらう必要がある）
*/
enum COLLISION_TYPE
{
	PLAYER,
	PLAYER_WITH_OBJECT,
	ENEMY,
	STAGE_OBJECT,
	TRIGAR,
	COLLISION_TYPE_MAX,
};

/**
* トリガーの種類
*/
enum TRIGAR_TYPE
{
	TRIGAR_QR,
	TRIGAR_MOVABLE,
	TRIGAR_CHARGING
};
