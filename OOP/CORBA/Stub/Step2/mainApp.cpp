//本例子用于理解stub与skeleton的作用
//例子中的“ORB”只起到方法调用媒介作用
//未进行空间释放
//未使用流
//更未使用套接字模拟进程外或异地传输.
//未把Server与接口真正实现（单纯实现）分开

#include <iostream.h>
#include <stdio.h>
#include <string.h>

class Interface
{
public:
	virtual int add(int,int) = 0;
	virtual int f1(int ) = 0;
	virtual void f2(float) = 0;
};

struct Type_Value
{
public:
	char parameterType[50];
	char parameterValue[50];
};

struct Func
{
	char returnType[50];
	char functionName[50];
	int numOfParameters;
	Type_Value* typeValues[10];

};

class BaseSkeleton
{
public:
	virtual char* invoke(Func* pFunc) = 0;
};

class PartOfORB 
//可用单件模式设计成只产生唯一实例
{
public:
	PartOfORB( )
	{
		pFunc = 0;
		pReturnValue = 0;
		pBOA = 0;
	}
	void initFunc(Func* pFunction)
	{
		pFunc = pFunction;
	}
	void initSkeleton(BaseSkeleton* pBS)
	{
		pBOA = pBS;
	}
	void invokeFunction( )
	{
		if ((pFunc)&&(pBOA))
			pReturnValue = pBOA->invoke(pFunc);
		else
			pReturnValue = 0;
	}
	char* getReturnValue( )
	{
		return pReturnValue;
	}
			
private:
	Func* pFunc;
	char* pReturnValue;
	BaseSkeleton* pBOA;
};

class Stub : public Interface
{
public:
	Stub(PartOfORB* anORB)
	{
		pORB = anORB;
	}
	int add(int i1,int i2)
	{
		Func* pF = new Func;
		strcpy(pF->returnType,"int");
		pF->numOfParameters = 2;
		strcpy(pF->functionName,"add"); 
		Type_Value* pTV1 = new Type_Value;
		strcpy(pTV1->parameterType,"int");
		sprintf(pTV1->parameterValue,"%d",i1);
		pF->typeValues[0] = pTV1;

		Type_Value* pTV2 = new Type_Value;
		strcpy(pTV2->parameterType,"int");
		sprintf(pTV2->parameterValue,"%d",i2);
		pF->typeValues[1] = pTV2;
		pORB->initFunc(pF);
		pORB->invokeFunction( );
		char* pRet = pORB->getReturnValue( );
		int theRet;
		sscanf(pRet,"%d",&theRet);
		return theRet;
	}
	int f1(int anInt )
	{
		Func* pF = new Func;
		strcpy(pF->returnType,"int");
		pF->numOfParameters = 1;
		strcpy(pF->functionName,"f1"); 
		Type_Value* pTV = new Type_Value;
		strcpy(pTV->parameterType,"int");
		sprintf(pTV->parameterValue,"%d",anInt);
		pF->typeValues[0] = pTV;
		pORB->initFunc(pF);
		pORB->invokeFunction( );
		char* pRet = pORB->getReturnValue( );
		int theRet;
		sscanf(pRet,"%d",&theRet);
		return theRet;

	}
	void f2(float aFloat)
	{
		//类似
	}
private:
	PartOfORB* pORB;
};
//----------------------------------------------

class Skeleton : public BaseSkeleton
{
public:
	Skeleton(Interface* pS)
	{
		theServer = pS;
	}
	virtual char* invoke(Func* pFunc)
	{
		char* pName = pFunc->functionName;
		if (strcmp(pName,"add")==0)
		{
			Type_Value* pTV1 = pFunc->typeValues[0];
			int para1;
			sscanf(pTV1->parameterValue,"%d",&para1);
			Type_Value* pTV2 = pFunc->typeValues[1];
			int para2;
			sscanf(pTV2->parameterValue,"%d",&para2);

			int returnValue = theServer->add(para1,para2);
			char* returnString = new char[50];
			sprintf(returnString, "%d", returnValue);
			return returnString;
		}
		else if (strcmp(pName,"f1")==0)
		{
			Type_Value* pTV = pFunc->typeValues[0];
			int para1;
			sscanf(pTV->parameterValue,"%d",&para1);
			int returnValue = theServer->f1(para1);
			char* returnString = new char[50];
			sprintf(returnString, "%d", returnValue);
			return returnString;
		}
		else if (strcmp(pName,"f2")==0)
		{
			//.....
			char* returnString = new char[50];
			sprintf(returnString,"");
			return returnString;
		}
		else
			return 0;
	}

private:
	Interface* theServer;
};

class Server : public Interface
//这个类的名字可以起成InterfaceImp;
//另用一个类Server完成InterfaceImp的构建.
//这里只是简单地把两者合并在一起.
{
public:
	Server(PartOfORB* pORB)
	{
		BaseSkeleton* pSkeleton = new Skeleton(this);
		pORB->initSkeleton(pSkeleton); 		
	}

	int add(int anInt1,int anInt2)
	{
		return (anInt1+anInt2);
	}
	int f1(int anInt )
	{ 
		cout << "Service named f1 from Server " << endl;
		return (anInt+10000);
	}
	void f2(float aFloat )
	{ 
		cout << "Service named f2 from Server " << endl;
		cout << "The float number is: " << aFloat << endl;
	}
private:
//	PartOfORB* pORB;

};
//----------------------------------------------


class Client
{
public:
	Client(PartOfORB* pORB)
	{
		theORB = pORB;
		pStub = new Stub(theORB);
	}
	void g( )
	{
		int i = pStub->add(10,20);
		cout << i << endl;
	}
	void h( )
	{
		//Step1( );
		//Step2( );
		int theInt = pStub->f1(100 );
		//OtherSteps( );
	}
private:
	PartOfORB* theORB;
	Stub* pStub;
};


int main( )
{
	PartOfORB* orb = new PartOfORB;
	Server* server = new Server(orb);
	
	cout <<"ORB 和 Server 已经启动，按任意键继续..." <<endl;
	getchar( );

	Client* client = new Client(orb);
	client->g( ); 
	cout << endl << endl;
	client->h( );
	cout << endl;

	cout << "按任意键返回..." <<endl;
	getchar( );
	return 0;
}