#include<iostream>
#include <string>
#include<vector>
#include <stack>

using namespace std;

//先定义一个命令接口

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
		//最初的命令数据  
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
			//无法后退撤销没有数据  
			cout<<"undo failed.\n"<<endl;
			return;
		}

		cout<<"undo:\n"<<endl;

		//当前命令  
		auto pCmd = mUndo.top();

		//保存当前命令  
		mRedo.push(pCmd);

		//弹出  
		mUndo.pop();

		//还原到上个命令  
		pCmd = mUndo.top();

		pCmd->Execute();
	}

	void Redo()
	{
		if (mRedo.empty())
		{
			//无法前进重做没有数据  
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
//模拟输入字符串,然后对输入的字符串进行undo redo操作  
int main()
{
	//默认没有输入字符串可以是空，这里为了演示赋值一个特殊的字符串  
	Commander *p = new Commander(new InputCommand("[empty]"));

	//输入1234  
	p->ExecuteCommand(new InputCommand("1234"));
	//输入567  
	p->ExecuteCommand(new InputCommand("567"));
	//输入xxx  
	p->ExecuteCommand(new InputCommand("xxx"));

	//执行一次undo 撤销到 567  
	p->Undo();
	//执行一次undo 撤销到 1234  
	p->Undo();

	//undo后中间输入新字符串 insert 覆盖 1234  
	p->ExecuteCommand(new InputCommand("insert"));

	//执行一次undo 撤销到 1234  
	p->Undo();

	//执行一次undo 撤销到最初情况 [empty]  
	p->Undo();

	//执行失败已经undo 到最原始情况  
	p->Undo();

	//执行一次redo 重做到 1234  
	p->Redo();
	//执行一次redo 重做到 insert  
	p->Redo();
	//执行一次redo 重做到 567  
	p->Redo();

	//redo后中间输入新字符串 insert again 覆盖 567  
	p->ExecuteCommand(new InputCommand("insert again"));

	//执行一次undo 撤销到567  
	p->Undo();

	//执行一次redo 重做到 insert again  
	p->Redo();

	//执行一次redo 重做到 xxx  
	p->Redo();

	//执行失败已经redo 到最新情况  
	p->Redo();
	delete p;
	return 0;
}