@echo off
chcp 1251 >nul

echo -- строка параметров: %1 %2
echo -- режим: %1
echo -- имя файла: %2

if "%1" == "" goto error_parms_not_defined

if "%1" == "создать" goto try_create
if "%1" == "удалить" goto try_delete

goto error_modes


:try_create
	if "%2" NEQ "" goto create
	echo ---+ не задано имя файла
	goto exit

:create
	if exist %2 goto error_file_already_exists
	copy NUL %2 >nul
	echo ---+ файл %2 создан
	goto exit

:try_delete
	if "%2" NEQ "" goto delete
	echo ---+ не задано имя файла
	goto exit

:delete
	if not exist %2 goto error_file_not_found
	del %2
	echo ---+ файл %2 удален
	goto exit

:error_parms_not_defined
	echo --+ %0 режим файл
	echo --++ режим = {создать, удалить}
	echo --++ файл = имя файла
	goto exit

:error_mode
	echo --+ режим задан некорректно
	goto exit

:error_file_already_exists
	echo ---+ файл %2 уже есть
	goto exit

:error_file_not_found
	echo ---+ файл %2 не найден
	goto exit

:exit