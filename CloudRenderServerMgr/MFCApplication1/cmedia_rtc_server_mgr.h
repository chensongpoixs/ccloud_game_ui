/***********************************************************************************************
				created: 		2019-05-01

				author:			chensong

				purpose:		ccfg
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


************************************************************************************************/

#ifndef _C_MEDIA_RTC_SERVER_MGR_H_
#define _C_MEDIA_RTC_SERVER_MGR_H_
#include "cprocess_define.h"
#include "resource.h"
 
 namespace chen {



	 
	class cmedia_rtc_server_mgr
	{
	public:
		cmedia_rtc_server_mgr()
			: m_process_type(EProcessNone)
			, m_app_info()
			, m_timestamp(0)
		{}
		virtual ~cmedia_rtc_server_mgr();
	public:
		bool update();
		bool startup(const std ::string& wan_ip, const std::string& media_wan_port, const std::string& media_min_port, const std::string&  media_max_port, const std::string& media_timeouts);
		void destroy();
	public:
		void close_app();
		EProcessStateType get_media_server_status();
	protected:
	private:
		EProcessStateType		m_process_type;
		PROCESS_INFORMATION		m_app_info;
		uint64_t					m_timestamp;
	};
	//extern cmedia_rtc_server_mgr g_media_rtc_server_mgr;
 }


#endif // _C_MEDIA_RTC_SERVER_MGR_H_