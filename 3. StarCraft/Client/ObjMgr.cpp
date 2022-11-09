#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "CollisionMgr.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

int CObjMgr::Update()
{

	for (int i = 0; i < OBJID::END; ++i)
	{
		for (list<CObj*>::iterator& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent || OBJ_DEAD == (*iter)->Get_Dead())
			{
				delete *iter;
				*iter = nullptr;
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
			if (m_listObj[i].empty())
				break;
		}
	}

	return OBJ_LIVE;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->LateUpdate();
			if (m_listObj[i].empty())
				break;
		}
	}


	// 충돌함수
}

void CObjMgr::Render()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if (OBJ_LIVE == pObj->Get_Dead())
				pObj->Render();
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			if (pObj)
			{
				delete pObj;
				pObj = nullptr;
			}
		}
		m_listObj[i].clear();
	}
}

