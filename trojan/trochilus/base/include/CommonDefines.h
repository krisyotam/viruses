/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

//����Ϊ���ɸ��Ƶ���
#define DECLARE_UNCOPYABLE(className)			\
	private:									\
		className(const className&);			\
		className& operator=(const className&);	

//����Ϊ������
#define DECLARE_SINGLETON(className)			\
	public:										\
		static className& GetInstanceRef()		\
		{										\
			static className s_instance;		\
			return s_instance;					\
		}										\
		~className();							\
												\
		BOOL Init();							\
		void Deinit();							\
	private:									\
		className();

#define XOR(a, b) (((a) && !(b)) || (!(a) && (b)))
