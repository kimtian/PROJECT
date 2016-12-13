
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


// Component抽象基类，为组合中的对象声明接口,声明了类共有接口的缺省行为(如这里的Add,Remove,GetChild函数),

class Componet
{
public:
	Componet()
	{
	}
	virtual ~Componet()
	{
	}
	// 虚函数,提供接口

	virtual void Operation() = 0;
	virtual void Add(Componet *PChild)

	{
	}
	virtual void Remove(Componet *PChild)

	{
	}
	virtual Componet* GetChild(int index)
	{
		return NULL;
	}

};

//叶子节点
class Leaf :public Componet
{
public:
	Leaf()
	{
	}
	virtual ~Leaf()
	{}

	virtual void Operation()
	{
		cout << "Operation by Leaf" << endl;
	}
};

//composite

class Composite :public Componet
{
public:
	Composite()
	{
	}

	virtual ~Composite()
	{
		list<Componet*>::iterator iter1, temp;
		for (iter1 = m_ListOfComponet.begin(); iter1 != m_ListOfComponet.end();)
		{
			temp = iter1;
			iter1++;
			delete(*temp);
		}

	}

	virtual void Operation()
	{
		cout << "Operation by Composite" << endl;
		list<Componet*>::iterator iter1;
		for (iter1 = m_ListOfComponet.begin(); iter1 != m_ListOfComponet.end(); iter1++)
		{
			(*iter1)->Operation();
		}

	}
	virtual void Add(Componet *PChild)
	{
		m_ListOfComponet.push_back(PChild);
	}
	virtual void Remove(Componet *pChild)
	{
		list<Componet*>::iterator iter;
		iter = find(m_ListOfComponet.begin(), m_ListOfComponet.end(), pChild);
		if (m_ListOfComponet.end() != iter)
		{
			m_ListOfComponet.erase(iter);
		}
	}

	virtual Componet* GetChild(int index)
	{
		if (index <= 0 || index> m_ListOfComponet.size())
			return NULL;

		list<Componet*>::iterator iter1, iter2;
		int i;
		for (i = 1, iter1 = m_ListOfComponet.begin(), iter2 = m_ListOfComponet.end(); iter1 != iter2; ++iter1, ++i)
		{
			if (i == index)
				break;
		}
		return *iter1;
	}

private:
	list<Componet*> m_ListOfComponet;

};
int main ()
{
	Leaf *pLeaf1 = new Leaf();
	Leaf *pLeaf2 = new Leaf();

	Composite* pComposite = new Composite();
	pComposite->Add(pLeaf1);
	pComposite->Add(pLeaf2);
	pComposite->Operation();
	pComposite->GetChild(2)->Operation();

	delete pComposite;

	return 0;
}