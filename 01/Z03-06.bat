@echo off
chcp 1251

echo -- ������ ����������: %1 %2
echo -- �����: %1
echo -- ��� �����: %2

if "%1" EQU "" goto error_empty_parm
if /I "%1" EQU "�������" goto try_create
if /I "%1" EQU "�������" goto try_delete
if "%1" NEQ "�������" goto error_operation
if "%1" NEQ "�������" goto error_operation

:try_create
	if "%2" NEQ "" goto create
	echo ---+ �� ������ ��� �����
	goto exit

:create
	if exist %2 (goto fileExists)
	copy NUL %2 >nul
	echo ---+ ���� %2 ������
	goto exit

:fileExists
	echo ---+ ���� %2 ��� ����
	goto exit

:try_delete
	if "%2" NEQ "" goto delete
	echo ---+ �� ������ ��� �����
	goto exit

:delete
	if not exist %2 (goto fileNotFound)
	del %2
	echo ---+ ���� %2 ������
	goto exit

:fileNotFound
	echo ---+ ���� %2 �� ������
	goto exit

:error_empty_parm
	echo --+ %0 ����� ����
	echo --++ ����� = {�������, �������}
	echo --++ ���� = ��� �����
	goto exit

:error_operation
	echo --+ ����� ����� �����������
	goto exit

:exit