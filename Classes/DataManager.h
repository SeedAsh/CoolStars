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

struct StageData      //关卡内容表
{
	int col[COlUMNS_SIZE];//列
};

struct StageconfigData      //关卡配置表
{
	int stage;   //关卡
	int game_mode;   //游戏模式     1-救羊模式 2-得分模式 4-打钥匙模式 8-时间模式 16-限制球数模式 32-BOSS模式
	float falldown_speed;    //下降速度
	int timer;    //关卡限定时间
	int score;    //关卡要求分数
	int ball;     //关卡限制球数
	int award_coin;
};

struct BallconfigData        //球ID表
{
	int index;    //下标
	int ball_num;    //球ID
	string miaoshu;    //描述
	int appear;    //出现机率
	int h_timer;    //出现需要的次数
	int ishave_yang;   //是否有羊
};

//球包含内容 没有，羊，钥匙，其它待补充
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
	int id;		//球ID
	int ballType;//球类型：普通球,石头等
	int score;	//得分
	int extra;	//附加属性
	int reward;	//奖励
	int content;	//包含内容，如某种动物或钥匙
	int state;	//球的状态
};

//关卡包含内容content[7] 0羊数量(若新增动物,再考虑),1分数，2钥匙数量，3速度(每秒移动多少个球)，4球顺序索引ID，,5时间限制，6球数限制
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
	int stageId;		//引用关卡ID
	int stageType;	//关卡类型, 1-得分模式 2-消星模式 4-打道具模式 8-精灵模式
	int params[2];	//	关卡目标参数，第一个是目标，第二个是个数
	int step;	//关卡步数
	int petId;	//宠物ID
	int extraReward;	//额外奖励，默认0，无奖励
	int content[12];	//包含内容(配合关卡类型使用)，0羊数量(若新增动物,再考虑),1分数，2钥匙数量，3速度(每秒移动多少个球)，4、4个发射球队列索引ID，  add by fandy 5时间限制，6球数限制
	int starPre[2];//获取星星的分数比例，至少一星所以标记三星和两星即可，0为三星达到分数百分比，1为二星达到分数百分比（默认90，60）
	int starCount;//当前关卡已经获得的星星数量 -1为未打开关卡，0已经打开
	int hightScore;//当前关卡最高分数
};

//关卡模式
typedef enum 
{
	MODE_SCORE = 1,  //分数模式
	MODE_STAR,	//星星模式
	MODE_TOOL,	//道具模式
	MODE_SPRITE	//精灵模式
};

struct BallQueue   //发射球的表
{
	int queueId;   //id
	int bqueue[BALL_QUEUE_SIZE];   //球的列表
};

struct BallqueueData   //发射球的表
{
	int stage;   //关卡
	int bqueue[100];   //球的列表
};

//Boss attack Type
typedef enum 
{
	BOSS_TYPE_MOVEFAST = 0, //加速
	BOSS_TYPE_KILL_TIME, //消耗时间
	BOSS_TYPE_FORZEN, //冻结
	BOSS_TYPE_CONFUSE,//混乱
	BOSS_TYPE_FORZENBALL, //冰冻某个球
	BOSS_TYPE_ADDBALL, //加球
	BOSS_TYPE_SKILL_MAX
};
//Boss ani Type
typedef enum 
{
	BOSS_ANI_MOVE = 0, //移动
	BOSS_ANI_DEFALUT, //默认动作
	BOSS_ANI_ACT,//攻击
	BOSS_ANI_MAX
};

struct PetConfig    //BOSS配置表
{
	int id;
	int energy[5];     //技能所需能量
	int count[5];     //技能作用的数量
	int upgrade[5];   //升级所需经验值
};

struct StartViewTools      //关卡开始界面的道具列表
{
	int stage;         //关卡数
	int tools[4];      //道具列表
};

struct LuckyConfigs      //幸运转盘配置信息
{
	int id;         
	int A;				//首次抽奖金币数A（0为免费）
	int B;				//递增基数B
	int X;				//递增倍数X
	int hint[2];		//提示线：概率&数量
	int hammer[2];		//锤子
	int bomb[2];		//炸弹
	int brush[2];		//刷子
	int anycolor[2];	//彩色
	int removecolor[2];	//闪电
	int steel[2];		//铁球
	int moneysmall[2];  //小钱
	int moneybig[2];	//大钱
};

struct GideConfig      //引导配置
{
	int type;         //类型
	int level;      //关卡数
	int extral[3];		//额外参数
};
//Guide Type
typedef enum
{
	GUIDE_TYPE_REWORD = 0, //产生三种奖励引导
	GUIDE_TYPE_QISHIYANG, //骑士羊引导
	GUIDE_TYPE_SHENSHIYANG, //绅士羊引导
	GUIDE_TYPE_BOSS,//BOSS引导
	GUIDE_TYPE_COLOR, //彩色球引导
	GUIDE_TYPE_STEEL, //铁球引导
	GUIDE_TYPE_LIGHTING, //同色球引导
	GUIDE_TYPE_LINE, //线条引导
};

struct GameString      //中文字
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

struct CurState
{
	int curStage;
	int curScore;
	int topScore;
	vector<int> save_pet_ids;
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
	void loadStarsConfig();
	const StarsConfig &getStarsConfig(int starType);

	void loadCurState();
	const CurState &getCurState();

	void loadCommonPetsConfig();
	const PetsConfig &getCommonPetsConfig(int petId);
private:
	vector<StarsConfig> m_starsConfig;
	CurState m_curState;
	vector<PetsConfig> m_petsConfig;

};

#endif