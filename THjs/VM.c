#include "VM.h"
   
#include <stdio.h>


#define CONDITION_NOT_STRING_INT_DOUBLE(x)  (x== OBJECT_STRUCT_TYPE_NUMBER_NAN || \
x == OBJECT_STRUCT_TYPE_NUMBER_NEGATIVE_INFINITY ||\
x == OBJECT_STRUCT_TYPE_NUMBER_POSITIVE_INFINITY ||\
x == OBJECT_STRUCT_TYPE_UNDEFINED ||\
x == OBJECT_STRUCT_TYPE_NULL )

#define CONDITION_INFINITY(x)  ( x == OBJECT_STRUCT_TYPE_NUMBER_NEGATIVE_INFINITY ||\
x == OBJECT_STRUCT_TYPE_NUMBER_POSITIVE_INFINITY )

#define CONDITION_NAN_UNDEFINED_NULL(x)  (x== OBJECT_STRUCT_TYPE_NUMBER_NAN || \
  x == OBJECT_STRUCT_TYPE_UNDEFINED ||\
x == OBJECT_STRUCT_TYPE_NULL )

inline stringAdd(struct BaseObjectStruct * l, struct BaseObjectStruct * r,struct  NormalObjectStruct * stack)
{

}

inline stringAddInt(int l, struct BaseObjectStruct * r, struct  NormalObjectStruct * stack)
{
	struct NormalObjectStruct *  result=newStringObjectStruct();
	memset(result, 0x00, sizeof(struct NormalObjectStruct));
	int number = 12345;
	char string[32];
	itoa(number, string, 10);
}
 

inline   char * myItoa(int n,char * result)
{
	int power = 0, j = 0;
	int i;
// 	result = malloc(10);
//	memset(result, 0x00, 10);
	char *p = result;
	if (n < 0)
	{
		j = -n;
		*p = '-';
		p++;
	}
	else if (n == 0)
	{
		*p = '0';
		p++;
		 
		return p;
	}
	else
	{
		j = n;
	}
 
	for (power = 1; j > 10; j /= 10)		power *= 10;

	for (; power > 0; power /= 10)
	{
		*p = '0' + j / power;
		p++;
		j %= power;
	}
	*p = 0x00;
	return p;
}

void initOneVM(struct VmObject * vmObj)
{
	initGlobalEnvTmp(vmObj->globalObj);
	
	struct EnvSymbol *p = vmObj->envSymbolList;
	while(p!=NULL)
	{ 
		initEnvTmp(vmObj->envSymbolList, vmObj->globalObj);
	}
	
}

void singleCoreLinkCPU(struct VmObject * vmObj)
{
	struct AstNode * node = vmObj->excNodeList;
	struct ExecEnv *currentEnv;
	struct ComputeNode * nextNode;
	currentEnv = &(vmObj->globalObj->envTmp);
//	struct AstNode * node = ;
	while (node != NULL)
	{
		nextNode = node->next;
		procNode(node->ComputeNode,&nextNode, &currentEnv);
		node = nextNode;

	}
	return;
}


 
    procNode(struct ComputeNode * node, struct ComputeNode ** nextNode, struct ExecEnv **currentEnv)
{
//	struct AstNode *node = bootNode;
	struct ExecEnv *env = *currentEnv;
	struct NormalObjectStruct *variant;
	struct NormalObjectStruct *variant2;
 
	char *tmpChar,*tmpChar2;
// 	struct  NormalObjectStruct * stack;

	int lenTmp = 0;
	struct StringProperty *stringProperty;
	struct ExecEnv *envTmp;
	struct FunctionStruct *func  ;
 	struct ExecEnv * newEnv  ;
	struct ObjectField * pField;
 	



	switch (node->nodeType)
	{
		case OPER_ADD_VAR_1_INT_LEFT:
			variant =(* currentEnv)->variantArray+ (node->operData.operData2IntInt.r);
				
		LABEL_COMPUTE_OPER_ADD_VAR_1_INT_LEFT:
			switch (variant->baseObjectStruct.type)
			{
			case OBJECT_STRUCT_TYPE_NUMBER_DOUBLE:	//int + double
				env->stackHead->value.valueDouble = node->operData.operData2IntInt.l + variant->value.valueDouble;
				break;
			case OBJECT_STRUCT_TYPE_NUMBER_INT:   //int + int
				env->stackHead->value.valueInt = node->operData.operData2IntInt.l + variant->value.valueInt;
				env->stackHead->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;
				break;
			case OBJECT_STRUCT_TYPE_STRING: //int +string
 				tmpChar = malloc(11 + variant->value.stringProperty.len);
				tmpChar = myItoa(node->operData.operData2IntInt.l, tmpChar);
				memcpy(tmpChar, (char *)variant->value.stringProperty.value, variant->value.stringProperty.len);
				*(tmpChar + variant->value.stringProperty.len) = 0x00;
				env->stackHead->value.valueInt = tmpChar;
				break;
			case OBJECT_STRUCT_TYPE_POINT: //int +外部变量
				variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);

				goto LABEL_COMPUTE_OPER_ADD_VAR_1_INT_LEFT;
				break;
			}
				
			break;

		case OPER_ADD_VAR_1_INT_RIGHT:
			//TODO
			break;


		case OPER_ADD_VAR_1_DOUBLE_LEFT:
			variant = env->variantArray + (node->operData.operData2DobuleInt.r);
		LABEL_COMPUTE_OPER_ADD_VAR_1_DOUBLE_LEFT:
			switch (variant->baseObjectStruct.type)
			{
			case OBJECT_STRUCT_TYPE_NUMBER_DOUBLE:	//double + double
				env->stackHead->value.valueDouble = node->operData.operData2DobuleInt.l + variant->value.valueDouble;
				break;
			case OBJECT_STRUCT_TYPE_NUMBER_INT:   //double + int
				env->stackHead->value.valueDouble = node->operData.operData2DobuleInt.l + variant->value.valueInt;
				break;
			case OBJECT_STRUCT_TYPE_STRING: //double +string
				env->stackHead->value.stringProperty.value = (void *)malloc(30 + variant->value.stringProperty.len);
				lenTmp = sprintf(env->stackHead->value.stringProperty.value, "%10.2lf", node->operData.operData2DobuleInt.l);
				memcpy((char *)(env->stackHead->value.stringProperty.value) + lenTmp, variant->value.stringProperty.value, variant->value.stringProperty.len);
				env->stackHead->value.stringProperty.len = variant->value.stringProperty.len + lenTmp;
				break;
			case OBJECT_STRUCT_TYPE_POINT: //int +外部变量
				variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);

				goto LABEL_COMPUTE_OPER_ADD_VAR_1_DOUBLE_LEFT;
				break;

			}
			break;
		case OPER_ADD_VAR_1_DOUBLE_RIGHT:
			//TODO
			break;


		case OPER_ADD_VAR_1_STRING_LEFT:
		 
			variant = env->variantArray + (node->operData.operData2IntInt.r);
		LABEL_COMPUTE_OPER_ADD_VAR_1_STRING_LEFT:
			
			switch (variant->baseObjectStruct.type)
			{
				case OBJECT_STRUCT_TYPE_NUMBER_DOUBLE: //string + double
					env->stackHead->value.stringProperty.value =(void *) malloc(30 + node->operData.operData2StringInt.l.len);
					memcpy((char *)(env->stackHead->value.stringProperty.value) ,node ->operData.operData2StringInt.l.value,
										node->operData.operData2StringInt.l.len);
					lenTmp=sprintf((char*)env->stackHead->value.stringProperty.value + node->operData.operData2StringInt.l.len
							, "%10.2lf", variant->value.valueDouble);
					env->stackHead->value.stringProperty.len = node->operData.operData2StringInt.l.len + lenTmp;

					break;
				case OBJECT_STRUCT_TYPE_NUMBER_INT: //string + int
					env->stackHead->value.stringProperty.value = (void *)malloc(11 + node->operData.operData2StringInt.l.len);
					memcpy((char *)(env->stackHead->value.stringProperty.value), node->operData.operData2StringInt.l.value,
						node->operData.operData2StringInt.l.len);

					tmpChar = (char*)env->stackHead->value.stringProperty.value + node->operData.operData2StringInt.l.len;
					tmpChar = myItoa(variant->value.valueInt, tmpChar);
					env->stackHead->value.stringProperty.len = tmpChar - (char*)env->stackHead->value.stringProperty.value;
					 

					break;
				case OBJECT_STRUCT_TYPE_STRING://string + string
					env->stackHead->value.stringProperty.len = variant->value.stringProperty.len + node->operData.operData2StringInt.l.len;
					env->stackHead->value.stringProperty.value = (void *)malloc(env->stackHead->value.stringProperty.len);
					memcpy((char *)(env->stackHead->value.stringProperty.value), node->operData.operData2StringInt.l.value,
						node->operData.operData2StringInt.l.len);
					memcpy((char *)(env->stackHead->value.stringProperty.value), variant->value.stringProperty.value,
						variant->value.stringProperty.len );
					break;
				case OBJECT_STRUCT_TYPE_POINT: //int +外部变量
					variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);

					goto LABEL_COMPUTE_OPER_ADD_VAR_1_STRING_LEFT;
					break;
			}

			break;
		case OPER_ADD_VAR_1_STRING_RIGHT:
			//TODO
			break;

		case OPER_ADD_EXPR_1_INT_LEFT:
			if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = node->operData.operDataInt.l + env->stackHead->value.valueDouble;
			}
			else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueInt = node->operData.operDataInt.l + env->stackHead->value.valueInt;

			}
 			break;
		case OPER_ADD_EXPR_1_INT_RIGHT:
			//TODO
			break;

		case OPER_ADD_EXPR_1_DOUBLE_LEFT:
			if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = node->operData.operDataDouble.l + env->stackHead->value.valueDouble;
			}
			else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueDouble = node->operData.operDataDouble.l + env->stackHead->value.valueInt;
 			}
			break;
		case OPER_ADD_EXPR_1_DOUBLE_RIGHT:
			//TODO
			break;

		case OPER_ADD_EXPR_1_STRING_LEFT:
			//TODO
			break;
		case OPER_ADD_EXPR_1_STRING_RIGHT:
			//TODO
			break;
		case OPER_ADD_EXPR_2:
			//stack--;
 			if ((env->stackHead - 1)->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
				{
					(env->stackHead - 1)->value.valueDouble += (env->stackHead->value.valueDouble);
					//stack->value.valueDouble += stack[1].value.valueDouble;
				}
				else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
				{
					(env->stackHead - 1)->value.valueDouble += (env->stackHead->value.valueInt);
					//stack->value.valueDouble += stack[1].value.valueInt;
				}
			}
			else if ((env->stackHead - 1)->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
				{
					(env->stackHead - 1)->value.valueDouble = (env->stackHead - 1)->value.valueInt + env->stackHead->value.valueDouble;

				}
				else  if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
				{
					(env->stackHead - 1)->value.valueInt += env->stackHead->value.valueInt;
					(env->stackHead - 1)->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;

				}
			}

			break;
		case OPER_ADD_VAR_2:  
			variant = env->variantArray + (node->operData.operData2IntInt.l);

			//variant = (struct NormalObjectStruct *)(node->operData.operData2IntInt.l);
			if(variant->baseObjectStruct.type ==OBJECT_STRUCT_TYPE_POINT)  //外部变量
			{
				variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			}
			variant2 = env->variantArray + (node->operData.operData2IntInt.r);
			if (variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_POINT)   //外部变量
			{
				variant2 = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			}



			env->stackHead->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_DOUBLE;

			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE &&variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = variant->value.valueDouble + variant2->value.valueDouble;

			}
			else if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE &&variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueDouble = variant->value.valueDouble + variant2->value.valueInt;
			}
			else if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT &&variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = variant->value.valueInt + variant2->value.valueDouble;
			}
			else if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT &&variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueInt = variant->value.valueInt + variant2->value.valueInt;
				env->stackHead->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;
			}

			 
			break;
		case OPER_ADD_EXPR_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_POINT)
			{
				variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			}

			if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE&&variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = variant->value.valueDouble + env->stackHead->value.valueDouble;
			}
			else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE	&&variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueDouble = variant->value.valueDouble + env->stackHead->value.valueInt;

			}
			else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT&&variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE)
			{
				env->stackHead->value.valueDouble = variant->value.valueInt + env->stackHead->value.valueDouble;
				env->stackHead->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_DOUBLE;

			}
			else if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT&&variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT)
			{
				env->stackHead->value.valueInt = variant->value.valueInt + env->stackHead->value.valueInt;
				env->stackHead->baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;

			}
			break;
		case OPER_ADD_VAR_EXPR:
			//TODO
			break;


		case OPER_CALL_LOCAL_PREPARE:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
 
			newEnv= constructEnv(variant,   env,env, &env->stackHead, node);
		 
			break;
		case OPER_CALL_OUTER_PREPARE:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
 			
			newEnv = constructEnv(variant->value.outerVariantPoint.point, variant->value.funcEnv.env,env, &env->stackHead, node);
 

			break;

		case OPER_CALL_JUMP:
			//env = env->next;//压入当前执行环境栈
			//stack = env->stack;
			//node = env->bootNode;
			*nextNode=env->bootNode;
			//return node;

			break;
		case OPER_FUNC_RETURN_PREPARE:
			//node = env->returnNode;

			env->stackHead = env->returnStack;
			//env->next = NULL;
			//return node;

			break;
		case OPER_FUNC_RETURN :
			*nextNode = env->returnNode;
			env = env->prev;
			env->stackHead = env->returnStack;

			break;

		case OPER_LOAD_LOCAL_VAR_STACK:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			 
			memcpy(env->stackHead, variant, sizeof(struct NormalObjectStruct));
				 
			break;
		case OPER_LOAD_OUTER_VAR_STACK:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			memcpy(env->stackHead, variant, sizeof(struct NormalObjectStruct));
			break;
		case OPER_LOAD_STACK_LOCAL_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			memcpy(variant, env->stackHead,  sizeof(struct NormalObjectStruct));

			break;
		case OPER_LOAD_STACK_OUTER_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			memcpy(variant, env->stackHead, sizeof(struct NormalObjectStruct));
			break;
		case OPER_LOAD_LOCAL_VAR_LOCAL_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant2 = env->variantArray + (node->operData.operData2IntInt.r);

			memcpy(variant2, variant, sizeof(struct NormalObjectStruct));

			break;
		case OPER_LOAD_LOCAL_VAR_OUTER_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant2 = env->variantArray + (node->operData.operData2IntInt.r);
			variant2 = (struct NormalObjectStruct *)(variant2->value.outerVariantPoint.point);

			memcpy(variant2, variant, sizeof(struct NormalObjectStruct));

			break;

		case OPER_LOAD_OUTER_VAR_LOCAL_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			variant2 = env->variantArray + (node->operData.operData2IntInt.r);
			memcpy(variant2, variant, sizeof(struct NormalObjectStruct));


			break;

		case OPER_LOAD_OUTER_VAR_OUTER_VAR:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);

			variant2 = env->variantArray + (node->operData.operData2IntInt.r);
			variant2 = (struct NormalObjectStruct *)(variant2->value.outerVariantPoint.point);

			memcpy(variant2, variant, sizeof(struct NormalObjectStruct));

			break;


		case OPER_STACK_PUSH:
			env->stackHead++;
			break;
		case OPER_STACK_POP:
			env->stackHead--;
			break;
			
		case OPER_GET_LOCAL_OBJECT_POINT_2_STACK:
			variant = env->variantArray + (node->operData.operData2IntInt.l);

			stringProperty = (  struct StringProperty *)(node->operData.operData2IntInt.r);
			variant = searchObjField2Stack(variant->value.objPoint, stringProperty );
			memcpy(env->stackHead, variant, sizeof(struct NormalObjectStruct));

			break;
		case OPER_GET_OUTER_OBJECT_POINT_2_STACK:
			variant = env->variantArray + (node->operData.operData2IntInt.l);
			variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);

			stringProperty = (struct StringProperty *)(node->operData.operData2IntInt.r);

			variant=searchObjField2Stack(variant->value.objPoint, stringProperty);
			memcpy(env->stackHead, variant, sizeof(struct NormalObjectStruct));
			break;
		case OPER_GET_OBJECT_POINT_POINT_2_STACK:
			//variant = node->operData.operData2IntInt.l;

			stringProperty = (struct StringProperty *)(node->operData.operData2IntInt.r);

			variant = searchObjField2Stack((struct  ObjectStruct *)(node->operData.operData2IntInt.l), stringProperty);
			memcpy(env->stackHead, variant, sizeof(struct NormalObjectStruct));

			break;
 
		case OPER_SET_LOCAL_OBJECT_POINT_FROM_STACK:
			//TODO 
			break;
		case OPER_SET_OUTER_OBJECT_POINT_FROM_STACK:
			//TODO 


			break;
		case OPER_IF_VALUE_JUMP:
			if (node->operData.operData2IntInt.l == 0)
			{
				*nextNode = (struct   ComputeNode *)(node->operData.operData2IntInt.r);

				//node = (struct   ComputeNode *)(node->operData.operData2IntInt.r);
			}
			//return node;
			
			break;

		case OPER_IF_VAR_JUMP:
 
		 
			if (env->stackHead->value.valueInt == 0)

			{
				*nextNode = (struct   ComputeNode *)(node->operData.operData2IntInt.r);
				//node = (struct   ComputeNode *)(node->operData.operData2IntInt.r);
			}

		 


			return node;

			break;

		case OPER_IF_STACK_JUMP:

			variant = (*currentEnv)->variantArray + (node->operData.operData2IntInt.l);

			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_POINT)
			{
				//variant = (struct NormalObjectStruct *)(variant->value.point);
				*nextNode = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			}

			if (variant->value.valueInt == 0)
			{
				//node = (struct   ComputeNode *)(node->operData.operData2IntInt.r);
				*nextNode = (struct   ComputeNode *)(node->operData.operData2IntInt.r);
			}




			//return node;

			break;
		case OPER_JUMP:
			*nextNode = (struct   ComputeNode *)(node->operData.operData2IntInt.l);
			break;
		case OPER_NEW_FUNC :
		 

			variant = env->variantArray + (node->operData.operData2IntInt.l);
			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_POINT)
			{
				variant = (struct NormalObjectStruct *)(variant->value.outerVariantPoint.point);
			}

			variant2 = env->variantArray + (node->operData.operData2IntInt.r);
			
			memcpy(env->stackHead, variant2, sizeof(struct NormalObjectStruct));
			
			if (variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT
				|| variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE
				|| variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_BOOLEAN
				|| variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_STRING)
			{
				
			}
			 
			else if (variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_OBJECT)
			{
				env->stackHead->value.objPoint = malloc(sizeof(struct ObjectStruct));
				memcpy(variant->value.objPoint, &(objectTemplate), sizeof(struct ObjectStruct));

			}
			else if (variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_FUNCTION)
			{
				env->stackHead->value.objPoint = malloc(sizeof(struct FunctionStruct));
				memcpy(variant->value.objPoint, &(functionTemplate), sizeof(struct ObjectStruct));

			}
			else if (variant2->baseObjectStruct.type == OBJECT_STRUCT_TYPE_ARRAY)
			{
				env->stackHead->value.objPoint = malloc(sizeof(struct ArrayStruct));
				memcpy(variant->value.objPoint, &(arrayTemplate), sizeof(struct ObjectStruct));
			}
			
			//准备函数环境
		 
			env->stackHead++;
			newEnv = constructEnv(variant, env, env, env->stackHead, node);
 
			memcpy(newEnv->stack, env->stackHead, sizeof(struct NormalObjectStruct)); //复制this指针



			break;
		case OPER_NEW_FUNC_BACK:
			newEnv->stackHead--;
			 //判断返回的值是否引用类型
			if (env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_INT
				|| env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_NUMBER_DOUBLE
				|| env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_BOOLEAN
				|| env->stackHead->baseObjectStruct.type == OBJECT_STRUCT_TYPE_STRING)
			{
			}
			else
			{
				memcpy(newEnv->stackHead , env->stackHead+1, sizeof(struct NormalObjectStruct)); //引用类型，复制返回值 

			}
			break;
		case OPER_PROGRAM_END:
			//node = NULL;
			*nextNode = NULL;
			//return;
 			break;
	}

	//stack++;
	//node = node->next;
	 
 	//return node;
}




inline   struct BaseObjectStruct *  searchObjField2Stack(struct  ObjectStruct * obj, struct StringProperty * stringProperty)
{
	struct ObjectField * p;

	for (int i = 0; i < stringProperty->len; i++)
	{
		if (obj->baseObjectStruct.type != OBJECT_STRUCT_TYPE_OBJECT  &&obj->baseObjectStruct.type !=PROTO_TYPE_STRING )
		{
			goto LABEL_SEARCH_PROTOTYPE;
		}
	LABEL_SEARCH_AGAIN:

		p = obj->fieldList;
		while (p)
		{
			if (p->name->value == stringProperty[i].value)
			{
				break;
			}
			p = p->next;
		}

	LABEL_SEARCH_PROTOTYPE:
		if (p == NULL) //对象找不到，找prototype
		{
			obj =(struct ObjectStruct *) (obj->baseObjectStruct.__proto__);
			if (obj == NULL)
			{
				return  &undefinedObject;
			}
 			goto 	LABEL_SEARCH_AGAIN;
		}
		else
		{
			obj = (struct ObjectStruct *) (p->fieldValue);
		}

	}

	return obj;
}
 

inline struct ExecEnv * constructEnv(struct NormalObjectStruct * variantFunc,  struct ExecEnv *envScop , struct ExecEnv * currentEnv, struct NormalObjectStruct *  stack, struct ComputeNode * returnNode)
{
	struct FunctionStruct * func =  variantFunc->value.funcEnv.func;


 	struct ExecEnv *newEnv  ;
	struct ExecEnv *envTmp;
	struct NormalObjectStruct *  variant;
	int i = 0;
	newEnv = variantFunc->value.funcEnv.env;
	if (newEnv != NULL)//复用之前的环境，只初始化本地变量 this指针、 参数
	{
		memcpy(newEnv->variantArray, func->envTemplate->variantArray, func->envTemplate->localLen);

	}
	else
	{
		
		newEnv = malloc(sizeof(struct ExecEnv));

		memcpy(newEnv, func->envTemplate, sizeof(struct ExecEnv));
		newEnv->variantArray = malloc(newEnv->variantArrayLen+ newEnv->stackSize);
		memcpy(newEnv->variantArray, func->envTemplate->variantArray, func->envTemplate->variantArrayLen + newEnv->stackSize);
		newEnv->stack = newEnv->variantArray + newEnv->variantArrayLen;
		newEnv->stackHead = newEnv->stack;

		//初始化本地变量
		/*variant = newEnv->localVariant;
		for (i=0variant < newEnv->outerVariant)
		{
			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_FUNCTION)
			{
				//variant->value.funcEnv.env = newEnv;
			}

			variant++;
		}
		*/


		//初始化外部变量
		
 		for (i = newEnv->localLen; i<  func->envTemplate->variantArrayLen ;i++)
		{
			envTmp = env->scope;
			while (envTmp->envTemplate != newEnv->variantArray[i].value.outerVariantIndex.envTemplate)
			{

				envTmp = envTmp->scope;
			};
			if (variant->baseObjectStruct.type == OBJECT_STRUCT_TYPE_OUTER_POINT)
			{
				//variant->baseObjectStruct.type = OBJECT_STRUCT_TYPE_POINT;
				newEnv->variantArray[i].value.outerVariantPoint.point = envTmp->variantArray + newEnv->variantArray[i].value.outerVariantIndex.index;
				newEnv->variantArray[i].value.outerVariantPoint.env = envTmp ;

			}		 
		}
		
	}
 
	newEnv->returnStack = stack;
 
	newEnv->scope = envScop;
	newEnv->prev = currentEnv;
	currentEnv->next = newEnv;


	newEnv->returnNode = returnNode;


	return newEnv;
}