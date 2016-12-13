#include <iostream>  
#include <string>  
#include <vector>  
#include <list>  
#include <algorithm> 
using namespace std;
//模拟留言场景

//观察者，为那些在目标发生改变时需获得通知的对象定义一个更新接口
class Observer
{

public:
	Observer(){}
	virtual ~Observer(){}
	//更新函数
	virtual void Update(){};
};


//目标，知道它的观察者，提供注册和删除观察者对象的接口

class Subject
{
public:
	Subject(){}
	virtual ~Subject(){}
	//提供接口
	void ADD(Observer* observer)
	{
		vec_observer.push_back(observer);
	}

	void DEL(Observer* observer)
	{
		vector<Observer*>::iterator iter;
		for (iter = vec_observer.begin(); iter != vec_observer.end(); ++iter)
		{
			if ((*iter) == observer)
				vec_observer.erase(iter);
		}
	}
	//通知更新
	void Notify()
	{
		vector<Observer*>::iterator iter;
		for (iter = vec_observer.begin(); iter != vec_observer.end(); ++iter)
		{
			(*iter)->Update();
		}
	}

	virtual void SetStatus(string sts){}//重置状态
	virtual string GetStatus() { return m_status; };//获得当前状态

private:
	vector<Observer*> vec_observer;//观察者数组
protected:
	string m_status;
};


//具体目标，存储对象状态，状态改变时，向各个观察者发出通知
class ConcreteSubject :public Subject
{
public:
	ConcreteSubject(string name) :m_Subject_name(name){}
	~ConcreteSubject(){}


	void SetStatus(string sts)
	{
		m_status = "收到更新！ \n" + m_Subject_name + sts;
	}

	string GetStatus()
	{
		return m_status;
	}

private:
	string m_Subject_name;
};


//具体观察者，维护一个指向ConcreteSubject对象的引用，存储有关状态，实现更新接口update，使自身状态与目标的状态保持一致
class ConcreteObserver :public Observer
{
private:
	string m_observer_name;
	Subject *m_Subject;
public:
	ConcreteObserver(string name, Subject* blog) :m_observer_name(name), m_Subject(blog){}
	~ConcreteObserver(){}

	void Update()
	{
		string status = m_Subject->GetStatus();
		cout << m_observer_name << ":" << status << endl;
	}
};

int main()//模拟场景：A（具体的目标）重置状态，通知更新
{
	Subject *message = new ConcreteSubject("A");
	Observer *ob1 = new ConcreteObserver("Observer1", message);
	Observer *ob2 = new ConcreteObserver("Observer2", message);
	Observer*ob3 = new ConcreteObserver("Observer3", message);
	message->ADD(ob1);
	message->ADD(ob2);
	message->ADD(ob3);
	message->SetStatus(" 发布了新信息!");
	message->Notify();

	delete message;
	delete ob1;
	delete ob2;
	delete ob3;
	system("pause");
	return 0;
}
