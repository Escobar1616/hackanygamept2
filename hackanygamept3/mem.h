#pragma once

namespace mem
{
	//�w�肳�ꂽ�A�h���X������������
	//����: ���������郁�����A�h���X�ւ̃|�C���^, �������ރf�[�^���܂ރA�h���X�ւ̃|�C���^, �������ރf�[�^�̃T�C�Y, �v���Z�X�ւ̃n���h��
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);

	//�w�肳�ꂽ�A�h���X��nop���߂�}��
	//����: nop���߂�}������A�h���X�ւ̃|�C���^, �}������nop���߂̐�, �v���Z�X�ւ̃n���h��
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

}