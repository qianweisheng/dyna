const int gridRow = 6;
const int gridCol = 9;
const int startState = 18;		//状态是线性编号，从0开始编到53
const int goalState = 8;
const int actionNum = 4;								//4个动作0代表的动作时右，1是下，2是左，3是上

const double epsilon = 0.10;
const double gamma = 0.95;
const double alpha = 0.10;

class GridWorld
{
private:
	int gridEnviroment[gridRow+2][gridCol+2];
	double qValue[gridRow*gridCol][actionNum];
	int model[gridRow*gridCol][actionNum][2];			//学习的模型，第一维是状态
														//第二维是动作，第三维是下一状态和奖赏
public:
	GridWorld();										//初始化格子世界，1代表障碍			
	~GridWorld();
	int getgridEnviroment(int row, int col);
	double getQValue(int state, int action);
	void setQValue(int state, int action, double q);
	int getModelNextState(int currentState, int currentAction);
	int getModelReward(int currentState, int currentAction);
	void setModel(int currentState, int currentAction, int nextState, int reward);
};


