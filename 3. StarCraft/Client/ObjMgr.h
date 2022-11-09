#pragma once
class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	~CObjMgr();

public:
	int Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	const CObj* Get_Player() const { return m_listObj[OBJID::PLAYER].front(); }
	const list<CObj*>* Get_listObj() const { return m_listObj;  }
	const list<CObj*> Get_Obj(OBJID::ID _eID) const { return m_listObj[_eID]; }

public:
	void AddObject(OBJID::ID eID, CObj* pObj) { m_listObj[eID].emplace_back(pObj); }
	void DeleteID(OBJID::ID eID)
	{
		for (auto& pObj : m_listObj[eID])
		{
			SafeDelete(pObj);
		}
		m_listObj[eID].clear();
	}

private:
	list<CObj*> m_listObj[OBJID::END];

};
