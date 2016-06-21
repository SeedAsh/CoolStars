#ifndef __PETMANAGER_H__
#define __PETMANAGER_H__
#include "cocos2d.h"
#include "PetEntity.h"
#include "CommonMacros.h"

class PetEntity;
class PetManager
{
public:
	static PetManager *petMgr();
	void init();
	PetEntity *getPetById(int id);
	std::vector<int> getOwnedPetIds();
	bool ownThisPet(int id);

	//��ǰѡ�еĳ��� �����ڹؿ������
	const std::vector<int> &getCurPetIds() { return m_curPets; }
	void setCurPets(std::vector<int> &ids);
private:
	PetManager();
	~PetManager();
private:
	std::map<int, PetEntity *> m_pets;
	std::vector<int> m_curPets;
};
#endif