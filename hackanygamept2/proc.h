#pragma once
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

//��������v���Z�X�̂����O -> �v���Z�XID(������Ȃ��Ȃ�0)
DWORD GetProcId(const wchar_t* procName);

//�v���Z�XID -> ���W���[���̃x�[�X�A�h���X(������Ȃ��Ȃ�0)
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

//�v���Z�X�̃n���h���A��ƂȂ�A�h���X�A�I�t�Z�b�g�̃x�N�^ -> �I�t�Z�b�g��K�p������̃A�h���X 
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>);
