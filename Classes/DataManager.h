#ifndef __DATAMANAGER__
#define __DATAMANAGER__

#include "sqlite3.h"
#include <vector>
#include <string.h>
#include "cocos2d.h"
#include "ConfData.h"

using namespace std;
USING_NS_CC;

//modify by liuhuan
struct AchieveData
{
	int id;
	int type;
	string desc;
	int param1;
	int param2;
	int money;
	int line;
	int hammer;
	int bomb;
	int brush;
	int color;
	int lightning;
	int ironball;
	int has;
};

/*
struct PetData
{
	int id;
	string name;
	string png;
	string plist;
	string json;
	int toolid; //add by liuhuan
	int paytype; //modify by liuhuan
	int cost;
	int combo_num;
	int probabilty;
	float duration;
};
*/
struct ShoptoolsData
{
	int id;
	string name;
	int paytype;//modify by liuhuan
	int get;
	int cost;
	string desc;
};

struct MoneyshopData
{
	int id;
	string name;
	int get;
	int present;
	int cost;
	string desc;
};

struct StageData      //�ؿ����ݱ�
{
	int col[COlUMNS_SIZE];//��
};

struct StageconfigData      //�ؿ����ñ�
{
	int stage;   //�ؿ�
	int game_mode;   //��Ϸģʽ     1-����ģʽ 2-�÷�ģʽ 4-��Կ��ģʽ 8-ʱ��ģʽ 16-��������ģʽ 32-BOSSģʽ
	float falldown_speed;    //�½��ٶ�
	int timer;    //�ؿ��޶�ʱ��
	int score;    //�ؿ�Ҫ�����
	int ball;     //�ؿ���������
	int award_coin;
};

struct BallconfigData        //��ID��
{
	int index;    //�±�
	int ball_num;    //��ID
	string miaoshu;    //����
	int appear;    //���ֻ���
	int h_timer;    //������Ҫ�Ĵ���
	int ishave_yang;   //�Ƿ�����
};

//��������� û�У���Կ�ף�����������
typedef enum 
{
	BALL_CONTENT_TYPE_DEFAULT, 
	BALL_CONTENT_TYPE_YANG, 
	BALL_CONTENT_TYPE_BING,
	BALL_CONTENT_TYPE_KEY, 
	BALL_CONTENT_TYPE_MAX
};

typedef enum 
{
	BALL_STATE_DEFAULT = 0,
	BALL_STATE_SHAKING,
	BALL_STATE_REMOVE,
	BALL_STATE_DROP
};

struct Ball        
{
	int id;		//��ID
	int ballType;//�����ͣ���ͨ��,ʯͷ��
	int score;	//�÷�
	int extra;	//��������
	int reward;	//����
	int content;	//�������ݣ���ĳ�ֶ����Կ��
	int state;	//���״̬
};

//�ؿ���������content[7] 0������(����������,�ٿ���),1������2Կ��������3�ٶ�(ÿ���ƶ����ٸ���)��4��˳������ID��,5ʱ�����ƣ�6��������
typedef enum {
	INDEX_YANG_COUNT, 
	INDEX_SCORE, 
	INDEX_KEY_COUNT, 
	INDEX_SPEED, 
	INDEX_BOSSSQE_ID,
	INDEX_SHIJIAN,
	INDEX_QIUSHU,
	INDEX_MAX
};

struct StageInfo        
{
	int stageId;		//���ùؿ�ID
	int stageType;	//�ؿ�����, 1-�÷�ģʽ 2-����ģʽ 4-�����ģʽ 8-����ģʽ
	int params[2];	//	�ؿ�Ŀ���������һ����Ŀ�꣬�ڶ����Ǹ���
	int step;	//�ؿ�����
	int petId;	//����ID
	int extraReward;	//���⽱����Ĭ��0���޽���
	int content[12];	//��������(��Ϲؿ�����ʹ��)��0������(����������,�ٿ���),1������2Կ��������3�ٶ�(ÿ���ƶ����ٸ���)��4��4���������������ID��  add by fandy 5ʱ�����ƣ�6��������
	int starPre[2];//��ȡ���ǵķ�������������һ�����Ա�����Ǻ����Ǽ��ɣ�0Ϊ���Ǵﵽ�����ٷֱȣ�1Ϊ���Ǵﵽ�����ٷֱȣ�Ĭ��90��60��
	int starCount;//��ǰ�ؿ��Ѿ���õ��������� -1Ϊδ�򿪹ؿ���0�Ѿ���
	int hightScore;//��ǰ�ؿ���߷���
};

//�ؿ�ģʽ
typedef enum 
{
	MODE_SCORE = 1,  //����ģʽ
	MODE_STAR,	//����ģʽ
	MODE_TOOL,	//����ģʽ
	MODE_SPRITE	//����ģʽ
};

struct BallQueue   //������ı�
{
	int queueId;   //id
	int bqueue[BALL_QUEUE_SIZE];   //����б�
};

struct BallqueueData   //������ı�
{
	int stage;   //�ؿ�
	int bqueue[100];   //����б�
};

//Boss attack Type
typedef enum 
{
	BOSS_TYPE_MOVEFAST = 0, //����
	BOSS_TYPE_KILL_TIME, //����ʱ��
	BOSS_TYPE_FORZEN, //����
	BOSS_TYPE_CONFUSE,//����
	BOSS_TYPE_FORZENBALL, //����ĳ����
	BOSS_TYPE_ADDBALL, //����
	BOSS_TYPE_SKILL_MAX
};
//Boss ani Type
typedef enum 
{
	BOSS_ANI_MOVE = 0, //�ƶ�
	BOSS_ANI_DEFALUT, //Ĭ�϶���
	BOSS_ANI_ACT,//����
	BOSS_ANI_MAX
};

struct PetConfig    //BOSS���ñ�
{
	int id;
	int energy[5];     //������������
	int count[5];     //�������õ�����
	int upgrade[5];   //�������辭��ֵ
};

struct StartViewTools      //�ؿ���ʼ����ĵ����б�
{
	int stage;         //�ؿ���
	int tools[4];      //�����б�
};

struct LuckyConfigs      //����ת��������Ϣ
{
	int id;         
	int A;				//�״γ齱�����A��0Ϊ��ѣ�
	int B;				//��������B
	int X;				//��������X
	int hint[2];		//��ʾ�ߣ�����&����
	int hammer[2];		//����
	int bomb[2];		//ը��
	int brush[2];		//ˢ��
	int anycolor[2];	//��ɫ
	int removecolor[2];	//����
	int steel[2];		//����
	int moneysmall[2];  //СǮ
	int moneybig[2];	//��Ǯ
};

struct GideConfig      //��������
{
	int type;         //����
	int level;      //�ؿ���
	int extral[3];		//�������
};
//Guide Type
typedef enum
{
	GUIDE_TYPE_REWORD = 0, //�������ֽ�������
	GUIDE_TYPE_QISHIYANG, //��ʿ������
	GUIDE_TYPE_SHENSHIYANG, //��ʿ������
	GUIDE_TYPE_BOSS,//BOSS����
	GUIDE_TYPE_COLOR, //��ɫ������
	GUIDE_TYPE_STEEL, //��������
	GUIDE_TYPE_LIGHTING, //ͬɫ������
	GUIDE_TYPE_LINE, //��������
};

struct GameString      //������
{
	string desc;      
};

struct StarsConfig
{
	int id;
	string desc;
	int score;
	string resPath;
	int extra;
	string explosionPath;
};

struct PetsConfig
{
	int id;
	int skillId;
	vector<int> energy;
	vector<int> count;
	vector<int> upgrade;
	vector<string> iconPath;
	string desc;
};

struct StageConfig
{
	int id;
	int tagetType;
	vector<int> targetParam;
	int step;
	vector<int> direction;
};

struct SystemConfig
{
	int stageAmount;
};

class DataManager
{
public:
	DataManager(void);
	virtual ~DataManager(void);
	static DataManager* m_pSelf;

	static DataManager* GetSelf()
	{
		if (m_pSelf == NULL)
		{
			m_pSelf = new DataManager;
		}
		return m_pSelf;
	}

#define DataManagerSelf DataManager::GetSelf()

	void UnzipGameData(bool update);
	void LoadData();

	void LoadAchieveData();
	void updateAchieveData(int id, int count);
	void deleteAchieveData(int id);
	void LoadPetData();
	void LoadShoptoolsData();
	void LoadMoneyshopData();
	void LoadStageData(int level);
	void LoadStageconfigData();
	void LoadBallconfigData();
	void LoadBallqueueData();
	void LoadBallQueueDataEx();
	void LoadPetlistData();
	void loadBallConfigDataEx();
	void loadStageConfigDataEx();
	void LoadStageViewToolsData();
	void LoadLuckyConfigsData();
	void setStateStarCount(int stageIndex,int starCount);
	void loadGuideConfig();
	void loadGameString();
	vector<AchieveData> AchieveVec;
	vector<ShoptoolsData> ShoptoolsVec;
	vector<MoneyshopData> MoneyshopVec;
	vector<StageData> StageVec;
	vector<StageconfigData> StageconfigVec;
	vector<BallconfigData> BallconfigVec;
	vector<BallqueueData> BallqueueVec;
	vector<PetConfig> PetListVec;
	vector<Ball> BallsVec;
	vector<StageInfo> StagesVec;
	vector<BallQueue> BallsQueueVec;
	vector<StartViewTools> StartToolsVec;
	vector<LuckyConfigs> LuckyConfigsVec;
	vector<GideConfig> GuideConfigVec;
	vector<GameString> GameStringVec;


public:
	void loadStageConfig();
	const StageConfig &getStageConfig(int stage);

	void getNewStageStarsData(std::vector<std::vector<int>> &stars, int stageNum);

	void loadStarsConfig();
	const StarsConfig &getStarsConfig(int starType);

	void loadCommonPetsConfig();
	const PetsConfig &getCommonPetsConfig(int petId);

	void loadSystemConfig();
	const SystemConfig &getSystemConfig();
private:
	vector<StageConfig> m_stagesConfig;
	vector<StarsConfig> m_starsConfig;
	vector<PetsConfig> m_petsConfig;
	SystemConfig m_systemConfig;
};

#endif