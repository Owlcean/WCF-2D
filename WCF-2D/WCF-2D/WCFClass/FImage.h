#pragma once
#include "FColor.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include<random>
#include<stdlib.h>
#include<time.h>

#include <windows.h>
#include <io.h>
#include <wrl.h>
#include <array>
#include <direct.h>
#include "shlobj.h" 
#include "FVector2D.h"
using namespace std;

namespace FileHelper
{
	/*	Example:
		vector<string> paths;
		const string FilePath = "C:\\Users\\yivanli\\Desktop\\DX12Lab\\DX12Lab\\Textures";
		FileHelper::GetFiles(FilePath, paths);
	*/
	static void GetFiles(string path, vector<string>& files)
	{
		//�ļ����  
		long long hFile = 0;
		//�ļ���Ϣ  
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).c_str(), &fileinfo)) != -1)
		{
			do
			{
				//�����Ŀ¼,����֮  
				//�������,�����б�  
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						GetFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}

	/*	Example:
		string path;
		FileHelper::GetProjectPath(path);
		������E�̵Ĺ��̣���ô���ֵ��Ϊ��
		"E:\\DX12\\DX12Lab\\DX12Lab"
	*/
	static void GetProjectPath(string& OutPath)
	{
		char* buffer;
		//Ҳ���Խ�buffer��Ϊ�������
		if ((buffer = _getcwd(NULL, 0)) != NULL)
		{
			OutPath = buffer;
		}
	}

	/*	CSIDL_BITBUCKET ����վ
		CSIDL_CONTROLS �������
		CSIDL_DESKTOP Windows����desktop;
		CSIDL_DESKTOPDIRECTORY desktop��Ŀ¼��
		CSIDL_DRIVES �ҵĵ���
		CSIDL_FONTS ����Ŀ¼
		CSIDL_NETHOOD �����ھ�
		CSIDL_NETWORK �����ھ�virtual folder
		CSIDL_PERSONAL �ҵ��ĵ�
		CSIDL_PRINTERS ��ӡ��
		CSIDL_PROGRAMS ������
		CSIDL_RECENT ������ĵ�
		CSIDL_SENDTO ���͵��˵���
		CSIDL_STARTMENU �����˵�
		CSIDL_STARTUP ����Ŀ¼
		CSIDL_TEMPLATES ��ʱ�ĵ�
	*/

	static string GetDesktopPath()
	{
		LPITEMIDLIST pidl;
		LPMALLOC pShellMalloc;
		char szDir[1024];
		if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
		{
			if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
				// ����ɹ�����true  
				SHGetPathFromIDListA(pidl, szDir);
				pShellMalloc->Free(pidl);
			}
			pShellMalloc->Release();
		}

		string Ret = string(szDir);
		//Ret.replace(Ret.find_first_of(""), filePath.length(), "")

		return Ret;
	}
}

class FImage
{
public:
	FImage(int X, int Y, string ImageName) :SizeX(X), SizeY(Y), ImageName(ImageName)
	{
		for (int i = 0; i < SizeX; i++)
		{
			vector<FColor>row(SizeY);
			Imagedata.push_back(row);
		}
	}

	bool SaveImageToDesk()
	{
		const string& Path = FileHelper::GetDesktopPath();

		cout << endl << "begin save image to desk operation" << endl;

		bool bCreateImage = false;

		ofstream fout(Path + "/" + ImageName + ".ppm");
		fout << "P3\n" << SizeX << " " << SizeY << "\n255\n";

		for (int y = 0; y < SizeY; y++)
		{
			for (int x = 0; x < SizeX; x++)
			{
				FColor& color = Imagedata[x][y];
				fout << color.R << " " << color.G << " " << color.B << "\n";
			}
		}
		fout.close();

		cout << endl << "Save image successfully" << endl;

		return bCreateImage;
	}

	void ClearImage(FColor& ClearColor)
	{
		cout << endl << "Begin clear image operation" << endl;

		int x = SizeX;
		int y = SizeY;
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; y++)
			{
				Imagedata[i][j] = ClearColor;
			}
		}
	}

	void SetPixleColor(const FColor& newData, const FVector2D<int>& PixleLocation)
	{
		if (PixleLocation.X < SizeX&&PixleLocation.Y < SizeY)
		{
			Imagedata[PixleLocation.X][PixleLocation.Y] = newData;
		}
	}

	void SetPixleColor(const int& newData, const FVector2D<int>& PixleLocation)
	{
		if (PixleLocation.X < SizeX&&PixleLocation.Y < SizeY)
		{
			Imagedata[PixleLocation.X][PixleLocation.Y] = FColor(newData);
		}
	}

	int SizeX;
	int SizeY;
	string ImageName;
	string ImagePath;
	vector<vector<FColor>>Imagedata;
};