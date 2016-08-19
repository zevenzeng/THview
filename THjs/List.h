#pragma once
struct List
{
	int len;
};

struct SingleList
{
	int len;
	struct ListNode * head;

};

struct SingleListNode
{
	void * item;
	struct ListNode * next
};