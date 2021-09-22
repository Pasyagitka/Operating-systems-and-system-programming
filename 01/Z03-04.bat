@echo off
chcp 1251 >nul
echo -- строка параметров: %1 %2 %3
echo -- параметр 1: %1
echo -- параметр 2: %2
echo -- параметр 3: %3
set /a res = %1 + %2
echo -- %1 + %2 = %res%
set /a res = %1 * %2 
echo -- %1 * %2 = %res% 
set /a res = %3 / %2 
echo -- %3 / %2 = %res% 
set /a res = %2 - %1 
echo -- %2 - %1 = %res% 
set /a res = (%2 - %1) * (%1 - %2)
echo -- (%2 - %1)*(%1 - %2) = %res%