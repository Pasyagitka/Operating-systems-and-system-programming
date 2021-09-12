@echo off
chcp 1251
echo -- строка параметров: %1 %2 %3
echo -- параметр 1: %1
echo -- параметр 2: %2
echo -- параметр 3: %3
set /a sum = %1 + %2
set /a mul = %1 * %2 
set /a del = %3 / %2 
set /a min = %2 - %1 
set /a res = (%2 - %1) * (%1 - %2)
echo -- %1 + %2 = %sum%
echo -- %1 * %2 = %mul% 
echo -- %3 / %2 = %del% 
echo -- %2 - %1 = %min% 
echo -- (%2 - %1)*(%1 - %2) = %res%