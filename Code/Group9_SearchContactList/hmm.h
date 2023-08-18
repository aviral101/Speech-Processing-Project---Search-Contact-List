#include "stdio.h"
//#include "stdafx.h"
#include "math.h"
#include "limits"
#include<string>
#include<iostream>
#include<fstream>
#include "conio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "windows.h"
#include "codebook_generation.h"
#include "training.h"
#include "testing.h"
#pragma warning (disable : 4996)
#pragma comment(lib,"Winmm.lib")


int hmm_main()
{
	int n;
	while(1)
	{
		system("cls");
		printf("\n\nPress  1) Create Universe  2) Generate Codebook  3)Train Models  4)Offline Testing  5)Live Testing  6) Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
					system("cls");
					create_universe();
					getch();
					break;
			case 2:
					system("cls");
					generate_codebook();
					getch();
					break;
			case 3:
					system("cls");
					training();
					getch();
					break;
			case 4:
					system("cls");
					printf("\n\nStarting offline testing..\n");
					Sleep(1000);
					testing();
					printf("\nOffline testing completed. Press any key to continue\n");
					getch();
					break;
			case 5:
					system("cls");
					printf("\n\nStarting live testing...\n");
					live_testing();
					printf("\nLive testing completed. Press any key to continue\n");
					getch();
					break;
			case 6:
					return 0;
			default:
					printf("Enter correct choice!!\n");
					Sleep(1000);
		}
	}
	getch();
	return 0;
}