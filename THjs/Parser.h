#pragma once
#include "ObjectStruct.h"

struct StringProperty { void * value; int len; };
union IndexValue {
	struct NormalObjectStruct * field;  //全局对象的属性将设置为 UNDEFINED值
	unsigned  int index;
};
struct SymbolString 
{
	struct StringProperty stringProperty;
	struct SymbolStringCacheNode ** cache ;//每个字符串一个缓存
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


struct EnvSymbol    //将会链接成一条链表
{
	struct ExecEnv * envTmp;
	struct EnvSymbol * scope;//上层
	struct ExecEnv * child;//下层
	struct ExecEnv * brother;
	struct ExecEnv * next;//解析链
	struct SymbolTableElement * localVaraintSymbol;
	struct SymbolTableElement * localVaraintSymbolTail;
	unsigned int thisIndex;
	unsigned int localVaraintSymbolSize;// 

	struct SymbolTableElement * outerSymbol; //全局环境中，指向属性
	struct SymbolTableElement * outerSymbolTail; //全局环境中，指向属性
	unsigned int outerSymbolSize;

	//struct SymbolTableElement * thisSymbol;

};

//struct EnvSymbol    globalEnvObj//将会链接成一条链表
