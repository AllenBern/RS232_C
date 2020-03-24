// rs232_C.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <iostream>
using namespace std;

int main() {
	HANDLE hCom1 = CreateFile(TEXT("COM1"),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hCom1 == INVALID_HANDLE_VALUE)
		printf("打开COM1失败！\n");
	else
		printf("COM1已打开\n");

	HANDLE hCom2 = CreateFile(TEXT("COM2"),
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hCom2 == INVALID_HANDLE_VALUE)
		printf("打开COM1失败！\n");
	else
		printf("COM2已打开\n");

	DCB dcb1;
	GetCommState(hCom1, &dcb1);
	//可以自行设置串口属性
	dcb1.BaudRate = 9600;
	dcb1.ByteSize = 8;
	dcb1.Parity = 0;
	dcb1.StopBits = 1;
	SetCommState(hCom1, &dcb1);
	//输出串口信息 
	printf("-----------------------------------\n");
	printf("COM1串口信息：\n");
	printf("BaudRate:%d\nDataBits:%d\nParity:%d\nStopBits:%d\n",
		dcb1.BaudRate, dcb1.ByteSize, dcb1.Parity, dcb1.StopBits);

	DCB dcb2;
	GetCommState(hCom2, &dcb2);
	dcb2.BaudRate = 9600;
	dcb2.ByteSize = 8;
	dcb2.Parity = 0;
	dcb2.StopBits = 1;
	SetCommState(hCom2, &dcb2);
	printf("-----------------------------------\n");
	printf("COM2串口信息：\n");
	printf("BaudRate:%d\nDataBits:%d\nParity:%d\nStopBits:%d\n",
		dcb2.BaudRate, dcb2.ByteSize, dcb2.Parity, dcb2.StopBits);
	printf("-----------------------------------\n");

	char sendBuf[128] = "";
	char recvBuf[128] = "";
	DWORD wSendLen = 0;
	DWORD wRecvLen = 0;

	while (1) {
		printf("请向COM2发送信息：\n");
		cin >> sendBuf;
		WriteFile(hCom1, sendBuf, sizeof(sendBuf), &wSendLen, NULL);

		ReadFile(hCom2, recvBuf, sizeof(recvBuf), &wRecvLen, NULL);
		printf("COM2接收的信息为：%s\n\n", recvBuf);
		PurgeComm(hCom1, PURGE_TXCLEAR | PURGE_RXCLEAR);
		PurgeComm(hCom2, PURGE_TXCLEAR | PURGE_RXCLEAR);
	}
}


