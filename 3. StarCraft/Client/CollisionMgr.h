#pragma once
class CObj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionRectEX(list<CObj*>& rDst, list<CObj*>& rSrc);
	static void CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc);

public:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);

public:
	static bool EnemyCollTile(list<CObj*> rDst, list<CObj*> rSrc);						// Enemy, 타일 충돌
};

