/********************************************************************
created:	2019-03-24

author:		chensong

purpose:	�ַ�����������
��Ӯ����Ҫ���𰸶�������ʲô�������Ҫ��

�����ߣ��ٴ�֮����Ҳ��Ψ�з������ܣ�����������ʱ����ʱ����Ӣ�ۣ�Ӣ�۴�����ʱ�����������˵�����񣬿��㱾�����ٰ��� �����ã��Լ�������ͼ��顣


�ҿ��ܻ������ܶ���ˣ������ǽ���2��Ĺ��£�����д�ɹ��»��ɸ裬����ѧ���ĸ���������������
Ȼ�󻹿�����һ����������һ�������ҵĹ�������ܻᱻ��˧����������ֻᱻ��������ں���������ĳ�������ҹ������ȫ����͸Ȼ��Ҫ������С��ס�������ϵ�ʪ�·���
3Сʱ���������������ʵ��������ҵĹ�������Ը���򸸻���顣�Ҳ����Ѹ��������Ǵ�Խ�����������ǣ���ʼ��Ҫ�ص��Լ������硣
Ȼ���ҵ���Ӱ������ʧ���ҿ������������ˮ������ȴû���κ�ʹ�࣬�Ҳ�֪����ԭ���ҵ��ı������ˣ�������ȫ�����ԭ�򣬾���Ҫ�һ��Լ��ı��ġ�
�����ҿ�ʼ����Ѱ�Ҹ��ָ���ʧȥ�ĵ��ˣ��ұ��һ��שͷ��һ������һ��ˮ��һ����ƣ�ȥ�����Ϊʲô��ʧȥ�Լ��ı��ġ�
�ҷ��֣��ճ����ı��������Ļ��ڣ������ģ����ǵı��ľͻ���ʧ���յ��˸��ֺڰ�֮�����ʴ��
��һ�����ۣ������ʺͱ��ߣ�����ί����ʹ�࣬�ҿ���һֻֻ���ε��֣������ǵı��ĳ��飬�ɱΣ�͵�ߣ���Ҳ�ز������˶���ߡ�
�ҽ����������֡��������Ǻ�����ͬ�ڵļ��� �����Ҳ������£�����ϸ�����Լ�ƽ����һ�� Ѱ�ұ������ֵĺۼ���
�����Լ��Ļ��䣬һ�����ĳ�����������������֣��ҵı��ģ�����д�����ʱ�򣬻������
��������Ȼ����������ҵ�һ�У�д��������ұ��Ļع����÷�ʽ���һ�û�ҵ��������֣��������ţ�˳�������������һ����˳�����ϣ�������������

*********************************************************************/
#ifndef _C_DIGIT2STR_H_
#define _C_DIGIT2STR_H_
#include <algorithm>
#include <cstdio>
#include "cnet_type.h"
#ifdef _MSC_VER
#pragma warning (disable:4996)
#endif
#ifdef _MSC_VER
#pragma warning (disable:4996)
#include <malloc.h>
#include <wchar.h>
#include <windows.h>
#define alloca _alloca

#define STACK_ARRAY(TYPE, LEN) \
  static_cast<TYPE*>(::alloca((LEN) * sizeof(TYPE)))
#endif
#include "cnet_type.h"
namespace chen
{
	//convert int to decimal string, add '\0' at end
	template<typename T>
	int32 digit2str_dec(char* buf, int32 buf_size, T value);


	// TODO(jonasolsson): replace with absl::Hex when that becomes available.
	std::string ToHex(const int i);
#ifdef _MSC_VER

	inline std::wstring ToUtf16(const char* utf8, size_t len) {
		int len16 = ::MultiByteToWideChar(CP_UTF8, 0, utf8, static_cast<int>(len), nullptr, 0);
		wchar_t* ws = STACK_ARRAY(wchar_t, len16);
		::MultiByteToWideChar(CP_UTF8, 0, utf8, static_cast<int>(len), ws, len16);
		return std::wstring(ws, len16);
	}

	inline std::wstring ToUtf16(const std::string& str) {
		return ToUtf16(str.data(), str.length());
	}

	inline std::string ToUtf8(const wchar_t* wide, size_t len) {
		int len8 = ::WideCharToMultiByte(CP_UTF8, 0, wide, static_cast<int>(len),
			nullptr, 0, nullptr, nullptr);
		char* ns = STACK_ARRAY(char, len8);
		::WideCharToMultiByte(CP_UTF8, 0, wide, static_cast<int>(len), ns, len8,
			nullptr, nullptr);
		return std::string(ns, len8);
	}

	inline std::string ToUtf8(const wchar_t* wide) {
		return ToUtf8(wide, wcslen(wide));
	}

	inline std::string ToUtf8(const std::wstring& wstr) {
		return ToUtf8(wstr.data(), wstr.length());
	}

#endif


}// namespace chen

#endif //_C_DIGIT2STR_H_