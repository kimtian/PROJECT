#include<iostream>
#include <string>
#include<vector>
#include <stack>

using namespace std;

//�ȶ���һ������ӿ�

class Command
{
public:
	Command(){}
	virtual ~Command(){}

	virtual void Execute() = 0;
};


class InputCommand : public Command
{
public:

	InputCommand(const string &input)
	{
		mInput = input;
	}
	~InputCommand()
	{}

	void Execute()
	{
		cout << "current string is:" << mInput.c_str() << endl;
	
	}

private:

	 string mInput;
};

class Commander
{
public:
	Commander(Command *pCmd)
	{
		//�������������  
		mUndo.push(pCmd);
	}
	~Commander()
	{
		while ( mUndo.empty()==false)
		{
			delete mUndo.top();
			mUndo.pop();
		}
		while ( mRedo.empty()==false )
		{
			delete mRedo.top();
			mRedo.pop();
		}
	}

	void ExecuteCommand(Command *pCmd)
	{
		pCmd->Execute();
		mUndo.push(pCmd);
	}

	void Undo()
	{
		if (mUndo.size() < 2)
		{
			//�޷����˳���û������  
			cout<<"undo failed.\n"<<endl;
			return;
		}

		cout<<"undo:\n"<<endl;

		//��ǰ����  
		auto pCmd = mUndo.top();

		//���浱ǰ����  
		mRedo.push(pCmd);

		//����  
		mUndo.pop();

		//��ԭ���ϸ�����  
		pCmd = mUndo.top();

		pCmd->Execute();
	}

	void Redo()
	{
		if (mRedo.empty())
		{
			//�޷�ǰ������û������  
			printf("redo failed.\n");
			return;
		}

		printf("redo:\n");

		auto pCmd = mRedo.top();

		pCmd->Execute();

		mRedo.pop();

		mUndo.push(pCmd);
	}

private:
	 stack< Command* > mUndo;
	 stack< Command* > mRedo;
};
//ģ�������ַ���,Ȼ���������ַ�������undo redo����  
int main()
{
	//Ĭ��û�������ַ��������ǿգ�����Ϊ����ʾ��ֵһ��������ַ���  
	Commander *p = new Commander(new InputCommand("[empty]"));

	//����1234  
	p->ExecuteCommand(new InputCommand("1234"));
	//����567  
	p->ExecuteCommand(new InputCommand("567"));
	//����xxx  
	p->ExecuteCommand(new InputCommand("xxx"));

	//ִ��һ��undo ������ 567  
	p->Undo();
	//ִ��һ��undo ������ 1234  
	p->Undo();

	//undo���м��������ַ��� insert ���� 1234  
	p->ExecuteCommand(new InputCommand("insert"));

	//ִ��һ��undo ������ 1234  
	p->Undo();

	//ִ��һ��undo ������������ [empty]  
	p->Undo();

	//ִ��ʧ���Ѿ�undo ����ԭʼ���  
	p->Undo();

	//ִ��һ��redo ������ 1234  
	p->Redo();
	//ִ��һ��redo ������ insert  
	p->Redo();
	//ִ��һ��redo ������ 567  
	p->Redo();

	//redo���м��������ַ��� insert again ���� 567  
	p->ExecuteCommand(new InputCommand("insert again"));

	//ִ��һ��undo ������567  
	p->Undo();

	//ִ��һ��redo ������ insert again  
	p->Redo();

	//ִ��һ��redo ������ xxx  
	p->Redo();

	//ִ��ʧ���Ѿ�redo ���������  
	p->Redo();
	delete p;
	return 0;
}