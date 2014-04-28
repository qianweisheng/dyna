const int gridRow = 6;
const int gridCol = 9;
const int startState = 18;		//״̬�����Ա�ţ���0��ʼ�ൽ53
const int goalState = 8;
const int actionNum = 4;								//4������0����Ķ���ʱ�ң�1���£�2����3����

const double epsilon = 0.10;
const double gamma = 0.95;
const double alpha = 0.10;

class GridWorld
{
private:
	int gridEnviroment[gridRow+2][gridCol+2];
	double qValue[gridRow*gridCol][actionNum];
	int model[gridRow*gridCol][actionNum][2];			//ѧϰ��ģ�ͣ���һά��״̬
														//�ڶ�ά�Ƕ���������ά����һ״̬�ͽ���
public:
	GridWorld();										//��ʼ���������磬1�����ϰ�			
	~GridWorld();
	int getgridEnviroment(int row, int col);
	double getQValue(int state, int action);
	void setQValue(int state, int action, double q);
	int getModelNextState(int currentState, int currentAction);
	int getModelReward(int currentState, int currentAction);
	void setModel(int currentState, int currentAction, int nextState, int reward);
};


