#ifndef __CEVENTFACTORY_H
#define __CEVENTFACTORY_H
#include "CAutoRegisterFactory.h"
#include <vector>
#include <assert.h>
#pragma warning(disable:4996)

//�ο��ˡ������Զ�����-��ݹ�˼�롷��ʵ�ִ˵ݹ��
//���ӣ�http://www.cppblog.com/kevinlynx/archive/2008/08/20/59451.html
///////////////////////////////////////�ݹ���ʵ��///////////////////////////////////////
#define DECVALUE_1 0
#define DECVALUE_2 1
#define DECVALUE_3 2
#define DECVALUE_4 3
#define DECVALUE_5 4
#define DECVALUE_6 4
#define DECVALUE_7 4
#define DECVALUE_8 4
#define DECVALUE_9 4

#ifndef DECVALUE
#define DECVALUE(n) DECVALUE_##n
#else
#error "DECVALUE�ѱ����壬�����������"
#endif

//Ŀ����Ϊ���ӳ�����չ��ʱ��
#ifndef MERGECHAR
#define MERGECHAR(a,b) _MERGECHAR(a,b)
#define _MERGECHAR(a,b) a##b
#else
#error "MERGECHAR�ѱ����壬�����������"
#endif

#define REPEAT_1( n, f, e ) e(n)
#define REPEAT_2( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) )
#define REPEAT_3( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_4( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_5( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_6( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_7( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_8( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 
#define REPEAT_9( n, f, e ) MERGECHAR( MERGECHAR( REPEAT_, DECVALUE( n ) )( DECVALUE( n ), f, e ), f( n ) ) 

#define PARAM_ARG(n) typename T##n
#define PARAM_ARRARY(n) ,PARAM_ARG(n)
#define PARAM_DEF( n ) REPEAT_##n( n, PARAM_ARRARY, PARAM_ARG )

#define PARAM_ARGEX(n) T##n t##n
#define PARAM_ARRARYEX(n) ,PARAM_ARGEX(n)
#define PARAM_DEFEX( n ) REPEAT_##n( n, PARAM_ARRARYEX, PARAM_ARGEX )

#define REAL_ARG(n) t##n
#define REAL_ARRARY(n) ,REAL_ARG(n)
#define REAL_DEF( n ) REPEAT_##n( n, REAL_ARRARY, REAL_ARG )

#define REAL_ARGEX(n) T##n
#define REAL_ARRARYEX(n) ,REAL_ARGEX(n)
#define REAL_DEFEX( n ) REPEAT_##n( n, REAL_ARRARYEX, REAL_ARGEX )
///////////////////////////////////////�ݹ���ʵ��///////////////////////////////////////

//////////////////////////////////////��������//////////////////////////////////////
template<typename TBase>
class TplForwarderForEvent :public IForwarder<TBase>
{
private:
	TBase* m_Obj;

public:
	TplForwarderForEvent(const TBase &Obj)
	{
		m_Obj = Obj.Clone();
	}

	virtual ~TplForwarderForEvent()
	{
		if (NULL != m_Obj)
		{
			delete m_Obj;
			m_Obj = NULL;
		}
	}

public:
	virtual TBase* CloneClass() { return m_Obj->Clone(); }
	virtual TBase* InvokeClass() { return m_Obj; }

};

/** @brief �źŲ����� */
enum {
	Slot_Unknown,   /**< δ֪�������� */
	Slot_Normal,	/**< ��ͨ�������� */
	Slot_Member,	/**< ��Ա�������� */
};

//////////////////////////////////////��������//////////////////////////////////////

/////////////////////////////////////ʵ�ֽ���һ���������¼��������/////////////////////////////////////
#define DEF_SLOTFUNCTOR(classname,n)																	\
																										\
template<PARAM_DEF(n)>																					\
class ISlotFunctionr##n																					\
{																										\
public:																									\
	virtual ~ISlotFunctionr##n() {}																		\
	virtual void InvokeFunction(REAL_DEFEX(n)) = 0;														\
	virtual ISlotFunctionr##n* Clone() const = 0;														\
	virtual bool Equal(const ISlotFunctionr##n & sour)const = 0;										\
	virtual int GetSlotType() const { return Slot_Unknown; }											\
};																										\
																										\
template<PARAM_DEF(n)>																					\
class NormalFunctionr##n :public ISlotFunctionr##n<REAL_DEFEX(n)>										\
{																										\
	typedef ISlotFunctionr##n<REAL_DEFEX(n)> TSlotFunc;													\
	typedef void(pSlotFunction)(REAL_DEFEX(n));															\
																										\
public:																									\
	NormalFunctionr##n(pSlotFunction* pNormalFunc)														\
		:m_pNormalFunc(pNormalFunc)																		\
	{																									\
		assert((pNormalFunc, "pNormalFuncָ��ΪNULL������"));											\
	}																									\
																										\
	virtual ~NormalFunctionr##n() {}																	\
																										\
	void InvokeFunction(PARAM_DEFEX(n))																	\
	{																									\
		assert((m_pNormalFunc, "m_pNormalFuncָ��ΪNULL������"));										\
		m_pNormalFunc(REAL_DEF(n));																		\
	}																									\
																										\
	TSlotFunc* Clone() const																			\
	{																									\
		return new NormalFunctionr##n(m_pNormalFunc);													\
	}																									\
																										\
	int GetSlotType() const { return Slot_Normal; }														\
																										\
	virtual bool Equal(const TSlotFunc & sour) const													\
	{																									\
		if (sour.GetSlotType() != Slot_Normal) return false;											\
		const NormalFunctionr##n *psour = static_cast<const NormalFunctionr##n*>(&sour);				\
		assert(psour);																					\
		return psour->m_pNormalFunc == m_pNormalFunc;													\
	}																									\
																										\
private:																								\
	pSlotFunction *m_pNormalFunc;	/**< ��ͨ����ָ�� */												\
};																										\
																										\
template<PARAM_DEF(n)>																					\
NormalFunctionr##n<REAL_DEFEX(n)> Subscriber(void(*pNormalFunc)(REAL_DEFEX(n)))							\
{																										\
	return NormalFunctionr##n<REAL_DEFEX(n)>(pNormalFunc);												\
}																										\
																										\
template<typename TClass, PARAM_DEF(n)>																	\
class MemberFunctionr##n :public ISlotFunctionr##n<REAL_DEFEX(n)>										\
{																										\
	typedef ISlotFunctionr##n<REAL_DEFEX(n)> TSlotFunc;													\
	typedef void(TClass::*pSlotFunction)(REAL_DEFEX(n));												\
																										\
public:																									\
	MemberFunctionr##n(TClass *pClassInst, pSlotFunction pMemberFunc)									\
		:m_pClassInst(pClassInst),m_pMemberFunc(pMemberFunc)											\
	{																									\
		assert((pClassInst, "pClassInstָ��ΪNULL������"));											    \
		assert((pMemberFunc, "pMemberFuncָ��ΪNULL������"));											\
	}																									\
																										\
	virtual ~MemberFunctionr##n() {}																	\
																										\
	void InvokeFunction(PARAM_DEFEX(n))																	\
	{																									\
		assert((m_pClassInst, "m_pClassInstָ��ΪNULL������"));										    \
		assert((m_pMemberFunc, "m_pMemberFuncָ��ΪNULL������"));										\
		(m_pClassInst->*m_pMemberFunc)(REAL_DEF(n));													\
	}																									\
																										\
	TSlotFunc* Clone() const																			\
	{																									\
		return new MemberFunctionr##n(m_pClassInst, m_pMemberFunc);										\
	}																									\
																										\
	int GetSlotType() const { return Slot_Member; }														\
																										\
	virtual bool Equal(const TSlotFunc & sour) const													\
	{																									\
		if (sour.GetSlotType() != Slot_Member) return false;											\
		const MemberFunctionr##n *psour = static_cast<const MemberFunctionr##n*>(&sour);				\
		assert(psour);																					\
		return psour->m_pMemberFunc == m_pMemberFunc;													\
	}																									\
																										\
private:																								\
	pSlotFunction m_pMemberFunc;	/**< ��ĳ�Ա����ָ�� */											\
	TClass *m_pClassInst;			/**< ��ʵ����ָ�� */												\
};																										\
																										\
template<typename TClass, PARAM_DEF(n)>																	\
MemberFunctionr##n<TClass, REAL_DEFEX(n)> Subscriber(TClass *pClassInst,								\
													void(TClass::*pNormalFunc)(REAL_DEFEX(n)))			\
{																										\
	return MemberFunctionr##n<TClass, REAL_DEFEX(n)>(pClassInst, pNormalFunc);							\
}																										\
																										\
template<typename TKEY, PARAM_DEF(n)>																	\
class classname##n																					    \
{																										\
	/*����VC 6.0�޷�����>>���ķ��ţ����Ϊ�ۺ����������������*/									    \
	typedef ISlotFunctionr##n<REAL_DEFEX(n)> TSlotFunc;													\
																										\
public:																									\
	/*ͳһ��ע��ӿڣ�Ҳ���Խ�����ΪConnect();*/														\
	void SubscribeEvent(TKEY Key, const TSlotFunc &subscriber)											\
	{																									\
		m_ContainterFactory.RegisterFactory(Key, 														\
		new TplForwarderForEvent<TSlotFunc>(subscriber));												\
	}																									\
																										\
	/*��ע��ָ���¼���Ҳ���Խ�����ΪDisconnect();*/													    \
	void UnsubscribeEvent(TKEY Key,const TSlotFunc &subscriber)											\
	{																									\
		m_ContainterFactory.UnregisterContainter(Key,false,												\
		new TplForwarderForEvent<TSlotFunc>(subscriber));												\
	}																									\
																										\
	void FireEvent(TKEY Key, PARAM_DEFEX(n))															\
	{																									\
		typedef std::list<IForwarder<TSlotFunc>*> ForwardContainter;									\
		std::list<IForwarder<TSlotFunc>*> *pContainter = m_ContainterFactory.InvokeContanter(Key);		\
		if(NULL!=pContainter)																			\
		{																								\
			typename ForwardContainter::iterator it = pContainter->begin();								\
			for(;it!=pContainter->end();it++)															\
			{																							\
				IForwarder<TSlotFunc>* pItem = *it;														\
				pItem->InvokeClass()->InvokeFunction(REAL_DEF(n));										\
			}																							\
		}																								\
	}																									\
																										\
private:																								\
	CMutipleRegisteredFactory<TKEY, TSlotFunc> m_ContainterFactory;										\
};			

DEF_SLOTFUNCTOR(CEventFactory,1)
DEF_SLOTFUNCTOR(CEventFactory,2)
DEF_SLOTFUNCTOR(CEventFactory,3)
DEF_SLOTFUNCTOR(CEventFactory,5)
DEF_SLOTFUNCTOR(CEventFactory,6)
DEF_SLOTFUNCTOR(CEventFactory,7)
DEF_SLOTFUNCTOR(CEventFactory,8)

/*
�¼���������ʹ����·��
1.��ִ��AddEventID()��ע���¼�֪ͨ��
2.Ȼ����ָ����ʱ��ִ��SubscribeEvent()������֪ͨ�����Ӧ�¼�
3.��������Ҫ����֪ͨ��Ĵ��봦ִ��FireEvent()
4.����ʵ����Ҫ��ͨ��UnsubscribeEvent()���� ע��

�ĳ�QT�źŲ۵����ʱ���������淽ʽ���滻���
SubscribeEvent --> Connect
UnsubscribeEvent --> Disconnect
EventID --> SignalIDAddEventID
*/

#endif
