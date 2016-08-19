#pragma once
#include "ObjectStruct.h"

struct StringProperty { void * value; int len; };
union IndexValue {
	struct NormalObjectStruct * field;  //ȫ�ֶ�������Խ�����Ϊ UNDEFINEDֵ
	unsigned  int index;
};
struct SymbolString 
{
	struct StringProperty stringProperty;
	struct SymbolStringCacheNode ** cache ;//ÿ���ַ���һ������
 };
struct SymbolStringCacheNode
{
	struct ExecEnv  * env;
	union IndexValue indexValue;
	struct SymbolStringCacheNode * next;

};


 struct SymbolTableElement
{	

 	struct SymbolString symbolString;
	union IndexValue indexValue;
	struct SymbolTableElement * next;
	unsigned int type;
};

struct SymbolTableFuncElement
{
	struct SymbolTableElement symbol;
	struct  FunctionStruct *func;

};


struct EnvSymbol    //�������ӳ�һ������
{
	struct ExecEnv * envTmp;
	struct EnvSymbol * scope;//�ϲ�
	struct ExecEnv * child;//�²�
	struct ExecEnv * brother;
	struct ExecEnv * next;//������
	struct SymbolTableElement * localVaraintSymbol;
	struct SymbolTableElement * localVaraintSymbolTail;
	unsigned int thisIndex;
	unsigned int localVaraintSymbolSize;// 

	struct SymbolTableElement * outerSymbol; //ȫ�ֻ����У�ָ������
	struct SymbolTableElement * outerSymbolTail; //ȫ�ֻ����У�ָ������
	unsigned int outerSymbolSize;

	//struct SymbolTableElement * thisSymbol;

};

//struct EnvSymbol    globalEnvObj//�������ӳ�һ������
