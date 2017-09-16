#include <net/netstd.h>
#include "logind_app.h"
#include "logind_context.h"
#include "logind_mongodb.h"

#ifdef GOOGLE_PERFTOOLS
#  include "setup_profiler.h"
#endif

#define WELCOME_MSG "Welcome to LOGIND,^C to stop!\n--------------------------------------------------------------\n\n"

//int run_test(int argc, char **argv)
//{
//	std::cout << "Running main() from gtest_main.cc\n";
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

int main(int argc, char **argv)
{	
#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(TRUE);	
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF  );	
	//_CrtSetBreakAlloc(97369);//����ϵ�
#endif

	//��ӡ��ӭ��Ϣ
	printf("%s\n",WELCOME_MSG);

//�������� 
//logindLogsDB db(0,0);
//auto i = db.Open("192.168.3.31;27017;qihei;qihei123",0,"");
//exit(1);
//return 0;

	//�������ò���
	SvrCoreParams params;
	if(!params.Load(argc,(const char **)argv,NULL))
		return EXIT_FAILURE;

	//���������ļ�
	LogindConfig config;
	if(!config.Load(params.config_file, params.centd_port))
		return EXIT_FAILURE;

	//��Ӧ�ó���
	LogindApp::g_app = new LogindApp(params,config);

	LogindApp::HookSignals();
	if(LogindApp::g_app->Open())
	{
		//���ӵ�¼������ڣ�����������ʹ��
		//if (params.run_test) 
		//	run_test(argc,argv);
		//�ȴ������̲߳�ֱ���˳�
		tea_pinfo("logind running!\n----------------------------\n");
		LogindApp::g_app->Wait();
	}

	//�رղ��ͷ�Ӧ�ó�����Դ
	LogindApp::g_app->Close();
	LogindApp::UnHookSinals();
	safe_delete(LogindApp::g_app);

#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(FALSE);	
#endif
	return 0;
}

