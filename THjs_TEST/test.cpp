#include <gtest/gtest.h>

#ifdef __cplusplus 
extern "C" {
#endif
#include <VM.h>

	//Ò»¶Î´úÂë
#ifdef __cplusplus 
}
#endif
 
 int Add(int a, int b)
{
	return a + b;
}
TEST(testCase, test_int_add_variant)
{
	struct AstNode * node;
	struct ExecEnv *envP;
	//////////////int + a     3 +a
	struct AstNode bootNode;
	bootNode.next = NULL;
	bootNode.nodeType = OPER_ADD_VAR_1_INT_LEFT;
	bootNode.operData.operData2IntInt.l = 3;
	struct NormalObjectStruct variant_a;
	variant_a.baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;
	variant_a.value.valueInt = 5;

	bootNode.operData.operData2IntInt.r = (int) &variant_a;


	struct ExecEnv env;
	run(&bootNode, &env);


	EXPECT_EQ(8, env.stack[0].value.valueInt);


	//////////////double + b    3 +a

	struct AstNode bootNode2;
	bootNode2.next = NULL;
	bootNode2.nodeType = OPER_ADD_VAR_1_DOUBLE_LEFT;
	bootNode2.operData.operData2DobuleInt.l = 3.1;
	struct NormalObjectStruct variant_b;
	variant_b.baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;
	variant_b.value.valueInt = 5;

	bootNode2.operData.operData2DobuleInt.r = (int)&variant_b;


	struct ExecEnv env2;
	run(&bootNode2, &env2);
	EXPECT_DOUBLE_EQ(bootNode2.operData.operData2DobuleInt.l + variant_b.value.valueInt, env2.stack[0].value.valueDouble);


	//////////////////string + variant (int)
	struct AstNode bootNode3;
	struct ExecEnv env3;

	node = &bootNode3;
	envP = &env3;
	node->next = NULL;
	node->nodeType = OPER_ADD_VAR_1_STRING_LEFT;
	char *st = "hello";
	node->operData.operData2StringInt.l.value = st;
	node->operData.operData2StringInt.l.len = strlen(st);


	struct NormalObjectStruct variant_c;
	variant_c.baseObjectStruct.type = OBJECT_STRUCT_TYPE_NUMBER_INT;
	variant_c.value.valueInt = 5;

	node->operData.operData2DobuleInt.r = (int)&variant_c;



	run(node, envP);

	EXPECT_STREQ("hello5", (char *)(envP->stack[0].value.stringProperty.value));
}
 

TEST(testCase, test_call)
{
	struct AstNode * nodeList =(struct AstNode *) malloc(sizeof(struct AstNode));


	struct ExecEnv global_env;
	struct FunctionStruct globale_func;
	global_env.bootNode = nodeList;
	global_env.func = &globale_func;
	global_env.envTemplate = &global_env;
	global_env.variantArrayLen = 4;
	global_env.variantArray = (struct NormalObjectStruct*) malloc(sizeof(struct NormalObjectStruct) * global_env.variantArrayLen);
	global_env.localVariant = global_env.variantArray;
	global_env.localFunc = global_env.localVariant +2;
	global_env.parentFunctionObj = NULL;
	global_env.outerFunc = NULL;
	global_env.outerVariant = NULL;
	global_env.scope = NULL;
	global_env.


}
