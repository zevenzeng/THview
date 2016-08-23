#pragma once
#define PROTO_TYPE_STRING 0
#define PROTO_TYPE_FUNCTION 1
#define PROTO_TYPE_OBJECT 2


struct ProtoTypeStruct
{
	struct ObjectStruct objectStruct;  //¼Ì³ÐObjStruct
	//struct ProtoTypeStruct * __proto__;
 	unsigned int protoType;

	struct FunctionStruct * constructor;
 
};

struct ProtoTypeStruct stringProtoType;
struct ProtoTypeStruct functionProtoType;
struct ProtoTypeStruct objectProtoType;
