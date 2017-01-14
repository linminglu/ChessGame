#ifndef DISPATCH_HANDLER_H__
#define DISPATCH_HANDLER_H__
#include <iostream>
#include <map>
#include <vector>
#include "cocos2d.h"

typedef std::function<void(int cmd, void *data, size_t lenght)> ccDispatchCallBack;
typedef std::function<void(void)> ccDispatchEndCallBack;

#define DISPATCHHANDLER_LUA_FILE_NAME	"DispatchConfig"
class DispatchHandler
{
public:
	struct DispatchData
	{
		int m_cmd;
		int m_order;
		ccDispatchCallBack m_func;
	};

	struct Dispatch
	{
		int m_cmd;
		void *m_data;
		size_t m_lenght;
		ccDispatchEndCallBack m_endCallBack;
	};
public:
	DispatchHandler();
	virtual ~DispatchHandler();

	static DispatchHandler *getInstance();

	// 添加消息处理
	int addDispatchHandler(const int cmd,const ccDispatchCallBack &dispatch);

	// 添加消息处理
	int addDispatchHandler(int cmd, DispatchData& dispatch);

	// 添加处理消息
	void postDispatchHandler(int cmd, void *data,size_t lenght,const ccDispatchEndCallBack &endCallBack = nullptr);

	// 删除cmd所有消息处理
	void removeDispatchHandler(int cmd);

	// 删除cmd中的编号为order的消息处理
	void removeDispatchHandler(int cmd,int order);
protected:
	// 检测当前是否有对应的命令的操作
	bool checkHandler(int cmd);

	// 获取消息内容
	std::vector<DispatchData> &getHandler(int cmd);

	// 每帧处理的消息
	void update();

	std::vector<Dispatch> getDispatchs(int cmd);
private:
	// 消息队列
	std::map<int , std::vector<DispatchData>> m_dispatchMaps;

	// 等待处理的数据列表
	std::vector<Dispatch> m_dispatchs;

	static DispatchHandler *m_instances;
};

#define gDispatchhandler DispatchHandler::getInstance()

#endif // DISPATCH_HANDLER_H__