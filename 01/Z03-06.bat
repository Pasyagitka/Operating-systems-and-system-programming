@echo off
chcp 1251 >nul

echo -- ������ ����������: %1 %2
echo -- �����: %1
echo -- ��� �����: %2

if "%1" == "" goto error_parms_not_defined

if "%1" == "�������" goto try_create
if "%1" == "�������" goto try_delete

goto error_modes


:try_create
	if "%2" NEQ "" goto create
	echo ---+ �� ������ ��� �����
	goto exit

:create
	if exist %2 goto error_file_already_exists
	copy NUL %2 >nul
	echo ---+ ���� %2 ������
	goto exit

:try_delete
	if "%2" NEQ "" goto delete
	echo ---+ �� ������ ��� �����
	goto exit

:delete
	if not exist %2 goto error_file_not_found
	del %2
	echo ---+ ���� %2 ������
	goto exit

:error_parms_not_defined
	echo --+ %0 ����� ����
	echo --++ ����� = {�������, �������}
	echo --++ ���� = ��� �����
	goto exit

:error_mode
	echo --+ ����� ����� �����������
	goto exit

:error_file_already_exists
	echo ---+ ���� %2 ��� ����
	goto exit

:error_file_not_found
	echo ---+ ���� %2 �� ������
	goto exit

:exit