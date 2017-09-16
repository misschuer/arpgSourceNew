#include <net/netstd.h>
#include "robotd_app.h"
/*#include "action/FindGridPath.h"*/
#ifdef GOOGLE_PERFTOOLS
#  include "setup_profiler.h"
#endif

#define WELCOME_MSG "Welcome to ROBOT,^C to stop!\n--------------------------------------------------------------\n\n"
int main(int argc, const char **argv)
{
#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(TRUE);	
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF  );	
	//_CrtSetBreakAlloc(393678);//����ϵ�
#endif



	//��ӡ��ӭ��Ϣ
	printf("%s\n",WELCOME_MSG);

	//�������ò���
	SvrCoreParams params;
	if(!params.Load(argc,(const char **)argv,NULL))
		return EXIT_FAILURE;

	//���������ļ�
	RobotConfig config;
	if(!config.Load(params.config_file, params.centd_port))
		return EXIT_FAILURE;

	//��Ӧ�ó���
	RobotdApp::g_app = new RobotdApp(params,config);
	//RobotdApp::HookSignals();
	if(!RobotdApp::g_app->Open())
	{
		//RobotdApp::UnHookSinals();
		delete RobotdApp::g_app;
		return EXIT_FAILURE;
	}

	//�ȴ������̲߳�ֱ���˳�
	tea_pinfo("appd running!\n----------------------------\n");				
	RobotdApp::g_app->RunLoop();

	//�رղ��ͷ�Ӧ�ó�����Դ
	RobotdApp::g_app->Close();
	//RobotdApp::UnHookSinals();
	safe_delete(RobotdApp::g_app);

#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(FALSE);	
#endif
	return 0;
}

