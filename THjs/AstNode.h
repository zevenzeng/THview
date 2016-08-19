#pragma once

struct AstNode
{
	char nodeType;

	struct ComputeNode * ComputeNode;


	struct node * next;   //��һ����ڵ�
	struct node * child;// ��һ�ӽڵ�
	struct node * brotherNode;   //��һ�ֵܽڵ�
};

struct ComputeNode
{

	char nodeType;


	union OperDataUnion
	{
		struct  OperData2DobuleInt { double l; int r; } operData2DobuleInt;   //  
		struct  OperData2StringInt { struct StringProperty l; int r; } operData2StringInt;   //  
		struct  OperData2IntInt { int l; int r; } operData2IntInt;   //   ���������� ������nodeType�ֶ����֣������������������λ���һ�����Σ�һ�������������������������б����Ƿ��ű�����
		struct OperDataInt { int l; } operDataInt;  //�м������������������  ������������������һ���Ǳ��ʽ����������ջ�У�
		struct OperDataDouble { double l; } operDataDouble;  //�м������������������  ������������������һ���Ǳ��ʽ����������ջ�У�

	} operData;
};