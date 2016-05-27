#ifndef __STAGEMODEL_H__
#define  __STAGEMODEL_H__

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

class StageModel
{
public:
	static StageModel *theModel();
	int getCurDirection(){ return m_direction; }
private:
	StageModel();
	~StageModel();
private:
	int m_direction;
};
#endif