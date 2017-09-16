#include <net/netstd.h>
#include "policed_app.h"

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
	PolicedConfig config;
	if(!config.Load(params.config_file, params.centd_port))
		return EXIT_FAILURE;

	//��Ӧ�ó���
	PolicedApp::g_app = new PolicedApp(params,config);
	PolicedApp::HookSignals();
	if(!PolicedApp::g_app->Open())
	{
		PolicedApp::UnHookSinals();
		delete PolicedApp::g_app;
		return EXIT_FAILURE;
	}

	//�ȴ������̲߳�ֱ���˳�
	tea_pinfo("appd running!\n----------------------------\n");
	PolicedApp::g_app->Wait();

	//�رղ��ͷ�Ӧ�ó�����Դ
	PolicedApp::g_app->Close();
	PolicedApp::UnHookSinals();
	safe_delete(PolicedApp::g_app);

#if PLATFORM == PLATFORM_WINDOWS
	wsa_initializer(FALSE);	
#endif
	return 0;
}

