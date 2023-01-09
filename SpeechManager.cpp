#include "SpeechManager.h"

SpeechManager::SpeechManager(){
	this->Init_speaker();
	this->Create_speaker();
	this->Load_record();
}

SpeechManager::~SpeechManager(){
}

void SpeechManager::Show_menu(){
	cout << "                                      " << endl;
	cout << "            欢迎参加演讲比赛!         " << endl;
	cout << "            1.开始演讲比赛            " << endl;
	cout << "            2.查看往届记录            " << endl;
	cout << "            3.清空比赛记录            " << endl;
	cout << "            0.退出比赛程序            " << endl;
	cout << "                                      " << endl;
}

void SpeechManager::Exit_system(){
	cout << "            欢迎下次使用            " << endl;
	system("pause");
	exit(0);
}

void SpeechManager::Init_speaker(){
	//初始化选手数据
	this->v1.clear();
	this->v2.clear();
	this->third.clear();
	this->speaker.clear();
	this->record.clear();

	this->rounds = 1;//初始化比赛轮次
}

void SpeechManager::Create_speaker(){
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "选手";
		name += nameSeed[i];

		Speaker s;
		s.Name = name;
		for (int j = 0; j < 2; j++) s.Score[j] = 0;

		this->v1.push_back(10001 + i);
		this->speaker.insert(make_pair(10001 + i, s));
	}
}

void SpeechManager::Start_speech(){
	//第一轮比赛
	//抽签
	this->Drawing();
	//比赛
	this->Completion();
	//显示晋级成果
	this->Show_score();
	//第二轮比赛
	this->rounds++;
	//抽签
	this->Drawing();
	//比赛
	this->Completion();
	//显示最终结果
	this->Show_score();
	//保存分数
	this->Record();

	//重置比赛
	this->Init_speaker();
	this->Create_speaker();
	this->Load_record();

	cout << "本届比赛顺利结束" << endl;
	system("pasue");
	system("cls");
}

void SpeechManager::Drawing(){
	if (this->rounds == 1) cout << "            第一轮比赛选手正在抽签" << endl;
	else cout << "            第二轮比赛选手正在抽签" << endl;
	cout << "-------------------------------------" << endl;
	cout << "            演讲顺序如下" << endl;
	if (this->rounds == 1){
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) cout << *it << " ";
		cout << endl;
	}
	else{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) cout << *it << " ";
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::Completion(){
	if (this->rounds == 1) cout << "            第一轮比赛正式开始" << endl;
	else cout << "            第二轮比赛正式开始" << endl;

	multimap<double, int, greater<double>>group;//记录每组选手数据
	int num = 0;//6人为一组

	vector<int>v;
	if (this->rounds == 1) v = v1;
	else v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		num++;

		deque<double>d;//存放分数
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f; //600~1000
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//去除最高分
		d.pop_back();//去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//计算总分
		double avg = sum / (double)d.size();//计算平均分
		this->speaker[*it].Score[this->rounds - 1] = avg;

		group.insert(make_pair(avg, *it));
		//6人一组
		if (num % 6 == 0){
			if (num / 6 == 1) cout << "第一小组比赛名次如下：" << endl;
			else cout << "第二小组比赛名次如下：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end(); it++)
				cout << "编号：" << it->second << " 姓名：" << this->speaker[it->second].Name
				<< " 成绩：" << this->speaker[it->second].Score[this->rounds - 1] << endl;

			//取各组前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end() && count < 3; it++, count++){
				if (this->rounds == 1) v2.push_back((*it).second);
				else third.push_back((*it).second);
			}

			group.clear();
			cout << endl;
		}
	}
	if (this->rounds == 1) cout << "            第一轮比赛完毕" << endl;
	else cout << "            第二轮比赛完毕" << endl;

	system("pause");
}

void SpeechManager::Show_score(){
	if (this->rounds == 1) cout << "            第一轮比赛晋级选手信息如下：" << endl;
	else cout << "            第二轮比赛晋级选手信息如下：" << endl;

	vector<int>v;
	if (this->rounds == 1) v = v2;
	else v = third;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		cout << "编号：" << *it<< " 姓名：" <<this-> speaker[*it].Name
		<< " 成绩：" << this->speaker[*it].Score[this->rounds - 1] << endl;
    cout << endl;

	system("pause");
	system("cls");
	this->Show_menu();
}

void SpeechManager::Record(){
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = third.begin(); it != third.end(); it++)
		ofs << *it << "," << speaker[*it].Score[1] << ",";
	ofs <<endl;

	ofs.close();
	cout << "记录已保存" << endl;
	this->File_is_empty = false;
}

void SpeechManager::Load_record(){
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()){
		this->File_is_empty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()){
		cout << "文件为空！" << endl;
		this->File_is_empty = true;
		ifs.close();
		return;
	}

	this->File_is_empty = false;

	ifs.putback(ch);//把读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data){
		vector<string>v;

		int pos = -1;
		int start = 0;
		
		while (true){
			pos = data.find(",", start);
			if (pos == -1) break;
			string tmp = data.substr(start, pos - start);//第一个是起始位置，第二个是到逗号的截取长度
			v.push_back(tmp);
			start = pos + 1;
		}
		this->record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::Show_record(){
	if (this->File_is_empty) cout << "文件不存在，或记录为空！" << endl;
	else{
		for (map<int, vector<string>>::iterator it = this->record.begin(); it != this->record.end(); it++){
			cout << "第" << it->first+1 << "届" <<
				"冠军编号：" << it->second[0] << " 得分：" << it->second[1] << " "
				"亚军编号：" << it->second[2] << " 得分：" << it->second[3] << " "
				"季军编号：" << it->second[4] << " 得分：" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::Clear_record()
{
	cout << "确认清空？" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl;

	int select;
	cin >> select;

	if (select == 1){
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->Init_speaker();
		this->Create_speaker();
		this->Load_record();

		cout << "清除成功" << endl;
	}
	else if (select == 2) return;
	else cout << "输入有误！" << endl;

	system("pause");
	system("cls");
}