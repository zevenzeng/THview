#pragma once
#include "ObjectStruct.h"
#include "AstNode.h"
#include  <limits.h>
enum OPER_CODE{
 OPER_PROGRAM_END=0 , 

 OPER_ADD_VAR_1_INT_LEFT  ,        // 1��int��1����
 OPER_ADD_VAR_1_INT_RIGHT,       // 1��int��1����
 OPER_ADD_VAR_1_DOUBLE_LEFT ,      // 1��double ��1����
 OPER_ADD_VAR_1_DOUBLE_RIGHT ,       // 1��double ��1����
 OPER_ADD_VAR_1_STRING_LEFT ,        // 1��string��1����
 OPER_ADD_VAR_1_STRING_RIGHT ,       // 1��string��1����
 OPER_ADD_EXPR_1_INT_LEFT ,     // 1��int��1�����ʽ
 OPER_ADD_EXPR_1_INT_RIGHT ,    // 1��int��1�����ʽ
 OPER_ADD_EXPR_1_DOUBLE_LEFT ,       // 1��double��1�����ʽ
 OPER_ADD_EXPR_1_DOUBLE_RIGHT ,      // 1��double��1�����ʽ
 OPER_ADD_EXPR_1_STRING_LEFT ,         // 1��string��1�����ʽ
 OPER_ADD_EXPR_1_STRING_RIGHT    ,        // 1��string��1�����ʽ
 OPER_ADD_EXPR_2  ,        // 2�����ʽ,�ڵ�˳��    ( ...EXPR1�Ľڵ���) ==>��ջǰ��ָ��Ľڵ�==��( ...EXPR2�Ľڵ���) ===���ڵ� EXPR_ADD_EXPR
 OPER_ADD_VAR_2   ,      // 2����
 OPER_ADD_EXPR_VAR  ,        // 1�����ʽ+1������ 
 OPER_ADD_VAR_EXPR ,         // 1������ +1�����ʽ


 OPER_CALL_LOCAL_PREPARE  ,   //׼�����ñ��غ��� 
 OPER_CALL_OUTER_PREPARE,     //׼�������ⲿ���� 

 OPER_STACK_PUSH			, 	//������ջ
 OPER_STACK_POP			, //������ջ

 OPER_CALL_JUMP, 	//���뺯��
 OPER_FUNC_RETURN_PREPARE, //׼���Ӻ�������

 OPER_FUNC_RETURN     , //�Ӻ�������
 OPER_LOAD_LOCAL_VAR_STACK, //���ر��ر�������ջ
 OPER_LOAD_OUTER_VAR_STACK , 	//�����ⲿ��������ջ
 OPER_LOAD_STACK_LOCAL_VAR, 	//���ض�ջ�����ر���
 OPER_LOAD_STACK_OUTER_VAR, 	//���ض�ջ���ⲿ����
 OPER_LOAD_LOCAL_VAR_LOCAL_VAR  , 	//���ر��ر��������ر���
 OPER_LOAD_LOCAL_VAR_OUTER_VAR , 	//���ر��ر������ⲿ����
 OPER_LOAD_OUTER_VAR_LOCAL_VAR   , 	//�����ⲿ���������ر���
 OPER_LOAD_OUTER_VAR_OUTER_VAR , 	//�����ⲿ�������ⲿ����

 OPER_GET_LOCAL_OBJECT_POINT_2_STACK ,    //���ر��ر�������ָ�뵽��ջ
 OPER_GET_OUTER_OBJECT_POINT_2_STACK,   //�����ⲿ��������ָ�뵽��ջ
 OPER_SET_LOCAL_OBJECT_POINT_FROM_STACK,   //���ر��ر�������ָ�뵽��ջ
 OPER_SET_OUTER_OBJECT_POINT_FROM_STACK ,   //���ض���ָ�뵽��ջ
 OPER_GET_OBJECT_POINT_POINT_2_STACK  ,

 OPER_IF_VALUE_JUMP,
 OPER_IF_STACK_JUMP,
 OPER_IF_VAR_JUMP,

 OPER_JUMP,

 OPER_NEW_FUNC,//׼�����빹�캯��
 OPER_NEW_FUNC_BACK,  //�ӹ��캯������

 


};

struct ExecEnv g_globalEnv;
struct ExecEnv * envStackHead; //ִ��ջ
struct ExecEnv * env; //��ǰ����
procNode(struct ComputeNode * node, struct ComputeNode ** nextNode, struct ExecEnv **currentEnv);


//struct GlobalObject globalObject;


struct  FunctionStruct functionObject;
struct NormalObjectStruct stringObject;
struct NormalObjectStruct numberObject;
struct ObjectStruct objectObject;

//struct SymbolTableElement * SymbolTable;//ȫ�ַ��ű����г��ֹ��ķ���
  

//struct GlobalEnvObj * globalObjList;


struct VmObject
{
	struct GlobalEnvObj 	* globalObj;
	struct EnvSymbol * envSymbolList; //��ȫ�ַ��ţ��������������뵽��������
	//struct SymbolTableElement * SymbolTable;//ȫ�ַ��ű����г��ֹ��ķ���
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