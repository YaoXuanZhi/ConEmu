#include "CEventFactory.h"
//
//enum
//{
//	EVT_CREATE = 0,
//	EF_PAINT,
//	EF_CLICK,
//};
//
//void OnEvent_Create(char* szMsg)
//{
//#if (_MSC_VER <=1200)
//	printf("在OnEvent_Create函数内，消息：%s\n", szMsg);
//#else
//	printf("在%s函数内，消息：%s\n", __FUNCTION__, szMsg);
//	::MessageBoxA(NULL,__FUNCTION__,"警告",MB_OK);
//#endif
//	//return false;
//}
//
//class CTest1
//{
//public:
//	CTest1()
//	{
//		m_EvtUI.SubscribeEvent(EVT_CREATE, Subscriber(this, &CTest1::OnEvent_Paint));
//		m_EvtUI.SubscribeEvent(EF_PAINT, Subscriber(OnEvent_Create));
//	}
//
//	void OnCreate()
//	{
//		m_EvtUI.FireEvent(EVT_CREATE, "创建窗口");
//	}
//
//	void OnPaint()
//	{
//		m_EvtUI.FireEvent(EF_PAINT, "正在重绘");
//	}
//
//private:
//	CEventFactory2<UINT,/*bool, */char*,int> m_EvtUI;
//
//public:
//	void OnEvent_Paint(char* szMsg,int)
//	{
//#if (_MSC_VER <=1200)
//		printf("在OnEvent_Paint函数内，消息：%s\n", szMsg);
//#else
//		printf("在%s函数内，消息：%s\n", __FUNCTION__,szMsg);
//		::MessageBoxA(NULL,__FUNCTION__,"警告",MB_OK);
//#endif
//		//return false;
//	}
//};
//
//static void OnEvent_Click(int nTimes)
//{
//#if (_MSC_VER <=1200)
//	printf("在OnEvent_Click函数内，连击了%d次\n", nTimes);
//#else
//	printf("在%s函数内，连击了%d次\n", __FUNCTION__, nTimes);
//#endif
//	//return false;
//}
//
//class CTest2
//{
//private:
//	CEventFactory<UINT, /*bool, */int> m_EvtAction;
//	CEventFactory<UINT, /*bool, */char*> m_EvtUI;
//
//protected:
//	static void OnEvent_ClickEx(int nTimes)
//	{
//#if (_MSC_VER <=1200)
//		printf("在OnEvent_Click函数内，连击了%d次\n", nTimes);
//#else
//		printf("在%s函数内，连击了%d次\n", __FUNCTION__, nTimes);
//#endif
//		//return false;
//	}
//
//	void OnEvent_ClickPlus(int nTimes)
//	{
//#if (_MSC_VER <=1200)
//		printf("在OnEvent_Click函数内，连击了%d次\n", nTimes);
//#else
//		printf("在%s函数内，连击了%d次\n", __FUNCTION__, nTimes);
//#endif
//		//return false;
//	}
//
//public:
//	CTest2()
//	{
//		m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(OnEvent_Click));
//		//m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(OnEvent_ClickEx));//在VC 6.0下无法编译通过
//		m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(&CTest2::OnEvent_ClickEx));//可以在VC 6.0下编译通过
//		m_EvtAction.SubscribeEvent(EF_PAINT,Subscriber(this, &CTest2::OnEvent_ClickPlus));
//		//VC 6.0下其实比较笨的，打个比方，它在处理类的静态成员函数的时候，需要按照“&TClass::Function”的方式来实现
//	}
//
//	void PrintText()
//	{
//		m_EvtAction.FireEvent(EF_CLICK, 5);
//		m_EvtUI.FireEvent(EVT_CREATE, "嘿，现在在CTest2之中调用哦");		
//	}
//
//	CEventFactory<UINT, /*bool,*/ char*>& GetEventSetUI()
//	{
//		return m_EvtUI;
//	}
//
//};

void main48678()
{
	//CTest1 obj;
	//obj.OnCreate();
	//obj.OnPaint();

	//CTest2 obj2;
	//obj2.GetEventSetUI().SubscribeEvent(EVT_CREATE, Subscriber(&obj, &CTest1::OnEvent_Paint));
	//obj2.PrintText();
	//getchar();
}