#pragma once
#include "ObjectStruct.h"
#include "AstNode.h"
#include  <limits.h>
enum OPER_CODE{
 OPER_PROGRAM_END=0 , 

 OPER_ADD_VAR_1_INT_LEFT  ,        // 1个int，1变量
 OPER_ADD_VAR_1_INT_RIGHT,       // 1个int，1变量
 OPER_ADD_VAR_1_DOUBLE_LEFT ,      // 1个double ，1变量
 OPER_ADD_VAR_1_DOUBLE_RIGHT ,       // 1个double ，1变量
 OPER_ADD_VAR_1_STRING_LEFT ,        // 1个string，1变量
 OPER_ADD_VAR_1_STRING_RIGHT ,       // 1个string，1变量
 OPER_ADD_EXPR_1_INT_LEFT ,     // 1个int，1个表达式
 OPER_ADD_EXPR_1_INT_RIGHT ,    // 1个int，1个表达式
 OPER_ADD_EXPR_1_DOUBLE_LEFT ,       // 1个double，1个表达式
 OPER_ADD_EXPR_1_DOUBLE_RIGHT ,      // 1个double，1个表达式
 OPER_ADD_EXPR_1_STRING_LEFT ,         // 1个string，1个表达式
 OPER_ADD_EXPR_1_STRING_RIGHT    ,        // 1个string，1个表达式
 OPER_ADD_EXPR_2  ,        // 2个表达式,节点顺序：    ( ...EXPR1的节点组) ==>堆栈前移指令的节点==》( ...EXPR2的节点组) ===》节点 EXPR_ADD_EXPR
 OPER_ADD_VAR_2   ,      // 2变量
 OPER_ADD_EXPR_VAR  ,        // 1个表达式+1个变量 
 OPER_ADD_VAR_EXPR ,         // 1个变量 +1个表达式


 OPER_CALL_LOCAL_PREPARE  ,   //准备调用本地函数 
 OPER_CALL_OUTER_PREPARE,     //准备调用外部函数 

 OPER_STACK_PUSH			, 	//递增堆栈
 OPER_STACK_POP			, //递增堆栈

 OPER_CALL_JUMP, 	//进入函数
 OPER_FUNC_RETURN_PREPARE, //准备从函数返回

 OPER_FUNC_RETURN     , //从函数返回
 OPER_LOAD_LOCAL_VAR_STACK, //加载本地变量到堆栈
 OPER_LOAD_OUTER_VAR_STACK , 	//加载外部变量到堆栈
 OPER_LOAD_STACK_LOCAL_VAR, 	//加载堆栈到本地变量
 OPER_LOAD_STACK_OUTER_VAR, 	//加载堆栈到外部变量
 OPER_LOAD_LOCAL_VAR_LOCAL_VAR  , 	//加载本地变量到本地变量
 OPER_LOAD_LOCAL_VAR_OUTER_VAR , 	//加载本地变量到外部变量
 OPER_LOAD_OUTER_VAR_LOCAL_VAR   , 	//加载外部变量到本地变量
 OPER_LOAD_OUTER_VAR_OUTER_VAR , 	//加载外部变量到外部变量

 OPER_GET_LOCAL_OBJECT_POINT_2_STACK ,    //加载本地变量对象指针到堆栈
 OPER_GET_OUTER_OBJECT_POINT_2_STACK,   //加载外部变量对象指针到堆栈
 OPER_SET_LOCAL_OBJECT_POINT_FROM_STACK,   //加载本地变量对象指针到堆栈
 OPER_SET_OUTER_OBJECT_POINT_FROM_STACK ,   //加载对象指针到堆栈
 OPER_GET_OBJECT_POINT_POINT_2_STACK  ,

 OPER_IF_VALUE_JUMP,
 OPER_IF_STACK_JUMP,
 OPER_IF_VAR_JUMP,

 OPER_JUMP,

 OPER_NEW_FUNC,//准备进入构造函数
 OPER_NEW_FUNC_BACK,  //从构造函数返回

 


};

struct ExecEnv g_globalEnv;
struct ExecEnv * envStackHead; //执行栈
struct ExecEnv * env; //当前环境
procNode(struct ComputeNode * node, struct ComputeNode ** nextNode, struct ExecEnv **currentEnv);


//struct GlobalObject globalObject;


struct  FunctionStruct functionObject;
struct NormalObjectStruct stringObject;
struct NormalObjectStruct numberObject;
struct ObjectStruct objectObject;

//struct SymbolTableElement * SymbolTable;//全局符号表，所有出现过的符号
  

//struct GlobalEnvObj * globalObjList;


struct VmObject
{
	struct GlobalEnvObj 	* globalObj;
	struct EnvSymbol * envSymbolList; //除全局符号，其他环境都链入到该链表中
	//struct SymbolTableElement * SymbolTable;//全局符号表，所有出现过的符号
	void * excNodeList;
};
/*
struct StackNode
{
char flag;		//

union {
int valueInt;
double valueDouble;
} value;



};
*/