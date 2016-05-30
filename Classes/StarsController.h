#ifndef __STARSCONTROLLER_H__
#define __STARSCONTROLLER_H__

struct IStarsView
{
    void moveStar(){}
    void genNewStars(){}
    void initStars(){}
    
};

class StarsController
{
public:
	StarsController();
	~StarsController();
    
    void addView();
private:

};
#endif