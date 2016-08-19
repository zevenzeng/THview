#include <stdio.h>
#include "ObjectStruct.h"

#include "Parser.h"

//�ڻ����в��ҷ���,
inline struct SymbolStringCacheNode * searchSymbolCache(struct EnvSymbol *  p,struct SymbolTableElement * node)
{
	struct SymbolStringCacheNode * cacheNode;
	cacheNode = node->symbolString.cache[p->envTmp->level];

	while(cacheNode!=NULL)
	{
		if (cacheNode->env == p->envTmp)
		{
			return cacheNode;
		}
		cacheNode->next;
	}
	return NULL;
}

inline addGlobalSymbolCache(struct EnvSymbol * globalEnvSymbol,struct SymbolTableElement *  node)
{

 	struct SymbolStringCacheNode *  cacheNode;

//	while (node != NULL)
	//{
 		node->symbolString.cache = malloc(globalEnvSymbol->envTmp->level * sizeof(struct SymbolStringCacheNode *));
		memset(node->symbolString.cache, 0x00, globalEnvSymbol->envTmp->level*sizeof(struct SymbolStringCacheNode *));
		

		cacheNode = malloc(sizeof(struct SymbolStringCacheNode));
		cacheNode->env =globalEnvSymbol->envTmp;
		cacheNode->indexValue.field = node->indexValue.field;
		cacheNode->next = node->symbolString.cache[0];
		node->symbolString.cache[0] = cacheNode;

	//}
}

inline addSymbolCache(struct EnvSymbol * p,struct EnvSymbol *globalEnvSymbol,struct SymbolTableElement *  node)
{
 	struct SymbolStringCacheNode *  cacheNode;
 
	//while (node!=NULL)
	{
		if (node->symbolString.cache == NULL)
		{
			node->symbolString.cache = malloc(globalEnvSymbol->envTmp->level * sizeof(struct SymbolStringCacheNode *));
			memset(node->symbolString.cache, 0x00, globalEnvSymbol->envTmp->level*sizeof(struct SymbolStringCacheNode *));

		}
		
		cacheNode = malloc(sizeof(struct SymbolStringCacheNode));
		cacheNode->env = p->envTmp;
		cacheNode->indexValue.index = node->indexValue.index;
		cacheNode->next = node->symbolString.cache[p->envTmp->level];
		node->symbolString.cache[p->envTmp->level] = cacheNode;

	}

}


inline initGlobalEnvTmpLocal(struct GlobalEnvObj *   p)
{
	int i = 0;
	p->envTmp.variantArray = malloc((p->envSymbol.localVaraintSymbolSize   + p->envSymbol.outerSymbolSize)
		*(sizeof(struct NormalObjectStruct)));

 
	struct SymbolTableElement *  node;

	p->envTmp.variantArray[0].baseObjectStruct.type = OBJECT_STRUCT_TYPE_POINT;         //��ʼ��thisָ��
	p->envTmp.variantArray[0].value.objPoint = &(p->obj);         //��ʼ��thisָ��
 
	for (i = 1, node = p->envSymbol.localVaraintSymbol; i < p->envSymbol.localVaraintSymbolSize; i++, node = node->next)
	{
		
		if (node->type == OBJECT_STRUCT_TYPE_FUNCTION)
		{
			memcpy(p->envTmp.variantArray[i], &normalValueFunction, sizeof(struct NormalObjectStruct));

			//p->envTmp.variantArray[i].value.funcEnv.env = &( p->envTmp);
			p->envTmp.variantArray[i].value.funcEnv.func = ((struct SymbolTableFuncElement *)node)->func;
			node->indexValue.field = &(p->envTmp.variantArray[i]);

		}
		else
		{
			memcpy(p->envTmp.variantArray[i], &undefinedObject, sizeof(struct NormalObjectStruct));
			node->indexValue.field = &(p->envTmp.variantArray[i]);

		}
		
		 



		addPropertyWithField(&(p->obj), &(node->symbolString.stringProperty), &(p->envTmp.variantArray[i]));
		addGlobalSymbolCache(&(p->envSymbol),node);
	}

}

inline initGlobalEnvTmp(struct GlobalEnvObj *   p)
{
	struct SymbolTableElement *  node;
	int i = 0;
	initGlobalEnvTmpLocal(p);
	
	//node->next=p->envSymbol.outerSymbol;
	//����ȫ������
	for (i = 0, node = p->envSymbol.outerSymbol; i < p->envSymbol.outerSymbolSize; i++, node = node->next)
	{
		node->indexValue.field=  addProperty(&(p->obj), &(node->symbolString.stringProperty));
	}
}
//void searchProperty(struct EnvSymbol * q,){}
//��һ�׶�ɨ�裬ȷ����var������ȷ����ȫ�����ţ��ڶ��׶�ɨ���ⲿ�������Լ�this����


//��ʼ��envģ��ı��ر���
inline initEnvTmpLocal(struct EnvSymbol * p, struct GlobalEnvObj *globalEnvObj)
{

	int i = 0;
	p->envTmp->variantArray = malloc((p->localVaraintSymbolSize + p->outerSymbolSize)
		*(sizeof(struct NormalObjectStruct)));

 
	struct SymbolTableElement *  node;
	p->envTmp->variantArray[0].baseObjectStruct.type = OBJECT_STRUCT_TYPE_POINT ;         //��ʼ��thisָ��
	p->envTmp->variantArray[0].value.objPoint = globalEnvObj;         //��ʼ��thisָ��

	for (i = 1, node = p->localVaraintSymbol; i < p->localVaraintSymbolSize; i++, node = node->next)
	{
		if (node->type == OBJECT_STRUCT_TYPE_FUNCTION)
		{
			memcpy(p->envTmp->variantArray[i], &normalValueFunction, sizeof(struct NormalObjectStruct));
			//p->envTmp->variantArray[i].value.funcEnv.env = p->envTmp;
			p->envTmp->variantArray[i].value.funcEnv.func = ((struct SymbolTableFuncElement *)node)->func;

		}
		else
		{
			memcpy(p->envTmp->variantArray[i], &undefinedObject, sizeof(struct NormalObjectStruct));
		}
		if(i== p->envTmp)
		addSymbolCache(p,&( globalEnvObj->envSymbol), node);

	}




}
void initEnvTmp(struct EnvSymbol * p, struct GlobalEnvObj *globalEnvObj)
{
	int i = 0;
	int j = 0;
	//int k = 0;
	struct EnvSymbol * q;
 
	//q->localSymbolTail->next = q->outerSymbol;
	struct SymbolTableElement * node;
 	struct SymbolTableElement * outNode;
	struct SymbolStringCacheNode * cacheNode;

	initEnvTmpLocal(p, globalEnvObj);

	node = p->outerSymbol;		 		
 	j == p->localVaraintSymbolSize ;
	i = p->localVaraintSymbolSize + p->outerSymbolSize;
	q = p->scope;


	while (node != NULL)
	{
		cacheNode = searchSymbolCache(q, node);
		if (cacheNode == NULL)  //��ǰ����ģ���Ҳ���
		{
			if (q == &(globalEnvObj->envTmp))  //���ȫ������
			{

				outNode = malloc(sizeof(struct SymbolTableElement));
				outNode->next = globalEnvObj->envSymbol.outerSymbol;
				globalEnvObj->envSymbol.outerSymbol = outNode;


				outNode->indexValue.field = addProperty(&(globalEnvObj->obj), &(node->symbolString.stringProperty));
				globalEnvObj->envSymbol.outerSymbolSize++;

				p->envTmp->variantArray[j].value.point = outNode->indexValue.field;
				

				node = node->next;
				j++;
			}
			q = q->scope;
			continue;
		}
		if (q ==&( globalEnvObj->envTmp))  //ָ��ȫ�ֻ���
		{
 			p->envTmp->variantArray[j].value.point = cacheNode->indexValue.field;	
			p->envTmp->variantArray[j].baseObjectStruct.type = OBJECT_STRUCT_TYPE_POINT;
			j++;
		}
		else
		{
			p->envTmp->variantArray[i].value.outerVariantIndex.envTemplate = q->envTmp;
			p->envTmp->variantArray[i].value.outerVariantIndex.index = cacheNode->indexValue.index;
			p->envTmp->variantArray[i].baseObjectStruct.type = OBJECT_STRUCT_TYPE_OUTER_POINT;
			i--;
		}
		node = node->next;
 		q = p->scope;
	}
	 


}
 