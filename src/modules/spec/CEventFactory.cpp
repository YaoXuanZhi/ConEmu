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
//	printf("��OnEvent_Create�����ڣ���Ϣ��%s\n", szMsg);
//#else
//	printf("��%s�����ڣ���Ϣ��%s\n", __FUNCTION__, szMsg);
//	::MessageBoxA(NULL,__FUNCTION__,"����",MB_OK);
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
//		m_EvtUI.FireEvent(EVT_CREATE, "��������");
//	}
//
//	void OnPaint()
//	{
//		m_EvtUI.FireEvent(EF_PAINT, "�����ػ�");
//	}
//
//private:
//	CEventFactory2<UINT,/*bool, */char*,int> m_EvtUI;
//
//public:
//	void OnEvent_Paint(char* szMsg,int)
//	{
//#if (_MSC_VER <=1200)
//		printf("��OnEvent_Paint�����ڣ���Ϣ��%s\n", szMsg);
//#else
//		printf("��%s�����ڣ���Ϣ��%s\n", __FUNCTION__,szMsg);
//		::MessageBoxA(NULL,__FUNCTION__,"����",MB_OK);
//#endif
//		//return false;
//	}
//};
//
//static void OnEvent_Click(int nTimes)
//{
//#if (_MSC_VER <=1200)
//	printf("��OnEvent_Click�����ڣ�������%d��\n", nTimes);
//#else
//	printf("��%s�����ڣ�������%d��\n", __FUNCTION__, nTimes);
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
//		printf("��OnEvent_Click�����ڣ�������%d��\n", nTimes);
//#else
//		printf("��%s�����ڣ�������%d��\n", __FUNCTION__, nTimes);
//#endif
//		//return false;
//	}
//
//	void OnEvent_ClickPlus(int nTimes)
//	{
//#if (_MSC_VER <=1200)
//		printf("��OnEvent_Click�����ڣ�������%d��\n", nTimes);
//#else
//		printf("��%s�����ڣ�������%d��\n", __FUNCTION__, nTimes);
//#endif
//		//return false;
//	}
//
//public:
//	CTest2()
//	{
//		m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(OnEvent_Click));
//		//m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(OnEvent_ClickEx));//��VC 6.0���޷�����ͨ��
//		m_EvtAction.SubscribeEvent(EF_CLICK, Subscriber(&CTest2::OnEvent_ClickEx));//������VC 6.0�±���ͨ��
//		m_EvtAction.SubscribeEvent(EF_PAINT,Subscriber(this, &CTest2::OnEvent_ClickPlus));
//		//VC 6.0����ʵ�Ƚϱ��ģ�����ȷ������ڴ�����ľ�̬��Ա������ʱ����Ҫ���ա�&TClass::Function���ķ�ʽ��ʵ��
//	}
//
//	void PrintText()
//	{
//		m_EvtAction.FireEvent(EF_CLICK, 5);
//		m_EvtUI.FireEvent(EVT_CREATE, "�٣�������CTest2֮�е���Ŷ");		
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