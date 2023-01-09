#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"Speaker.h"
#include<algorithm>
#include<numeric>
#include<functional>
#include<deque>
#include<fstream>

using namespace std;

class SpeechManager{
public:
	SpeechManager();

	void Show_menu();

	void Exit_system();

	void Init_speaker();

	int rounds; //�����ִ�
	vector<int>v1; //��һ�ֲ���ѡ�֣�12λ
	vector<int>v2;//�����ڶ��ֵ�ѡ�֣�6λ
	vector<int>third;//���ǰ������ѡ��
	map<int, Speaker>speaker;//��ű���Լ���Ӧ����ѡ��

	void Create_speaker();

	void Start_speech();

	void Drawing();

	void Show_score();

	void Record();

	void Completion();

	void Load_record();//��ȡ�����¼

	bool File_is_empty;//�ж��ļ��Ƿ�Ϊ��

	map<int, vector<string>>record;//�����¼

	void Show_record();

	void Clear_record();

	~SpeechManager();
};