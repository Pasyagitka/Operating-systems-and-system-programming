@echo off
chcp 1251 >nul
echo -- ������ ����������: %1 %2 %3
echo -- �������� 1: %1
echo -- �������� 2: %2
echo -- �������� 3: %3
set /a res = %1 %3 %2
echo ���������: %res%