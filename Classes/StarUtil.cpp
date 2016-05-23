#include "StarUtil.h"
#include "UserInfo.h"
#include <sys/stat.h>
#include "CCUserDefaultEx.h"
#include "DataManager.h"

int StarUtil::m_nDirection = 0;
int StarUtil::m_nCurDirectionIndex = 0;

string g_starFrameNameArray[][2] = {
	{ "stars/star1.png", "stars/star1.png" },
	{ "stars/star2.png", "stars/star2.png" },
	{ "stars/star3.png", "stars/star3.png" },
	{ "stars/star4.png", "stars/star4.png" },
	{ "stars/star5.png", "stars/star5.png" },
	{ "stars/bomb.png", "stars/bomb.png" },
	{ "stars/diamond.png", "stars/diamond.png" },
	{ "stars/stone.png", "stars/stone.png" }
};
//Withered timbo
string g_trapFrameNameArray[3] = {
	"iceball.png"
};

string g_rewardFrameNameArray[3] = {
	"combo_1.png",
	"combo_2.png",
	"combo_3.png"
};

StarUtil::StarUtil()
{
	initScore();
	//initStar();
}

StarUtil::~StarUtil()
{

}

void StarUtil::initScore(){
	score = 0;
	stage = 0;
	m_nStep = 0;
	m_nCurStageScore = 0;
	stageTarget = 0;
	m_fCurrentPersent = 0;
	m_nScoreRate = 1;
	m_nNextColor = STAR_COLOR_NULL;
	m_nNextColorCount = 0;
}

void StarUtil::initStarEx()
{
	StageInfo m_sCurrentStageInfo = DataManagerSelf->StagesVec.at((stage) % DataManagerSelf->StagesVec.size());
	DataManagerSelf->LoadStageData((stage + 1) % DataManagerSelf->StagesVec.size());
	int stageCount = DataManagerSelf->StageVec.size();
	for (int i = 0; i < ROWS_SIZE; i++)
	{
		for (int j = 0; j < stageCount; j++)
		{
			StageData stageStarRow = DataManagerSelf->StageVec.at(j);
			star[i][j].color = stageStarRow.col[i] - 1;
			star[i][j].state = STAR_SELECT_NO;
			star[i][j].intTag = i * COlUMNS_SIZE + j;
			star[i][j].targetIndex.x = i;
			star[i][j].targetIndex.y = j;
		}
	}
	m_fCurrentPersent += GameData::getInstance()->m_nHardPre;
	m_nCurStageScore = score;
	//stageTarget = getStageTarget();
	m_nStageMode = m_sCurrentStageInfo.stageType;
	m_nTargetType = m_sCurrentStageInfo.params[0];
	m_nTargetCount = m_sCurrentStageInfo.params[1];
	stageTarget = m_sCurrentStageInfo.params[1];
	m_nStep = m_sCurrentStageInfo.step;
	m_nPetId = m_sCurrentStageInfo.petId;
	findStarMax();

	m_nColorStarCount = 0;
	m_bIsgameWin = false;


	m_bScoreMode = (m_sCurrentStageInfo.stageType & GAME_MODE_SCORE) != NULL;
	m_bStarMode = (m_sCurrentStageInfo.stageType & GAME_MODE_STAR) != NULL;
	m_bToolMode = (m_sCurrentStageInfo.stageType & GAME_MODE_TOOL) != NULL;
	m_SpriteMode = (m_sCurrentStageInfo.stageType & GAME_MODE_SPRITE) != NULL;
}

void StarUtil::initStar(){
	srand(time(NULL));
	int maxRadomColor = rand() % (STAR_COLOR_5 + 1);
	for (int i = 0; i < COlUMNS_SIZE; i++){
		for (int j = 0; j < ROWS_SIZE; j++){
			if (GameData::getInstance()->m_nHardType == USE_PRO_TYPE_HARD){
				int pro = CCRANDOM_0_1() * 100;
				if (GameData::getInstance()->m_nRadomUnSame >= pro){
					int color1 = STAR_COLOR_NULL;
					int color2 = STAR_COLOR_NULL;
					if (i - 1 >= 0){
						color1 = star[i - 1][j].color;
					}
					if (j - 1 >= 0){
						color2 = star[i][j - 1].color;
					}
					star[i][j].color = getUnSameColor(color1, color2);
				}
				else{
					star[i][j].color = rand() % (STAR_COLOR_5 + 1);
				}
			}
			else if (GameData::getInstance()->m_nHardType == USE_PRO_TYPE_EASY){
				int pro = CCRANDOM_0_1() * 100;
				if (GameData::getInstance()->m_nRadomPro >= pro){
					star[i][j].color = maxRadomColor;
				}
				else{
					star[i][j].color = rand() % (STAR_COLOR_5 + 1);
				}
			}
			else if (GameData::getInstance()->m_nHardType == USE_PRO_TYPE_NORMAL){
				star[i][j].color = rand() % (STAR_COLOR_5 + 1);
			}
			else{//难度渐强				
				int pro = CCRANDOM_0_1() * 100;
				if (m_fCurrentPersent < GameData::getInstance()->m_nRadomPro){//容易模式
					if (GameData::getInstance()->m_nRadomPro - m_fCurrentPersent >= pro){
						star[i][j].color = maxRadomColor;
					}
					else{
						star[i][j].color = rand() % (STAR_COLOR_5 + 1);
					}
				}
				else{//困难模式
					int unRadomPro = m_fCurrentPersent - GameData::getInstance()->m_nRadomPro;
					if (unRadomPro < 0){
						unRadomPro = GameData::getInstance()->m_nHardPre;
					}
					else if (unRadomPro > GameData::getInstance()->m_nRadomUnSame){
						unRadomPro = GameData::getInstance()->m_nRadomUnSame;
					}
					if (unRadomPro >= pro){
						int color1 = STAR_COLOR_NULL;
						int color2 = STAR_COLOR_NULL;
						if (i - 1 >= 0){
							color1 = star[i - 1][j].color;
						}
						if (j - 1 >= 0){
							color2 = star[i][j - 1].color;
						}
						star[i][j].color = getUnSameColor(color1, color2);
					}
					else{
						star[i][j].color = rand() % (STAR_COLOR_5 + 1);
					}
				}
			}
			star[i][j].state = STAR_SELECT_NO;
			star[i][j].intTag = i * COlUMNS_SIZE + j;
			star[i][j].targetIndex.x = i;
			star[i][j].targetIndex.y = j;
		}
	}
	m_fCurrentPersent += GameData::getInstance()->m_nHardPre;
	m_nCurStageScore = score;
	stageTarget = getStageTarget();
	findStarMax();
}

void StarUtil::radomRemain(){
	srand(time(NULL));
	for (int i = 0; i < COlUMNS_SIZE; i++){
		for (int j = 0; j < ROWS_SIZE; j++){
			int oriColor = star[i][j].color;
			if (oriColor == STAR_COLOR_NULL){
				continue;
			}
			star[i][j].state = STAR_SELECT_NO;
			star[i][j].color = rand() % (STAR_COLOR_5 + 1);
			if (oriColor == star[i][j].color){
				srand(i * j);
				star[i][j].color = (oriColor + 3) % (STAR_COLOR_5 + 1);
			}
			star[i][j].state = STAR_SELECT_NO;
		}
	}
	findStarMax();
}

void StarUtil::resetStarState(){
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = 0; j < STAR_ROW_COUNT; j++){
			star[i][j].state = STAR_SELECT_NO;
		}
	}
}

int StarUtil::InitQueue()
{
	LinkQ.front = new(QNode);
	LinkQ.rear = LinkQ.front;
	if (!LinkQ.front) return (OVER_FLOW);
	LinkQ.front->next = NULL;
	return OK;
}

int StarUtil::EnQueue(Index e)
{
	QueuePtr p;
	p = new(QNode);
	if (!p)return(OVER_FLOW);
	p->pp.x = e.x;
	p->pp.y = e.y;
	p->next = NULL;
	LinkQ.rear->next = p;
	LinkQ.rear = p;
	return OK;
}

int StarUtil::DeQueue(Index &e)
{
	QueuePtr p;
	if (LinkQ.front == LinkQ.rear)//队空时
	{
		p = LinkQ.front;
		delete(p);
		return ERROR;
	}
	p = LinkQ.front->next;
	e.x = p->pp.x;
	e.y = p->pp.y;
	LinkQ.front->next = p->next;
	if (LinkQ.rear == p) LinkQ.rear = LinkQ.front;//最后一个
	//printf("%d  ",e);
	delete(p);
	return OK;
}

Result StarUtil::onStarClicked(int x, int y){
	Result ret = { false, 0, STAR_COLOR_NULL, NULL, NULL };

	if (star[x][y].state == STAR_SELECT_NO || star[x][y].state == STAR_SELECT_1 || star[x][y].state == STAR_SELECT_2)  //第一次单击时，找出所有。
	{
		ret.count = findStar(x, y);
	}
	//	else  //第二次单击时，消除被选中的
	{
		int clickStarState = star[x][y].state;
		if (clickStarState == STAR_SELECT_NO || clickStarState == STAR_SELECT_1 || star[x][y].state == STAR_SELECT_2){
			return ret;
		}
		int count = 0;
		Index tempStar[STAR_ROW_COUNT * STAR_ROW_COUNT];
		//for (int i = 0;i < STAR_ROW_COUNT;i++){
		//	for(int j = 0;j < STAR_ROW_COUNT;j++){
		//		if(star[i][j].state == clickStarState && star[i][j].color != STAR_COLOR_NULL){   
		//			tempStar[count].x = i;
		//			tempStar[count].y = j;
		//			count++;
		//			//star[i][j].color = STAR_COLOR_NULL;
		//			star[i][j].state = STAR_SELECT_NO;   //失去选中状态
		//		}
		//	}
		//}
		for (int i = 0; i < STAR_ROW_COUNT; i++){
			for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
				if (star[i][j].state == clickStarState && star[i][j].color != STAR_COLOR_NULL){
					tempStar[count].x = i;
					tempStar[count].y = j;
					count++;
					//star[i][j].color = STAR_COLOR_NULL;
					star[i][j].state = STAR_SELECT_NO;   //失去选中状态
				}
			}
		}
		if (count >= 2) {
			ret.del = true;
			ret.count = count;
			ret.color = star[x][y].color;
			ret.pTags = new int[STAR_ROW_COUNT * STAR_ROW_COUNT];
			ret.tools = new int[6];
			ret.toolIndex = new int[STAR_ROW_COUNT * STAR_ROW_COUNT];
			if (m_bStarMode && ret.color + 1 == m_nTargetType)
			{
				m_nColorStarCount += count;
			}
			int diamondCount = 0;
			int stoneCount = 0;
			
			for (int j = 0; j < count; j++){
				diamondCount += findStar(tempStar[j].x, tempStar[j].y, TOOL_DIAMOND, false);
				stoneCount += findStar(tempStar[j].x, tempStar[j].y, TOOL_STONE, false);
				
				ret.pTags[j] = star[tempStar[j].x][tempStar[j].y].intTag;
				star[tempStar[j].x][tempStar[j].y].color = STAR_COLOR_NULL; //marker
			}
			if (diamondCount > 0)
			{
				ret.count += diamondCount;
				ret.tools[TOOL_DIAMOND] = diamondCount;
				int temp = 0;
				Index tempTool[STAR_ROW_COUNT * STAR_ROW_COUNT];
				for (int i = 0; i < STAR_ROW_COUNT; i++){
					for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
						if (star[i][j].state == STAR_SELECT_1 && star[i][j].color == TOOL_DIAMOND){
							tempTool[temp].x = i;
							tempTool[temp].y = j;
							temp++;
							//star[i][j].color = STAR_COLOR_NULL;
							star[i][j].state = STAR_SELECT_NO;   //失去选中状态
						}
					}
				}
				for (int j = 0; j < temp; j++){
					ret.toolIndex[j] = j + count;
					ret.pTags[j+count] = star[tempTool[j].x][tempTool[j].y].intTag;
					star[tempTool[j].x][tempTool[j].y].color = STAR_COLOR_NULL;
				}
				count += temp;
			}
			if (stoneCount > 0)
			{
				ret.count += stoneCount;
				ret.tools[TOOL_STONE] = stoneCount;
				int temp = 0;
				Index tempTool[STAR_ROW_COUNT * STAR_ROW_COUNT];
				for (int i = 0; i < STAR_ROW_COUNT; i++){
					for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
						if (star[i][j].state == STAR_SELECT_1 && star[i][j].color == TOOL_STONE){
							tempTool[temp].x = i;
							tempTool[temp].y = j;
							temp++;
							//star[i][j].color = STAR_COLOR_NULL;
							star[i][j].state = STAR_SELECT_NO;   //失去选中状态
						}
					}
				}
				for (int j = 0; j < temp; j++){
					ret.toolIndex[j] = j + count;
					ret.pTags[j + count] = star[tempTool[j].x][tempTool[j].y].intTag;
					star[tempTool[j].x][tempTool[j].y].color = STAR_COLOR_NULL;
				}
			}
		}
		score += getScore(count)*m_nScoreRate;
		m_nScoreRate = 1;
		m_nNextColorCount--;
		if (m_nNextColorCount <= 0)
		{
			m_nNextColorCount = 0;
			m_nNextColor = STAR_COLOR_NULL;
		}
		starMove();
		//deleteEmptyLeftColumn();
		resetStarState();
		//findStarMax();
	}
	return ret;
}

//星星向上
int StarUtil::starUp()
{
	for (int i = 0; i < COlUMNS_SIZE; i++)   //x  列
	{
		int totalNoColorCount = 0;
		for (int m = 0; m < ROWS_SIZE; m++)   //y  行
		{
			if (star[i][m].color == STAR_COLOR_NULL)
			{
				int noColorCount = 0;
				for (int j = m; j < ROWS_SIZE; j++)
				{
					if (star[i][j].color == STAR_COLOR_NULL)
					{
						noColorCount++;
						totalNoColorCount++;
					}
					else{
						break;
					}
				}
				for (int j = m; j < ROWS_SIZE - noColorCount; j++){
					star[i][j].color = star[i][j + noColorCount].color;
					if (j + totalNoColorCount < ROWS_SIZE)
					{
						star[i][j + totalNoColorCount].targetIndex.y = j;
					}
				}
				for (int j = ROWS_SIZE - noColorCount; j < ROWS_SIZE; j++){//将最下面的星星置空
					star[i][j].color = STAR_COLOR_NULL;
				}
				if (noColorCount >(ROWS_SIZE - 1) - m){//最下面的星星都是空的时候，结束
					break;
				}
			}
		}
	}
	return 0;
}

//星星掉落
int StarUtil::starDrop()
{
	for (int i = 0; i < COlUMNS_SIZE; i++)   //x  列
	{
		int totalNoColorCount = 0;
		for (int m = (ROWS_SIZE - 1); m > 0; m--)   //y  行
		{
			if (star[i][m].color == STAR_COLOR_NULL)
			{
				int noColorCount = 0;
				for (int j = m; j >= 0; j--)
				{
					if (star[i][j].color == STAR_COLOR_NULL)
					{
						noColorCount++;
						totalNoColorCount++;
					}
					else{
						break;
					}
				}
				for (int j = m; j >= noColorCount; j--){
					star[i][j].color = star[i][j - noColorCount].color;
					if (j - totalNoColorCount >= 0)
					{
						star[i][j - totalNoColorCount].targetIndex.y = j;
					}
				}
				for (int j = noColorCount - 1; j >= 0; j--){//将最上面的星星置空
					star[i][j].color = STAR_COLOR_NULL;
				}
				if (noColorCount > m){//最上面的星星都是空的时候，结束
					break;
				}
			}
		}
	}
	return 0;
}

//星星向左
int StarUtil::starLeft()
{
	for (int j = 0; j < ROWS_SIZE; j++)   //y  行
	{
		int totalNoColorCount = 0;
		for (int m = 0; m < COlUMNS_SIZE; m++)   //x  列
		{
			if (star[m][j].color == STAR_COLOR_NULL)
			{
				int noColorCount = 0;
				for (int i = m; i < COlUMNS_SIZE; i++)
				{
					if (star[i][j].color == STAR_COLOR_NULL)
					{
						noColorCount++;
						totalNoColorCount++;
					}
					else{
						break;
					}
				}
				for (int i = m; i < COlUMNS_SIZE - noColorCount; i++){
					star[i][j].color = star[i + noColorCount][j].color;
					if (i + totalNoColorCount < COlUMNS_SIZE)
					{
						star[i + totalNoColorCount][j].targetIndex.x = i;
					}
				}
				for (int i = COlUMNS_SIZE - noColorCount; i < COlUMNS_SIZE; i++){//将最右边的星星置空
					star[i][j].color = STAR_COLOR_NULL;
				}
				if (noColorCount >(COlUMNS_SIZE - 1) - m){//最右面的星星都是空的时候，结束
					break;
				}
			}
		}
	}
	return 0;
}

//星星向右
int StarUtil::starRight()
{
	for (int j = 0; j < ROWS_SIZE; j++)   //y  行
	{
		int totalNoColorCount = 0;
		for (int m = (COlUMNS_SIZE - 1); m > 0; m--)   //x  列
		{
			if (star[m][j].color == STAR_COLOR_NULL)
			{
				int noColorCount = 0;
				for (int i = m; i >= 0; i--)
				{
					if (star[i][j].color == STAR_COLOR_NULL)
					{
						noColorCount++;
						totalNoColorCount++;
					}
					else{
						break;
					}
				}
				for (int i = m; i >= noColorCount; i--){
					star[i][j].color = star[i - noColorCount][j].color;
					if (i - totalNoColorCount >= 0)
					{
						star[i - totalNoColorCount][j].targetIndex.x = i;
					}
				}
				for (int i = noColorCount - 1; i >= 0; i--){//将最上面的星星置空
					star[i][j].color = STAR_COLOR_NULL;
				}
				if (noColorCount > m){//最上面的星星都是空的时候，结束
					break;
				}
			}
		}
	}
	return 0;
}

void StarUtil::starMove()
{
	m_nStep--;
	StageInfo m_sCurrentStageInfo = DataManagerSelf->StagesVec.at((stage) % DataManagerSelf->StagesVec.size());
	m_nDirection = m_sCurrentStageInfo.content[m_nCurDirectionIndex];
	m_nCurDirectionIndex++;
	int contentSize = 0;
	for (int i = 0; i < sizeof(m_sCurrentStageInfo.content) / sizeof(int); i++)
	{
		if (m_sCurrentStageInfo.content[i] != 0)
		{
			contentSize++;
		}
		else
		{
			break;
		}
	}
	if (m_nCurDirectionIndex >= contentSize)
	{
		m_nCurDirectionIndex = 0;
	}
	switch (m_nDirection)
	{
	case DIC_UP:
		starUp();
		break;
	case DIC_DOWN:
		starDrop();
		break;
	case DIC_LEFT:
		starLeft();
		break;
	case DIC_RIGHT:
		starRight();
		break;
	}
}

//删除左列空行
int StarUtil::deleteEmptyLeftColumn()
{
	int totalEmptyColumnCount = 0;
	for (int i = 0; i < COlUMNS_SIZE; i++)
	{
		if (star[i][ROWS_SIZE - 1].color == STAR_COLOR_NULL)//先让星星掉落，所以如果最后一行为空，则是空列
		{
			int emptyColumnCount = 0;
			for (int j = i; j < COlUMNS_SIZE; j++)
			{
				if (star[j][ROWS_SIZE - 1].color == STAR_COLOR_NULL)
				{
					emptyColumnCount++;
					totalEmptyColumnCount++;
				}
				else{
					break;
				}
			}
			for (int j = i; j < (COlUMNS_SIZE - emptyColumnCount); j++){
				for (int k = 0; k < ROWS_SIZE; k++)
				{
					star[j][k].color = star[j + emptyColumnCount][k].color;
					if (j + totalEmptyColumnCount < COlUMNS_SIZE)
					{
						star[j + totalEmptyColumnCount][k].targetIndex.x = j;
					}
				}
			}
			for (int j = (COlUMNS_SIZE - emptyColumnCount); j < COlUMNS_SIZE; j++){//将最后几列置空
				for (int k = 0; k < ROWS_SIZE; k++)
				{
					star[j][k].color = STAR_COLOR_NULL;
				}
			}
			if (emptyColumnCount >= COlUMNS_SIZE - i){//剩下的都是空列时，结束
				break;
			}
		}
	}

	return 0;
}

//查找点中的点的左边与它相同颜色的点。
int StarUtil::SearchSameColorLeft(int x, int y, int color, bool inqueue, int state){
	Index e;  //临时变量
	if (x > 0 && star[x - 1][y].color == color && star[x - 1][y].state != state){
		if (inqueue){
			star[x - 1][y].state = state;
			e.x = x - 1;
			e.y = y;
			EnQueue(e);
		}
		return 1;
	}
	return 0;
}

//查找点中的点的右边与它相同颜色的点。
int StarUtil::SearchSameColorRight(int x, int y, int color, bool inqueue, int state){
	Index e;  //临时变量
	if (x < (STAR_ROW_COUNT - 1) && star[x + 1][y].color == color && star[x + 1][y].state != state){
		if (inqueue){
			star[x + 1][y].state = state;
			e.x = x + 1;
			e.y = y;
			EnQueue(e);
		}
		return 1;
	}
	return 0;
}

//查找点中的点的上面与它相同颜色的点。
int StarUtil::SearchSameColorTop(int x, int y, int color, bool inqueue, int state){
	Index e;  //临时变量
	if (y > 0 && star[x][y - 1].color == color && star[x][y - 1].state != state){
		if (inqueue){
			star[x][y - 1].state = state;
			e.x = x;
			e.y = y - 1;
			EnQueue(e);
		}
		return 1;
	}
	return 0;
}

//查找点中的点的下面与它相同颜色的点。
int StarUtil::SearchSameColorBottom(int x, int y, int color, bool inqueue, int state){
	Index e;  //临时变量
	if (y < (STAR_ROW_COUNT - 1) && star[x][y + 1].color == color && star[x][y + 1].state != state){
		if (inqueue){
			star[x][y + 1].state = state;
			e.x = x;
			e.y = y + 1;
			EnQueue(e);
		}
		return 1;
	}
	return 0;
}

void StarUtil::setStarColor(int x, int y, int color){
	if (x >= STAR_ROW_COUNT || x < 0 || y >= STAR_ROW_COUNT || y < 0 || color > STAR_COLOR_5 || color < STAR_COLOR_NULL)
		return;
	star[x][y].color = color;
	starMove();
	//deleteEmptyLeftColumn();
}

int StarUtil::saveState(){
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DATA_FILE;
	//CCLOG("path = %s",path.c_str()); 
	FILE *file = fopen(path.c_str(), "wb+");
	if (file) {
		putInt(xorEncDecInt(GAME_CONFIG_FILE_VERSION), file);
		putInt(xorEncDecInt(score), file);
		putInt(xorEncDecInt(stage), file);
		putInt(xorEncDecInt(m_nStep), file);
		for (int i = 0; i < STAR_ROW_COUNT; i++){
			for (int j = 0; j < STAR_ROW_COUNT; j++){
				putInt(xorEncDecInt(star[i][j].color), file);
			}
		}
		fclose(file);
		saveCurStageScore();
		saveCurPresent();
		return OK;
	}
	else{
		CCLOG("save file error.");
	}
	return ERROR;
}

void StarUtil::putInt(int src, FILE* file){
	int temp = src;
	fwrite((char *)(&temp), sizeof(temp), 1, file);
}

int StarUtil::loadLastState(){
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DATA_FILE;
	//CCLOG("path = %s",path.c_str()); 
	FILE *file = fopen(path.c_str(), "r");
	if (file) {
		int temp = -1;
		getInt(temp, file);
		if (xorEncDecInt(temp) != GAME_CONFIG_FILE_VERSION){
			return ERROR;
		}
		getInt(temp, file);
		score = xorEncDecInt(temp);
		getInt(temp, file);
		stage = xorEncDecInt(temp);
		getInt(temp, file);
		m_nStep = xorEncDecInt(temp);
		for (int i = 0; i < COlUMNS_SIZE; i++){
			for (int j = 0; j < ROWS_SIZE; j++){
				getInt(temp, file);
				star[i][j].color = xorEncDecInt(temp);
				star[i][j].state = STAR_SELECT_NO;
				star[i][j].intTag = i * COlUMNS_SIZE + j;
				star[i][j].targetIndex.x = i;
				star[i][j].targetIndex.y = j;
			}
		}
		fclose(file);
		loadCurStageScore();
		loadCurPresent();
		stageTarget = getStageTarget();
		return OK;
	}
	else{
		CCLOG("save file error.");
	}
	return ERROR;
}

void StarUtil::getInt(int &temp, FILE* file){
	fread((char *)(&temp), sizeof(temp), 1, file);
}

void StarUtil::getChar(char &temp, FILE* file){
	fread((char *)(&temp), sizeof(temp), 1, file);
}

int StarUtil::xorEncDecInt(int ch){
	return ch ^ 0x8B7E;
}

bool StarUtil::isStageOver(){
	if (m_nStep <= 0)
	{
		return true;
	}
	switch (m_nStageMode)
	{
	case MODE_SCORE:
		if (getScore() >= m_nTargetCount)
		{
			m_bIsgameWin = true;
			return true;
		}
		break;
	case MODE_STAR:
		if (m_nColorStarCount >= m_nTargetCount)
		{
			m_bIsgameWin = true;
			return true;
		}
		break;
	case MODE_TOOL:

		break;
	case MODE_SPRITE:

		break;
	default:
		break;
	}
	return false;
}

int StarUtil::stageOverScore(){
	int notClearCount = getNotClearCount();
	m_nLastScore = score;
	if (notClearCount < STAR_ROW_COUNT){
		score = score + getBonus(notClearCount);
	}
	return score;
}

int StarUtil::getNotClearCount(bool countEnd){
	int notClearCount = 0;
	bool end = false;
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = (STAR_ROW_COUNT - 1); j >= 0; j--){
			int color = star[i][j].color;
			if ((color == STAR_COLOR_NULL && j == (STAR_ROW_COUNT - 1)) || (countEnd && (notClearCount >= STAR_ROW_COUNT))){//会将左边空行移除，所以如果发现是空行，则不用判断右边的都为空行
				end = true;
				break;
			}
			if (color == STAR_COLOR_NULL){//由下往上，如果是无颜色则上面也不会再有
				break;
			}
			notClearCount++;
		}
		if (end){
			break;
		}
	}
	return notClearCount;
}

bool StarUtil::starClear(int x, int y){
	int clearCount = 0;
	if (x < 0 || y < 0 || x >= STAR_ROW_COUNT || y >= STAR_ROW_COUNT || star[x][y].color == STAR_COLOR_NULL){
		return false;
	}
	star[x][y].color = STAR_COLOR_NULL;
	star[x][y].state = STAR_SELECT_NO;
	clearCount++;
	if (x - 1 >= 0){//清除左排
		if (y - 1 >= 0 && star[x - 1][y - 1].color != STAR_COLOR_NULL){
			star[x - 1][y - 1].color = STAR_COLOR_NULL;
			star[x - 1][y - 1].state = STAR_SELECT_NO;
			clearCount++;
		}
		if (star[x - 1][y].color != STAR_COLOR_NULL){
			star[x - 1][y].color = STAR_COLOR_NULL;
			star[x - 1][y].state = STAR_SELECT_NO;
			clearCount++;
		}
		if (y + 1 < STAR_ROW_COUNT && star[x - 1][y + 1].color != STAR_COLOR_NULL){
			star[x - 1][y + 1].color = STAR_COLOR_NULL;
			star[x - 1][y + 1].state = STAR_SELECT_NO;
			clearCount++;
		}
	}
	if (x + 1 < STAR_ROW_COUNT){//清除右排
		if (y - 1 >= 0 && star[x + 1][y - 1].color != STAR_COLOR_NULL){
			star[x + 1][y - 1].color = STAR_COLOR_NULL;
			star[x + 1][y - 1].state = STAR_SELECT_NO;
			clearCount++;
		}
		if (star[x + 1][y].color != STAR_COLOR_NULL){
			star[x + 1][y].color = STAR_COLOR_NULL;
			star[x + 1][y].state = STAR_SELECT_NO;
			clearCount++;
		}
		if (y + 1 < STAR_ROW_COUNT && star[x + 1][y + 1].color != STAR_COLOR_NULL){
			star[x + 1][y + 1].color = STAR_COLOR_NULL;
			star[x + 1][y + 1].state = STAR_SELECT_NO;
			clearCount++;
		}
	}
	if (y - 1 >= 0 && star[x][y - 1].color != STAR_COLOR_NULL){
		star[x][y - 1].color = STAR_COLOR_NULL;
		star[x][y - 1].state = STAR_SELECT_NO;
		clearCount++;
	}
	if (y + 1 < STAR_ROW_COUNT && star[x][y + 1].color != STAR_COLOR_NULL){
		star[x][y + 1].color = STAR_COLOR_NULL;
		star[x][y + 1].state = STAR_SELECT_NO;
		clearCount++;
	}
	score = score + clearCount*clearCount * 5;
	starMove();
	//deleteEmptyLeftColumn();
	return true;
}

void StarUtil::resetTargetTags()
{
	for (int i = 0; i < COlUMNS_SIZE; i++){
		for (int j = 0; j < ROWS_SIZE; j++){
			star[i][j].targetIndex.x = i;
			star[i][j].targetIndex.y = j;
		}
	}
	//for (int i = 0; i < STAR_ROW_COUNT; i++){
	//	for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
	//		if (star[i][j].color == STAR_COLOR_NULL){
	//			star[i][j].color = STAR_COLOR_1;
	//			star[i][j].state = STAR_SELECT_NO;   //失去选中状态
	//			star[i][j].intTag = i * COlUMNS_SIZE + j;
	//			star[i][j].targetIndex.x = i;
	//			star[i][j].targetIndex.y = j;
	//		}
	//	}
	//}
}

int StarUtil::getTarget(){
	return stageTarget;
}

bool StarUtil::nextStage(){
	//stageTarget = getStageTarget();
	if (m_bIsgameWin/*score >= stageTarget*/){
		stage++;
		//initStar();
		initStarEx();
		return true;
	}
	UserInfo::setBestScore(score);
	m_nNewScore = score;
	score = m_nLastScore;
	saveState();
	return false;
}

bool StarUtil::hasSavedState(){
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DATA_FILE;
	struct stat   buffer;
	return  (stat(path.c_str(), &buffer) == 0);
}

Result StarUtil::rowDelete(int x, int y, int count, bool makeChange /* = false */)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[9];

	int startX = (x - count) >= 0 ? (x - count) : 0;
	int endX = (x + count) < COlUMNS_SIZE ? (x + count) : (COlUMNS_SIZE - 1);

	for (int c = startX; c <= endX; c++)
	{
		if (star[c][y].color != STAR_COLOR_NULL)
		{
			Index index = { c, y };
			ret.pTags[ret.count] = getTagByIndex(index);
			ret.count++;
			if (makeChange)
			{
				if (m_bStarMode && star[c][y].color + 1 == m_nTargetType)
				{
					m_nColorStarCount++;
				}
				star[c][y].color = STAR_COLOR_NULL;
			}
		}
	}
	if (makeChange && ret.count > 0){
		score += getScore(ret.count);
		starMove();
	}
	return ret;
}

Result StarUtil::colDelete(int x, int y, int count, bool makeChange /* = false */)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[9];

	int startY = (y - count) >= 0 ? (y - count) : 0;
	int endY = (y + count) < ROWS_SIZE ? (y + count) : (ROWS_SIZE - 1);

	for (int r = startY; r <= endY; r++)
	{
		if (star[x][r].color != STAR_COLOR_NULL)
		{
			Index index = { x, r };
			ret.pTags[ret.count] = getTagByIndex(index);
			ret.count++;
			if (makeChange)
			{
				if (m_bStarMode && star[x][r].color + 1 == m_nTargetType)
				{
					m_nColorStarCount++;
				}
				star[x][r].color = STAR_COLOR_NULL;
			}
		}
	}

	if (makeChange && ret.count > 0){
		score += getScore(ret.count);
		starMove();
		//deleteEmptyLeftColumn();
	}
	return ret;
}

Result StarUtil::bulkDelete(int x, int y, bool makeChange /* = false */)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[9];

	int startX = (x - 1) >= 0 ? (x - 1) : 0;
	int endX = (x + 1) < COlUMNS_SIZE ? (x + 1) : (COlUMNS_SIZE - 1);
	int startY = (y - 1) >= 0 ? (y - 1) : 0;
	int endY = (y + 1) < ROWS_SIZE ? (y + 1) : (ROWS_SIZE - 1);

	for (int c = startX; c <= endX; c++)
	{
		for (int r = startY; r <= endY; r++)
		{
			if (star[c][r].color != STAR_COLOR_NULL)
			{
				Index index = { c, r };
				ret.pTags[ret.count] = getTagByIndex(index);
				ret.count++;
				if (makeChange)
				{
					if (m_bStarMode && star[c][r].color + 1 == m_nTargetType)
					{
						m_nColorStarCount++;
					}
					star[c][r].color = STAR_COLOR_NULL;
				}
			}
		}
	}

	if (makeChange && ret.count > 0){
		score += getScore(ret.count)*m_nScoreRate;
		m_nScoreRate = 1;
		m_nNextColorCount--;
		if (m_nNextColorCount <= 0)
		{
			m_nNextColorCount = 0;
			m_nNextColor = STAR_COLOR_NULL;
		}
		starMove();
	}
	return ret;
}

Result StarUtil::centerDelete(int x, int y, int count, bool makeChange /* = false */)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[9];

	int startX = (x - count) >= 0 ? (x - count) : 0;
	int endX = (x + count) < COlUMNS_SIZE ? (x + count) : (COlUMNS_SIZE - 1);
	int startY = (y - count) >= 0 ? (y - count) : 0;
	int endY = (y + count) < ROWS_SIZE ? (y + count) : (ROWS_SIZE - 1);

	for (int c = startX; c <= endX; c++)
	{
		for (int r = startY; r <= endY; r++)
		{
			if (star[c][r].color != STAR_COLOR_NULL)
			{
				Index index = { c, r };
				ret.pTags[ret.count] = getTagByIndex(index);
				ret.count++;
				if (makeChange)
				{
					if (m_bStarMode && star[c][r].color + 1 == m_nTargetType)
					{
						m_nColorStarCount++;
					}
					star[c][r].color = STAR_COLOR_NULL;
				}
			}
		}
	}

	if (makeChange && ret.count > 0){
		score += getScore(ret.count)*m_nScoreRate;
		m_nScoreRate = 1;
		m_nNextColorCount--;
		if (m_nNextColorCount <= 0)
		{
			m_nNextColorCount = 0;
			m_nNextColor = STAR_COLOR_NULL;
		}
		starMove();
	}
	return ret;
}

int StarUtil::findStar(int x, int y, int color, bool reseState){
	int findState = STAR_SELECT_YES;
	if (reseState){
		resetStarState();//清除所有状态			
	}
	else{
		findState = STAR_SELECT_1;
	}
	star[x][y].state = findState;
	if (color == STAR_COLOR_NULL)
	{
		color = star[x][y].color;
	}
	InitQueue();
	Index e;  //临时变量
	e.x = x;
	e.y = y;
	EnQueue(e);
	if (star[x][y].color != STAR_COLOR_NULL){
		int searchRet = 0;
		do{
			searchRet += SearchSameColorLeft(e.x, e.y, color, true, findState);
			searchRet += SearchSameColorRight(e.x, e.y, color, true, findState);
			searchRet += SearchSameColorTop(e.x, e.y, color, true, findState);
			searchRet += SearchSameColorBottom(e.x, e.y, color, true, findState);
		} while (DeQueue(e));
		if (!searchRet){
			star[x][y].state = STAR_SELECT_NO;
		}
		return searchRet;
	}
	return 0;
}

int StarUtil::findStarMax(){
	int maxCount = 0;
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = 0; j < STAR_ROW_COUNT; j++){
			if (star[i][j].state == STAR_SELECT_NO && star[i][j].color != STAR_COLOR_NULL){
				int findCount = findStar(i, j, false);
				if (findCount > maxCount){
					maxCount = findCount;
					resetMax();
					for (int k = 0; k < STAR_ROW_COUNT; k++){
						for (int l = 0; l < STAR_ROW_COUNT; l++){
							if (star[k][l].state == STAR_SELECT_1){
								star[k][l].state = STAR_SELECT_MAX;
							}
						}
					}
				}
				else{
					for (int k = 0; k < STAR_ROW_COUNT; k++){
						for (int l = 0; l < STAR_ROW_COUNT; l++){
							if (star[k][l].state == STAR_SELECT_1){
								star[k][l].state = STAR_SELECT_2;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

bool StarUtil::resetMax(){
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = 0; j < STAR_ROW_COUNT; j++){
			if (star[i][j].state == STAR_SELECT_MAX){
				star[i][j].state = STAR_SELECT_2;
			}
		}
	}
	return true;
}

int StarUtil::remainCount(){
	int count = 0;
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
			if (star[i][j].color != STAR_COLOR_NULL){
				count++;
			}
			if (j == (STAR_ROW_COUNT - 1) && star[i][j].color == STAR_COLOR_NULL){
				break;
			}
		}
	}
	return count;
}

void StarUtil::saveCurStageScore(){
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(KEY_CURSTAGE_SCORE, m_nCurStageScore);
	CCUserDefaultEx::sharedUserDefault()->flush();
}

void StarUtil::loadCurStageScore(){
	m_nCurStageScore = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(KEY_CURSTAGE_SCORE, 0);
}

void StarUtil::saveCurPresent(){
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(KEY_CURPRESENT, m_fCurrentPersent);
	CCUserDefaultEx::sharedUserDefault()->flush();
}

void StarUtil::loadCurPresent(){
	m_fCurrentPersent = CCUserDefaultEx::sharedUserDefault()->getFloatForKey(KEY_CURPRESENT, 0.0f);
}

int StarUtil::getUnSameColor(int color1, int color2){
	if (color1 == STAR_COLOR_NULL){
		if (color2 == STAR_COLOR_NULL){
			return rand() % (STAR_COLOR_5 + 1);
		}
		return (color2 + 3) % (STAR_COLOR_5 + 1);
	}
	if (color2 == STAR_COLOR_NULL){
		return (color1 + 3) % (STAR_COLOR_5 + 1);
	}
	if (color1 == color2){
		return (color1 + 3) % (STAR_COLOR_5 + 1);
	}
	if (color1 > color2){
		if ((color1 - color2) == 1){
			return (color1 + 3) % (STAR_COLOR_5 + 1);
		}
		else{
			return (color2 + (color1 - color2) / 2) % (STAR_COLOR_5 + 1);
		}
	}
	else{
		if ((color2 - color1) == 1){
			return (color2 + 3) % (STAR_COLOR_5 + 1);
		}
		else{
			return (color1 + (color2 - color1) / 2) % (STAR_COLOR_5 + 1);
		}
	}
}

int StarUtil::getStageTarget() {
	if (stage < GameData::getInstance()->m_nPassScoreSize){
		return GameData::getInstance()->m_nPassScore[stage];
	}
	if (GameData::getInstance()->m_nPassScoreLevel > 0 &&
		((stage - GameData::getInstance()->m_nPassScoreSize + 1) > GameData::getInstance()->m_nPassScoreLevel)){
		return GameData::getInstance()->m_nPassScoreMaxBase +
			GameData::getInstance()->m_nPassScoreMax *
			(stage - GameData::getInstance()->m_nPassScoreLevel - GameData::getInstance()->m_nPassScoreSize + 1);
	}
	return (stage - GameData::getInstance()->m_nPassScoreSize + 2) * (stage - GameData::getInstance()->m_nPassScoreSize + 1) / 2 * GameData::getInstance()->m_nPassScoreUp
		+ GameData::getInstance()->m_nPassScore[GameData::getInstance()->m_nPassScoreSize - 1]
		+ GameData::getInstance()->m_nPassScoreBase * (stage - GameData::getInstance()->m_nPassScoreSize + 1);
};

void StarUtil::addStep(int count)
{
	m_nStep += count;
}

void StarUtil::randomStarColorChange(int color, int count)
{
	srand(time(NULL));
	int sum = 0;
	do
	{
		int i = rand() % STAR_ROW_COUNT;
		int j = rand() % STAR_ROW_COUNT;
		if (star[i][j].color >= STAR_COLOR_1 && star[i][j].color <= STAR_COLOR_5)
		{
			star[i][j].color = color;
			sum++;
		}
	} while (sum < count);
}

void StarUtil::randomStarToSomething(int color, int count)
{
	srand(time(NULL));
	int sum = 0;
	do
	{
		int i = rand() % STAR_ROW_COUNT;
		int j = rand() % STAR_ROW_COUNT;
		if (star[i][j].color >= STAR_COLOR_1 && star[i][j].color <= STAR_COLOR_5)
		{
			star[i][j].color = color;
			sum++;
		}
	} while (sum < count);
}

void StarUtil::setScoreRate(int rate)
{
	m_nScoreRate = rate;
}

Result StarUtil::randomDeleteStar(int count, bool makeChange)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[9];

	srand(time(NULL));
	int sum = 0;
	do
	{
		int i = rand() % STAR_ROW_COUNT;
		int j = rand() % STAR_ROW_COUNT;
		if ((star[i][j].color >= STAR_COLOR_1 && star[i][j].color <= STAR_COLOR_5) || star[i][j].color == TOOL_DIAMOND)
		{
			Index index = { i, j };
			ret.pTags[ret.count] = getTagByIndex(index);
			ret.count++;
			if (makeChange)
			{
				if (m_bStarMode && star[i][j].color + 1 == m_nTargetType)
				{
					m_nColorStarCount++;
				}
				star[i][j].color = STAR_COLOR_NULL;
				sum++;
			}
		}
	} while (sum < count);

	if (makeChange && ret.count > 0){
		score += getScore(ret.count)*m_nScoreRate;
		m_nScoreRate = 1;
		m_nNextColorCount--;
		if (m_nNextColorCount <= 0)
		{
			m_nNextColorCount = 0;
			m_nNextColor = STAR_COLOR_NULL;
		}
		starMove();
	}
	return ret;
}

void StarUtil::setNextColor(int color, int count)
{
	m_nNextColor = color;
	m_nNextColorCount = count;
}

Result StarUtil::bombClearAllStar(bool makeChange /*= false*/)
{
	Result ret = { false, 0, STAR_COLOR_NULL, NULL };
	ret.pTags = new int[STAR_ROW_COUNT*STAR_ROW_COUNT];
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = 0; j < STAR_ROW_COUNT; j++){
			Index index = { i, j };
			ret.pTags[ret.count] = getTagByIndex(index);
			ret.count++;
			if (makeChange)
			{
				if (m_bStarMode && star[i][j].color + 1 == m_nTargetType)
				{
					m_nColorStarCount++;
				}
				star[i][j].color = STAR_COLOR_NULL;
			}
		}
	}
	if (makeChange)
	{
		//score += getScore(ret.count)*m_nScoreRate;
		m_nScoreRate = 1;
		m_nNextColorCount--;
		if (m_nNextColorCount <= 0)
		{
			m_nNextColorCount = 0;
			m_nNextColor = STAR_COLOR_NULL;
		}
		starMove();
	}
	return ret;
}