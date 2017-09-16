#include <net/netstd.h>
#include "appd_app.h"

#ifdef GOOGLE_PERFTOOLS
#  include "setup_profiler.h"
#endif

#define WELCOME_MSG "Welcome to APPD,^C to stop!\n--------------------------------------------------------------\n\n"

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
	AppConfig config;
	if(!config.Load(params.config_file, params.centd_port))
		return EXIT_FAILURE;

	//��Ӧ�ó���
	AppdApp::g_app = new AppdApp(params,config);
	AppdApp::loadXiulian();
	AppdApp::HookSignals();
	if(!AppdApp::g_app->Open())
	{
		AppdApp::UnHookSinals();
		delete AppdApp::g_app;
		return EXIT_FAILURE;
	}
	//�ȴ������̲߳�ֱ���˳�
	tea_pinfo("appd running!\n----------------------------\n");				
	AppdApp::g_app->Wait();

	//�رղ��ͷ�Ӧ�ó�����Դ
	AppdApp::g_app->Close();
	AppdApp::UnHookSinals();
	safe_delete(AppdApp::g_app);

#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(FALSE);	
#endif
	return 0;
}

