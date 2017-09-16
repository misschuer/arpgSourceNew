@set root_path=%~dp0

@set tool_exe=%root_path%\CodeBuilder\GZCodeBuilder.exe
@set protocol_dir=%root_path%
@set server_path=%root_path%\..\..\
@set server_net=%server_path%\src\svrcore\protocol
@set robot_net=%server_path%\src\robotd\handler
@set lua_h_dir=%server_path%\contrib\scripts\share
@set as_h_dir=%server_path%\contrib\as
@set ts_h_dir=%server_path%\contrib\ts


@echo ���ɷ����c����
%tool_exe% -f %protocol_dir%\Cow.Msg -t %server_net% -o %server_net%
@echo ����lua����
%tool_exe% -f %protocol_dir%\Cow.Msg -t %lua_h_dir% -o %lua_h_dir%
@echo ���ɻ�����Э��
%tool_exe% -f %protocol_dir%\Cow.Msg -t %robot_net% -o %robot_net%
@echo ����tsЭ��
%tool_exe% -f %protocol_dir%\Cow.Msg -t %ts_h_dir% -o %ts_h_dir%
::@echo ����asЭ��
::%tool_exe% -f %protocol_dir%\Cow.Msg -t %as_h_dir% -o %as_h_dir%

pause