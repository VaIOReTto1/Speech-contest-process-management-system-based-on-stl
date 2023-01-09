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

	int rounds; //比赛轮次
	vector<int>v1; //第一轮参与选手（12位
	vector<int>v2;//晋级第二轮的选手（6位
	vector<int>third;//获得前三名的选手
	map<int, Speaker>speaker;//存放编号以及对应具体选手

	void Create_speaker();

	void Start_speech();

	void Drawing();

	void Show_score();

	void Record();

	void Completion();

	void Load_record();//读取往届记录

	bool File_is_empty;//判断文件是否为空

	map<int, vector<string>>record;//往届记录

	void Show_record();

	void Clear_record();

	~SpeechManager();
};