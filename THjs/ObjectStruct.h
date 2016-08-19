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
	//#define OBJECT_STRUCT_TYPE_SELF_DEFINE 5      //�Զ������


 OBJECT_STRUCT_TYPE_FUNC_ENV,

 //OBJECT_STRUCT_TYPE_FUNC_POINT ,
 OBJECT_STRUCT_TYPE_OUTER_POINT ,    //����ģ���У�Ҫ�ڻ�����ʼ����ʱ����м���
 OBJECT_STRUCT_TYPE_POINT ,   //ָ��OBJECT



 NUMBER_MAX_VALUE ,//  1.79E+308,
 NUMBER_MIX_VALUE,//	 5e-324	,


 OBJECT_FIELD_CAN_DELETE ,
 OBJECT_FIELD_DELETE  
};


struct BaseObjectStruct
{
	int  type;   //��������
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
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct
	struct ObjectField * fieldList;
	int count;//���ü���

	//struct ProtoTypeStruct *   __proto__;

	//struct List   objList;   //��������
	//struct Map objMap;
	//struct List     functionList;
//	struct Map 	functionMap;
};

struct ArrayStruct
{
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct

};

/*

struct StringObjectStruct
{
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct
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
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct
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
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct
	struct FunctionStruct * func;
	struct ExecEnv * env;

};
//���������л����İ�
struct FunctionEnvBind
{
	struct BaseObjectStruct baseObjectStruct;  //�̳�ObjStruct
	struct FunctionStruct * func;
	struct ExecEnv * env;   //��ǰ����
	
};


 

struct  FunctionStruct
{
	struct ObjectStruct baseObjectStruct;  //�̳�ObjStruct
	struct ProtoTypeStruct * prototype;
	struct StringProperty name;

	struct List paramList;						// �����б�
	struct Map  paramMap;
	struct ObjectStruct renturnType;	//  ��������
	char  size;  //���������� 255Ϊ�ɱ����
	struct FunctionStruct * scope; //������         ��������
	struct ExecEnv * envTemplate;    //ִ�л���ģ��
	//struct List envList;
	struct AstNode *  AstTreeNode; //�﷨���ڵ�
};





struct ExecEnv
{
	struct NormalObjectStruct * variantArray;//��������  thisָ��(Ĭ��ָ��ȫ�ֶ��󣬿���ͨ��)��param,localVariant ,localFunc, globalProperty��outerVariant
	unsigned int variantArrayLen;
	unsigned int localLen;

	struct NormalObjectStruct *  localVariant;
	//struct NormalObjectStruct * localFunc;
	struct NormalObjectStruct * outerVariant;
	//struct NormalObjectStruct * globalProperty;  //ȫ������ 
	//struct NormalObjectStruct * outerFunc;
	struct ExecEnv * envTemplate;    //ִ�л���ģ��

	//struct List  paramValue; //ʵ���б�ֵ
	//struct List  localVariant; //�ڲ�����
	//struct List  outerVariant; //�ⲿNumberStruct����
	//struct FunctionStruct * functionObj;//��������
	struct FunctionStruct * callFunctionObj;// ���ú�������
	struct FunctionStruct * parentFunctionObj;// �ϲ㺯������
	struct FunctionStruct * func;// ��Ӧ��������

	struct ExecEnv * scope; //����������ָ����һ��ִ�л���

	struct ExecEnv * prev;// ����ջ��һ������
	struct ExecEnv * next;// ����ջ��һ������
	struct NormalObjectStruct  stack[2];  //ִ�н��ջ
	struct NormalObjectStruct * returnStack;  //���ؽ��ջ
	struct ComputeNode * bootNode;
	struct ComputeNode *  returnNode; //�������ڵ�

//	struct BaseObjectStruct * thisPoint;   //this ָ��
	unsigned int level;
	int count;//���ü���
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



//���캯��

struct  FunctionStruct constructFunction;
struct  FunctionStruct constructArray;
struct  FunctionStruct constructNumber;
struct  FunctionStruct constructObject;
