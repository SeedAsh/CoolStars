#ifndef  _STAR_UTIL_H_
#define  _STAR_UTIL_H_

#include "stdlib.h"
#include "GameData.h"

USING_NS_CC; 
using namespace std;

#define GAME_CONFIG_FILE_VERSION 1

#define OK 1
#define ERROR 0
#define OVER_FLOW -2

#define STAR_COLOR_NULL -1
#define STAR_COLOR_1 0
#define STAR_COLOR_2 1
#define STAR_COLOR_3 2
#define STAR_COLOR_4 3
#define STAR_COLOR_5 4
#define TOOL_BOMB	 5
#define TOOL_DIAMOND 6
#define TOOL_STONE   7

#define STAR_ROW_COUNT COlUMNS_SIZE

#define STAR_SELECT_NO 0
#define STAR_SELECT_YES 1
#define STAR_SELECT_1 2
#define STAR_SELECT_2 3
#define STAR_SELECT_MAX 4

#define MAX_BONUS 2000

#define DATA_FILE "state.dat"
#define KEY_CURSTAGE_SCORE "key-curstage-score"
#define KEY_CURPRESENT "key-curpresent"
typedef struct
{
    int x;
    int y;
} Index;

typedef struct  
{
    bool del; // is this result delete or select?
    int count;
    int color;
    int* pTags; // free by user
	int* tools;
	int* toolIndex;
} Result;

typedef struct QNode       //链式存储结构。
{
    Index pp;
    struct QNode *next;
}QNode ,*QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

struct Star
{
	int color;//颜色，STAR_COLOR_NULL为不显示,STAR_COLOR_1 ~STAR_COLOR_5分别是5种颜色
	int state;//是否选中，0为未选中,1为选中
    int intTag; // 初始化时生成的唯一的tag
    Index targetIndex; // 消除操作后当前星星移动后的索引
};

/************************************************************************/
/* 第一维对应Star结构体中的color                                           */
/* 第二维对应Star结构体中的state                                           */
/***********************************************************************/
extern string g_starFrameNameArray[][2];
extern string g_rewardFrameNameArray[3];

class  StarUtil
{
public:
    struct Star star[STAR_ROW_COUNT][STAR_ROW_COUNT];//star[列][行]序号从上到下，从左往右
public:
    StarUtil();
	virtual ~StarUtil();
	void initStar();//初始化生成随机星星数组
	void initStarEx();
	void resetStarState();//初始化星星数组的状态值
	void initScore();
    inline int getScore() {
        return score;
    }
	inline void setScore(int newScore){
		score = newScore;
	}
	inline int getNewScore() {
		return m_nNewScore;
	}
	inline int getCurStageScore() {
		return m_nCurStageScore;
	}
    inline int getStage() {
        return stage;
    }
	inline int getStep() {
		return m_nStep;
	}
	inline int getPetId()
	{
		return m_nPetId;
	}
	inline int getNextColor()
	{
		return m_nNextColor;
	}
	Result onStarClicked(int x,int y);	//点中星星, 返回消除的个数
    static inline int getScore(int count) {
        return count * count * 5;
    };
    static inline int getBonus(int leftCount) {
        int bonus = (MAX_BONUS - 20 * leftCount * leftCount);
        if (bonus <= 0){
            return 0;
        }
        return bonus;
    };
    static inline string getRewardFrame(int count) {
        int index = -1;
        for (int i = 0; i < 3; i++){
            if (count >= GameData::getInstance()->m_nCombo[i]){
                index = i;
            }else{
                break;
            }
        }
        if (index != -1){
            return g_rewardFrameNameArray[index];
        }
        return "";
    };
    static inline int getTagByIndex(Index index) {
        return (index.x * COlUMNS_SIZE + index.y);
    };
    static inline Index getIndexByTag(int tag) {
        Index index;
        index.x = tag / COlUMNS_SIZE;
        index.y = tag % COlUMNS_SIZE;
        return index;
    };
	int getNotClearCount(bool end = true);
	void saveCurStageScore();
	void loadCurStageScore();
	void saveCurPresent();
	void loadCurPresent();
	int getUnSameColor(int color1,int color2);
	void setStarColor(int x,int y,int color);//设置某个星星的颜色
    Result bulkDelete(int x, int y, bool makeChange = false); // 清除方圆9格内的星星, makeChange表示是否要将颜色改动到star数组中
	Result rowDelete(int x, int y, int count, bool makeChange = false); // 清除以(x,y)为中心水平方向的count个星星, makeChange表示是否要将颜色改动到star数组中
	Result colDelete(int x, int y, int count, bool makeChange = false); // 清除以(x,y)为中心竖直方向的count个星星, makeChange表示是否要将颜色改动到star数组中
	Result centerDelete(int x, int y, int count, bool makeChange = false); // 清除以(x,y)为中心水平加竖直方向的count个星星, makeChange表示是否要将颜色改动到star数组中
	void randomStarColorChange(int color, int count);
	void randomStarToSomething(int color, int count);
	Result randomDeleteStar(int count, bool makeChange = false); // 随机清除count个星星, makeChange表示是否要将颜色改动到star数组中
	void setScoreRate(int rate);
	void setNextColor(int color, int count);
	Result bombClearAllStar(bool makeChange = false); //炸弹清楚屏幕内的所有星星，makeChange表示是否要将颜色改动到star数组中

	int saveState();//保存最后退出时分数与当前的星星数组状态
    int loadLastState();
    static bool hasSavedState();
	int deleteEmptyLeftColumn();
    bool isStageOver();
    inline bool isStageClear() {
       // int stageTarget = getStageTarget();
		return m_bIsgameWin;// (score >= stageTarget);
    };
	int stageOverScore();//关卡结束时的额外分数
    bool nextStage(); // 返回false表示游戏结束，否则继续下一关
	bool starClear(int x, int y);//清除x,y位置星星为中心的9个星星,选中的星星是无颜色或位置越界时，返回false
    void resetTargetTags();
	int getStageTarget();
	int getTarget();
	int remainCount();
	void radomRemain();
	int findStar(int x,int y,int color = STAR_COLOR_NULL, bool resetState = true);
	int findStarMax();
	bool resetMax();
	float m_fCurrentPersent;
	static int m_nDirection;
	static int m_nCurDirectionIndex;
	
private:
	int stageTarget;
    int score;
	int m_nLastScore;
	int m_nCurStageScore;
	int m_nNewScore;	
    int stage; // 级别
	LinkQueue LinkQ;
	int InitQueue();
	int EnQueue(Index e);
	int DeQueue(Index &e);
	int SearchSameColorLeft(int x,int y,int color,bool inqueue,int state);
	int SearchSameColorRight(int x,int y,int color,bool inqueue,int state);
	int SearchSameColorTop(int x,int y,int color,bool inqueue,int state);
	int SearchSameColorBottom(int x,int y,int color,bool inqueue,int state);
	void putInt(int i,FILE* file);
	void getInt(int &i,FILE* file);
	void getChar(char &i,FILE* file);
	int xorEncDecInt(int i);

	int starDrop();
	int starUp();
	int starLeft();
	int starRight();
	void starMove();
	void addStep(int count);

	int m_nStageMode;
	int m_nTargetType;
	int m_nTargetCount;
	int m_nStep;
	int m_nPetId;
	int m_nScoreRate;
	bool m_bScoreMode;
	bool m_bStarMode;
	bool m_bToolMode;
	bool m_SpriteMode;
	int m_nColorStarCount; 
	bool m_bIsgameWin;
	int m_nNextColor;
	int m_nNextColorCount;
};

#endif // _STAR_UTIL_H_

