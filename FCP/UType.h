#pragma once
#include<string>
#include <vector>
enum EncodeType {
	JSON=0,
	PB
};

enum FcpMessage_FcpType {
	FcpMessage_FcpType_Publish = 0,
	FcpMessage_FcpType_ExtPublish = 2,
	FcpMessage_FcpType_SUBSCRIBE = 3,
	FcpMessage_FcpType_UNSUBSCRIBE = 4
};
using binary= std::vector<unsigned char>;
class UType
{
protected:
	static std::string m_name;
	static std::string m_type;
public:
	UType();
	~UType();
	static std::string get_name() {
		return m_name;
	}
	static std::string get_type() {
		return m_type;
	}
	std::string print() {
		return "type:" + m_name + "/" + m_type + "\n" + "data:" + SerializeAsString();
	}
	virtual const std::string SerializeAsString() const = 0;
	virtual void ParseFromString(const std::string data)=0;
};

template <class T>
class PbType :
	public UType
{
private:
	T m_data;
public:
	PbType() {
		m_name= typeid(T).name();
		m_type = "PB";
	}
	const std::string SerializeAsString() const {
		return m_data.SerializeAsString();
	}
	void ParseFromString(const std::string data)
	{
		m_data.ParseFromString(data);
	}

	T* operator->() {
		return &m_data;
	}
};

class SType:
	public UType
{
private:
	std::string m_data;
public:
	SType() {
		m_name ;
		m_type = "S";
	}
	 const std::string SerializeAsString() const{
		return m_data;
	}
	void  ParseFromString(const std::string data)
	{
		m_data=(data);
	}

	std::string* operator->() {
		return &m_data;
	}

	SType operator=(std::string data) {
		m_data = data;
		return *this;
	}
};