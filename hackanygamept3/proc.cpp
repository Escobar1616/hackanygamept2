#include "proc.h"

//�v���Z�X������v���Z�XID���擾���邽�߂̊֐�
DWORD GetProcId(const wchar_t* procName) //procName�Ƃ������O��wchar_t�^�|�C���^���󂯎��
{
	DWORD procId = 0; //�G���[�m�F�p��0�ɏ��������Ƃ�
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//�v���Z�X�̃X�i�b�v�V���b�g�����

	if (hSnap != INVALID_HANDLE_VALUE)//hSnap��INVALID_HANDLE_VALUE����Ȃ����m�F
	{
		PROCESSENTRY32 procEntry; //�X�g���N�`����procEntry�Ƃ������O�Ŏ��̉�
		procEntry.dwSize = sizeof(procEntry);//procEntry����dwSize�Ƃ��������o�ϐ���procEntry�Ƃ����X�g���N�`���̃T�C�Y����

		if (Process32First(hSnap, &procEntry))//�v���Z�X�̃X�i�b�v�V���b�g�̍ŏ��̃v���Z�X�G���g�����擾
		{

			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))//procEntry����szExeFile�����o��procName���r�B_wcsicmp�֐��͑啶������������ʂ����ɕ�������r���邽�߂̂��́B
				{
					procId = procEntry.th32ProcessID;
					break;//��v������̂�����������A���̃v���Z�X��ID��procId�ɑ���A���[�v���I����
				}
			} while (Process32Next(hSnap, &procEntry));//�X�i�b�v�V���b�g���̃v���Z�X�G���g�����A�w�肵���v���Z�X���Ɉ�v������̂�������܂ŏ��Ԃɑ�������

		}
	}
	CloseHandle(hSnap);
	return procId;//�v���Z�Xid��Ԃ�
}

//�v���Z�XID�ƃ��W���[�������烂�W���[����BaseAddress���擾���邽�߂̊֐�
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);//�����Ƃ��Ďw�肳�ꂽprocId�̃��W���[���̃X�i�b�v�V���b�g���쐬

	if (hSnap != INVALID_HANDLE_VALUE)//hSnap��INVALID_HANDLE_VALUE����Ȃ����m�F
	{
		MODULEENTRY32 modEntry;//�X�g���N�`����modEntry�Ƃ������O�Ŏ��̉�
		modEntry.dwSize = sizeof(modEntry);//modEntry����dwSize�Ƃ��������o�ϐ���modEntry�Ƃ����X�g���N�`���̃T�C�Y����

		if(Module32First(hSnap,&modEntry))//���W���[���̃X�i�b�v�V���b�g�́A�ŏ��̃��W���[���G���g�����擾
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))//modEntry����szModule�����o��modName���r�B
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;//��v������̂�����������A���̃��W���[���̃x�[�X�A�h���X��modBaseAddr�ɑ���A���[�v���I����
				}
			} while (Module32Next(hSnap, &modEntry));
		}

	}
	CloseHandle(hSnap);
	return modBaseAddr;


}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;

	for (unsigned int i = 0; i < offsets.size(); ++i) //i��0����offsets�̃T�C�Y�����ł���ԁA�������J��Ԃ�
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);//RPM�֐����g���āA�w�肳�ꂽ�v���Z�X�̃���������"�ϐ�addr"�Ɋi�[����Ă���l��ǂݎ���āA���̌��ʂ�addr�ɑ������B���ʁAaddr�������������A�h���X�̒l���擾����
		addr += offsets[i];//addr��offsets[i]�����Z����B�@�܂�A���̃A�h���X���v�Z����
	}
	return addr;//�I�t�Z�b�g�����Z�����A�h���X��addr�Ƃ��ĕԂ�
}


//�Ƃ肠����windows API�̊֐��ƁA�ϐ��̌`���o���Ă�΂���