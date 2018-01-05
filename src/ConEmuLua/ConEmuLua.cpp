#include "ConEmuLua.h"

#define USEMODALDLG

class base_t
{
public:
	base_t():v(789){}
	void dump()
	{
		printf("in %s a:%d\n", __FUNCTION__, v);
	}
	int v;
};
class foo_t: public base_t
{
public:
	foo_t(int b):a(b)
	{
		printf("in %s b:%d this=%p\n", __FUNCTION__, b, this);
	}
	~foo_t()
	{
		printf("in %s\n", __FUNCTION__);
	}
	void print(int64_t a, base_t* p) const
	{
		printf("in foo_t::print a:%ld p:%p\n", (long)a, p);
	}

	static void dumy()
	{
		printf("in %s\n", __FUNCTION__);
	}
	int a;
};

//! lua talbe 可以自动转换为stl 对象
void dumy(map<string, string> ret, vector<int> a, list<string> b, set<int64_t> c)
{
	printf("in %s begin ------------\n", __FUNCTION__);
	for (map<string, string>::iterator it =  ret.begin(); it != ret.end(); ++it)
	{
		printf("map:%s, val:%s:\n", it->first.c_str(), it->second.c_str());
	}
	printf("in %s end ------------\n", __FUNCTION__);
}

class clazz{
public:
	static void static_func(){
		printf("in clazz::%s end ------------\n", __FUNCTION__);
	}
};

static void lua_reg(lua_State* ls)
{
	//! 注册基类函数, ctor() 为构造函数的类型
	ff::fflua_register_t<base_t, ctor()>(ls, "base_t")  //! 注册构造函数
		.def(&base_t::dump, "dump")     //! 注册基类的函数
		.def(&base_t::v, "v");          //! 注册基类的属性

	//! 注册子类，ctor(int) 为构造函数， foo_t为类型名称， base_t为继承的基类名称
	ff::fflua_register_t<foo_t, ctor(int)>(ls, "foo_t", "base_t")
		.def(&foo_t::print, "print")        //! 子类的函数
		.def(&foo_t::a, "a");               //! 子类的字段

	ff::fflua_register_t<>(ls)
		.def(&dumy, "dumy");                //! 注册静态函数


	ff::fflua_register_t<clazz, ctor()>(ls, "clazz")
		.def(&clazz::static_func, "static_func"); 

}

class CCliHelper:public CCliplus{
public:
    void LoadScript()
    {
        m_fflua.setModFuncFlag(true);
        //! 注册C++ 对象到lua中
        m_fflua.reg(lua_reg);
        //! 载入lua文件
        m_fflua.add_package_path("./ConEmuLua/");
        if (PathFileExistsA("test.lua"))
        {
            m_fflua.load_file("test.lua");
        }
        else if (PathFileExistsA("./ConEmuLua/test.lua"))
        {
            m_fflua.load_file("./ConEmuLua/test.lua");
        }
	}

	void TestScript()
	{
		//! 获取全局变量
		int var = 0;
		_ASSERTE(0 == m_fflua.get_global_variable("test_var", var));
		//! 设置全局变量
		_ASSERTE(0 == m_fflua.set_global_variable("test_var", ++var));

		//! 执行lua 语句
		m_fflua.run_string("print(\"exe run_string!!\")");

		//! 调用lua函数, 基本类型作为参数
		int32_t arg1 = 1;
		float   arg2 = 2;
		double  arg3 = 3;
		string  arg4 = "4";
		m_fflua.call<bool>("test_func", arg1, arg2, arg3,  arg4);
		m_fflua.call<bool>("Mod:funcTest1", arg1, arg2);

		//! 调用lua函数，stl类型作为参数， 自动转换为lua talbe
		vector<int> vec;        vec.push_back(100);
		list<float> lt;         lt.push_back((float)99.99);
		set<string> st;         st.insert("OhNIce");
		map<string, int> mp;    mp["key"] = 200;
		m_fflua.call<string>("test_stl", vec, lt, st,  mp);

		//! 调用lua 函数返回 talbe，自动转换为stl结构
		vec = m_fflua.call<vector<int> >("test_return_stl_vector");
		lt  = m_fflua.call<list<float> >("test_return_stl_list");
		st  = m_fflua.call<set<string> >("test_return_stl_set");
		mp  = m_fflua.call<map<string, int> >("test_return_stl_map");

		//! 调用lua函数，c++ 对象作为参数, foo_t 必须被注册过
		foo_t* foo_ptr = new foo_t(456);
		m_fflua.call<void>("test_object", foo_ptr);

		//! 调用lua函数，c++ 对象作为返回值, foo_t 必须被注册过 
		_ASSERTE(foo_ptr == m_fflua.call<foo_t*>("test_ret_object", foo_ptr));
		//! 调用lua函数，c++ 对象作为返回值, 自动转换为基类
		base_t* base_ptr = m_fflua.call<base_t*>("test_ret_base_object", foo_ptr);
		_ASSERTE(base_ptr == foo_ptr);
        delete foo_ptr;
	}
private:
	ff::fflua_t m_fflua;

protected:
	void AcceptCommand(char *szCmd)
	{
		if (strncmp(szCmd, "run", 3) == 0) {
			//LOGI("run lua code");
			m_fflua.run_string("print(\"Hello World!!!\")");
		}
		else if (strncmp(szCmd, "ldb", 3) == 0) {
			m_fflua.call<void>("pause","open ldb debugger", 1);
		}
		else if (strncmp(szCmd, "console", 7) == 0) {
            LOGW("执行Console命令");
		}
		else if (strncmp(szCmd, "pipe", 4) == 0) {
            LOGI("执行Pipe");

            // 开启一个匿名管道通讯
            //int nPID = 0;
            //CConEmuPipe pipe(nPID, 1000);

            //if (pipe.Init(_T("CVirtualConsole::OnPanelViewSettingsChanged"), TRUE))
            //{
            //    CESERVER_REQ_GUICHANGED lWindows = { sizeof(CESERVER_REQ_GUICHANGED) };
            //    lWindows.nGuiPID = GetCurrentProcessId();
            //    lWindows.hLeftView = NULL;
            //    lWindows.hRightView = NULL;
            //    pipe.Execute(CMD_GUICHANGED, &lWindows, sizeof(lWindows));
            //}
		}else
		{
			LOGW("无效输入： << "<< szCmd);
		}
	}

	void ShowHelpTips()
	{
		LOGI("演示Cli窗口应用的功能");
	}

	void ShowQuitTip()
	{
		LOGI("按下任意键退出...");
	}
};

int mainplus(int argc, char* argv[])
{
    HeapInitialize();

	ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "ConEmuLua");
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./ConEmuLua");
	//ILog4zManager::getRef().enableLogger(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, true);
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerThreadId(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerOutFile(LOG4Z_MAIN_LOGGER_ID, true);
	ILog4zManager::getRef().start();

	CCliHelper m_AppObj;
	//try 
	//{
		m_AppObj.LoadScript();
		m_AppObj.Open();
        m_AppObj.TestScript();
        ILog4zManager::getRef().stop();
	//}
	//catch (exception& e)
	//{
	//	LOGF("exception:"<<e.what());
	//}

    //HeapDeinitialize();
	return 0;
}

class CAppWnd :public CSimModalDialog {
public:
    CAppWnd() {}
    virtual ~CAppWnd() {}
protected:
    LRESULT OnRButtonDBClick(WPARAM, LPARAM) {
        EndDialog(IDCLOSE);
        return FALSE;
    }

    LRESULT OnPaint(WPARAM, LPARAM) {
        PAINTSTRUCT ps;
        HDC hDC = ::BeginPaint(*this, &ps);

        ::EndPaint(*this, &ps);
        return TRUE;
    }

	BEGIN_MSG_MAP_SIMWNDPROC(CAppWnd)
		MSG_MAP_SIMWNDPROC(WM_RBUTTONDBLCLK, OnRButtonDBClick)
		MSG_MAP_SIMWNDPROC(WM_PAINT, OnPaint)
	END_MSG_MAP_SIMWNDPROC(CSimModalDialog)
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
    HeapInitialize();

	ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "ConEmuLua");
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./ConEmuLua");
	//ILog4zManager::getRef().enableLogger(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, true);
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerThreadId(LOG4Z_MAIN_LOGGER_ID, false);
	ILog4zManager::getRef().setLoggerOutFile(LOG4Z_MAIN_LOGGER_ID, true);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	//非模态对话框
	CAppWnd myWnd;
    LOGT("CreateWindows");

#ifndef USEMODALDLG
	myWnd.CreateEx(WS_EX_ACCEPTFILES | WS_EX_APPWINDOW, _T("MyClass"), _T("SimDUIDemo"),
		WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,
		200, 200, 400, 300, GetActiveWindow(), NULL, hInstance
		);
	myWnd.ModifyStyle(WS_CAPTION, NULL);
	::ShowWindow(myWnd, SW_SHOW);
	return myWnd.MessageLoop();
#else
	int nRet =  myWnd.DoModal(_T("MyClass"), _T("SimDUIDemo"), 200, 200, 400, 300, GetActiveWindow(), hInstance);
    return nRet;
#endif
}
