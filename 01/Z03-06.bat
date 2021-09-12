@echo off
chcp 1251

echo -- строка параметров: %1 %2
echo -- режим: %1
echo -- имя файла: %2

if "%1" EQU "" goto error_empty_parm
if /I "%1" EQU "создать" goto try_create
if /I "%1" EQU "удалить" goto try_delete
if "%1" NEQ "удалить" goto error_operation
if "%1" NEQ "создать" goto error_operation

:try_create
	if "%2" NEQ "" goto create
	echo ---+ не задано имя файла
	goto exit

:create
	if exist %2 (goto fileExists)
	copy NUL %2 >nul
	echo ---+ файл %2 создан
	goto exit

:fileExists
	echo ---+ файл %2 уже есть
	goto exit

:try_delete
	if "%2" NEQ "" goto delete
	echo ---+ не задано имя файла
	goto exit

:delete
	if not exist %2 (goto fileNotFound)
	del %2
	echo ---+ файл %2 удален
	goto exit

:fileNotFound
	echo ---+ файл %2 не найден
	goto exit

:error_empty_parm
	echo --+ %0 режим файл
	echo --++ режим = {создать, удалить}
	echo --++ файл = имя файла
	goto exit

:error_operation
	echo --+ режим задан некорректно
	goto exit

:exit