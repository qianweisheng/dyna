#include "stdafx.h"
#include "GridWorld.h"

GridWorld::GridWorld()
{
/*********************��ʼ������***************************/
	for (int row = 0; row < gridRow+2; row++)
	{
		for (int col = 0; col < gridCol+2; col++)
		{
			gridEnviroment[row][col] = 1;
		}
	}
	for (int row = 1; row < gridRow+1; row++)
	{
		for (int col = 1; col < gridCol+1; col++)
		{
			gridEnviroment[row][col] = 0;
		}
	}
	gridEnviroment[2][3] = 1;
	gridEnviroment[3][3] = 1;
	gridEnviroment[4][3] = 1;
	gridEnviroment[5][6] = 1;
	gridEnviroment[1][8] = 1;
	gridEnviroment[2][8] = 1;
	gridEnviroment[3][8] = 1;

/*****************   ��ʼ��Qֵ   ****************************/
	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
			qValue[state][action] = 0.00;
		}
	}

/*****************   ��ʼ��ģ��    ************************/

	for (int state = 0; state < gridRow*gridCol; state++)
	{
		for (int action = 0; action < actionNum; action++)
		{
			for (int next = 0; next < 2; next++)
			{
				if (next == 0)
				{
					model[state][action][next] = -100;			//������һ״̬Ϊ-100,Ҳ����û����һ��״̬
				}else
				{
					model[state][action][next] = 0;				//���ý���Ϊ0����Ϊû���ܵ����״̬������û�н���
				}
				
			}
		}
	}
}

GridWorld::~GridWorld()
{

}

int GridWorld::getgridEnviroment( int row, int col )
{
	return gridEnviroment[row][col];
}

void GridWorld::setQValue( int state, int action, double q )
{
	qValue[state][action] = q;
}

double GridWorld::getQValue( int state, int action )
{
	return qValue[state][action];
}

int GridWorld::getModelNextState( int currentState, int currentAction )
{
	return model[currentState][currentAction][0];
}

int GridWorld::getModelReward( int currentState, int currentAction )
{
	return model[currentState][currentAction][1];
}

void GridWorld::setModel( int currentState, int currentAction, int nextState, int reward )
{
	model[currentState][currentAction][0] = nextState;
	model[currentState][currentAction][1] = reward;
}

