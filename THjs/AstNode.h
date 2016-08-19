#pragma once

struct AstNode
{
	char nodeType;

	struct ComputeNode * ComputeNode;


	struct node * next;   //下一运算节点
	struct node * child;// 下一子节点
	struct node * brotherNode;   //下一兄弟节点
};

struct ComputeNode
{

	char nodeType;


	union OperDataUnion
	{
		struct  OperData2DobuleInt { double l; int r; } operData2DobuleInt;   //  
		struct  OperData2StringInt { struct StringProperty l; int r; } operData2StringInt;   //  
		struct  OperData2IntInt { int l; int r; } operData2IntInt;   //   两个操作数 ，按照nodeType字段区分，两个操作数都是整形或者一个整形，一个变量，或者两个变量，其中变量是符号表索引
		struct OperDataInt { int l; } operDataInt;  //有几种情况，单操作数，  两个操作数，但是有一个是表达式结果，存放于栈中，
		struct OperDataDouble { double l; } operDataDouble;  //有几种情况，单操作数，  两个操作数，但是有一个是表达式结果，存放于栈中，

	} operData;
};