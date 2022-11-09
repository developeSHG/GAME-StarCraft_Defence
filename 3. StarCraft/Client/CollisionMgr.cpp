#include "stdafx.h"
#include "CollisionMgr.h"

#include "Obj.h"
#include "Unit.h"
#include "CollRect.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//RECT rc = {};
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (IntersectRect(&rc, pDest->Get_Rect(), pSource->Get_Rect()))
	//		{
	//			pDest->Set_Dead();
	//			pSource->Set_Dead();
	//		}
	//	}
	//}
}

void CCollisionMgr::CollisionRectEX(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//float fMoveX = 0.f, fMoveY = 0.f;
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
	//		{
	//			float x = pSource->Get_Info().fx;
	//			float y = pSource->Get_Info().fy;

	//			if (fMoveX > fMoveY)
	//			{
	//				if (y < pDest->Get_Info().fy)
	//					fMoveY *= -1.f;

	//				pSource->Set_Pos(x, y + fMoveY);
	//			}
	//			else
	//			{
	//				if (x < pDest->Get_Info().fx)
	//					fMoveX *= -1.f;

	//				pSource->Set_Pos(x + fMoveX, y);
	//			}

	//		}
	//	}
	//}

}

void CCollisionMgr::CollisionSphere(list<CObj*>& rDst, list<CObj*>& rSrc)
{
	//for (auto& pDest : rDst)
	//{
	//	for (auto& pSource : rSrc)
	//	{
	//		if (CheckSphere(pDest, pSource))
	//		{
	//			pDest->Set_Dead();
	//			pSource->Set_Dead();
	//		}
	//	}
	//}
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	//float fRadiusSum = (pDst->Get_Info().fcx * 0.5f) + (pSrc->Get_Info().fcx * 0.5f);
	//float x = pDst->Get_Info().fx - pSrc->Get_Info().fx;
	//float y = pDst->Get_Info().fy - pSrc->Get_Info().fy;

	//float fDist = sqrtf(x * x + y * y);

	//return fRadiusSum > fDist;
	return false;
}

//bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
//{
//	//float fRadiusSumX = (pDst->Get_Info().fcx * 0.5f) + (pSrc->Get_Info().fcx * 0.5f);
//	//float fRadiusSumY = (pDst->Get_Info().fcy * 0.5f) + (pSrc->Get_Info().fcy * 0.5f);
//
//	//// fabs 절대값 구해주는 함수. 
//	//float fDistX = fabs(pDst->Get_Info().fx - pSrc->Get_Info().fx);
//	//float fDistY = fabs(pDst->Get_Info().fy - pSrc->Get_Info().fy);
//
//	//if (fRadiusSumX > fDistX && fRadiusSumY > fDistY)
//	//{
//	//	*pMoveX = fRadiusSumX - fDistX;
//	//	*pMoveY = fRadiusSumY - fDistY;
//	//	return true;
//	//}
//	return false;
//}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	float fRadiusSumX = (pDst->Get_Info().vSize.x * 0.5f) + (pSrc->Get_Info().vSize.x * 0.5f);
	float fRadiusSumY = (pDst->Get_Info().vSize.y * 0.5f) + (pSrc->Get_Info().vSize.y * 0.5f);

	// fabs 절대값 구해주는 함수. 
	float fDistX = fabs(pDst->Get_Info().vPos.x - pSrc->Get_Info().vPos.x);
	float fDistY = fabs(pDst->Get_Info().vPos.y - pSrc->Get_Info().vPos.y);

	if (fRadiusSumX > fDistX && fRadiusSumY > fDistY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true;
	}
	return false;
}

bool CCollisionMgr::EnemyCollTile(list<CObj*> rDst, list<CObj*> rSrc)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto& pDest : rDst)
	{
		for (auto& pSource : rSrc)
		{
			if (CheckRect(pDest, pSource, &fMoveX, &fMoveY))
			{
				switch (SCAST<CCollRect*>(pSource)->Get_Dir())
				{
				case 0:
					SCAST<CUnit*>(pDest)->Set_Dir(SCAST<CUnit*>(pDest)->LEFT);
					break;
				case 1:
					SCAST<CUnit*>(pDest)->Set_Dir(SCAST<CUnit*>(pDest)->RIGHT);
					break;
				case 2:
					SCAST<CUnit*>(pDest)->Set_Dir(SCAST<CUnit*>(pDest)->UP);
					break;
				case 3:
					SCAST<CUnit*>(pDest)->Set_Dir(SCAST<CUnit*>(pDest)->DOWN);
					break;
				default:
					break;
				}

				/*float x = pSource->Get_Info().fx;
				float y = pSource->Get_Info().fy;

				if (fMoveX > fMoveY)
				{
				if (y < pDest->Get_Info().fy)
				fMoveY *= -1.f;

				pSource->Set_Pos(x, y + fMoveY);
				}
				else
				{
				if (x < pDest->Get_Info().fx)
				fMoveX *= -1.f;

				pSource->Set_Pos(x + fMoveX, y);
				}*/

			}
		}
	}


	return false;
}
