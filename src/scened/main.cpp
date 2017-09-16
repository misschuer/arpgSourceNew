#include "scened_app.h"

#ifdef GOOGLE_PERFTOOLS
#  include "setup_profiler.h"
#endif

#define WELCOME_MSG "Welcome to SCENED,^C to stop!\n--------------------------------------------------------------\n\n"

int main(int argc, char **argv)
{
#if PLATFORM == PLATFORM_WINDOWS
    wsa_initializer(TRUE);
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF  );	
	//_CrtSetBreakAlloc(969991);
#endif

	//��ӡ��ӭ��Ϣ
	printf("%s\n",WELCOME_MSG);

    int ret = 0;

    //�������ò���
    SvrCoreParams params;

    if(!params.Load(argc, (const char **)argv, NULL))
        return EXIT_FAILURE;

    //���������ļ�
    ScenedConfig config;

    if(!config.Load(params.config_file, params.centd_port))
        return EXIT_FAILURE;

    //��Ӧ�ó���
    ScenedApp::g_app = new ScenedApp(params, config);
    ScenedApp::HookSignals();

    //�ȴ������̲߳�ֱ���˳�
    if(ScenedApp::g_app->Open())
    {
        ret = EXIT_SUCCESS;

		//�ȴ������̲߳�ֱ���˳�
		tea_pinfo("scened running!\n----------------------------\n");
        ScenedApp::g_app->Wait();
    }
    else ret = EXIT_SUCCESS;

    //�رղ��ͷ�Ӧ�ó�����Դ
    ScenedApp::g_app->Close();
    ScenedApp::UnHookSinals();	
    delete ScenedApp::g_app;
	ScenedApp::g_app = NULL;
	
#if PLATFORM == PLATFORM_WINDOWS
    wsa_initializer(FALSE);
#endif
    return ret;
}

