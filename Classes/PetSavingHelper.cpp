#include "PetSavingHelper.h"
#include "SqliteHelper.h"
#include "PetManager.h"

USING_NS_CC;
using namespace std;

void PetSavingHelper::setPetState(int petId)
{
	//save_pet_ids
}

PetData PetSavingHelper::getPetState(int petId)
{
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "select * from save_pets where id = %d;", petId);
	auto result = sqlHelper.readRecord(str);
	assert(result.size() == 1);

	PetData data;
	data.petId = atoi(result[0][0]);
	data.commonid = atoi(result[0][1]);
	data.color = atoi(result[0][2]);
	data.level = atoi(result[0][3]);
	data.exp = atoi(result[0][4]);
	data.energy = atoi(result[0][5]);
	return data;
	
}
void PetSavingHelper::recordCurActivePets()
{
	SqliteHelper sqlHelper(DB_SAVING);

	string sql = "replace into save_cur_pets values(1;";
	char str[100] = { 0 };
	vector<int> curPets = PetManager::petMgr()->getCurPetIds();
	for (size_t i = 0; i < curPets.size(); ++i)
	{
		sprintf(str, ",%d", curPets[i]);
		sql += str;
	}
	sql += ");";

	sqlHelper.insertRecordIntoSqlite(sql.c_str());
}

vector<int> PetSavingHelper::getCurActivePets()
{
	vector<int> curPets;
	SqliteHelper sqlHelper(DB_SAVING);

	string sql = "select * from save_cur_pets;";
	auto result = sqlHelper.readRecord(sql.c_str());
	assert(result.size() == 1);

	//获取save_pet_ids,以逗号分隔
	string ids = result[0][1];

	auto pos = ids.find(",");
	auto prePos = 0;
	while (pos != string::npos)
	{
		int id = atoi(ids.substr(prePos, pos).c_str());
		curPets.push_back(id);

		prePos = pos + 1;
		pos = ids.find(",", prePos);
	}

	//最后一个逗号后的数据
	int id = atoi(ids.substr(prePos).c_str());
	if (id > 0)
	{
		curPets.push_back(id);
	}

	return curPets;
}