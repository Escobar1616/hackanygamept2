#include <windows.h>
#include <iostream>
#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{

	DWORD oldprotect; //��Ń������A�N�Z�X�������ɖ߂����Ɏg��
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);//�������A�N�Z�X����ύX�B�ύX�O�̋�����oldprotect�ϐ��ɕۑ������
	WriteProcessMemory(hProcess, dst, src, size, nullptr);//�O���v���Z�X�̃������Ƀf�[�^����������
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);//�ύX�O�̃A�N�Z�X����oldprotect���畜���B���̑���ɂ��A�������A�N�Z�X�������̏�Ԃɖ߂�

}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
{

	BYTE* nopArray = new BYTE[size];//nopArray�Ƃ������O��BYTE�^�̔z����쐬���A���̃T�C�Y��size�ɐݒ�
	memset(nopArray, 0x90, size);//nopArray�̊e�v�f��0x90�iNOP���߂̃o�C�i���\���j�ŏ��������A�������A�h���X��NOP���߂�z�u

	PatchEx(dst, nopArray, size, hProcess);//PatchEx�֐����Ăяo���Adst�������A�h���X��nopArray�iNOP���߂̔z��j���w�肳�ꂽsize��hProcess�ŏ�������
	delete[] nopArray;//���I�Ɋ��蓖�Ă�ꂽnopArray������������B���������[�N�΍�

}