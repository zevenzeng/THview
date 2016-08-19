#pragma once

#include "Map.h"
#include "List.h"
#include "ExecEnv.h"
#include "ProtoTypeStruct.h"
#include "Parser.h"

#include <math.h>

enum ObjectType
{
 OBJECT_STRUCT_TYPE_BASE ,

 OBJECT_STRUCT_TYPE_STRING,
 OBJECT_STRUCT_TYPE_NUMBER_INT,
 OBJECT_STRUCT_TYPE_NUMBER_DOUBLE,
 OBJECT_STRUCT_TYPE_BOOLEAN,
 OBJECT_STRUCT_TYPE_ARRAY,
 OBJECT_STRUCT_TYPE_OBJECT,

 OBJECT_STRUCT_TYPE_NULL,



 OBJECT_STRUCT_TYPE_FUNCTION ,
	//#define OBJECT_STRUCT_TYPE_SELF_DEFINE 5      //自定义对象


 OBJECT_STRUCT_TYPE_FUNC_ENV,

 //OBJECT_STRUCT_TYPE_FUNC_POINT ,
 OBJECT_STRUCT_TYPE_OUTER_POINT ,    //用于模板中，要在环境初始化的时候进行计算
 OBJECT_STRUCT_TYPE_POINT ,   //指向OBJECT



 NUMBER_MAX_VALUE ,//  1.79E+308,
 NUMBER_MIX_VALUE,//	 5e-324	,


 OBJECT_FIELD_CAN_DELETE ,
 OBJECT_FIELD_DELETE  
};


struct BaseObjectStruct
{
	int  type;   //对象类型
	struct ProtoTypeStruct *   __proto__;


};


struct ObjectField
{
	char type;
	struct BaseObjectStruct * fieldValue;
	struct StringProperty * name;
	struct ObjectField * next;

};

struct ObjectStruct
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct
	struct ObjectField * fieldList;
	int count;//引用计数

	//struct ProtoTypeStruct *   __proto__;

	//struct List   objList;   //对象链表
	//struct Map objMap;
	//struct List     functionList;
//	struct Map 	functionMap;
};

struct ArrayStruct
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct

};

/*

struct StringObjectStruct
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct
	char *  value;
	int len;
};*/

struct OuterVariantIndex {
	struct ExecEnv * envTemplate;
	unsigned int index;
};
struct OuterVariantPoint {
	struct ExecEnv * env ;
	struct BaseObjectStruct * point;    
};
  
struct NormalObjectStruct
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct
 	union {
		int valueInt;
		double valueDouble;
		struct StringProperty stringProperty;
		struct ObjectStruct * objPoint;
		struct BaseObjectStruct * point;   //OBJECT_STRUCT_TYPE_OBJECT

		struct FunctionEnvBind funcEnv;
		struct OuterVariantIndex outerVariantIndex;
		struct OuterVariantPoint outerVariantPoint;

	} value;

};
struct Local
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct
	struct FunctionStruct * func;
	struct ExecEnv * env;

};
//函数和运行环境的绑定
struct FunctionEnvBind
{
	struct BaseObjectStruct baseObjectStruct;  //继承ObjStruct
	struct FunctionStruct * func;
	struct ExecEnv * env;   //当前环境
	
};


 

struct  FunctionStruct
{
	struct ObjectStruct baseObjectStruct;  //继承ObjStruct
	struct ProtoTypeStruct * prototype;
	struct StringProperty name;

	struct List paramList;						// 参数列表
	struct Map  paramMap;
	struct ObjectStruct renturnType;	//  返回类型
	char  size;  //参数个数， 255为可变个数
	struct FunctionStruct * scope; //创建者         作用域链
	struct ExecEnv * envTemplate;    //执行环境模板
	//struct List envList;
	struct AstNode *  AstTreeNode; //语法树节点
};





struct ExecEnv
{
	struct NormalObjectStruct * variantArray;//变量数组  this指针(默认指向全局对象，可以通过)、param,localVariant ,localFunc, globalProperty，outerVariant
	unsigned int variantArrayLen;
	unsigned int localLen;

	struct NormalObjectStruct *  localVariant;
	//struct NormalObjectStruct * localFunc;
	struct NormalObjectStruct * outerVariant;
	//struct NormalObjectStruct * globalProperty;  //全局属性 
	//struct NormalObjectStruct * outerFunc;
	struct ExecEnv * envTemplate;    //执行环境模板

	//struct List  paramValue; //实参列表值
	//struct List  localVariant; //内部变量
	//struct List  outerVariant; //外部NumberStruct变量
	//struct FunctionStruct * functionObj;//函数对象
	struct FunctionStruct * callFunctionObj;// 调用函数对象
	struct FunctionStruct * parentFunctionObj;// 上层函数对象
	struct FunctionStruct * func;// 对应函数对象

	struct ExecEnv * scope; //作用域链，指向上一个执行环境

	struct ExecEnv * prev;// 调用栈上一个环境
	struct ExecEnv * next;// 调用栈下一个环境
	struct NormalObjectStruct  stack[2];  //执行结果栈
	struct NormalObjectStruct * returnStack;  //返回结果栈
	struct ComputeNode * bootNode;
	struct ComputeNode *  returnNode; //返回树节点

//	struct BaseObjectStruct * thisPoint;   //this 指针
	unsigned int level;
	int count;//引用计数
};
 

struct GlobalEnvObj
{
	struct ObjectStruct obj;
	struct ExecEnv envTmp;
	struct EnvSymbol envSymbol;

};
struct NormalObjectStruct undefinedObject;
struct NormalObjectStruct nullObject;
struct NormalObjectStruct normalValueFunction;
struct ObjectStruct Object;

struct NormalObjectStruct * newStringObjectStruct();
struct BaseObjectStruct * addProperty(struct ObjectStruct *obj, struct StringProperty *	stringProperty);
struct ObjectStruct * newObject();



//构造函数

struct  FunctionStruct constructFunction;
struct  FunctionStruct constructArray;
struct  FunctionStruct constructNumber;
struct  FunctionStruct constructObject;
