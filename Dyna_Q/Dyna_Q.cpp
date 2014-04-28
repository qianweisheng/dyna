// Dyna_Q.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GridWorld.h"
#include "rangedRand.h"

using namespace std;

int getBestAction( GridWorld &gridworld, int currentState )
{
	double maxQ = gridworld.getQValue(currentState, 0);
	int bestAction = 0;
	int array[4] = {1, 0, 0, 0};
	int tempAction = -1;
	int flag = 0;
	/*for (int itera = 0; itera < 4; itera++)
	{
		if ((currentState+1) % 9 ==0)
		{
			max = gridworld.getQValue(currentState, 0);
		}else
		{
			max = gridworld.getQValue(currentState+1, 0);
		}

		if (currentState > 44)
		{
			max = (max > gridworld.getQValue(currentState, 1)) ? max : gridworld.getQValue(currentState, 1);
			bestAction = (max > gridworld.getQValue(currentState, 1)) ? bestAction : 1;
		} 
		else
		{
			max = (max > gridworld.getQValue(currentState+9, 1)) ? max : gridworld.getQValue(currentState+9, 1);
			bestAction = (max > gridworld.getQValue(currentState+9, 1)) ? bestAction : 1;
		}

		if ((currentState % 9) ==0)
		{
			max = (max > gridworld.getQValue(currentState, 2)) ? max : gridworld.getQValue(currentState, 1);
			bestAction = (max > gridworld.getQValue(currentState, 2)) ? bestAction : 2;
		}else
		{
			max = (max > gridworld.getQValue(currentState-1, 2)) ? max : gridworld.getQValue(currentState-1, 1);
			bestAction = (max > gridworld.getQValue(currentState-1, 2)) ? bestAction : 2;
		}

		if (currentState < 9)
		{
			max = (max > gridworld.getQValue(currentState, 3)) ? max : gridworld.getQValue(currentState, 3);
			bestAction = (max > gridworld.getQValue(currentState, 3)) ? bestAction : 3;
		} 
		else
		{
			max = (max > gridworld.getQValue(currentState-9, 3)) ? max : gridworld.getQValue(currentState-9, 3);
			bestAction = (max > gridworld.getQValue(currentState-9, 3)) ? bestAction : 3;
		}
	}*/

	if (gridworld.getQValue(currentState, 1) > maxQ)
	{
		maxQ = gridworld.getQValue(currentState, 1);
		array[1] = 1;
		array[0] = 0;
	}

	if(gridworld.getQValue(currentState, 1) == maxQ)
		array[1] = 1;

	if (gridworld.getQValue(currentState, 2) > maxQ)
	{
		maxQ = gridworld.getQValue(currentState, 2);
		array[2] = 1;
		array[0] = array[1] = 0;
	}
	if(gridworld.getQValue(currentState, 2) == maxQ)
		array[2] = 1;

	if (gridworld.getQValue(currentState, 3) > maxQ)
	{
		maxQ = gridworld.getQValue(currentState, 3);
		array[3] = 1;
		array[0] = array[1] = array[2] = 0;
	}

	if(gridworld.getQValue(currentState, 3) == maxQ)
		array[3] = 1;

	while(!flag){
		tempAction = rangedRand(0, 4);
		int flagpie = array[tempAction];
		if(flagpie == 1)
		{
			flag = 1;
			bestAction = tempAction;
		}

	}	

	return bestAction;
}

int epsilon_greedy_selection(GridWorld gridworld, int currentState, double epsilonPie)
{
	if (((double)rand() / (RAND_MAX+1)) > epsilonPie)
	{
		return getBestAction(gridworld, currentState);
	} 
	else
	{
		return rangedRand(0, 4);
	}
}

int getNextState( GridWorld &gridWorld, int currentState, int currentAction )
{
	int nextState = -100;
	int currentRowInGridEnviroment = currentState/9 + 1;
	int currentColInGridEnviroment = currentState - 9*(currentRowInGridEnviroment - 1) + 1; 
//采用向右动作
	if (currentAction == 0)
		if ( gridWorld.getgridEnviroment(currentRowInGridEnviroment, currentColInGridEnviroment+1) ==1)
		{
			nextState = currentState;
		} 
		else
		{
			nextState = currentState+1;
		}
//采用向下动作
	if (currentAction == 1)
		if ( gridWorld.getgridEnviroment(currentRowInGridEnviroment+1, currentColInGridEnviroment) ==1)
		{
			nextState = currentState;
		} 
		else
		{
			nextState = currentState+9;
		}
//采用向左动作
	if (currentAction == 2)
		if ( gridWorld.getgridEnviroment(currentRowInGridEnviroment, currentColInGridEnviroment-1) ==1)
		{
			nextState = currentState;
		} 
		else
		{
			nextState = currentState-1;
		}
//采用向上动作
	if (currentAction == 3)
		if ( gridWorld.getgridEnviroment(currentRowInGridEnviroment-1, currentColInGridEnviroment) == 1)
		{
			nextState = currentState;
		} 
		else
		{
			nextState = currentState-9;
		}

	return nextState;
}

int getReward( int nextState )
{
	if (nextState == 8) return 1;
	else return 0;
}

/************************************************************************/
/*                          某状态的最大Q值                              */
/************************************************************************/
double maxQForAllAction(GridWorld &gridWorld, int state)
{
	double max = 0.0;
	double temp = 0.0;

	for (int ite = 0; ite < 4; ite++)
	{
		temp = gridWorld.getQValue(state, ite);
		if (max < temp)
		{
			max = temp;
		}
	}	

	return max;
}

void iterationPlanning( GridWorld &gridWorld )
{
	int stateSample = -100;
	int actionSample = -1;
	int nextState = -100;
	int reward = 0;
	int flag = 0;				//抽到的状态和动作是模型中有的时，置为1

	while (!flag)
	{
		stateSample = rangedRand(0, 54);
		actionSample = rangedRand(0, 4);
		nextState = gridWorld.getModelNextState(stateSample, actionSample);
		if (nextState != -100)
		{
			flag = 1;
		}
	}

	reward = gridWorld.getModelReward(stateSample, actionSample);

/************************************************************************/
/*                        一步Q规划                                     */
/************************************************************************/
	double oldQ = 0.0;
	double tempQ = 0.0;
	double maxNextQ = 0.0;

	oldQ = gridWorld.getQValue(stateSample,actionSample);
	maxNextQ = maxQForAllAction(gridWorld, nextState);
	tempQ = oldQ + alpha*(reward + gamma*maxNextQ - oldQ);
	//if (oldQ != 0.00)
	//{
	//	cout << "currentState = " << stateSample << "  oldQ = " << oldQ << "  tempQ = " << tempQ << endl;
	//}
	//if(stateSample == 26 && actionSample ==3)
	//	cout << 26 << "\t" << 3 << endl << oldQ <<endl << tempQ << endl << maxNextQ << endl << nextState << endl;

	gridWorld.setQValue(stateSample, actionSample, tempQ);

}

int iteration(int currentState, GridWorld &gridWorld, int episodeCounter)				//返回下一个状态
{
	int currentAction = -1;			//无效动作
	int nextState = -100;			//无效状态
	int reward = 0;
	double tempQ = 0.0;
	double oldQ = 0.0;

	currentAction = epsilon_greedy_selection(gridWorld, currentState, epsilon);
//	cout << currentAction << endl;
	nextState = getNextState(gridWorld, currentState, currentAction);
	reward = getReward(nextState);


/************************************************************************/
/*                            Q 学习                                    */
/************************************************************************/
	oldQ = gridWorld.getQValue(currentState,currentAction);
	tempQ = oldQ + alpha*(reward + gamma*maxQForAllAction(gridWorld, nextState) - oldQ);
	gridWorld.setQValue(currentState, currentAction, tempQ);
	/*if (oldQ != 0.00)
	{
	cout << "currentState = " << currentState << "  oldQ = " << oldQ << "  tempQ = " << tempQ << endl;
	}*/

/************************************************************************/
/*                           模型学习                                    */
/************************************************************************/
	gridWorld.setModel(currentState, currentAction, nextState, reward);

/************************************************************************/
/*                           规划N次  50                                   */
/************************************************************************/
	for (int ite = 0; ite < 0; ite++)
	{
		if(episodeCounter == 1) break;
		iterationPlanning(gridWorld);
	}

	return nextState;
}

void iterationEpisode( const int startState, GridWorld &gridWorld, int episodeCounter)
{
	int flag = 0;							//flag=1的时候，表示情节结束
	int counterStep = 1;					//计数器，记录一个情节所走的步数
	int currentState = startState;
	int nextState = -100;

	while (!flag)
	{
		nextState = iteration(currentState, gridWorld, episodeCounter);
		if (nextState == 8)
		{
			flag = 1;
		}
		currentState = nextState;
		counterStep++;
		/*cout <<"episode :" << episodeCounter <<  "   step :" << counterStep << endl;*/
	}
	cout <<"episode :" << episodeCounter <<  "   step :" << counterStep << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

	/*GridWorld gridWorld;
	for (int row = 0; row < gridRow+2; row++)
	{
		for (int col = 0; col < gridCol+2; col++)
		{
			cout << setw(6) << gridWorld.getgridEnviroment(row, col);
		}

		cout << endl;
	}*/

	/*GridWorld gridWorld;
	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
			cout << setw(6) << gridWorld.getQValue(state, action);
		}
		cout << endl;
	}*/

	/*GridWorld gridWorld;
	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
				cout << setw(10) << gridWorld.getModelReward(state, action); 
		}
		cout << endl;
	}*/

	int currentState = startState;
	int nextState = -100;
	int episodeCounter = 1;
//	int flag = 0;							//flag=1的时候，表示情节结束
//	int counter = 1;						//计数器，记录一个情节所走的步数
	GridWorld gridWorld;

	for (int iteEpisode = 0; iteEpisode < 100; iteEpisode++)
	{
		iterationEpisode(startState,gridWorld, episodeCounter);
		episodeCounter++;
	}
	

	/*while (!flag)
	{
		nextState = iteration(currentState, gridWorld);
		if (nextState == 8)
		{
			flag = 1;
		}
		currentState = nextState;
		counter++;
		cout << "step :" << counter << endl;
	}*/


	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
//			cout << setw(6) << gridWorld.getQValue(state, action);
			printf("%10.6f", gridWorld.getQValue(state, action));
		}
		cout << endl;
	}
	cout << "reward" << endl;
	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
			cout << setw(10) << gridWorld.getModelReward(state, action); 
		}
		cout << endl;
	}
	cout << "nextState" << endl;
	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
			cout << setw(10) << gridWorld.getModelNextState(state, action);
		}
		cout << endl;
	}

	return 0;
}

